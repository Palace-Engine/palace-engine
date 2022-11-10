#include "../../../../include/os/cocoa/binding/cocoa_interface_context.h"

#include "../../../../include/os/cocoa/binding/cocoa_interface_internal_types.h"

#include <Cocoa/Cocoa.h>
#include <stdlib.h>

@interface PalaceCocoaApplicationDelegate : NSObject <NSApplicationDelegate>
@end

@implementation PalaceCocoaApplicationDelegate
- (void)applicationDidFinishLaunching:(NSNotification *)notification {
    [NSApp stop:nil];
}
@end

PalaceCocoaContextHandle palaceCreateCocoaContext(void) {
    @autoreleasepool {
        PalaceCocoaContext *context =
            (PalaceCocoaContext *)malloc(sizeof(PalaceCocoaContext));
        
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
        
        return (PalaceCocoaContextHandle)context;
    }
}

void palaceFreeCocoaContext(PalaceCocoaContextHandle contextHandle) {
    @autoreleasepool {
        PalaceCocoaContext *context = (PalaceCocoaContext *)contextHandle;
        
        if (context->delegate) {
            CFRelease(context->delegate);
            context->delegate = nil;
        }
        
        free(contextHandle);
    }
}
