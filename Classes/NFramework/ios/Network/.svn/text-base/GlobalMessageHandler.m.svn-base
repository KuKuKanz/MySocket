//
//  GlobalMessageHandler.m
//  SocketTest
//
//  Created by DanhPhan on 4/8/14.
//  Copyright (c) 2014 DanhPhan. All rights reserved.
//

#import "GlobalMessageHandler.h"
#include "Session.h"
#include "RootViewController.h"

@implementation GlobalMessageHandler

static id instance;

+(id) gI {
    if(instance == nil)
    {
        instance = [[GlobalMessageHandler alloc] init];
    }
    return instance;
}

-(id) init {
    if(self = [super init]) {
    }
    return self;
}

/*
 receive message from Server
 */
-(void)onMessage:(SenderParket *)msg
{
    [[RootViewController gI] onMessage:msg];
}

/*
 connect to server (FAILED)
 */
-(void)onConnectionFail
{
   // NSLog(@"GlobalMessageHandler-onConnectionFail");
    [[RootViewController gI] onConnectionFail];
}

/*
 Disconnect
 */
-(void)onDisconnected
{
   // NSLog(@"GlobalMessageHandler-onDisconnected");
    [[RootViewController gI] onDisconnect];
}

/*
 connect to Server OK
 */
-(void)onConnectOK
{
   // NSLog(@"GlobalMessageHandler-onConnectOK");
    [[RootViewController gI] onConnectOK];
}

/*
 send read byte error to GA
 */
-(void)onSendReadByteErrorToGA{
    [[RootViewController gI] onSendReadByteErrorToGA];
}

@end