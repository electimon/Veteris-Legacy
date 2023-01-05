#import "FeaturedViewController.h"
#import "../VAPIHelper.h"
#import "../Application/Application.h"
#import "../../TouchXML/CXMLDocument.h"
#import "../../Delegate/Veteris-LegacyApplication.h"
#import "Classes/ApplicationCell/ApplicationCell.h"

@implementation FeaturedViewController {
  VAPIHelper *_apiHelper;
  UILabel *indicatorText;
  UIActivityIndicatorView *indicator;
  NSOperationQueue *queue;
}
@synthesize tableView;
@synthesize featuredApps;
- (void)loadView {
  // Vars
  VeterisLegacyApplication *app = [[UIApplication sharedApplication] delegate];
  queue = [[NSOperationQueue alloc] init];
  featuredApps = [[NSMutableArray alloc] init];
  // UI
  // Main View
  self.view = [[UIView alloc] initWithFrame:[[UIScreen mainScreen] applicationFrame]];

  // Table View
  CGRect tableViewFrame = CGRectMake(self.navigationController.view.bounds.origin.x, self.navigationController.view.bounds.origin.y, self.navigationController.view.bounds.size.width, self.view.frame.size.height-(self.tabBarController.tabBar.frame.size.height+self.navigationController.navigationBar.frame.size.height));
  DebugLog(@"%f", self.navigationController.view.frame.size.height-self.tabBarController.tabBar.frame.size.height);
  tableView = [[UITableView alloc] initWithFrame:tableViewFrame];
  tableView.delegate = self;
  tableView.dataSource = self;
  [self.view addSubview:tableView];

  // Data Source
  NSInvocationOperation *operation = [[NSInvocationOperation alloc] initWithTarget:self selector:@selector(loadFeaturedData) object:nil];
  [queue addOperation:operation];
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
  DebugLog(@"called");
  if (featuredApps.count != 0) {
    [indicator stopAnimating];
    self.tableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
    return [featuredApps count];
  };
  // Indicator for loading
  indicator = [[UIActivityIndicatorView alloc] initWithFrame:self.view.frame];
  indicator.activityIndicatorViewStyle = UIActivityIndicatorViewStyleWhiteLarge;
  [indicator sizeToFit];
  [indicator setCenter:CGPointMake(self.view.frame.size.width/2, self.view.frame.size.height/2)];
  indicator.hidesWhenStopped = YES;
  [indicator startAnimating];
  self.tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
  [self.view addSubview:indicator];
  return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
  ApplicationCell *cell = (ApplicationCell*)[self.tableView dequeueReusableCellWithIdentifier:@"ApplicationCell"];
  Application *app = [featuredApps objectAtIndex:indexPath.row];
  if (!cell) {
    CGRect frame = CGRectMake(0, 0, self.view.frame.size.width, 90.0);
    cell = [[[ApplicationCell alloc] initWithFrame:frame reuseIdentifier:@"ApplicationCell"] autorelease];
  }
  [cell updateFromApp:app];
  cell.tag = indexPath.row;
  NSInvocationOperation *operation = [[NSInvocationOperation alloc]
                                      initWithTarget:self
                                      selector:@selector(loadCellImage:)
                                      object:indexPath];
  [queue addOperation:operation];
  return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
  return 64;
}

// Callback for loaded featured data
- (void)featuredDataLoaded {
  DebugLog(@"array: %i", [featuredApps count]);
  [self.tableView reloadData];
}

// Start getting featured data
- (void)loadFeaturedData {
  [VAPIHelper getFeaturedData:self];
}

- (void)loadCellImage:(NSIndexPath *)indexPath {
  UIImage *image = [Application getAppImage:[featuredApps objectAtIndex:indexPath.row] forTableView:self.tableView];
  ApplicationCell *cell = (ApplicationCell*)[self.tableView cellForRowAtIndexPath:indexPath];
  if (cell.tag == indexPath.row) {
    cell.appImageView.image = image;
  }
}
@end











