//
//  GString.cpp
//  GX
//
//  Created by Gengxin Gu on 16/4/29.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GString.h"
#include <memory.h>


GX_OBJECT_IMPLEMENT(GString, GDataString<gchar>);


GString::GString()
{

}

GString::~GString()
{

}

/*
void GString::format(const gchar* fmt,va_list va)
{
    if (getLength()>0) {
        clear();
    }
    appendFormat(fmt, va);
}

void GString::format(const gchar* fmt,...)
{
    va_list va;
    va_start(va, fmt);
    format(fmt, va);
    va_end(va);
}
void GString::appendFormat(const gchar* fmt,va_list va)
{
    gint iLast=0;
    gint i=0;
    while (true) {
        if (fmt[i]=='\0') {
            if (iLast<i-1) {
                append(&fmt[iLast],i-iLast);
            }
            break;
        }
        else if (fmt[i]=='%') {
            if (iLast<i-1) {
                append(&fmt[iLast],i-iLast);
                iLast=i;
            }
            if (fmt[i+1]=='%') {
                append(&fmt[i],1);
                i+=2;
                iLast=i;
            }
            else {
                gint j=i+1;
                
                while (true) {
                    if (fmt[j]=='d') {
                        
                    }
                    else if(fmt[j]=='u') {
                        
                    }
                    else if(fmt[j]=='x') {
                        
                    }
                    else if(fmt[j]=='X') {
                        
                    }
                    else if(fmt[j]=='f') {
                        
                    }
                    else if(fmt[j]=='s') {
                        
                    }
                    else {
                        j++;
                    }
                }
                
            }
        }
        else {
            i++;
        }
    }
}
void GString::appendFormat(const gchar* fmt,...)
{
    va_list va;
    va_start(va, fmt);
    appendFormat(fmt, va);
    va_end(va);
}
//*/




