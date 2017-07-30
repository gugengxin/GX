//
//  GList.h
//  GX
//
//  Created by Gengxin Gu on 16/6/15.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GList_h
#define GList_h

#include "GXPrefix.h"
#include "GObject.h"

#include "GXGObject.h"

class GList : public GObject {
    GX_GOBJECT(GList);
public:
    class Node : GObject {
        friend class GList;
        GX_VIRTUAL_GOBJECT(Node);
    public:
        Node* getPrev() {
            return m_Prev;
        }
        Node* getNext() {
            return m_Next;
        }
    private:
        void setPrev(Node* v) {
            m_Prev=v;
        }
        void setNext(Node* v) {
            m_Next=v;
        }
    private:
        Node*   m_Prev;
        Node*   m_Next;
    };
public:
//    Node* add(Node* v) {
//        Node* p=new Node(v);
//        if (m_NodeLast) {
//            m_NodeLast->setNext(p);
//            p->setPrev(m_NodeLast);
//            m_NodeLast=p;
//        }
//        else {
//            m_Node=p;
//            m_NodeLast=p;
//        }
//        return p;
//    }
    
    
private:
    Node* m_Node;
    Node* m_NodeLast;
};



#include "GXGObjectUD.h"

#endif /* GList_h */
