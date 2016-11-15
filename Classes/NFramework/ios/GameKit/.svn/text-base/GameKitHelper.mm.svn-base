//
//  GameKitHelper.m
//  CatRaceStarter
//
//  Created by Kauserali on 12/01/14.
//  Copyright (c) 2014 Raywenderlich. All rights reserved.
//

#import "GameKitHelper.h"
#import "IOSNDKHelper.h"
#import "RootViewController.h"

NSString *const PresentAuthenticationViewController = @"present_authentication_view_controller";
NSString *const LocalPlayerIsAuthenticated = @"local_player_authenticated";

@implementation GameKitHelper {
    BOOL _enableGameCenter;
}

+ (instancetype)sharedGameKitHelper
{
    static GameKitHelper *sharedGameKitHelper;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedGameKitHelper = [[GameKitHelper alloc] init];
    });
    return sharedGameKitHelper;
}

- (id)init
{
    self = [super init];
    if (self) {
        self.allowLoginGameCenter = false;
        _enableGameCenter = YES;
    }
    return self;
}

- (void)authenGameCenter
{
    if( SYSTEM_VERSION_LESS_THAN(@"6.0.0")){
        NSLog(@"version less than 6.0.0" );
        NSArray *keys = [NSArray arrayWithObjects:@"err_description", nil];
        NSArray *objs = [NSArray arrayWithObjects:@"SYSTEM_VERSION_LESS_THAN_6",nil];
        NSDictionary *dict = [NSDictionary dictionaryWithObjects:objs forKeys:keys];
        [IOSNDKHelper sendMessage:@"receiveErrorGameCenter" withParameters:dict];
        
        return;
    }
    
    GKLocalPlayer *localPlayer = [GKLocalPlayer localPlayer];
    if (localPlayer.isAuthenticated) {
        
        if( self.allowLoginGameCenter  ){
            
            NSString *displayName= @"";
            if( [GKLocalPlayer localPlayer].alias != nil )
                displayName = [GKLocalPlayer localPlayer].alias;
            [self sendInfoGameCenter: [GKLocalPlayer localPlayer].playerID Name: displayName ];
            [[NSNotificationCenter defaultCenter] postNotificationName:LocalPlayerIsAuthenticated object:nil];
            self.allowLoginGameCenter = false;
        }
        return;
    }
    
    localPlayer.authenticateHandler  = ^(UIViewController *viewController, NSError *error) {
        
        if( self.allowLoginGameCenter  ){
            
            [self setLastError:error];
            
            if(viewController != nil) {
                
                [self setAuthenticationViewController:viewController];
            } else if([GKLocalPlayer localPlayer].isAuthenticated) {
                
                NSString *displayName= @"";
                if( [GKLocalPlayer localPlayer].alias != nil )
                    displayName = [GKLocalPlayer localPlayer].alias;
                
                [self sendInfoGameCenter: [GKLocalPlayer localPlayer].playerID Name: displayName ];
                _enableGameCenter = YES;
                
                [[NSNotificationCenter defaultCenter] postNotificationName:LocalPlayerIsAuthenticated object:nil];
                
                self.allowLoginGameCenter = false;
            } else {
                
                _enableGameCenter = NO;
                self.allowLoginGameCenter = false;
            }
        }
        
    };
}

- (void)setAuthenticationViewController:(UIViewController *)authenticationViewController
{
    if (authenticationViewController != nil) {
        self.authenGameCenterViewController = authenticationViewController;
        [[NSNotificationCenter defaultCenter] postNotificationName:PresentAuthenticationViewController object:self];
    }
}

- (void)setLastError:(NSError *)error
{
    _lastError = [error copy];
    if (_lastError) {
		NSLog(@"GameKitHelper descript: %@",[[_lastError userInfo] objectForKey:@"NSLocalizedDescription"] );
        NSLog(@"GameKitHelper ERROR: %@",[[_lastError userInfo] objectForKey:@"NSURLErrorKey"] );
        
        if( [[_lastError userInfo] objectForKey:@"NSLocalizedDescription"] != nil ) {
            NSArray *keys = [NSArray arrayWithObjects:@"err_description", nil];
            NSArray *objs = [NSArray arrayWithObjects:[[_lastError userInfo] objectForKey:@"NSLocalizedDescription"],nil];
            
            NSDictionary *dict = [NSDictionary dictionaryWithObjects:objs forKeys:keys];
            [IOSNDKHelper sendMessage:@"receiveErrorGameCenter" withParameters:dict];
        } else {
            NSArray *keys = [NSArray arrayWithObjects:@"err_description", nil];
            NSArray *objs = [NSArray arrayWithObjects:@"Bạn hãy đăng nhập Game Center của Apple trước khi bạn thực hiện đăng nhập trên NPlay.",nil];
            
            NSDictionary *dict = [NSDictionary dictionaryWithObjects:objs forKeys:keys];
            [IOSNDKHelper sendMessage:@"receiveErrorGameCenter" withParameters:dict];
        }
        
    }
    
}

- (void)sendInfoGameCenter: (NSString* )playerID  Name:(NSString* )displayName
{
    NSArray *keys = [NSArray arrayWithObjects:@"GC_playerID", @"GC_displayName",nil];
    NSArray *objs = [NSArray arrayWithObjects:playerID,displayName,nil];
    NSDictionary *dict = [NSDictionary dictionaryWithObjects:objs forKeys:keys];
    
    [IOSNDKHelper sendMessage:@"receiveInfoGameCenter" withParameters:dict];
    
}
@end

