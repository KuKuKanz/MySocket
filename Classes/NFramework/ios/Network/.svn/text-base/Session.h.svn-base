//
//  Session.h
//  SocketTest
//
//  Created by DanhPhan on 4/8/14.
//  Copyright (c) 2014 DanhPhan. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SenderParket.h"
#import "IMessageHandler.h"

@interface Session : NSObject<NSStreamDelegate> {
    
    //ReadStream and WriteSrtream
    CFReadStreamRef m_readStreamRef;
    CFWriteStreamRef m_writeStreamRef;
    NSInputStream* m_readStream;
    NSOutputStream* m_writeStream;
    
    //ip - port
    NSString* m_ip;
    int m_port;
    
    //connected
    BOOL isConnected;
    
    //List message to Send
    NSMutableArray* list_msg_send;
    
    //Message handler
    id messageHandler;
}

+(id)gI; //get instance
-(void)connect:(NSString*)ipValue : (int)portValue;
-(void)AddMessage:(SenderParket*)obj;
-(void)closeSocket;
-(void)readBytes;
-(void)disconnect;
-(void)sendReadByteError;
-(void) sendEvent:(NSString*)event action:(NSString*)actionValue content:(NSString*)contentValue;

@property(strong,nonatomic) NSString* m_ip;
@property(assign,nonatomic) int port;

@end