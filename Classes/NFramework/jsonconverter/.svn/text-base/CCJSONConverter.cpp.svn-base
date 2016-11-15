//
//  CCJSONConverter.cpp
//  cocos2d-x-jc
//
//  Created by LIN BOYU on 11/14/12.
//
//

#include "CCJSONConverter.h"

static CCJSONConverter _sharedConverter;

CCJSONConverter * CCJSONConverter::sharedConverter()
{
    static bool firstUse = true;
    if (firstUse)
    {
        firstUse = false;
    }
    return &_sharedConverter;
}

char * CCJSONConverter::strFrom( __Dictionary *dictionary)
{
    CCAssert(dictionary, "CCJSONConverter:can not convert a null pointer");
    cJSON * json = cJSON_CreateObject();
    convertDictionaryToJson(dictionary, json);
    char* jsonString = cJSON_Print(json);
    cJSON_Delete(json);
    return jsonString;
}

__Dictionary * CCJSONConverter::dictionaryFrom(const char *str)
{
    cJSON * json = cJSON_Parse(str);
    CCAssert(json && json->type==cJSON_Object, "CCJSONConverter:wrong json format");
    __Dictionary * dictionary = CCDictionary::create();
    convertJsonToDictionary(json, dictionary);
    cJSON_Delete(json);
    return dictionary;
}

void CCJSONConverter::convertJsonToDictionary(cJSON *json, __Dictionary *dictionary)
{
    dictionary->removeAllObjects();
    cJSON * j = json->child;
    while (j) {
        Ref * obj = getJsonObj(j);
        dictionary->setObject(obj, j->string);
        j = j->next;
    }
}

void CCJSONConverter::convertDictionaryToJson( __Dictionary *dictionary, cJSON *json)
{
    DictElement * pElement = NULL;
    CCDICT_FOREACH(dictionary, pElement){
        Ref * obj = pElement->getObject();
        cJSON * jsonItem = getObjJson(obj);
        cJSON_AddItemToObject(json, pElement->getStrKey(), jsonItem);
    }
}

void CCJSONConverter::convertJsonToArray(cJSON * json, __Array * array)
{
    array->removeAllObjects();
    int size = cJSON_GetArraySize(json);
    for (int i=0; i<size; i++) {
        cJSON * jsonItem = cJSON_GetArrayItem(json, i);
        Ref * objItem = getJsonObj(jsonItem);
        array->addObject(objItem);
    }
}

void CCJSONConverter::convertArrayToJson( __Array * array, cJSON * json)
{
    Ref * obj = NULL;
    CCARRAY_FOREACH(array, obj){
        cJSON * jsonItem = getObjJson(obj);
        cJSON_AddItemToArray(json, jsonItem);
    }
}

cJSON * CCJSONConverter::getObjJson( Ref * obj)
{
    std::string s = typeid(*obj).name();
    if(s.find("CCDictionary")!=std::string::npos){
        cJSON * json = cJSON_CreateObject();
        convertDictionaryToJson((__Dictionary *)obj, json);
        return json;
    }else if(s.find("CCArray")!=std::string::npos){
        cJSON * json = cJSON_CreateArray();
        convertArrayToJson(( __Array *)obj, json);
        return json;
    }else if(s.find("CCString")!=std::string::npos){
        __String * s = (__String *)obj;
        cJSON * json = cJSON_CreateString(s->getCString());
        return json;
    }else if(s.find("CCNumber")!=std::string::npos){
        CCNumber * n = (CCNumber *)obj;
        cJSON * json = cJSON_CreateNumber(n->getDoubleValue());
        return json;
    }else if(s.find("CCBool")!=std::string::npos){
        __Bool * b = (__Bool *)obj;
        cJSON * json;
        if (b->getValue()) {
            json = cJSON_CreateTrue();
        }else{
            json = cJSON_CreateFalse();
        }
        return json;
    }else if(s.find("CCNull")!=std::string::npos){
        cJSON * json = cJSON_CreateNull();
        return json;
    }
    CCLOG("CCJSONConverter encountered an unrecognized type");
    return NULL;
}

Ref * CCJSONConverter::getJsonObj(cJSON * json)
{
    switch (json->type) {
        case cJSON_Object:
        {
            __Dictionary * dictionary = __Dictionary::create();
            convertJsonToDictionary(json, dictionary);
            return dictionary;
        }
        case cJSON_Array:
        {
            __Array * array = __Array::create();
            convertJsonToArray(json, array);
            return array;
        }
        case cJSON_String:
        {
            __String * string = __String::create(json->valuestring);
            return string;
        }
        case cJSON_Number:
        {
            CCNumber * number = CCNumber::create(json->valuedouble);
            return number;
        }
        case cJSON_True:
        {
            __Bool * boolean = __Bool::create(true);
            return boolean;
        }
        case cJSON_False:
        {
            __Bool * boolean = __Bool::create(false);
            return boolean;
        }
        case cJSON_NULL:
        {
            CCNull * null = CCNull::create();
            return null;
        }
        default:
        {
            CCLOG("CCJSONConverter encountered an unrecognized type");
            return NULL;
        }
    }
}
