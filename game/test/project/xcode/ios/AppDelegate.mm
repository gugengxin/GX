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

@end

@implementation AppDelegate
@synthesize window=_window;

- (id)init
{
    self=[super init];
    if (self) {
        
    }
    return self;
}

- (void)dealloc
{
    [_window release];
    [super dealloc];
}


- (BOOL)application:(UIApplication *)application willFinishLaunchingWithOptions:(nullable NSDictionary *)launchOptions
{
    
    return YES;
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    NSLog(@"%s",__FUNCTION__);
    _window=[[UIWindow alloc] initWithFrame:[UIScreen mainScreen].bounds];
    [_window makeKeyAndVisible];
    GApplication::main(0,NULL,"AppDge");
    GWindow::main(_window, "Game");
    
    /*
    NSString* path=[[NSBundle mainBundle] pathForResource:@"png-0029.png" ofType:nil];
    
    for (gint count=100; count<=1000; count+=100) {
        gint64 curTime=GSystem::tickCountNS();
        
        for (gint i=0;i<count;i++) {
            UIImage* img=[[UIImage alloc] initWithContentsOfFile:path];
            
            [img release];
        }
        
        gint keyTime0=GSystem::tickCountNS();
        
        for (gint i=0;i<count;i++) {
            UIImage* img=[[UIImage alloc] initWithContentsOfFile:path];
            
            gint width=CGImageGetWidth(img.CGImage);
            gint height=CGImageGetHeight(img.CGImage);
            void* data=malloc(width*height*4);
            CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
            CGContextRef context = CGBitmapContextCreate(data, width, height, 8, width * 4, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big);
            CGColorSpaceRelease(colorSpace);
            CGContextSetBlendMode(context, kCGBlendModeCopy);
            CGContextDrawImage(context, CGRectMake(0, 0, width, height), img.CGImage);
            CGContextRelease(context);
            free(data);
            
            [img release];
        }
        
        gint keyTime1=GSystem::tickCountNS();
        
        {
            GAutoreleasePool pool;
            for (gint i=0; i<count; i++) {
                GFileReader* reader=GFileReader::alloc();
                reader->open([path UTF8String]);
                
                GDib* data=GPng::read(reader);
                
                reader->close();
                
                GO::release(reader);
            }
        }
        
        gint keyTime2=GSystem::tickCountNS();
        
        printf("%15lld\t%15lld\t%15lld\n",keyTime0-curTime,keyTime1-keyTime0,keyTime2-keyTime1);
    }
    //*/
    
    
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    NSLog(@"%s",__FUNCTION__);
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    NSLog(@"%s",__FUNCTION__);
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    NSLog(@"%s",__FUNCTION__);
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    NSLog(@"%s",__FUNCTION__);
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application {
    NSLog(@"%s",__FUNCTION__);
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}

@end
