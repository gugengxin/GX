//
// Created by Gengxin Gu on 2016/12/9.
//

#ifndef AS_GANDROID_H
#define AS_GANDROID_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)

#include "GJNI.h"

class GAndroid : public GJNI {
public:
    static GAndroid* shared();
private:
    GAndroid();
    ~GAndroid();





private:

};


#endif

#endif //AS_GANDROID_H
