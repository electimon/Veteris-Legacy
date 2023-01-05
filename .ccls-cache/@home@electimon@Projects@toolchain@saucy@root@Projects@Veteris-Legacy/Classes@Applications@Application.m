#import "Application.h"

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
@end