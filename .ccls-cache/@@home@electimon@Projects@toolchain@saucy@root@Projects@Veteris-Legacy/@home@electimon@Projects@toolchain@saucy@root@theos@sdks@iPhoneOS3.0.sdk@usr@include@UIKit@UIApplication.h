//
//  UIApplication.h
//  UIKit
//
//  Copyright 2005-2009 Apple Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKitDefines.h>
#import <UIKit/UIResponder.h>
#import <UIKit/UIInterface.h>
#import <UIKit/UIDevice.h>
#import <UIKit/UIAlert.h>

typedef enum {
    UIStatusBarStyleDefault,
    UIStatusBarStyleBlackTranslucent,
    UIStatusBarStyleBlackOpaque
} UIStatusBarStyle;

// Note that UIInterfaceOrientationLandscapeLeft is equal to UIDeviceOrientationLandscapeRight (and vice versa).
// This is because rotating the device to the left requires rotating the content to the right.
typedef enum {
    UIInterfaceOrientationPortrait           = UIDeviceOrientationPortrait,
    UIInterfaceOrientationPortraitUpsideDown = UIDeviceOrientationPortraitUpsideDown,
    UIInterfaceOrientationLandscapeLeft      = UIDeviceOrientationLandscapeRight,
    UIInterfaceOrientationLandscapeRight     = UIDeviceOrientationLandscapeLeft
} UIInterfaceOrientation;

#define UIDeviceOrientationIsValidInterfaceOrientation(orientation) ((orientation) == UIDeviceOrientationPortrait || (orientation) == UIDeviceOrientationPortraitUpsideDown || (orientation) == UIDeviceOrientationLandscapeLeft || (orientation) == UIDeviceOrientationLandscapeRight)
#define UIInterfaceOrientationIsPortrait(orientation)  ((orientation) == UIInterfaceOrientationPortrait || (orientation) == UIInterfaceOrientationPortraitUpsideDown)
#define UIInterfaceOrientationIsLandscape(orientation) ((orientation) == UIInterfaceOrientationLandscapeLeft || (orientation) == UIInterfaceOrientationLandscapeRight)

typedef enum {
    UIRemoteNotificationTypeNone    = 0,
    UIRemoteNotificationTypeBadge   = 1 << 0,
    UIRemoteNotificationTypeSound   = 1 << 1,
    UIRemoteNotificationTypeAlert   = 1 << 2
} UIRemoteNotificationType;

@class UIView, UIWindow;
@protocol UIApplicationDelegate;

UIKIT_EXTERN_CLASS @interface UIApplication : UIResponder <UIActionSheetDelegate>
{
  @package
    id <UIApplicationDelegate>  _delegate;
    CFMutableDictionaryRef      _touchMap;
    NSMutableSet               *_exclusiveTouchWindows;
    UIEvent                    *_touchesEvent;
    UIEvent                    *_motionEvent;
    NSArray                    *_topLevelNibObjects;
    NSInteger                   _orientation;
    NSInteger                   _networkResourcesCurrentlyLoadingCount;
    NSTimer                    *_hideNetworkActivityIndicatorTimer;
    struct {
        unsigned int isActive:1;
        unsigned int isSuspended:1;
        unsigned int isSuspendedEventsOnly:1;
        unsigned int isLaunchedSuspended:1;
        unsigned int isHandlingURL:1;
        unsigned int isHandlingRemoteNotification:1;
        unsigned int statusBarMode:8;
        unsigned int statusBarShowsProgress:1;
        unsigned int blockInteractionEvents:4;
        unsigned int forceExit:1;
        unsigned int receivesMemoryWarnings:1;
        unsigned int showingProgress:1;
        unsigned int receivesPowerMessages:1;
        unsigned int launchEventReceived:1;
        unsigned int isAnimatingSuspensionOrResumption:1;
        unsigned int isSuspendedUnderLock:1;
        unsigned int shouldExitAfterSendSuspend:1;
        unsigned int terminating:1;
        unsigned int isHandlingShortCutURL:1;
        unsigned int idleTimerDisabled:1;
        unsigned int statusBarStyle:4;
        unsigned int statusBarHidden:1;
        unsigned int statusBarOrientation:3;
        unsigned int deviceOrientation:3;
        unsigned int delegateShouldBeReleasedUponSet:1;
        unsigned int delegateHandleOpenURL:1;
        unsigned int delegateDidReceiveMemoryWarning:1;
        unsigned int delegateWillTerminate:1;
        unsigned int delegateSignificantTimeChange:1;
        unsigned int delegateWillChangeInterfaceOrientation:1;
        unsigned int delegateDidChangeInterfaceOrientation:1;
        unsigned int delegateWillChangeStatusBarFrame:1;
        unsigned int delegateDidChangeStatusBarFrame:1;
        unsigned int delegateDeviceAccelerated:1;
        unsigned int delegateDeviceChangedOrientation:1;
        unsigned int delegateDidBecomeActive:1;
        unsigned int delegateWillResignActive:1;
        unsigned int idleTimerDisableActive:1;
        unsigned int userDefaultsSyncDisabled:1;
        unsigned int doubleHeightMode:4;
        unsigned int headsetButtonClickCount:4;
        unsigned int disableViewGroupOpacity:1;
        unsigned int disableViewEdgeAntialiasing:1;
        unsigned int shakeToEdit:1;
        unsigned int editWindowIsVisible:1;
    } _applicationFlags;
}

