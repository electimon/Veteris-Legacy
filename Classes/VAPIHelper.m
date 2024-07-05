#import "VAPIHelper.h"
#import "../Delegate/Veteris-LegacyApplication.h"
#import "../TouchXML/CXMLDocument.h"
#import "../TouchJSON/JSON/CJSONSerializer.h"
#import "../TouchJSON/JSON/CJSONDeserializer.h"
#import "../TouchJSON/JSON/CJSONScanner.h"
#import "Application/Application.h"
#import "FeaturedViewController/FeaturedViewController.h"

@implementation VAPIHelper {
}

+ (NSData *)getVAPIDataForEndpoint:(NSString*)endpoint withHeaders:(NSDictionary *)headers {
    VeterisLegacyApplication *appdelegate = [[UIApplication sharedApplication] delegate];
    NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    NSURL *currentAPIURL = [NSURL URLWithString:[NSString stringWithFormat:@"%@%@", appdelegate.apiBaseURL, endpoint]];
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
    NSMutableDictionary *requiredHeaders = [[NSMutableDictionary alloc] init];

    [request setURL:currentAPIURL];
    [request setHTTPMethod:@"GET"];
    if (headers) {
        requiredHeaders = [@{
            @"X-Veteris-Device": appdelegate.VAPIDeviceString,
            @"X-Veteris-Version": appVersion
        } mutableCopy];
        [requiredHeaders addEntriesFromDictionary:headers];
        request.allHTTPHeaderFields = requiredHeaders;
    } else {
        [request setValue:appdelegate.VAPIDeviceString forHTTPHeaderField:@"X-Veteris-Device"];
        [request setValue:appVersion forHTTPHeaderField:@"X-Veteris-Version"];
        [request setValue:@"json" forHTTPHeaderField:@"type"];
    }
    NSURLResponse *response;
    NSError *error;
    NSData *data = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
    //[appVersion release];
    [request release];
    [requiredHeaders release];
    return [data retain];
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
    DebugLog([NSString stringWithFormat:@"JSON: %@", jsonDict]);
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
@end