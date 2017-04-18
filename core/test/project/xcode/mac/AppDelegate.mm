//
//  AppDelegate.m
//  GXTest
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#import "AppDelegate.h"
#include "AppDge.h"

@interface AppDelegate ()
@property (nonatomic,assign) IBOutlet NSWindow *window;
@end

@implementation AppDelegate
@synthesize window=_window;


- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
    GApplication::main(0, NULL, "AppDge");
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {

}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
