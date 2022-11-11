#include "../../../../include/os/cocoa/binding/cocoa_interface_window.h"

#include "../../../../include/os/cocoa/binding/cocoa_interface_internal_types.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include <stdlib.h>

@interface PalaceCocoaWindow : NSWindow {}
@end

@implementation PalaceCocoaWindow

- (BOOL)canBecomeKeyWindow
{
    return YES;
}

- (BOOL)canBecomeMainWindow
{
    return YES;
}

@end

@interface PalaceWindowDelegate : NSObject <NSWindowDelegate> {
    palace::cocoa_interface::Window *m_window;
}

- (instancetype)initialize:(palace::cocoa_interface::Window *)window;

@end

@implementation PalaceWindowDelegate
- (instancetype)initialize:(palace::cocoa_interface::Window *)window {
    self = [super init];
    if (self != nil) {
        m_window = window;
    }
    
    return self;
}
@end

palace::cocoa_interface::WindowHandle palace::cocoa_interface::createWindow(const char *title, const math::ivec2 &position, const math::ivec2 &size, palace::Window::Style style) {
    @autoreleasepool {
        Window *newWindow = new Window;
        
        newWindow->delegate = [[PalaceWindowDelegate alloc] initialize:newWindow];
        if (newWindow->delegate == nil) {
            delete newWindow;
            return nullptr;
        }
        
        NSRect contentRect = NSMakeRect(position.x(), position.y(), size.w(), size.h());
        NSUInteger styleMask = NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskResizable;
        
        if (style == palace::Window::Style::Popup) {
            styleMask |= NSWindowStyleMaskBorderless;
        }
        
        newWindow->window = [[PalaceCocoaWindow alloc]
                             initWithContentRect:contentRect styleMask:styleMask backing:NSBackingStoreBuffered defer:YES];
        if (newWindow->window == nil) {
            delete newWindow;
            return nullptr;
        }
        
        const NSWindowCollectionBehavior behavior =
            NSWindowCollectionBehaviorFullScreenPrimary | NSWindowCollectionBehaviorManaged;
        [newWindow->window setCollectionBehavior:behavior];
        [newWindow->window setDelegate:newWindow->delegate];
        [newWindow->window makeKeyAndOrderFront:newWindow->window];
        [newWindow->window setAcceptsMouseMovedEvents:YES];
        [newWindow->window makeKeyWindow];
        [newWindow->window setOpaque:YES];
        [newWindow->window setFrameOrigin:contentRect.origin];
        [newWindow->window setTitle:@(title)];
        
        return static_cast<WindowHandle>(newWindow);
    }
}

void palace::cocoa_interface::freeWindow(WindowHandle windowHandle) {
    @autoreleasepool {
        Window *window = reinterpret_cast<Window *>(windowHandle);
        
        [window->delegate release];
        window->delegate = nil;
        
        [window->window close];
        window->window = nil;
        
        delete window;
    }
}
