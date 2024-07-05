#import "VAPIHelper.h"
#import "../Delegate/Veteris-LegacyApplication.h"
#import "../TouchXML/CXMLDocument.h"
#import "../TouchJSON/JSON/CJSONSerializer.h"
#import "../TouchJSON/JSON/CJSONDeserializer.h"
#import "../TouchJSON/JSON/CJSONScanner.h"
#import "Application/Application.h"
#import "FeaturedViewController/FeaturedViewController.h"

#import <dlfcn.h>

#define TEMP_IPA_PATH "/var/mobile/Media/Downloads/temp.ipa"

@implementation VAPIHelper {
}

// TODO:
// * Cache CFBundleShortVersionString

+ (NSData *)getVAPIDataForEndpoint:(NSString*)endpoint withHeaders:(NSDictionary *)headers {
    VeterisLegacyApplication *appdelegate = [[UIApplication sharedApplication] delegate];
    NSURL *currentAPIURL = [NSURL URLWithString:[NSString stringWithFormat:@"%@%@", appdelegate.apiBaseURL, endpoint]];
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
    NSMutableDictionary *requiredHeaders = [[NSMutableDictionary alloc] init];

    [request setURL:currentAPIURL];
    [request setHTTPMethod:@"GET"];
    if (headers) {
        requiredHeaders = [@{
            @"X-Veteris-Device": appdelegate.VAPIDeviceString,
            @"X-Veteris-Version": appdelegate.appVersion
        } mutableCopy];
        [requiredHeaders addEntriesFromDictionary:headers];
        request.allHTTPHeaderFields = requiredHeaders;
    } else {
        [request setValue:appdelegate.VAPIDeviceString forHTTPHeaderField:@"X-Veteris-Device"];
        [request setValue:appdelegate.appVersion forHTTPHeaderField:@"X-Veteris-Version"];
        [request setValue:@"json" forHTTPHeaderField:@"type"];
    }
    NSURLResponse *response;
    NSError *error;
    NSData *data = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
    [request release];
    [requiredHeaders release];
    return [data retain];
}

