#import "ApplicationCell.h"
#import "../../Delegate/Veteris-LegacyApplication.h"

@implementation ApplicationCell
@synthesize appNameLabel;
@synthesize appVersionLabel;
@synthesize appDeveloperLabel;
@synthesize appImageView;
- (id)initWithFrame:(CGRect)frame reuseIdentifier:(NSString *)reuseIdentifier {
    if (self = [super initWithFrame:frame reuseIdentifier:reuseIdentifier]) {
        CGFloat height = 78;

        // App Image
        appImageView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 64, 64)];

        // App Name
        appNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(70, 22, 200, 21)];
        appNameLabel.numberOfLines = 1;
        appNameLabel.lineBreakMode = UILineBreakModeTailTruncation;
        appNameLabel.text = @"Grrrr rawr :3";

        // App Version
        appVersionLabel = [[UILabel alloc] initWithFrame:CGRectMake(70, 48, 0, 0)];
        appVersionLabel.text = [NSString stringWithFormat:@"Version: 1.0.0"];
        appVersionLabel.font = [UIFont systemFontOfSize:10];
        appVersionLabel.textColor = [UIColor lightGrayColor];
        [appVersionLabel sizeToFit];

        // App Developer
        appDeveloperLabel = [[UILabel alloc] initWithFrame:CGRectMake(70, 6, 161, 12)];
        appDeveloperLabel.text = @"MrMcDickins";
        appDeveloperLabel.font = [UIFont systemFontOfSize:12];

        [self.contentView addSubview:appImageView];
        [self.contentView addSubview:appNameLabel];
        [self.contentView addSubview:appVersionLabel];
        [self.contentView addSubview:appDeveloperLabel];
    }
    return self;
}

- (void)prepareForReuse {
    [super prepareForReuse];
    appImageView.image = nil;
}

- (void)updateFromApp:(Application *)app {
    appNameLabel.text = app.name;
    appVersionLabel.text = [NSString stringWithFormat:@"Version: %@", app.version];
    appDeveloperLabel.text = app.developer;
    [appVersionLabel sizeToFit];
    [self setNeedsDisplay];
}
@end