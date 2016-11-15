//
//  Session.m
//  SocketTest
//
//  Created by DanhPhan on 4/8/14.
//  Copyright (c) 2014 DanhPhan. All rights reserved.
//

#import "Session.h"
#import "GlobalMessageHandler.h"
#import "../../../Classes/NFramework/Library/GoogleAnalyticIOS/GAI.h"
#import "../../../Classes/NFramework/Library/GoogleAnalyticIOS/GAIDictionaryBuilder.h"
#import "../../../Classes/NFramework/Library/GoogleAnalyticIOS/GAIFields.h"

//#define DEBUG 0

@implementation Session

static id instace;
@synthesize m_ip,port;

/*
 get instance
 */
+(id)gI {
    if(instace == nil) {
        instace = [[Session alloc] init];
    }
    return instace;
}

/*
 init
 */
-(id)init {
    if(self = [super init]) {
        isConnected = false;
        list_msg_send = [[NSMutableArray alloc] init];
        messageHandler = [GlobalMessageHandler gI];
    }
    
    return self;
}

-(void) sendEvent:(NSString *)event action:(NSString *)actionValue content:(NSString *)contentValue {
    id<GAITracker> tracker= [[GAI sharedInstance] defaultTracker];
    
    [tracker send:[[GAIDictionaryBuilder createEventWithCategory:event
                                                          action:actionValue
                                                           label:contentValue
                                                           value:nil] build]];
    
}

/*
 This is a functuon of NSStreamDelegate
 (To send and read message,....)
 */
-(void)stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode {
    @try {
        switch (eventCode) {
            case NSStreamEventNone:
#ifdef DEBUG
                NSLog(@"Session::handleEvent::NSStreamEventNone");
#endif
                break;
            case NSStreamEventEndEncountered:
            {
#ifdef DEBUG
                NSLog(@"Session::handleEvent::NSStreamEventEndEncountered");
#endif
                
                if(isConnected) {
#ifdef DEBUG
                    NSLog(@"Session::handleEvent::disconnect");
#endif
                    [self sendEvent:@"Session" action:@"NSStreamEventEndEncountered" content:@"disconnect"];
                    [self disconnect];
                }
                break;
            }
            case NSStreamEventErrorOccurred:
            {
#ifdef DEBUG
                NSError *theError = [aStream streamError];
                NSLog(@"Session::handleEvent::NSStreamEventErrorOccurred %@", theError);
                NSLog(@"Session::handleEvent::disconnect");
#endif
                [self sendEvent:@"Session" action:@"NSStreamEventErrorOccurred" content:@"disconnect"];
                [self disconnect];
                break;
            }
            case NSStreamEventHasBytesAvailable:
            {
                if(aStream == m_readStream)
                {
                    [self readBytes];
                }
                
                break;
            }
            case NSStreamEventHasSpaceAvailable:
            {
                break;
            }
            case NSStreamEventOpenCompleted:
            {
                if(!isConnected) {
//#ifdef DEBUG
//                    NSLog(@"Session::handleEvent::onConnectOK");
//#endif
                    isConnected = true;
                    
                }
                
                [messageHandler onConnectOK];
                
                break;
            }
            default:
                break;
        }
    }
    @catch (NSException *exception) {
//#ifdef DEBUG
//        NSLog(@"Session::handleEvent::NSException %@", [exception reason]);
//#endif
        [self sendEvent:@"Session" action:@"NSException" content:@"disconnect"];
        [self disconnect];
    }
}

/*
 connect to server withParams : IP and Port
 */
