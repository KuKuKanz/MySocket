//
//  NativeIOS.cpp
//  HelloCpp
//
//  Created by Huy Phan Quoc on 3/13/14.
//
//

#include "NativeIOS.h"
#import "../Library/GoogleAnalyticIOS/GAI.h"
#import "../Library/GoogleAnalyticIOS/GAIDictionaryBuilder.h"
#import "../Library/GoogleAnalyticIOS/GAIFields.h"
#import <AudioToolbox/AudioToolbox.h>

#include "cocos2d.h"

USING_NS_CC;

NativeIOS::NativeIOS()
{
    
}

NativeIOS::~NativeIOS()
{
    
}

void NativeIOS::sendEventToGA(const char* category,const char* action,const char *text)
{
    id<GAITracker> tracker= [[GAI sharedInstance] defaultTracker];
    
    [tracker send:[[GAIDictionaryBuilder createEventWithCategory:[NSString stringWithUTF8String:category]     // Event category (required)
                                                          action:[NSString stringWithUTF8String:action]  // Event action (required)
                                                           label:[NSString stringWithUTF8String:text]          // Event label
                                                           value:nil] build]];    // Event value
}

void NativeIOS::sendSceneToGA(const char* sceneName)
{
    [[GAI sharedInstance].defaultTracker set:kGAIScreenName
                                       value:[NSString stringWithUTF8String:sceneName]];
    
    // Send the screen view.
    [[GAI sharedInstance].defaultTracker
     send:[[GAIDictionaryBuilder createAppView] build]];
        
}

void NativeIOS::callbackEndInAppPurcharse()
{
    NotificationCenter::getInstance()->postNotification(MSG_END_PURCHARSE);
}

void NativeIOS::callbackBeginInAppPurcharse()
{
    NotificationCenter::getInstance()->postNotification(MSG_BEGIN_PURCHARSE);
}

void NativeIOS::vibrate(){
	AudioServicesPlaySystemSound (kSystemSoundID_Vibrate);
}
