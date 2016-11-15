//
//  SocketController.m
//  MySocket
//
//  Created by Dao Hoang Tung on 11/15/16.
//
//

#import "SocketController.h"

#include "HelloWorldScene.h"
@implementation SocketController

static id instance;

+(id)getInstance{
    
    if (instance == nil){
        instance = [[SocketController alloc] init];
    }
    return instance;
}

-(void)onConnectOk{
    HelloWorld::getInstance()->onConnectOk();
}

@end
