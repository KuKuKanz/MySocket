#include "PhoneHelper.h"

#include "../Common/Configure.h"
#include "../../Global/Global.h"
#include "../../Network/SocketAdapter/NetworkController.h"
#include "PluginGoogleAnalytics/PluginGoogleAnalytics.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "../NDKHelper/NDKHelper.h"
#include "NativeIOS.h"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "NativeHelper.h"
#include "../NDKHelper/NDKHelper.h"
#endif

using namespace SonarCocosHelper;

PhoneHelper *PhoneHelper::instance=NULL;

PhoneHelper *PhoneHelper::sharedInstace()
{
    if(instance==NULL)
        instance=new PhoneHelper();
    return instance;
}

PhoneHelper::PhoneHelper()
{
    retain();
    _ploginNativeDelegate = NULL;
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#ifdef DEBUG
    CCLOG("REGISTER NDK");
#endif
    NDKHelper::addSelector("PhoneHelper","receiveWebLogin",CC_CALLBACK_2(PhoneHelper::receiveWebLogin, this),this);
    
    NDKHelper::addSelector("PhoneHelper","receiveClientInfor",CC_CALLBACK_2(PhoneHelper::receiveClientInfor, this),this);
    
    NDKHelper::addSelector("PhoneHelper","receiveInfoGameCenter",CC_CALLBACK_2(PhoneHelper::receiveInfoGameCenter, this),this);
    
    NDKHelper::addSelector("PhoneHelper","receiveGooglePlusInfo",CC_CALLBACK_2(PhoneHelper::receiveGooglePlusInfo, this),this);
    
    NDKHelper::addSelector("PhoneHelper","receiveErrorGameCenter",CC_CALLBACK_2(PhoneHelper::receiveErrorGameCenter, this),this);
    
    NDKHelper::addSelector("PhoneHelper","receiveErrorGooglePlus",CC_CALLBACK_2(PhoneHelper::receiveErrorGooglePlus, this),this);
    
    NDKHelper::addSelector("PhoneHelper","receiveAppsFlyer",CC_CALLBACK_2(PhoneHelper::receiveAppsFlyer, this),this);
    
    
#endif // CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
}

PhoneHelper::~PhoneHelper()
{
    
}

void PhoneHelper::vibrate(const char* timeVibrates)
{
    if(!Configure::shareInstance()->getVibrate())
        return;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sendCMDToAndroid(VIBRATE,timeVibrates,"");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    NativeIOS::vibrate();
#endif // CC_PLATFORM_ANDROID
    
}

void PhoneHelper::showToastNotVideo(const char* content)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sendCMDToAndroid(VIDEO,0,content);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //NativeIOS::vibrate();
#endif
}

void PhoneHelper::smsTo(const char* _number,const char* _string)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sendCMDToAndroid(SMS,_number,_string);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    ValueMap valueMap;
    valueMap["sms_Address"] = _number;
    valueMap["phone_Number"] = _string;
    
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("SMSHelper"), parameters);
#endif // CC_PLATFORM_ANDROID
    
}

void PhoneHelper::callTo(const char* _number)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sendCMDToAndroid(CALL_PHONE,_number,"");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    ValueMap valueMap;
    valueMap["phone_number"] = _number;
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("CallHelper"), parameters);
#endif // CC_PLATFORM_ANDROID
    
}

void PhoneHelper::registerGCM()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sendCMDToAndroid(REGISTER_NOTIFI,"","");
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
#endif // CC_PLATFORM_ANDROID
}