-(void)connect:(NSString *)ipValue :(int)portValue {
    self.m_ip = ipValue;
    self.port = portValue;    
    
    CFStreamCreatePairWithSocketToHost(NULL, (__bridge CFStringRef)self.m_ip, self.port, &m_readStreamRef, &m_writeStreamRef);
    
    m_readStream = (__bridge NSInputStream*)m_readStreamRef;
    m_writeStream = (__bridge NSOutputStream*)m_writeStreamRef;
    
    [m_readStream retain];
    [m_writeStream retain];
    
    //set delegate
    [m_readStream setDelegate:self];
    [m_writeStream setDelegate:self];
    
    //set schedule Run loop
    [m_readStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [m_writeStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    
    //open
    [m_readStream open];
    [m_writeStream open];
    
    if (m_readStreamRef) {
        CFRelease(m_readStreamRef);
    }
    if (m_writeStreamRef) {
        CFRelease(m_writeStreamRef);
    }

}

/*
 disconnect
 */
-(void)disconnect
{
    [self closeSocket];
    [messageHandler onDisconnected];
}

/*
 Add message to Queue
 */
-(void)AddMessage:(SenderParket *)obj {
    
//#ifdef DEBUG
//    NSLog(@"Session::AddMessage To Send");
//#endif
    @synchronized(obj) {
        [m_writeStream write:[obj.bytes bytes] maxLength:obj.length];
    }
    
}

/*
 close socket
 */
-(void)closeSocket {
//#ifdef DEBUG
//    NSLog(@"Session::CloseSocket");
//#endif
    isConnected = false;
    
    if(m_writeStream!=nil) {
        [m_writeStream close];
        [m_writeStream removeFromRunLoop:[NSRunLoop mainRunLoop] forMode:NSDefaultRunLoopMode];
        [m_writeStream release];
        m_writeStream = nil;
    }
    
    if(m_readStream!=nil) {
        [m_readStream close];
        [m_readStream removeFromRunLoop:[NSRunLoop mainRunLoop] forMode:NSDefaultRunLoopMode];
        [m_readStream release];
        m_readStream = nil;
    }
    
    if (m_readStreamRef) {
        m_readStreamRef = nil;
    }
    
    if (m_writeStreamRef) {
        m_writeStream = nil;
    }
    
    m_readStreamRef = nil;
    m_writeStreamRef = nil;
}

-(void) dealloc {
    self.m_ip = nil;
    self.port = 0;
    
    [super dealloc];
}

/*
 readBytes
 */
-(void)readBytes
{
//#ifdef DEBUG
//    NSLog(@"Session::readBytes");
//#endif
    
    SenderParket* msg = [[SenderParket alloc] init];
    int recv_bytes = 0;
    uint length = 0;
    uint8_t bite;
    
    
    @try {
        NSInteger received = [m_readStream read:&bite maxLength:1];
        if (received < 0) {
//#ifdef DEBUG
//            NSLog(@"Session::ReadByteError");
//#endif
            [self sendEvent:@"Session" action:@"ReadByteError" content:@"ReadByteError"];
        } else {
            recv_bytes += received;
        }
        
        length = (bite & 0x7f);
        while (bite & 0x80) {
            memset(&bite, 0, 1);
            
            received = [m_readStream read:&bite maxLength:1];
            if (received < 0) {
//#ifdef DEBUG
//                NSLog(@"Session::ReadByteError");
//#endif
                [self sendEvent:@"Session" action:@"ReadByteError" content:@"ReadByteError"];
            } else {
                recv_bytes +=received;
            }
            
            length |= (bite & 0x7f) << (7*(recv_bytes - 1));
        }
        
        if(length > 0) {
            if(received >= 0) {
                @try {
                    msg.length = length;
                    uint8_t *ptrData = malloc(length);
                    uint8_t *temp = ptrData;
                    NSInteger len = 0;
                    int byteRead = 0;
                    
                    while (len != -1 && byteRead < length) {
                        len = [m_readStream read:temp maxLength:(length - byteRead)];
                        if (len > 0) {
                            byteRead += len;
                            temp = ptrData + byteRead;
                        } else {
                            break;
                        }
                    }
                    
                    [msg.bytes appendBytes:ptrData length:length];
                    free(ptrData);
                    
                    @synchronized(messageHandler){
                        [messageHandler onMessage:msg];
                        [msg release];
                    }
                    
                }
                @catch (NSException *exception) {
//#ifdef DEBUG
//                    NSLog(@"Session::Exception read msg");
//#endif
                    [self sendEvent:@"Session" action:@"ReadByteError Exception disconnect" content:@"ReadByteError Exception disconnect"];
                    [self disconnect];
                }
            }
        }
    }
    @catch (NSException *exception) {
//#ifdef DEBUG
//        NSLog(@"onMessage exception");
//#endif
        [self sendEvent:@"Session" action:@"NSException ReadByte" content:@"disconnect"];
        [self disconnect];
    }
}

-(void)sendReadByteError{
    [messageHandler sendReadByteError];
}

@end
