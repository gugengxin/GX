//
//  GDataList.h
//  GX
//
//  Created by Gengxin Gu on 16/6/15.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GDataList_h
#define GDataList_h

#include "GXPrefix.h"
#include "GObject.h"


#include "GXGObject.h"

class GDataListBase : public GObject {
    GX_GOBJECT(GDataListBase);
};


template <typename T>
class GDataList : public GDataListBase {
    friend class GContext;
    GX_GOBJECT(GDataList);
public:
    class Node {
        friend class GDataList;
    public:
        Node() {
            m_Prev=NULL;
            m_Next=NULL;
        }
        virtual ~Node() {
            
        }
        
        T& getData() {
            return m_Data;
        }
        void setData(const T& v) {
            m_Data=v;
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
        T m_Data;
        Node* m_Prev;
        Node* m_Next;
    };
public:
    Node* add(const T& v) {
        Node* p=new Node();
        p->setData(v);
        add(p);
        return p;
    }
    void add(Node* p) {
        if (m_NodeLast) {
            m_NodeLast->setNext(p);
            p->setPrev(m_NodeLast);
            m_NodeLast=p;
        }
        else {
            m_Node=p;
            m_NodeLast=p;
        }
    }
    void remove(Node* p,bool bDel=true) {
        Node* pNext=p->getNext();
        Node* pPrev=p->getPrev();

        if (pNext) {
            pNext->setPrev(pPrev);
        }
        if (pPrev) {
            pPrev->setNext(pNext);
        }

        if (bDel) {
            delete p;
        }
        else {
            p->setNext(NULL);
            p->setPrev(NULL);
        }

        if (m_NodeLast==p) {
            if (pNext) {
                m_NodeLast=pNext;
            }
            else {
                m_NodeLast=pPrev;
            }
        }
        if (m_Node==p) {
            if (pPrev) {
                m_Node=pPrev;
            }
            else {
                m_Node=pNext;
            }
        }
    }

    Node* first() const {
        return m_Node;
    }
    Node* last() const {
        return m_NodeLast;
    }
    
    
private:
    Node* m_Node;
    Node* m_NodeLast;
};

GX_GOBJECT_TEMPLATE_IMPLEMENT(typename T, GDataList<T>, GDataListBase);

template <typename T>
GDataList<T>::GDataList()
{
    m_Node=NULL;
    m_NodeLast=NULL;
}
template <typename T>
GDataList<T>::~GDataList()
{
    Node* p=m_Node;
    while (p) {
        Node* next=p->getNext();
        delete p;
        p=next;
    }
}

#include "GXGObjectUD.h"

#endif /* GDataList_h */
