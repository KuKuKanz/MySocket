//
//  NativeIOS.h
//  HelloCpp
//
//  Created by Huy Phan Quoc on 3/13/14.
//
//

#ifndef __HelloCpp__NativeIOS__
#define __HelloCpp__NativeIOS__

#include <iostream>

class NativeIOS
{
public:
    NativeIOS();
    ~NativeIOS();
    static void sendEventToGA(const char* category,const char* action,const char *text);
    static void sendSceneToGA(const char* sceneName);
    static void callbackEndInAppPurcharse();
    static void callbackBeginInAppPurcharse();
	static void vibrate();
};

#endif /* defined(__HelloCpp__NativeIOS__) */
