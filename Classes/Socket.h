//
//  Socket.h
//  MySocket
//
//  Created by Dao Hoang Tung on 11/14/16.
//
//

#import <Foundation/Foundation.h>
#import "SenderPacker.h"

@interface Socket : NSObject<NSStreamDelegate>{
    //ReadStream and WriteSrtream
    CFReadStreamRef m_readStreamRef;
    CFWriteStreamRef m_writeStreamRef;
    NSInputStream* m_readStream;
    NSOutputStream* m_writeStream;
    
    NSInputStream	*inputStream;
    NSOutputStream	*outputStream;
    NSString* m_ip;
    int m_port;
    
    bool isConnected;
    bool isSpaceAvai;
    
}

+(id)getInstance;
-(void) connect:(NSObject*)prms;
-(void) sendMessage: (SenderParket*) packer;
-(void) sendMessageData: (NSObject*)prms;

@property(strong,nonatomic) NSString* m_ip;
@property(assign,nonatomic) int port;
@property(assign,nonatomic) bool isConnected;
@property (nonatomic, retain) NSInputStream *inputStream;
@property (nonatomic, retain) NSOutputStream *outputStream;
@end