void PhoneHelper::showMailHelper(){
    ValueMap valueMap;
    
    valueMap["_to"] = "hotro.nplay@gmail.com";
    valueMap["_sub"] = "Yêu cầu hỗ trợ đến NPlay..";
    
    string _content = "";
    if(LoginController::shareLoginController()->getIsLoggedIn()==true){
        _content = StringUtils::format("Version %s [%s]\nVui lòng điền thông tin theo mẫu dưới đây để chúng tôi có thể trợ giúp bạn 1 cách nhanh nhất:\nSố điện thoại: ....\nDiễn giải tình huống cần trợ giúp : .... \n\n\nModel Device: %s\nSoftware Version: %s",
                                       GameController::shareInstance()->getClientInfor()->version().c_str(),
                                       GameController::shareInstance()->getDisplayname().c_str(),
                                       GameController::shareInstance()->getClientInfor()->model_device().c_str(),
                                       GameController::shareInstance()->getClientInfor()->software_device().c_str());
    }else{
        _content = StringUtils::format("Version %s \nVui lòng điền thông tin theo mẫu dưới đây để chúng tôi có thể trợ giúp bạn 1 cách nhanh nhất:\nSố điện thoại: ....\nTên hiển thị của bạn là gì : ....\nDiễn giải tình huống cần trợ giúp : ....\n\n\nModel Device: %s\nSoftware Version: %s",
                                       GameController::shareInstance()->getClientInfor()->version().c_str(),
                                       GameController::shareInstance()->getClientInfor()->model_device().c_str(),
                                       GameController::shareInstance()->getClientInfor()->software_device().c_str());
    }
    valueMap["_content"] = _content;
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("MailHelper"), parameters);
}

void PhoneHelper::showMailError(int error_code)
{
    ValueMap valueMap;
    
    valueMap["_to"] = "hotro.nplay@gmail.com";
    valueMap["_sub"] = "Yêu cầu hỗ trợ đến NPlay..";
    
    string _content = "";
    
    _content = StringUtils::format("Version %s [%s]\nError Code:%d\n----------- \nVui lòng điền thông tin theo mẫu dưới đây để chúng tôi có thể trợ giúp bạn 1 cách nhanh nhất.\nTên: ....\nSố điện thoại: ....\nDiễn giải tình huống cần trợ giúp : .... \n\n\nModel Device: %s\nSoftware Version: %s",
                                       GameController::shareInstance()->getClientInfor()->version().c_str(),
                                       GameController::shareInstance()->getDisplayname().c_str(),
                                        error_code,
                                       GameController::shareInstance()->getClientInfor()->model_device().c_str(),
                                       GameController::shareInstance()->getClientInfor()->software_device().c_str());
    
    valueMap["_content"] = _content;
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("MailHelper"), parameters);
}


void PhoneHelper::requestInAppPurcharse(const char* productID)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
    ValueMap valueMap;
    valueMap["productID"] = productID;
    valueMap["isUpdatePayment"] = GlobalService::getUpdatePayment();
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("requestProductID"), parameters);
#endif
}

void PhoneHelper::openBrowser (std::string url)
{
    ValueMap valueMap;
    valueMap["url"] = url;
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("openBrowser"), parameters);
}

void PhoneHelper::openWebView (std::string url)
{
    ValueMap valueMap;
    valueMap["url"] = url;
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("openWebview"), parameters);
}


void PhoneHelper::setupNotifcation()
{
    ValueMap valueMap;
    valueMap["setupNotifcation"] = "setupNotifcation";
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("setupNotification"), parameters);
}

void PhoneHelper::inviteFacebook ( )
{
    ValueMap valueMap;
    valueMap["inviteFacebook"] = "inviteFacebook";
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("inviteFriendFb"), parameters);
}


void  PhoneHelper::closedWebView() {
    ValueMap valueMap;
    valueMap["closedWebView"] = "closedWebView";
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("closedWebView"), parameters);
}

void PhoneHelper::getClientInfor ()
{
    ValueMap valueMap;
    valueMap["getClientInfor"] = "getClientInfor";
    Value parameters = Value(valueMap);

    sendMessageWithParams(string("getClientInfor"), parameters);
}

void PhoneHelper::receiveWebLogin(Node *sender, Value data)
{
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        ValueMap valueMap = data.asValueMap();
        
        string code = valueMap["code"].asString();
        if( strcmp("code", "1")){
            string token = valueMap["token"].asString();
#ifdef DEBUG
            CCLOG("PhoneHelper :  token: %s",token.c_str());
#endif
            GameController::shareInstance()->setToken( token );
            GameController::shareInstance()->setisLogouted(false);
            
            LoginController::shareLoginController()->loginNCT(GlobalService::getIP().c_str(), GlobalService::getPort(), token.c_str());
        }
    }
}

