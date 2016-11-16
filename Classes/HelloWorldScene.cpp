#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "NDKHelper.h"

USING_NS_CC;

using namespace cocostudio::timeline;


static HelloWorld* ROOT = NULL;


HelloWorld* HelloWorld::getInstance(){
    if (ROOT == NULL){
        ROOT = HelloWorld::create();
    }
    
    return ROOT;
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::getInstance();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    std::string _z = "hello";

    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    _label = rootNode->getChildByTag<Text*>(1);
    auto _button = (Button*)rootNode->getChildByTag(3);
    auto _buttonSend = (Button*)rootNode->getChildByTag(6);
    
    _txtField = (TextField*)rootNode->getChildByTag(4);
    _txtField->addEventListener(CC_CALLBACK_2(HelloWorld::callBackTextField, this));


    _label->setString("");
    
    _button->addTouchEventListener(CC_CALLBACK_2(HelloWorld::callBackTouchBtn, this));
    _buttonSend->addTouchEventListener(CC_CALLBACK_2(HelloWorld::callBackTouchBtn, this));

    addChild(rootNode);
    return true;
}


void HelloWorld::callBackTouchBtn(cocos2d::Ref *pSender, Widget::TouchEventType _type){
    
    switch (_type) {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
        {
            auto _btn = static_cast<Button*>(pSender);
            if (_btn->getTag() == 3){
                connect("localhost",8888);
                _btn->setTouchEnabled(false);
                
                _label->setString("Conneting to server...");
            }else if (_btn->getTag() == 6){
                sendMessage(_txtField->getString());
                _txtField->setString("");
            }
            break;
        }
            
        default:
            break;
    }
}

void HelloWorld::callBackTextField(cocos2d::Ref *pSender, TextField::EventType _type){
    switch (_type) {
        case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
        {
            _txtField->runAction(ScaleTo::create(0.5, 1.2));
        }
            break;
            
        case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
        {
            _txtField->runAction(ScaleTo::create(0.5, 1));
        }
            break;
            
        case cocos2d::ui::TextField::EventType::INSERT_TEXT:
            
            break;
            
        case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
            
            break;
            
        default:
            break;
    }
}

void HelloWorld::connect(string ip, int port){
    
    ValueMap valueMap;
    valueMap["myIP"] = ip;
    valueMap["myPort"] = port;
    Value parameters = Value(valueMap);
    
    // Send connect method to RootViewController class in order to connect to server
    sendMessageWithParams(string("connect"), parameters);
}

void HelloWorld::sendMessage(string s){
    ValueMap valueMap;
    valueMap["msg"] = s;
    Value parameters = Value(valueMap);
    
    sendMessageWithParams(string("sendMessageData"), parameters);
}

void HelloWorld::onConnectOk(){
    _label->setString("Connected successfully !");
}
























