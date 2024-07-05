#import "../Classes/FeaturedViewController/FeaturedViewController.h"
#import "../Classes/VAPIHelper.h"

#define DEBUG

#ifdef DEBUG
#define DebugLog(args...) _DebugLog(__FILE__,__LINE__,args);
#else
#define DebugLog(x...)
#endif

@interface VeterisLegacyApplication: NSObject <UIApplicationDelegate>
@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) UITabBarController *tabBarController;
@property (nonatomic, retain) NSURL *apiRootURL;
@property (nonatomic, retain) NSURL *apiStaticURL;
@property (nonatomic, retain) NSURL *apiBaseURL;
@property (nonatomic, retain) NSString *VAPIDeviceString;
@property (nonatomic, retain) NSMutableDictionary *imageCache;
@property (nonatomic, retain) NSOperationQueue *generalQueue;
@property (nonatomic) BOOL debugOn;
@property (nonatomic, retain) NSString *appVersion;
+ (NSString *) getSysInfoByName:(char *)typeSpecifier;
void _DebugLog(const char *file, int lineNumber, NSString *format,...);
@end