+ (NSData *)getIPAForApp:(Application *)app {
    VeterisLegacyApplication *appdelegate = [[UIApplication sharedApplication] delegate];
    NSString *ipaURL = [NSString stringWithFormat:@"%@/%@", appdelegate.apiRootURL, app.fileName];
    DebugLog([NSString stringWithFormat:@"Getting IPA at path: %@", ipaURL])
    NSURL *currentIPAURL = [NSURL URLWithString:[ipaURL stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
    [request setURL:currentIPAURL];
    [request setHTTPMethod:@"GET"];
    // [request setValue:appdelegate.VAPIDeviceString forHTTPHeaderField:@"X-Veteris-Device"];
    // [request setValue:appdelegate.appVersion forHTTPHeaderField:@"X-Veteris-Version"];
    NSURLResponse *response;
    NSError *error = NULL;
    DebugLog(@"Fetching");
    NSData *data = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
    if (error) {
        DebugLog([NSString stringWithFormat:@"Error fetching IPA: %@", error]);
        [error release];
        [request release];
        return nil;
    }
    [request release];
    return [data retain];
}

+ (BOOL)installApp:(Application *)app {
    DebugLog([NSString stringWithFormat:@"Installing app: %@", app.name]);
    NSData *data = [self getIPAForApp:app];
    if (data != nil) {
        DebugLog([NSString stringWithFormat:@"Got IPA data: %i bytes", [data length]]);
        return [self InstallIPA:data];
    }
    return false;
}

+ (NSData *)getVAPIDataForEndpoint:(NSString*)endpoint useXML:(BOOL)useXML {
    if (useXML) {
        return [self getVAPIDataForEndpoint:endpoint withHeaders:@{@"type": @"xml"}];
    }
    return [self getVAPIDataForEndpoint:endpoint withHeaders:nil];
}

+ (NSArray *)parseAppsJSONData:(NSData *)data {
    NSError *error = NULL;
    NSDictionary *jsonDict = [[CJSONDeserializer deserializer] deserialize:data error:&error];
    if (error) {
        DebugLog([NSString stringWithFormat:@"Error parsing JSON: %@", error]);
        [error release];
        return nil;
    }
    NSMutableArray *appsArray = [[NSMutableArray alloc] init];
    for (NSDictionary *appDict in [jsonDict objectForKey:@"applications"]) {
        Application *app = [[Application alloc] initFromDictionary:appDict];
        DebugLog([NSString stringWithFormat:@"App: %@", app])
        if (app) {
            [appsArray addObject:[app retain]];
        }
        [app release];
    }
    return appsArray;
}

+ (NSArray *)parseAppXMLElemenet:(CXMLElement*)element {
    NSMutableArray *appsArray = [[NSMutableArray alloc] init];
    for (CXMLNode *node in [element children]) {
      NSMutableDictionary *appDict = [[NSMutableDictionary alloc] init];
      for (CXMLNode *child in [node children]) {
        if ([child.localName isEqualToString:@"name"]) {
          [appDict setObject:[child stringValue] forKey:@"name"];
        }
        if ([child.localName isEqualToString:@"developer"]) {
          [appDict setObject:[child stringValue] forKey:@"developer"];
        }
        if ([child.localName isEqualToString:@"description"]) {
          [appDict setObject:[child stringValue] forKey:@"description"];
        }
        if ([child.localName isEqualToString:@"version"]) {
          [appDict setObject:[child stringValue] forKey:@"version"];
        }
        if ([child.localName isEqualToString:@"bundleid"]) {
          [appDict setObject:[child stringValue] forKey:@"bundleid"];
        }
        if ([child.localName isEqualToString:@"fileName"]) {
          [appDict setObject:[child stringValue] forKey:@"fileName"];
        }
        if ([child.localName isEqualToString:@"iconurl"]) {
          [appDict setObject:[child stringValue] forKey:@"iconurl"];
        }
        if ([child.localName isEqualToString:@"category"]) {
          [appDict setObject:[child stringValue] forKey:@"category"];
        }
        if ([child.localName isEqualToString:@"requiredOS"]) {
          [appDict setObject:[child stringValue] forKey:@"requiredOS"];
        }
        if ([child.localName isEqualToString:@"ipadApp"]) {
          [appDict setObject:[child stringValue] forKey:@"ipadApp"];
        }
        if ([child.localName isEqualToString:@"itemID"]) {
          [appDict setObject:[child stringValue] forKey:@"itemID"];
        }
      }
      Application *app = [[Application alloc] initFromDictionary:appDict];
      if (app) {
        [appsArray addObject:[app retain]];
      }
      [appDict release];
      [app release];
    }
    return appsArray;
}

+ (void)getFeaturedData:(FeaturedViewController *)viewController useXML:(BOOL)useXML {
    DebugLog([NSString stringWithFormat:@"Getting featured data with XML: %i", useXML]);
    NSArray *appsArray;
    VeterisLegacyApplication *appdelegate = [[UIApplication sharedApplication] delegate];
    NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    NSData *data = [self getVAPIDataForEndpoint:@"/listing/recommended" useXML:useXML];
    if (useXML) {
      CXMLDocument *doc = [[CXMLDocument alloc] initWithData:data options:0 error:nil];
      CXMLElement *rootNode = [doc rootElement];
      CXMLElement *applicationsElement = [[rootNode children] objectAtIndex:0];
      appsArray = [self parseAppXMLElemenet:applicationsElement];
      [doc release];
    } else {
      appsArray = [self parseAppsJSONData:data];
    }
    [data release];
    DebugLog([NSString stringWithFormat:@"Object: %@ %@", [appsArray class], appsArray]);
    viewController.featuredApps = [appsArray retain];
    [viewController performSelector:@selector(featuredDataLoaded)];
}

+ (NSString *)getVAPIDeviceString {
    NSString *VAPIDeviceString;
    NSArray *deviceInfo = @[[VeterisLegacyApplication getSysInfoByName:"hw.model"], [[UIDevice currentDevice] model], [[UIDevice currentDevice] systemVersion]];
    VAPIDeviceString = [deviceInfo componentsJoinedByString:@"/"];
    DebugLog([NSString stringWithFormat:@"VAPIDeviceString = %@", VAPIDeviceString]);
    return VAPIDeviceString;
}

+ (BOOL)InstallIPA:(NSData *)data MobileInstallionPath:(NSString *)frameworkPath {
    [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:false];
    void *lib = dlopen([frameworkPath UTF8String], RTLD_LAZY);
    puts(dlerror());
    DebugLog([NSString stringWithFormat:@"lib: %p", lib]);
    if (lib) {
        MobileInstallationInstall pMobileInstallationInstall = (MobileInstallationInstall)dlsym(lib, "MobileInstallationInstall");
        if (pMobileInstallationInstall) {
            NSString* temp = [NSTemporaryDirectory() stringByAppendingPathComponent:[@"Temp_" stringByAppendingString:[NSString stringWithFormat:@"%u", arc4random()]]];
            NSError *error = NULL;
            [data writeToFile:temp atomically:YES];
            DebugLog([NSString stringWithFormat:@"Temp IPA path: %@", temp]);
            if (error) {
                DebugLog([NSString stringWithFormat:@"Error writing IPA: %@", error]);
                [self removeTempIPA];
                return false;
            }
            DebugLog([NSString stringWithFormat:@"Installing IPA: %i bytes", [data length]]);
            int ret = pMobileInstallationInstall(temp, [NSDictionary dictionaryWithObject:@"User" forKey:@"ApplicationType"], &installCallback, NULL);
            NSString *alertTitle = (ret == 0) ? @"Success!" : @"Failure";
            NSString *alertMessage = (ret == 0) ? @"Application installed successfully!" : @"Application failed to install...";
            [[UIApplication sharedApplication] setIdleTimerDisabled:false];
            UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertTitle message:alertMessage delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil];
            [alert show];
            return (ret == 0);
        }
    }
    [self removeTempIPA];
    return false;
}

+ (BOOL)InstallIPA:(NSData *)data {
    return [self InstallIPA:data MobileInstallionPath:@"/System/Library/PrivateFrameworks/MobileInstallation.framework/MobileInstallation"];
}

+ (void)removeTempIPA {
    NSError *error;
    [[NSFileManager defaultManager] removeItemAtPath:@TEMP_IPA_PATH error:&error];
}

// Mystical install progress callback code, don't stare for too long or it'll stop working
void installCallback(CFDictionaryRef information) {
    NSDictionary *dict = (__bridge NSDictionary *)information;
    float percentDone = [[dict valueForKey:@"PercentComplete"] floatValue] / 100;
    NSString *status = [dict valueForKey:@"Status"];
    DebugLog([NSString stringWithFormat:@"Install progress: %f%%, status: %@", percentDone, status]);
}

@end