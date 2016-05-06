//
// Created by Gengxin Gu on 16/5/5.
//

#ifndef AS_GJAVACLASS_H
#define AS_GJAVACLASS_H

#include "GXPrefix.h"
#if defined(GX_OS_ANDROID)

#include <jni.h>

namespace GX {
    extern jclass JavaFindClass(JNIEnv* jniEnv,const char* name);
}

template <int N>
class GJavaClass {
public:
    GJavaClass() {
        m_Class=0;
        for(int i=0;i<N;i++) {
            m_Methods[i]=0;
        }
    }
    ~GJavaClass() {
    }

    inline jclass getClass() {
        return m_Class;
    }
    void setClass(JNIEnv* jniEnv,const char* name) {
        jclass tmp=GX::JavaFindClass(jniEnv,name);
        GX_ASSERT(tmp);
        m_Class=(jclass)jniEnv->NewGlobalRef(tmp);
        jniEnv->DeleteLocalRef(tmp);
    }

    inline jmethodID getMethod(gint idx) {
        return m_Methods[idx];
    }
    void setMethod(JNIEnv* jniEnv,gint idx,const char* name,const char* sig,bool isStatic)
    {
        if(isStatic) {
            m_Methods[idx]=jniEnv->GetStaticMethodID(m_Class,name,sig);
        }
        else {
            m_Methods[idx]=jniEnv->GetMethodID(m_Class,name,sig);
        }
        GX_ASSERT(m_Methods[idx]);
    }

    void callStaticVoidMethod(JNIEnv* jniEnv,gint idx,...)
    {
        va_list args;
        va_start(args, idx);
        jniEnv->CallStaticVoidMethodV(m_Class, getMethod(idx), args);
        va_end(args);
    }
    jobject callStaticObjectMethod(JNIEnv* jniEnv,gint idx,...)
    {
        va_list args;
        jobject result;
        va_start(args, idx);
        result = jniEnv->CallStaticObjectMethodV(m_Class, getMethod(idx), args);
        va_end(args);
        return result;
    }
    jbyte	callStaticByteMethod(JNIEnv* jniEnv,gint idx,...)
    {
        va_list args;
        jbyte result;
        va_start(args, idx);
        result = jniEnv->CallStaticByteMethodV(m_Class, getMethod(idx), args);
        va_end(args);
        return result;
    }
    jfloat	callStaticFloatMethod(JNIEnv* jniEnv,gint idx,...)
    {
        va_list args;
        jfloat result;
        va_start(args, idx);
        result = jniEnv->CallStaticFloatMethodV(m_Class, getMethod(idx), args);
        va_end(args);
        return result;
    }


    void callVoidMethod(JNIEnv* jniEnv,jobject obj,gint idx,...)
    {
        va_list args;
        va_start(args, idx);
        jniEnv->CallVoidMethodV(obj, getMethod(idx), args);
        va_end(args);
    }
    jobject callObjectMethod(JNIEnv* jniEnv,jobject obj,gint idx,...)
    {
        va_list args;
        jobject result;
        va_start(args, idx);
        result = jniEnv->CallObjectMethodV(obj, getMethod(idx), args);
        va_end(args);
        return result;
    }
    jint 	callIntMethod(JNIEnv* jniEnv,jobject obj,gint idx,...)
    {
        va_list args;
        int result;
        va_start(args, idx);
        result = jniEnv->CallIntMethodV(obj,getMethod(idx),args);
        va_end(args);
        return result;
    }
private:
    jclass 		m_Class;
    jmethodID	m_Methods[N];
};

#endif

#endif //AS_GJAVACLASS_H
