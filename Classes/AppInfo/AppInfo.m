#import "AppInfo.h"
#import "../VAPIHelper.h"
#import "../Application/Application.h"
#import "../../Delegate/Veteris-LegacyApplication.h"

@implementation AppInfo {
  VAPIHelper *_apiHelper;
  Application *_app;
}

- (id)initWithApp:(Application *)app {
    self = [super init];
    if (self) {
        _app = app;
        //_apiHelper = [[VAPIHelper alloc] init];
    }
    return self;
}

- (void)loadView {
    // UI
    // Main View
    self.view = [[UIView alloc] initWithFrame:[[UIScreen mainScreen] applicationFrame]];
    self.view.backgroundColor = [UIColor whiteColor];

    // Icon View
    UIImageView *iconView = [[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 64, 64)];
    iconView.image = [Application getAppImage:_app];

    // App Name
    UILabel *appNameLabel = [[UILabel alloc] initWithFrame:CGRectMake(70, 22, 200, 21)];
    appNameLabel.numberOfLines = 1;
    appNameLabel.lineBreakMode = UILineBreakModeTailTruncation;
    appNameLabel.text = _app.name;

    // App Version
    UILabel *appVersionLabel = [[UILabel alloc] initWithFrame:CGRectMake(70, 48, 0, 0)];
    appVersionLabel.text = [NSString stringWithFormat:@"Version: %@", _app.version];
    appVersionLabel.font = [UIFont systemFontOfSize:10];
    appVersionLabel.textColor = [UIColor lightGrayColor];
    [appVersionLabel sizeToFit];

    // App Developer
    UILabel *appDeveloperLabel = [[UILabel alloc] initWithFrame:CGRectMake(70, 6, 161, 12)];
    appDeveloperLabel.text = _app.developer;
    appDeveloperLabel.font = [UIFont systemFontOfSize:12];

    // Get button
    UIButton *getButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    getButton.frame = CGRectMake(260, 20, 50, 30);
    [getButton setTitle:@"Get" forState:UIControlStateNormal];
    [getButton addTarget:self action:@selector(getApp) forControlEvents:UIControlEventTouchUpInside];

    [self.view addSubview:iconView];
    [self.view addSubview:appNameLabel];
    [self.view addSubview:appVersionLabel];
    [self.view addSubview:appDeveloperLabel];
    [self.view addSubview:getButton];
}

- (void)getApp {
    DebugLog([NSString stringWithFormat:@"Getting app: %@", _app.name])
    [VAPIHelper installApp:_app];
}

- (void)dealloc {
    [super dealloc];
    if (_app) {
        [_app release];
    }
    if (_apiHelper) {
        [_apiHelper release];
    }
}

@end