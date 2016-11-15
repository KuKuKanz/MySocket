//
//  NDKHelper.h
//  EasyNDK-for-cocos2dx
//
//  Created by Amir Ali Jiwani on 23/02/2013.
//  Updated by Alfonso Cejudo March, 2014.
//
//

#ifndef __EasyNDK_for_cocos2dx__NDKHelper__
#define __EasyNDK_for_cocos2dx__NDKHelper__

#include <iostream>
#include "cocos2d.h"
#include <string>
#include <vector>
#include "jansson.h"
#include "NDKCallbackNode.h"

USING_NS_CC;
using namespace std;

class NDKHelper
{
public:
    static void addSelector(const char *groupName, const char *name, FuncNV selector, cocos2d::Node *target);
    static void printSelectorList();
    static void removeSelectorsInGroup(const char *groupName);
    
    static cocos2d::Value getValueFromJson(json_t *obj);
    static json_t *getJsonFromValue(cocos2d::Value value);
    
    static void handleMessage(json_t *methodName, json_t *methodParams);
    
private:
    static std::vector<NDKCallbackNode> selectorList;
    static void removeAtIndex(int index);
};

extern "C"
{
    void sendMessageWithParams(std::string methodName, cocos2d::Value methodParams);
    void sendMessageWithData(std::string methodName, void* data,int length);
}

#endif /* defined(__EasyNDK_for_cocos2dx__NDKHelper__) */
