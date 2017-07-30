//
//  GList.cpp
//  GX
//
//  Created by Gengxin Gu on 16/6/15.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GList.h"


#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GList::Node, GObject);

GList::Node::Node()
{
    
}

GList::Node::~Node()
{
    
}





GX_GOBJECT_IMPLEMENT(GList, GObject);

GList::GList()
{
    m_Node=NULL;
    m_NodeLast=NULL;
}
GList::~GList()
{
    Node* p=m_Node;
    while (p) {
        Node* next=p->getNext();
        delete p;
        p=next;
    }
}
