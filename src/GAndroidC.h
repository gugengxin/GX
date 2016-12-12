//
// Created by Gu Gengxin on 2016/12/10.
//

#ifndef AS_GANDROIDC_H
#define AS_GANDROIDC_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)

#include "GJNI.h"

class GAndroidC : public  GJNI::Caller {
public:
    static GAndroidC* shared();
private:
    GAndroidC();
    ~GAndroidC();

    virtual void init(JNIEnv* jniEnv,const char* className);


private:
};




#endif

#endif //AS_GANDROIDC_H
