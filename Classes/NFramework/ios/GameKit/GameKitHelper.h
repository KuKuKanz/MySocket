//
//  GameKitHelper.h
//  CatRaceStarter
//
//  Created by Kauserali on 12/01/14.
//  Copyright (c) 2014 Raywenderlich. All rights reserved.
//

#import "GameKit/GameKit.h";

extern NSString *const PresentAuthenticationViewController;
extern NSString *const LocalPlayerIsAuthenticated;

@interface GameKitHelper : NSObject

@property (nonatomic) UIViewController *authenGameCenterViewController;
@property (nonatomic, readonly) NSError *lastError;

@property (nonatomic) bool allowLoginGameCenter;

+ (instancetype)sharedGameKitHelper;
- (void)authenGameCenter;
- (void)sendInfoGameCenter: (NSString* )playerID  Name:(NSString* )displayName;

@end