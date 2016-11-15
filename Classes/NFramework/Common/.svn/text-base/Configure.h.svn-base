//
//  Configure.h
//  HelloCpp
//
//  Created by Tri Truong Mai Thanh on 8/13/13.
//
//

#ifndef __HelloCpp__Configure__
#define __HelloCpp__Configure__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Configure
{
    CC_PROPERTY(bool, m_isound, Sound)
    CC_PROPERTY(bool, m_ivibrate, Vibrate)
    CC_PROPERTY(float, m_volume, Volume)
private:
    static Configure* s_instance;
    Configure();
public:
    static Configure* shareInstance();
};
#endif
