//
//  Socket.m
//  MySocket
//
//  Created by Dao Hoang Tung on 11/14/16.
//
//

#import "Socket.h"
#import "SocketController.h"

@implementation Socket
@synthesize m_ip,port,isConnected;
@synthesize inputStream, outputStream;


static id ROOT;

+(id)getInstance{
    if (ROOT == nil){
        ROOT = [[Socket alloc] init];
    }
    
    return ROOT;
}

-(id) init{
    if (self == [super init]){
        self.m_ip = @"localhost";
        self.port = 8888;
        
        isConnected = false;
        isSpaceAvai = false;
        
    }


    return self;
}



-(void) connect:(NSObject *)prms{
    NSDictionary* paramaters = (NSDictionary*)prms;
    NSString* ip = (NSString*)[paramaters objectForKey:@"myIP"];
    NSString* myport = (NSString*)[paramaters objectForKey:@"myPort"];
    int port = [myport intValue];
    
    CFReadStreamRef readStream;
    CFWriteStreamRef writeStream;
    CFStreamCreatePairWithSocketToHost(NULL, (CFStringRef)ip, port, &readStream, &writeStream);
    
    inputStream = (NSInputStream *)readStream;
    outputStream = (NSOutputStream *)writeStream;
    [inputStream setDelegate:self];
    [outputStream setDelegate:self];
    [inputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [outputStream scheduleInRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
    [inputStream open];
    [outputStream open];

}


-(void) stream:(NSStream *)aStream handleEvent:(NSStreamEvent)eventCode{
    @try {
        switch (eventCode) {
            case NSStreamEventEndEncountered:
                
                break;
            case NSStreamEventErrorOccurred:
                
                break;
                
            case NSStreamEventHasBytesAvailable:
                break;
                
            case NSStreamEventHasSpaceAvailable:
            {
                if (!isSpaceAvai){
                    NSLog(@"OK !");
                    isSpaceAvai = true;
                }
            }
                break;
                
            case NSStreamEventNone:
                
                break;
                
            case NSStreamEventOpenCompleted:
                if (!isConnected){
                    NSLog(@"Connect OK !");
                   // [self dataSending:@"Hello"];
                    [[SocketController getInstance] onConnectOk];
                    isConnected = true;
                }
                break;
                
            default:
                break;
        }

    } @catch (NSException *exception) {
        NSLog(@"%@",[exception reason]);
    }
}



-(void)sendMessage:(SenderParket *)packer{
    SenderParket* _packer = [[SenderParket alloc] init];

    if ([outputStream hasSpaceAvailable]){
        
//        NSString *response  = @"Hello World";
//        NSData *data = [[NSData alloc] initWithData:[response dataUsingEncoding:NSUTF8StringEncoding]];
//        [_packer.bytes appendData:data];
//
        @synchronized (_packer) {
             [outputStream write:[_packer.bytes bytes] maxLength:packer.length];
        }

    }else{
        NSLog(@"No space available");
    }


//    SenderParket* sender = [[SenderParket alloc] init];
//    
//    if ([outputStream hasSpaceAvailable]){
//        NSString *response  = @"Hello World";
//        NSData *data = [[NSData alloc] initWithData:[response dataUsingEncoding:NSUTF8StringEncoding]];
//        [sender.bytes appendData:data];
//        
//        @synchronized (sender) {
//            [outputStream write:[sender.bytes bytes] maxLength:[data length]];
//        }
//        
//    }else{
//        NSLog(@"No space available");
//    }

}

@end
