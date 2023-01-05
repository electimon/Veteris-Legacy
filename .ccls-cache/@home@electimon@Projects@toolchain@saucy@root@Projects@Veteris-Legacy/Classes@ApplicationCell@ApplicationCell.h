#import "../../Veteris-Legacy.pch"
#import "../Application/Application.h"

@interface ApplicationCell : UITableViewCell
@property (nonatomic, retain) UILabel *appNameLabel;
@property (nonatomic, retain) UILabel *appVersionLabel;
@property (nonatomic, retain) UILabel *appDeveloperLabel;
@property (nonatomic, retain) UIImageView *appImageView;
- (void)updateFromApp:(Application *)app;
@end