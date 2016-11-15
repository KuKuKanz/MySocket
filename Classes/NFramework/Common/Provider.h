//
//  Provider.h
//  HelloCpp
//
//  Created by Tri Truong Mai Thanh on 8/15/13.
//
//

#ifndef __HelloCpp__Provider__
#define __HelloCpp__Provider__

#include <iostream>

class Provider
{
private:
    static int s_ID;
public:
    static int getID ();
};

#endif