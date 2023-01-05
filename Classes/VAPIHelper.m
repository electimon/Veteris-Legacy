#import "VAPIHelper.h"
#import "../Delegate/Veteris-LegacyApplication.h"
#import "../TouchXML/CXMLDocument.h"
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
        [request setValue:@"xml" forHTTPHeaderField:@"type"];
    }
    NSURLResponse *response;
    NSError *error;
    NSData *data = [NSURLConnection sendSynchronousRequest:request returningResponse:&response error:&error];
    //[appVersion release];
    [request release];
    [requiredHeaders release];
    return [data retain];
}

+ (NSData *)getVAPIDataForEndpoint:(NSString*)endpoint {
    return [self getVAPIDataForEndpoint:endpoint withHeaders:nil];
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
        if ([child.localName isEqualToString:@"itemId"]) {
          [appDict setObject:[child stringValue] forKey:@"itemId"];
        }
      }
      Application *app = [[Application alloc] initFromDictionary:appDict];
      if (app) {
        [appsArray addObject:[app retain]];
      }
      [appDict release];
      [app release];
      //NSLog(@"%@", [[[[node children] objectAtIndex:0] childAtIndex:0] stringValue]);
    }
    return appsArray;
}

+ (void)getFeaturedData:(FeaturedViewController *)viewController {
    DebugLog(@"called!");
    VeterisLegacyApplication *appdelegate = [[UIApplication sharedApplication] delegate];
    NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
    NSData *data = [self getVAPIDataForEndpoint:@"/listing/recommended"];
    CXMLDocument *doc = [[CXMLDocument alloc] initWithData:data options:0 error:nil];
    CXMLElement *rootNode = [doc rootElement];
    CXMLElement *applicationsElement = [[rootNode children] objectAtIndex:0];
    NSArray *appsArray = [self parseAppXMLElemenet:applicationsElement];
    [doc release];
    [data release];
    viewController.featuredApps = appsArray;
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