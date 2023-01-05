#import "../../Veteris-Legacy.pch"
@interface Application : NSObject
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *developer;
@property (nonatomic, strong) NSString *description;
@property (nonatomic, strong) NSString *version;
@property (nonatomic, strong) NSString *bundleid;
@property (nonatomic, strong) NSString *fileName;
@property (nonatomic, strong) NSString *iconurl;
@property (nonatomic, strong) NSString *category;
@property (nonatomic, strong) NSString *requiredOS;
@property (nonatomic) BOOL ipadApp;
@property (nonatomic) int itemId;

-(Application *)initFromDictionary:(NSDictionary *)dictionary;
@end
