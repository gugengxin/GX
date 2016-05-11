//
//  GMap.h
//  GX
//
//  Created by Gengxin Gu on 16/4/29.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GMap_h
#define GMap_h

#include "GXPrefix.h"
#include "GDataArray.h"
#include "GArray.h"


class GMapBase : public GObject {
    GX_OBJECT(GMapBase);
public:
    static const gint capabilitys[];
};


template <typename K,typename O>
class GMap : public GMapBase {
	friend class GNoticeCenter;
    GX_OBJECT(GMap);
private:
    class Node {
    public:
        Node(K* key,O* obj) {
            m_Key=key;
            m_Obj=obj;
            m_Next=NULL;
        }
        ~Node() {
            GO::release(m_Key);
            GO::release(m_Obj);
        }
        inline K* getKey() {
            return m_Key;
        }
        inline void setKey(K* v) {
            GO::retain(v);
            GO::release(m_Key);
            m_Key=v;
        }
        inline O* getObj() {
            return m_Obj;
        }
        inline void setObj(O* v) {
            GO::retain(v);
            GO::release(m_Obj);
            m_Obj=v;
        }
        inline Node* getNext() {
            return m_Next;
        }
        inline void setNext(Node* v) {
            m_Next=v;
        }
    private:
        K* m_Key;
        O* m_Obj;
        Node* m_Next;
    };
public:
    void set(K* key,O* obj) {
        if (m_ObjCount>=m_ObjArray.getCount()*2) {
            increaseCapability(m_ObjArray.getCount());
        }
        
        gint idx=GX_CAST_S(gint, key->getHash())%m_ObjArray.getCount();
        
        Node* p=m_ObjArray.get(idx);
        
        if(!p) {
            p=new Node(key,obj);
            m_ObjArray.set(idx,p);
            m_ObjCount++;
        }
        else {
            while (true) {
                if(p->getKey()->isEqual(key)) {
                    p->setObj(obj);
                    break;
                }
                else {
                    if(p->getNext()) {
                        p=p->getNext();
                    }
                    else {
                        p->setNext(new Node(key,obj));
                        m_ObjCount++;
                        break;
                    }
                }
            }
        }
    }
    
    O* get(K* key) {
        if(m_ObjCount>0) {
            gint idx=GX_CAST_S(gint, key->getHash())%m_ObjArray.getCount();
            Node* p=m_ObjArray.get(idx);
            while(p) {
                if(p->getKey()->isEqual(key)) {
                    return p->getObj();
                }
                p=p->getNext();
            }
        }
        return NULL;
    }
    bool remove(K* key) {
        if (m_ObjCount>0) {
            gint idx=GX_CAST_S(gint, key->getHash())%m_ObjArray.getCount();
            Node* p=m_ObjArray.get(idx);
            Node* pLast=NULL;
            while(p) {
                if(p->getKey()->isEqual(key)) {
                    if(pLast) {
                        pLast->setNext(p->getNext());
                    }
                    else {
                        m_ObjArray.set(idx,p->getNext());
                    }
                    delete p;
                    m_ObjCount--;
                    return true;
                }
                pLast=p;
                p=p->getNext();
            }
        }
        return false;
    }
    void removeAll() {
        if (m_ObjCount<=0) {
            return;
        }
        for (gint i=0; i<m_ObjArray.getCount(); i++) {
            Node* p=m_ObjArray.get(i);
            m_ObjArray.set(i, NULL);
            
            while (p) {
                Node* pTemp=p->next;
                delete p;
                p=pTemp;
            }
        }
        m_ObjCount=0;
    }
    
	GArray<K>* getAllKeys() {
		GArray<K>* res = GArray<K>::autoAlloc();
		if (m_ObjCount > 0) {
			for (gint i = 0; i < m_ObjArray.getCount(); i++) {
				Node* p = m_ObjArray.get(idx);
				while (p) {
					res->add(p->getKey());
					p=p->getNext();
				}
			}
		}
		return res;
	}
	GArray<O>* getAllObjects() {
		GArray<O>* res = GArray<O>::autoAlloc();
		if (m_ObjCount > 0) {
			for (gint i = 0; i < m_ObjArray.getCount(); i++) {
				Node* p = m_ObjArray.get(i);
				while (p) {
					res->add(p->getObj());
					p=p->getNext();
				}
			}
		}
		return res;
	}
private:
    bool increaseCapability(gint dc) {
        for (gint i=0;; i++) {
            if(capabilitys[i]>dc) {
                dc=capabilitys[i];
                break;
            }
            else if(capabilitys[i]<=0) {
                return false;
            }
        }
        
        GDArray<Node*> tempArr;
        tempArr.add(&m_ObjArray);
        
        if (!m_ObjArray.changeCount(dc)) {
            return false;
        }
        
        m_ObjArray.zeroSelf();
        
        for (gint i=0; i<tempArr.getCount(); i++) {
            Node* p=tempArr.get(i);
            while(p) {
                gint idx=GX_CAST_S(gint, p->getKey()->getHash())%dc;
                
                Node* pNew=m_ObjArray.get(idx);
                if(pNew) {
                    while (pNew->getNext()) {
                        pNew=pNew->getNext();
                    }
                    pNew->setNext(p);
                }
                else {
                    m_ObjArray.set(idx,p);
                }
                pNew=p;
                p=p->getNext();
                pNew->setNext(NULL);
            }
        }
        return true;
    }
    
private:
    GDArray<Node*>  m_ObjArray;
    gint            m_ObjCount;
};


GX_OBJECT_TEMPLATE_IMPLEMENT(typename K GX_COMMA typename O, GMap<K GX_COMMA O>, GMapBase);

template <typename K,typename O>
GMap<K,O>::GMap()
{
    m_ObjCount=0;
}
template <typename K,typename O>
GMap<K,O>::~GMap()
{
    Node* p;
    Node* pLast;
    for (gint i=m_ObjArray.getCount()-1; i>=0; i--) {
        p=m_ObjArray.get(i);
        while (p) {
            pLast=p;
            p=p->getNext();
            delete pLast;
        }
    }
}


#endif /* GMap_h */
