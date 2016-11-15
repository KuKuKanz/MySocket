//
//  Configure.cpp
//  HelloCpp
//
//  Created by Tri Truong Mai Thanh on 8/13/13.
//
//

#include "Configure.h"
#include "extensions/cocos-ext.h"
#include "SimpleAudioEngine.h"

USING_NS_CC_EXT;

Configure* Configure::s_instance = NULL;

Configure* Configure::shareInstance()
{
    if (s_instance==NULL) {
        s_instance = new Configure();
    }
    return s_instance;
}

Configure::Configure()
{
    m_isound = UserDefault::getInstance()->getBoolForKey("iSound", true);
    m_volume = UserDefault::getInstance()->getFloatForKey("Volume", 1);
    m_ivibrate = UserDefault::getInstance()->getBoolForKey("iVibrate", true);
    
    setSound(m_isound);
    setVibrate(m_ivibrate);
}

void Configure::setSound(bool var)
{
    m_isound = var;
    UserDefault::getInstance()->setBoolForKey("iSound", m_isound);
    if (m_isound) {
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(m_volume);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(m_volume);
        
    }else{
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0);
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(0);
        CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects();
    }
}

bool Configure::getSound()
{
    return  m_isound;
}

void Configure::setVibrate(bool var)
{
    m_ivibrate = var;
    UserDefault::getInstance()->setBoolForKey("iVibrate", m_ivibrate);
}


bool Configure::getVibrate()
{
    return m_ivibrate;
}

void Configure::setVolume(float var)
{
    m_volume = var;
    UserDefault::getInstance()->setFloatForKey("Volume", m_volume);
}

float Configure::getVolume()
{
    return m_volume;
}