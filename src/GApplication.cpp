//
//  GApplication.cpp
//  GX
//
//  Created by Gu Gengxin on 16/5/1.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GApplication.h"


GApplication* GApplication::shared()
{
    static GApplication g_Obj;
    return &g_Obj;
}

void GApplication::main(Delegate* dge)
{

}


GApplication::GApplication()
{
    m_Delegate=NULL;
}

GApplication::~GApplication()
{

}



