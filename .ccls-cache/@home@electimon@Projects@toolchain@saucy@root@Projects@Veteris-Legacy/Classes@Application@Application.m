#import "Application.h"
#import "../../Delegate/Veteris-LegacyApplication.h"

@implementation Application
-(Application *)initFromDictionary:(NSDictionary *)dictionary {
    self = [super init];
    if (
        [dictionary objectForKey:@"name"] != nil &&
        [dictionary objectForKey:@"developer"] != nil &&
        [dictionary objectForKey:@"description"] != nil &&
        [dictionary objectForKey:@"version"] != nil &&
        [dictionary objectForKey:@"bundleid"] != nil &&
        [dictionary objectForKey:@"fileName"] != nil &&
        [dictionary objectForKey:@"iconurl"] != nil &&
        [dictionary objectForKey:@"category"] != nil &&
        [dictionary objectForKey:@"requiredOS"] != nil &&
        [dictionary objectForKey:@"ipadApp"] != nil &&
        [dictionary objectForKey:@"itemId"] != nil
    ) {
        self.name = [dictionary objectForKey:@"name"];  
        self.developer = [dictionary objectForKey:@"developer"];
        self.description = [dictionary objectForKey:@"description"];
        self.version = [dictionary objectForKey:@"version"];
        self.bundleid = [dictionary objectForKey:@"bundleid"];
        self.fileName = [dictionary objectForKey:@"fileName"];
        self.iconurl = [dictionary objectForKey:@"iconurl"];
        self.category = [dictionary objectForKey:@"category"];
        self.requiredOS = [dictionary objectForKey:@"requiredOS"];
        self.ipadApp = [[dictionary objectForKey:@"ipadApp"] boolValue];
        self.itemId = [[dictionary objectForKey:@"itemId"] integerValue];
        return self;
    }
    return nil;
}

- (void)dealloc {
    [self.name release];
    [self.developer release];
    [self.description release];
    [self.version release];
    [self.bundleid release];
    [self.fileName release];
    [self.iconurl release];
    [self.category release];
    [self.requiredOS release];
    [super dealloc];
}

+(UIImage *)getAppImage:(Application *)app forTableView:(UITableView *)tableView {
    //DebugLog([NSString stringWithFormat:@"class1 = %@, class2 = %@", [app description], [tableView description]]);
    VeterisLegacyApplication *delegate = [[UIApplication sharedApplication] delegate];
    DebugLog([NSString stringWithFormat:@"%@", delegate.apiBaseURL.absoluteString])
    NSString *iconPath = [NSString stringWithFormat:@"%@/%@", delegate.apiRootURL.absoluteString, app.iconurl];
    UIImage *image = [delegate.imageCache objectForKey:iconPath];
    if (image) {
        return image;
    }
    NSURL *imageURL = [NSURL URLWithString:[iconPath stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding]];
    DebugLog([NSString stringWithFormat:@"imageURL: %@", imageURL.absoluteString]);
    NSData *imageData = [[NSData alloc] initWithContentsOfURL:imageURL];
    image = [UIImage imageWithData:imageData];
    if (image) {
        [delegate.imageCache setObject:image forKey:iconPath];
    }
    return image;
}
@end