void PhoneHelper::receiveClientInfor( Node *sender, Value data)
{
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        ValueMap valueMap = data.asValueMap();
        
        string deviceID = valueMap["deviceid"].asString();
        string version = valueMap["version"].asString();
        string model = valueMap["model"].asString();
        string os = valueMap["os"].asString();
        string osversion = valueMap["osversion"].asString();
        string bundleID = valueMap["bundleID"].asString();
        string temp = StringUtils::format("%s-%s", os.c_str() , osversion.c_str());
        string modelDevice = valueMap["modelDevice"].asString();
        string sofwareVersion = valueMap["softwareVersion"].asString();
        string mediaSource = valueMap["mediaSource"].asString();
        string campaign = valueMap["campaign"].asString();
        
        GameController::shareInstance()->getClientInfor()->set_device( deviceID );
        GameController::shareInstance()->getClientInfor()->set_version( version );
        GameController::shareInstance()->getClientInfor()->set_model( model );
        GameController::shareInstance()->getClientInfor()->set_os( temp );
        GameController::shareInstance()->getClientInfor()->set_bundleid( bundleID );
        GameController::shareInstance()->getClientInfor()->set_model_device( modelDevice );
        GameController::shareInstance()->getClientInfor()->set_software_device( sofwareVersion );
        
        GameController::shareInstance()->setHasClientInfor(true);
    }
}

void PhoneHelper::receiveAppsFlyer(cocos2d::Node *sender, cocos2d::Value data)
{
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        ValueMap valueMap = data.asValueMap();
        
        string mediaSource = valueMap["mediaSource"].asString();
        string campaign = valueMap["campaign"].asString();
        
        GameController::shareInstance()->setMediaSource(mediaSource);
        GameController::shareInstance()->setCampaign(campaign);
        
        //send appsFlyer-info to server if login success
        if(LoginController::shareLoginController()->getIsLoggedIn()){
            GameController::shareInstance()->requestAppFyer(campaign, mediaSource);
        }
    }
}

void PhoneHelper::receiveCMDFormJNI(int _ID,const char* _str)
{
    switch(_ID)
    {
        case REGISTER_NOTIFI:
        {
#ifdef DEBUG
            CCLOG("PhoneHelper::receiveCMDFormJNI REGISTER_NOTIFI : %s",_str);
#endif
            
            UserDefault::getInstance()->setStringForKey("DeviceToken",_str);
            LoginController::shareLoginController()->setDeviceToken(_str);
        }
            break;
    }
}

void PhoneHelper::puchasingForIOS()
{
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    setPurchasingForIOS(true);
#endif
    
}

bool PhoneHelper::isPurchasingForIOS()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    return UserDefault::getInstance()->getBoolForKey("isPurchasingIOS", false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    return false;
#endif
}

void PhoneHelper::setPurchasingForIOS(bool isPurchasing)
{
    UserDefault::getInstance()->setBoolForKey("isPurchasingIOS", isPurchasing);
}

void PhoneHelper::sendEventToGA( string category, string action, string text)
{
    SonarCocosHelper::GoogleAnalytics::sendEvent(category, action, text, 0);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //NativeIOS::sendEventToGA(category.c_str() , action.c_str() , text.c_str() );
    
//    sdkbox::PluginGoogleAnalytics::logEvent(category.c_str() , action.c_str() , text.c_str(), 1);
//    sdkbox::PluginGoogleAnalytics::dispatchHits();
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //sendEventoGAAndroid(category.c_str() ,action.c_str() , text.c_str() );
#endif

}

