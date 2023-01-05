//
//  UIMenuController.h
//  UIKit
//
//  Copyright 2009 Apple Inc. All rights reserved.
//

#if __IPHONE_3_0 <= __IPHONE_OS_VERSION_MAX_ALLOWED

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>

@class UIView;

UIKIT_EXTERN_CLASS @interface UIMenuController : NSObject {
  @private
    CGRect _targetRect;
}

+ (UIMenuController *)sharedMenuController;

@property(nonatomic,getter=isMenuVisible) BOOL menuVisible;	    // default is NO
- (void)setMenuVisible:(BOOL)menuVisible animated:(BOOL)animated;

- (void)setTargetRect:(CGRect)targetRect inView:(UIView *)targetView;

- (void)update;	

@property(nonatomic,readonly) CGRect menuFrame;

@end

UIKIT_EXTERN NSString *const UIMenuControllerWillShowMenuNotification;
UIKIT_EXTERN NSString *const UIMenuControllerDidShowMenuNotification;
UIKIT_EXTERN NSString *const UIMenuControllerWillHideMenuNotification;
UIKIT_EXTERN NSString *const UIMenuControllerDidHideMenuNotification;
UIKIT_EXTERN NSString *const UIMenuControllerMenuFrameDidChangeNotification;

#endif
