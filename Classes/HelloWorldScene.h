#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "NDKHelper.h"
#include <ui/CocosGUI.h>

using namespace cocos2d;
using namespace cocos2d::ui;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    static HelloWorld* getInstance();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    Text* _label;
    
    
    void callBackTouchBtn(Ref* pSender, Widget::TouchEventType _type);
    void connect(string ip, int port);
    void onConnectOk();

};

#endif // __HELLOWORLD_SCENE_H__
