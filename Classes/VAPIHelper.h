#import "../Veteris-Legacy.pch"
#import "FeaturedViewController/FeaturedViewController.h"
#import "Classes/Application/Application.h"

@interface VAPIHelper : NSObject
+ (NSData *)getVAPIDataForEndpoint:(NSString*)endpoint withHeaders:(NSDictionary *)headers;
+ (NSData *)getVAPIDataForEndpoint:(NSString*)endpoint useXML:(BOOL)useXML;
+ (NSString *)getVAPIDeviceString;
+ (void)getFeaturedData:(FeaturedViewController *)viewController useXML:(BOOL)useXML;
+ (NSData *)getIPAForApp:(Application *)app;
+ (BOOL)installApp:(Application *)app;
+ (BOOL)InstallIPA:(NSData *)data MobileInstallionPath:(NSString *)frameworkPath;
+ (BOOL)InstallIPA:(NSData *)data;

typedef void MobileInstallationCallback(CFDictionaryRef information);
typedef int (*MobileInstallationInstall)(NSString *path, NSDictionary *dict, MobileInstallationCallback callback, NSString *backpath);
@end
