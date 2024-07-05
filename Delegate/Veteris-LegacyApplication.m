#import "Veteris-LegacyApplication.h"
#include <sys/sysctl.h>

@implementation VeterisLegacyApplication
@synthesize window;
@synthesize tabBarController;
@synthesize debugOn;
@synthesize apiRootURL;
@synthesize apiBaseURL;
@synthesize VAPIDeviceString;
@synthesize imageCache;
@synthesize generalQueue;
- (void)applicationDidFinishLaunching:(UIApplication *)application {
  // Variables
  imageCache = [[NSMutableDictionary alloc] init];
  debugOn = YES;
  generalQueue = [[NSOperationQueue alloc] init];
  VAPIDeviceString = [VAPIHelper getVAPIDeviceString];
  apiRootURL = [[NSURL URLWithString:@"http://veteris.yzu.moe"] retain];
  apiBaseURL = [[NSURL URLWithString:[NSString stringWithFormat:@"%@/1.1", apiRootURL.absoluteString]] retain];
  DebugLog([NSString stringWithFormat:@"%@", apiBaseURL.absoluteString])
  // UI
  // Tab Bar Controller 
  tabBarController  = [[UITabBarController alloc] init];

  // Main Window
  window = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];

  // View Controller/Navigation Controller pairs
  // Featured
  FeaturedViewController *featuredViewController = [[FeaturedViewController alloc] init];
  UINavigationController *featuredNavigationController = [[UINavigationController alloc] initWithRootViewController:featuredViewController];
  featuredViewController.title = @"Featured";
  featuredViewController.tabBarItem = [[UITabBarItem alloc] initWithTabBarSystemItem:UITabBarSystemItemFeatured tag:0];

  // Settimongus
  [tabBarController setViewControllers:[NSArray arrayWithObject:featuredNavigationController]];
  [window addSubview:tabBarController.view];
  [window makeKeyAndVisible];
}

// Debug
void _DebugLog(const char *file, int lineNumber, NSString *message,...) {
  NSString *string = [[NSString alloc] initWithUTF8String:file];
  NSLog(@"%@:%d: %@", string, lineNumber, message);
}

// Analytical utilities
+ (NSString *) getSysInfoByName:(char *)typeSpecifier
{
    size_t size;
    sysctlbyname(typeSpecifier, NULL, &size, NULL, 0);
    
    char *answer = malloc(size);
    sysctlbyname(typeSpecifier, answer, &size, NULL, 0);
    
    NSString *results = [NSString stringWithCString:answer encoding: NSUTF8StringEncoding];
    
    free(answer);
    return results;
}
@end