+ (UIApplication *)sharedApplication;

@property(nonatomic,assign) id<UIApplicationDelegate> delegate;

- (void)beginIgnoringInteractionEvents;               // nested. set should be set during animations & transitions to ignore touch and other events
- (void)endIgnoringInteractionEvents;
- (BOOL)isIgnoringInteractionEvents;                  // returns YES if we are at least one deep in ignoring events

@property(nonatomic,getter=isIdleTimerDisabled)       BOOL idleTimerDisabled;	  // default is NO

- (BOOL)openURL:(NSURL*)url;
- (BOOL)canOpenURL:(NSURL *)url __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (void)sendEvent:(UIEvent *)event;

@property(nonatomic,readonly) UIWindow *keyWindow;
@property(nonatomic,readonly) NSArray  *windows;

- (BOOL)sendAction:(SEL)action to:(id)target from:(id)sender forEvent:(UIEvent *)event;

@property(nonatomic,getter=isNetworkActivityIndicatorVisible) BOOL networkActivityIndicatorVisible; // showing network spinning gear in status bar. default is NO
@property(nonatomic) UIStatusBarStyle statusBarStyle; // default is UIStatusBarStyleDefault
- (void)setStatusBarStyle:(UIStatusBarStyle)statusBarStyle animated:(BOOL)animated;
@property(nonatomic,getter=isStatusBarHidden) BOOL statusBarHidden;
- (void)setStatusBarHidden:(BOOL)hidden animated:(BOOL)animated;

// Rotate to a specific orientation.  This only rotates the status bar and updates the statusBarOrientation property.
// This does not change automatically if the device changes orientation.
@property(nonatomic) UIInterfaceOrientation statusBarOrientation;
- (void)setStatusBarOrientation:(UIInterfaceOrientation)interfaceOrientation animated:(BOOL)animated;

@property(nonatomic,readonly) NSTimeInterval statusBarOrientationAnimationDuration; // Returns the animation duration for the status bar during a 90 degree orientation change.  It should be doubled for a 180 degree orientation change.
@property(nonatomic,readonly) CGRect statusBarFrame; // returns CGRectZero if the status bar is hidden

@property(nonatomic) NSInteger applicationIconBadgeNumber;  // set to 0 to hide. default is 0

@property(nonatomic) BOOL applicationSupportsShakeToEdit __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end

@interface UIApplication (UIRemoteNotifications)

- (void)registerForRemoteNotificationTypes:(UIRemoteNotificationType)types __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)unregisterForRemoteNotifications __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);       // calls -registerForRemoteNotificationTypes with UIRemoteNotificationTypeNone

