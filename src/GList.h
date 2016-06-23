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

class GListBase : public GObject {
    GX_GOBJECT(GListBase);
};

template <class T>
class GList : public GListBase {
    GX_GOBJECT(GList);
public:
    class Node {
        friend class GList;
    private:
        Node(T* obj) {
            GO::retain(obj);
            m_Obj=obj;
            m_Prev=NULL;
            m_Next=NULL;
        }
        ~Node() {
            GO::release(m_Obj);
        }
    public:
        T* getObj() {
            return m_Obj;
        }
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
        T*      m_Obj;
        Node*   m_Prev;
        Node*   m_Next;
    };
public:
    Node* add(T* v) {
        Node* p=new Node(v);
        if (m_NodeLast) {
            m_NodeLast->setNext(p);
            p->setPrev(m_NodeLast);
            m_NodeLast=p;
        }
        else {
            m_Node=p;
            m_NodeLast=p;
        }
        return p;
    }
    
    
private:
    Node* m_Node;
    Node* m_NodeLast;
};

GX_GOBJECT_TEMPLATE_IMPLEMENT(typename T, GList<T>, GListBase);

template <typename T>
GList<T>::GList()
{
    m_Node=NULL;
    m_NodeLast=NULL;
}
template <typename T>
GList<T>::~GList()
{
    Node* p=m_Node;
    while (p) {
        Node* next=p->getNext();
        delete p;
        p=next;
    }
}

#include "GXGObjectUD.h"

#endif /* GList_h */
