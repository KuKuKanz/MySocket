#ifndef __NATIVE_HELPER_H__
#define __NATIVE_HELPER_H__

#include "cocos2d.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "jni/JniHelper.h"
#define CLASSNAME "org/cocos2dx/hellocpp/Cocos2dxNativeHelper"
extern "C"{
	void sendCMDToAndroid(int CMD,const char* number,const char* string);
    void sendBytes(unsigned char* data,int length);
    void sendEventoGAAndroid(const char* category,const char* action,const char* text);
    void sendSceneToGAAndroid(const char* sceneName);
    void Java_org_cocos2dx_hellocpp_Cocos2dxNativeHelper_jniReceiveCMD(JNIEnv *env, jobject thisObj,jint _ID,jstring _str);
    void Java_org_cocos2dx_hellocpp_Cocos2dxNativeHelper_jniReceiMsg(JNIEnv *env,jobject thisObj,jbyteArray data);
    
    //network
    void Java_org_cocos2dx_hellocpp_Cocos2dxNativeHelper_jniOnDisconnect(JNIEnv *env, jobject thisObj);
    void Java_org_cocos2dx_hellocpp_Cocos2dxNativeHelper_jniOnConnectOK(JNIEnv *env, jobject thisObj);
    void Java_org_cocos2dx_hellocpp_Cocos2dxNativeHelper_jniOnConnectConnectFail(JNIEnv *env, jobject thisObj);
    void Java_org_cocos2dx_hellocpp_Cocos2dxNativeHelper_jniOnNetworkStatus(JNIEnv *env, jobject thisObj, jboolean status);
    
    // video ads
    void Java_org_cocos2dx_hellocpp_Cocos2dxNativeHelper_rewardedVideoWasViewedAdcolony(JNIEnv *env, jobject thisObj);
    void Java_org_cocos2dx_hellocpp_Cocos2dxNativeHelper_videoNotAvailable(JNIEnv *env, jobject thisObj);
    void Java_org_cocos2dx_hellocpp_Cocos2dxNativeHelper_rewardedVideoWasViewedVungle(JNIEnv *env, jobject thisObj);
    
}
#endif // CCPLATFORM


#endif