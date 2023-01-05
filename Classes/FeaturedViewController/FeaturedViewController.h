#import "../../Veteris-Legacy.pch"
@interface FeaturedViewController: UIViewController <UITableViewDelegate, UITableViewDataSource>
@property (nonatomic, strong) UITableView *tableView;
@property (nonatomic, strong) NSArray *featuredApps;
@end
