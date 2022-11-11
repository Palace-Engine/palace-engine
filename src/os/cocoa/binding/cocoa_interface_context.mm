#include "../../../../include/os/cocoa/binding/cocoa_interface_context.h"

#include "../../../../include/os/cocoa/binding/cocoa_interface_internal_types.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include <stdlib.h>

@interface PalaceCocoaApplicationDelegate : NSObject <NSApplicationDelegate>
@end

@implementation PalaceCocoaApplicationDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    [NSApp stop:nil];
}
@end

palace::cocoa_interface::ContextHandle palace::cocoa_interface::createContext(void) {
    @autoreleasepool {
        Context *context = new Context;
        
        [NSApplication sharedApplication];
        [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
        
        context->delegate = [[PalaceCocoaApplicationDelegate alloc] init];
        if (context->delegate == nil) {
            return NULL;
        }
        
        [NSApp setDelegate:context->delegate];
        
        if (![[NSRunningApplication currentApplication] isFinishedLaunching]) {
            [NSApp run];
        }
        
        return static_cast<ContextHandle>(context);
    }
}

void palace::cocoa_interface::freeContext(ContextHandle contextHandle) {
    @autoreleasepool {
        Context *context = reinterpret_cast<Context *>(contextHandle);
        
        if (context->delegate) {
            CFRelease(context->delegate);
            context->delegate = nil;
        }
        
        delete context;
    }
}

void palace::cocoa_interface::pollEvents() {
    @autoreleasepool {
        for (;;) {
            NSEvent* event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                                untilDate:[NSDate distantPast]
                                                   inMode:NSDefaultRunLoopMode
                                                  dequeue:YES];
            if (event == nil)
                break;

            [NSApp sendEvent:event];
        }
    } // autoreleasepool
}