// returns the enabled types, also taking into account any systemwide settings; doesn't relate to connectivity
- (UIRemoteNotificationType)enabledRemoteNotificationTypes __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end

@protocol UIApplicationDelegate<NSObject>

@optional

- (void)applicationDidFinishLaunching:(UIApplication *)application;
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (void)applicationDidBecomeActive:(UIApplication *)application;
- (void)applicationWillResignActive:(UIApplication *)application;
- (BOOL)application:(UIApplication *)application handleOpenURL:(NSURL *)url;  // no equiv. notification. return NO if the application can't open for some reason

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application;      // try to clean up as much memory as possible. next step is to terminate app
- (void)applicationWillTerminate:(UIApplication *)application;
- (void)applicationSignificantTimeChange:(UIApplication *)application;        // midnight, carrier time update, daylight savings time change

- (void)application:(UIApplication *)application willChangeStatusBarOrientation:(UIInterfaceOrientation)newStatusBarOrientation duration:(NSTimeInterval)duration;
- (void)application:(UIApplication *)application didChangeStatusBarOrientation:(UIInterfaceOrientation)oldStatusBarOrientation;

- (void)application:(UIApplication *)application willChangeStatusBarFrame:(CGRect)newStatusBarFrame;   // in screen coordinates
- (void)application:(UIApplication *)application didChangeStatusBarFrame:(CGRect)oldStatusBarFrame;

// one of these will be called after calling -registerForRemoteNotifications
- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);
- (void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0);

@end

@interface UIApplication(UIApplicationDeprecated)

@property(nonatomic,getter=isProximitySensingEnabled) BOOL proximitySensingEnabled __OSX_AVAILABLE_BUT_DEPRECATED(__MAC_NA,__MAC_NA,__IPHONE_2_0,__IPHONE_3_0); // default is NO. see UIDevice for replacement

@end

// If nil is specified for principalClassName, the value for NSPrincipalClass from the Info.plist is used. If there is no
// NSPrincipalClass key specified, the UIApplication class is used. The delegate class will be instantiated using init.
UIKIT_EXTERN int UIApplicationMain(int argc, char *argv[], NSString *principalClassName, NSString *delegateClassName);

UIKIT_EXTERN NSString *const UITrackingRunLoopMode;

// These notifications are sent out after the equivalent delegate message is called
UIKIT_EXTERN NSString *const UIApplicationDidFinishLaunchingNotification;
UIKIT_EXTERN NSString *const UIApplicationDidBecomeActiveNotification;
UIKIT_EXTERN NSString *const UIApplicationWillResignActiveNotification;
UIKIT_EXTERN NSString *const UIApplicationDidReceiveMemoryWarningNotification;
UIKIT_EXTERN NSString *const UIApplicationWillTerminateNotification;
UIKIT_EXTERN NSString *const UIApplicationSignificantTimeChangeNotification;
UIKIT_EXTERN NSString *const UIApplicationWillChangeStatusBarOrientationNotification; // userInfo contains NSNumber with new orientation
UIKIT_EXTERN NSString *const UIApplicationDidChangeStatusBarOrientationNotification;  // userInfo contains NSNumber with old orientation
UIKIT_EXTERN NSString *const UIApplicationStatusBarOrientationUserInfoKey;            // userInfo dictionary key for status bar orientation
UIKIT_EXTERN NSString *const UIApplicationWillChangeStatusBarFrameNotification;       // userInfo contains NSValue with new frame
UIKIT_EXTERN NSString *const UIApplicationDidChangeStatusBarFrameNotification;        // userInfo contains NSValue with old frame
UIKIT_EXTERN NSString *const UIApplicationStatusBarFrameUserInfoKey;                  // userInfo dictionary key for status bar frame
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsURLKey                __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // userInfo constains NSURL with launch URL
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsSourceApplicationKey  __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // userInfo constains NSString with launch app bundle ID
UIKIT_EXTERN NSString *const UIApplicationLaunchOptionsRemoteNotificationKey __OSX_AVAILABLE_STARTING(__MAC_NA,__IPHONE_3_0); // userInfo constains NSDictionary with launch information
