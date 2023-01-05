//
//  UIResponder.h
//  UIKit
//
//  Copyright 2005-2009 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIEvent.h>

@class UIEvent;

UIKIT_EXTERN_CLASS @interface UIResponder : NSObject {    
}

- (UIResponder*)nextResponder;

- (BOOL)canBecomeFirstResponder;    // default is NO
- (BOOL)becomeFirstResponder;

- (BOOL)canResignFirstResponder;    // default is YES
- (BOOL)resignFirstResponder;

- (BOOL)isFirstResponder;

// Generally, all responders which do custom touch handling should override all four of these methods.
// Your responder will receive either touchesEnded:withEvent: or touchesCancelled:withEvent: for each
// touch it is handling (those touches it received in touchesBegan:withEvent:).
// *** You must handle cancelled touches to ensure correct behavior in your application.  Failure to
// do so is very likely to lead to incorrect behavior or crashes.
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;

- (void)motionBegan:(UIEventSubtype)motion withEvent:(UIEvent *)event __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)motionEnded:(UIEventSubtype)motion withEvent:(UIEvent *)event __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)motionCancelled:(UIEventSubtype)motion withEvent:(UIEvent *)event __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (BOOL)canPerformAction:(SEL)action withSender:(id)sender __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
@property(nonatomic,readonly) NSUndoManager *undoManager __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end

@interface NSObject(UIResponderStandardEditActions)   // these methods are not implemented in NSObject

- (void)cut:(id)sender __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)copy:(id)sender __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)paste:(id)sender __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)select:(id)sender __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)selectAll:(id)sender __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end
