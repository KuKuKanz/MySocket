#ifndef __PHONE_HELPER__
#define __PHONE_HELPER__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;
USING_NS_CC;
using namespace std;
enum
{
	VIBRATE = 0,
	SMS = 1,
	CALL_PHONE = 2,
	VIDEO = 3,
    REGISTER_NOTIFI = 4,
};

class loginNativeDelegate{
public:
	virtual void receiveErrorDesc( std::string errDesc) = 0;
};

class PhoneHelper : public Node
{
public:
	static PhoneHelper *sharedInstace();
	PhoneHelper();
	~PhoneHelper();
	void vibrate(const char* timeVibrates);
	void smsTo(const char* number,const char* string);
	void callTo(const char* number);
    void openBrowser (std::string url);
    void openWebView (std::string url );
    void inviteFacebook ( );
    void getClientInfor ();
    void showMailHelper ();
    void showMailError(int error_code);
    void registerGCM();
    void requestInAppPurcharse(const char* productID);
    void closedWebView();
    void showToastNotVideo(const char* content);
    
    void setupNotifcation();
    
    
    void receiveWebLogin( Node *sender, Value data);
    void receiveClientInfor( Node *sender, Value data);
    
    void receiveCMDFormJNI(int _ID,const char* _str);
    void sendEventToGA(string category,string action,string text);
    void sendSceneToGA(string sceneName);
    void sendUserIdToGA(string userID);
	
	//Game Center
	void requestLoginGameCenter();
	void requestLogoutGooglePlus();
	void receiveInfoGameCenter( Node *sender, Value data);
	void receiveErrorGameCenter( Node *sender, Value data);
    
    // request Restore for iOS
    void requestRestoreIAP();
	
	//G+
	void requestLoginGooglePlus();
	void receiveGooglePlusInfo( Node *sender, Value data);
	void receiveErrorGooglePlus( Node *sender, Value data);
	
	void setLoginNativeDelegate(loginNativeDelegate *pDelegate){
		_ploginNativeDelegate = pDelegate;
	}
	
    // AppsFlyer
    void receiveAppsFlyer(Node* sender,Value data);
    
    void playVideoAds();
    
    void puchasingForIOS();
    bool isPurchasingForIOS();
    void setPurchasingForIOS(bool isPurchasing);
	
private:
	static PhoneHelper *instance;
	loginNativeDelegate *_ploginNativeDelegate;
};

#endif