//
//  GApplication.h
//  GX
//
//  Created by Gu Gengxin on 16/5/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GApplication_h
#define GApplication_h

#include "GXPrefix.h"


class GApplication {
public:
    class Delegate {
    public:

    };
public:
    static GApplication* shared();
    static void main(Delegate* dge);
private:
    GApplication();
    ~GApplication();
public:

private:
    Delegate* m_Delegate;
};



#endif /* GApplication_h */
