//
//  AppDelegate.m
//  GXTest
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#import "AppDelegate.h"
#import "GDataArray.h"

@interface AppDelegate ()
@property (nonatomic,assign) IBOutlet NSWindow *window;
@end

@implementation AppDelegate
@synthesize window=_window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    GDataArray<int,8>::alloc();
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
