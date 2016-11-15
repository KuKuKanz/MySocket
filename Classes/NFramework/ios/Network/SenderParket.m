//
//  SenderParket.m
//  SocketTest
//
//  Created by DanhPhan on 4/8/14.
//  Copyright (c) 2014 DanhPhan. All rights reserved.
//

#import "SenderParket.h"

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
