//
//  SenderPacker.m
//  MySocket
//
//  Created by Dao Hoang Tung on 11/15/16.
//
//

#import "SenderPacker.h"

@implementation SenderParket

@synthesize bytes,length;

-(id)init {
    if(self=[super init]) {
        bytes = [[NSMutableData alloc] init];
        length = 0;
    }
    return self;
}

@end
