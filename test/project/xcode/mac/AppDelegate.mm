//
//  AppDelegate.m
//  GXTest
//
//  Created by Gengxin Gu on 16/4/19.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#import "AppDelegate.h"
#import "GDataArray.h"
#import "GMap.h"

@interface AppDelegate ()
@property (nonatomic,assign) IBOutlet NSWindow *window;
@end

@implementation AppDelegate
@synthesize window=_window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification {
    GPDArray<int>* arr=GPDArray<int>::alloc();
    arr->zeroSelf();
    GO::release(arr);
    GMap<GObject,GObject>* map=GMap<GObject,GObject>::alloc();
    map->set(NULL, NULL);
    GO::release(map);
    
    
}

- (void)applicationWillTerminate:(NSNotification *)aNotification {
    // Insert code here to tear down your application
}

@end
