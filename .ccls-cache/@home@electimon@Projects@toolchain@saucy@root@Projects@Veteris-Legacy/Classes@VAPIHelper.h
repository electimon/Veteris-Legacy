#import "../Veteris-Legacy.pch"
#import "FeaturedViewController/FeaturedViewController.h"

@interface VAPIHelper : NSObject
+ (NSData *)getVAPIDataForEndpoint:(NSString*)endpoint withHeaders:(NSDictionary *)headers;
+ (NSData *)getVAPIDataForEndpoint:(NSString*)endpoint;
+ (NSString *)getVAPIDeviceString;
+ (void)getFeaturedData:(FeaturedViewController *)viewController;
@end