void PhoneHelper::sendSceneToGA( string sceneName)
{
    SonarCocosHelper::GoogleAnalytics::setScreenName(sceneName);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //NativeIOS::sendSceneToGA(sceneName.c_str());
    
//    sdkbox::PluginGoogleAnalytics::logScreen(sceneName);
//    sdkbox::PluginGoogleAnalytics::dispatchHits();
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    //sendSceneToGAAndroid(sceneName.c_str());
#endif

}

void PhoneHelper::sendUserIdToGA(string userID)
{
   // sdkbox::PluginGoogleAnalytics::setUser(userID);
}

void PhoneHelper::requestLoginGameCenter() {
    ValueMap valueMap;
    valueMap["requestLoginGameCenter"] = "requestLoginGameCenter";
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("requestLoginGameCenter"), parameters);
}

void PhoneHelper::requestRestoreIAP()
{
//    if(!isPurchasingForIOS()) return;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    ValueMap valueMap;
    valueMap["requestRestoreIAP"] = "requestRestoreIAP";
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("requestRestoreIAP"), parameters);
#endif
    
    setPurchasingForIOS(false);
}

void PhoneHelper::receiveInfoGameCenter( Node *sender, Value data){
    
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        ValueMap valueMap = data.asValueMap();
        
        string playID = valueMap["GC_playerID"].asString();
        string displayName = valueMap["GC_displayName"].asString();
        const char* token = UserDefault::getInstance()->getStringForKey("DeviceToken").c_str();
        
        LoginController::shareLoginController()->loginGameNative(GlobalService::getIP().c_str(), GlobalService::getPort(), playID, displayName, "", "gamecenter", token , "" , "");
        PhoneHelper::sharedInstace()->sendEventToGA("Login Flow", "Game Center", "receive info form GameCenter");
    }
    
}

void PhoneHelper::receiveErrorGameCenter( Node *sender, Value data){
    
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        ValueMap valueMap = data.asValueMap();
        
        string errDesc = valueMap["err_description"].asString();
        
        if( _ploginNativeDelegate != NULL )
            _ploginNativeDelegate->receiveErrorDesc( errDesc );
    }
}

void PhoneHelper::requestLoginGooglePlus() {
#ifdef DEBUG
    CCLOG("PhoneHelper::requestLoginGooglePlus()");
#endif
    ValueMap valueMap;
    valueMap["requestLoginGooglePlus"] = "requestLoginGooglePlus";
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("requestLoginGooglePlus"), parameters);
}

void PhoneHelper::requestLogoutGooglePlus() {
#ifdef DEBUG
    CCLOG("PhoneHelper::requestLogoutGooglePlus()");
#endif
    ValueMap valueMap;
    valueMap["requestLogoutGooglePlus"] = "requestLogoutGooglePlus";
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("requestLogoutGooglePlus"), parameters);
}

void PhoneHelper::receiveGooglePlusInfo( Node *sender, Value data){
    
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        ValueMap valueMap = data.asValueMap();
        string profileID = valueMap["profileID"].asString();
        string displayName = valueMap["displayName"].asString();
        string photoUrl = valueMap["photoUrl"].asString();
        string email = valueMap["email"].asString();
        string gender = valueMap["gender"].asString();
        
        const char* token = UserDefault::getInstance()->getStringForKey("DeviceToken").c_str();
        
        LoginController::shareLoginController()->loginGameNative(GlobalService::getIP().c_str(), GlobalService::getPort(), profileID , displayName, photoUrl , "google", token , email , gender);
        PhoneHelper::sharedInstace()->sendEventToGA("Login Flow", "Goolge Plus", "receive info form G+");
    }
    
}

void PhoneHelper::receiveErrorGooglePlus( Node *sender, Value data){
    if (!data.isNull() && data.getType() == Value::Type::MAP) {
        ValueMap valueMap = data.asValueMap();
        string errDesc = valueMap["err_description"].asString();
        if( _ploginNativeDelegate != NULL )
            _ploginNativeDelegate->receiveErrorDesc( errDesc);
    }
}

void  PhoneHelper::playVideoAds() {
    ValueMap valueMap;
    valueMap["playVideoAds"] = "playVideoAds";
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("playVideoAds"), parameters);
}
