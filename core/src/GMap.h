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

#include "GXGObject.h"

class GMapBase : public GObject {
    GX_GOBJECT(GMapBase);
public:
    static const gint capabilitys[];
};


template <class K,class O>
class GMap : public GMapBase {
	friend class GNoticeCenter;
    GX_GOBJECT(GMap);
private:
    class Node {
    public:
        Node(K* key,O* obj) {
			GO::retain(key);
            m_Key=key;
			GO::retain(obj);
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

        //gint idx=GX_CAST_S(gint, GX_CAST_S(guint,key->getHash())%GX_CAST_S(guint,m_ObjArray.getCount()));
        gint idx=indexOfHash(key->getHash(),m_ObjArray.getCount());

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
            //gint idx=GX_CAST_S(gint, key->getHash())%m_ObjArray.getCount();
			gint idx=indexOfHash(key->getHash(),m_ObjArray.getCount());
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
			if (m_ObjCount < m_ObjArray.getCount() / 2) {
				decreaseCapability(m_ObjArray.getCount());
			}
            //gint idx=GX_CAST_S(gint, key->getHash())%m_ObjArray.getCount();
			gint idx=indexOfHash(key->getHash(),m_ObjArray.getCount());
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
		m_ObjArray.changeCount(0);
    }
    
	GArray<K>* getAllKeys() {
		GArray<K>* res = GArray<K>::autoAlloc();
		if (m_ObjCount > 0) {
			for (gint i = 0; i < m_ObjArray.getCount(); i++) {
				Node* p = m_ObjArray.get(i);
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
public:
	class Cursor {
		friend class GMap;
	public:
		Cursor() {
			m_Index = 0;
			m_Node = NULL;
			m_NodeEnd = NULL;
		}
		~Cursor() {

		}

		K* getKey() {
			return m_Node->getKey();
		}
		O* getObj() {
			return m_Node->getObj();
		}

	private:
		void setIndex(gint v) {
			m_Index = v;
		}
		void setNode(Node* v) {
			m_Node = v;
		}
		void setNodeEnd(Node* v) {
			m_NodeEnd = v;
		}
		gint getIndex() {
			return m_Index;
		}
		Node* getNode() {
			return m_Node;
		}
		Node* getNodeEnd() {
			return m_NodeEnd;
		}
	private:
		gint m_Index;
		Node* m_Node;
		Node* m_NodeEnd;
	};

	Cursor cursor() {
		Cursor res;
		for (gint i = 0; i < m_ObjArray.getCount(); i++) {
			Node* p = m_ObjArray.get(i);
			if (p) {
				res.setIndex(i);
				res.setNode(p);
			}
		}
		for (gint i = m_ObjArray.getCount() - 1; i >= 0; i--) {
			Node* p = m_ObjArray.get(i);
			if (p) {
				while (p->getNext()) {
					p = p->getNext();
				}
				res.setNodeEnd(p);
				break;
			}
		}
		return res;
	}
	void cursorNext(Cursor& cur) {
		cur.setNode(cur.getNode()->getNext());
		while (!cur.getNode()) {
			cur.setIndex(cur.getIndex() + 1);
			cur.setNode(m_ObjArray.get(cur.getIndex()));
		}
	}
	bool cursorValid(Cursor& cur) {
		return cur.getNode() != cur.getNodeEnd();
	}

private:
	inline gint indexOfHash(guint hash,gint count) {
		return GX_CAST_S(gint, hash%GX_CAST_S(guint,count));
	}
	bool increaseCapability(gint dc) {
		gint i=0;
		while(true) {
			if (capabilitys[i] > dc) {
				dc = capabilitys[i];
				break;
			}
			else if (capabilitys[i] <= 0) {
				return false;
			}
			i++;
		}

		return changeCapability(dc);
	}

	bool decreaseCapability(gint dc) {
		gint i=0;
		while(true) {
			if (capabilitys[i] >= dc) {
				if (i <= 0) {
					return false;
				}
				else {
					dc = capabilitys[i - 1];
					break;
				}
			}
			else if (capabilitys[i] <= 0) {
				return false;
			}
			i++;
		}
		return changeCapability(dc);
	}

	bool changeCapability(gint dc) {
		GDArray<Node*> tempArr;
		tempArr.add(&m_ObjArray);

		if (!m_ObjArray.changeCount(dc)) {
			return false;
		}

		m_ObjArray.zeroSelf();

		for (gint i = 0; i<tempArr.getCount(); i++) {
			Node* p = tempArr.get(i);
			while (p) {
				//gint idx = GX_CAST_S(gint, p->getKey()->getHash()) % dc;
				gint idx = indexOfHash(p->getKey()->getHash(),dc);

				Node* pNew = m_ObjArray.get(idx);
				if (pNew) {
					while (pNew->getNext()) {
						pNew = pNew->getNext();
					}
					pNew->setNext(p);
				}
				else {
					m_ObjArray.set(idx, p);
				}
				pNew = p;
				p = p->getNext();
				pNew->setNext(NULL);
			}
		}
		return true;
	}
    
private:
    GDArray<Node*>  m_ObjArray;
    gint            m_ObjCount;
};


GX_GOBJECT_TEMPLATE_IMPLEMENT(typename K GX_COMMA typename O, GMap<K GX_COMMA O>, GMapBase);

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

#include "GXGObjectUD.h"

#endif /* GMap_h */
