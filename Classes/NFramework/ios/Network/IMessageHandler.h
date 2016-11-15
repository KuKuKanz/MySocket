//
//  IMessageHandler.h
//  SocketTest
//
//  Created by DanhPhan on 4/8/14.
//  Copyright (c) 2014 DanhPhan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SenderParket.h"

@protocol IMessageHandler <NSObject>

-(void)onMessage:(SenderParket*)msg;
-(void)onConnectionFail;
-(void)onDisconnected;
-(void)onConnectOK;
-(void)onSendReadByteErrorToGA;

@end