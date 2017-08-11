//
// Created by Gengxin Gu on 16/5/9.
//

#include "GContext.h"
#include "GLog.h"
#include "GThread.h"


#include "GXGObject.h"

GX_GOBJECT_IMPLEMENT(GContext::NodeLoadObj, GObject);

GContext::NodeLoadObj::NodeLoadObj()
{
    context=NULL;
}
GContext::NodeLoadObj::~NodeLoadObj()
{
}

GX_GOBJECT_IMPLEMENT(GContext::NodeUnloadObj, GObject);

GContext::NodeUnloadObj::NodeUnloadObj()
{
    context=NULL;
}

GContext::NodeUnloadObj::~NodeUnloadObj()
{
}


GX_GOBJECT_IMPLEMENT(GContext::FBNodeLoadObj, NodeLoadObj);

GContext::FBNodeLoadObj::FBNodeLoadObj()
{
    use=GFrameBuffer::UseFor2D;
    nodeOut=NULL;

    texTarget=NULL;
}
GContext::FBNodeLoadObj::~FBNodeLoadObj()
{
}

GX_GOBJECT_IMPLEMENT(GContext::FBNodeUnloadObj, NodeUnloadObj);

GContext::FBNodeUnloadObj::FBNodeUnloadObj()
{
    nodeOut=NULL;
}
GContext::FBNodeUnloadObj::~FBNodeUnloadObj()
{
}



void GContext::initialize()
{
    GX_CONTEXT_BASE::initialize();
    
    
}


//不用在这里初始化
GContext::GContext()
{
}
//不用在这里反初始化
GContext::~GContext()
{
}

//在这里初始化
bool GContext::create(GWindow *win)
{
    if(!GX_CONTEXT_BASE::create(win)) {
        return false;
    }
    //GX_LOG_W(PrioINFO,"GContext","create");
    return true;
}
//在这里反初始化
void GContext::destroy()
{
    //GX_LOG_W(PrioINFO,"GContext","destroy");
    {
        GFrameBuffer::Node* p=GX_CAST_R(GFrameBuffer::Node*, m_FrameBuffers.last());
        while (p) {
            GFrameBuffer::Node* pTemp=GX_CAST_R(GFrameBuffer::Node*, p->getPrev());
			unloadFrameBufferNodeForContext(p);
            m_FrameBuffers.remove(p,false);
            p=pTemp;
        }
    }
    GX_CONTEXT_BASE::destroy();
}

#if defined(GX_OS_ANDROID)
void GContext::androidDestroy()
{
    //TODO
    //GX_LOG_W(PrioINFO,"GContext","androidDestroy");
    GX_CONTEXT_BASE::androidDestroy();
}
void GContext::androidRecreate(GWindow* win)
{
    //GX_LOG_W(PrioINFO,"GContext","androidRecreate");
    GX_CONTEXT_BASE::androidRecreate(win);
    //TODO
}
#endif

GFrameBuffer* GContext::loadFrameBuffer(gint32 width, gint32 height, GTexture2D::Parameter* param, GFrameBuffer::Use use)
{
	GFrameBuffer* res = NULL;
    GTexture2D* texTarget= GTexture2D::alloc();
	if(texTarget->create(getPixelFormatForFB(),width,height,param)) {
		GFrameBuffer::Node* node = new GFrameBuffer::Node();
		if (loadFrameBufferNode(node, texTarget, use)) {
			res = GFrameBuffer::alloc();
			res->config(node);
			GO::autorelease(res);
			return res;
		}
		else {
			delete node;
		}
    }
	GO::release(texTarget);
    return res;
}


void GContext::addFrameBufferNodeInMT(GFrameBuffer::Node* node)
{
    m_FrameBuffers.add(node);
}

void GContext::removeFrameBufferNodeInMT(GFrameBuffer::Node* node)
{
    m_FrameBuffers.remove(node,false);
}

bool GContext::loadFrameBufferNode(GFrameBuffer::Node* node, GTexture* texTarget, GFrameBuffer::Use use)
{
    FBNodeLoadObj* obj = FBNodeLoadObj::alloc();

    obj->context = this;
	obj->nodeOut = node;
	obj->texTarget = texTarget;
	obj->use = use;

    if (GThread::current()->isMain()) {
        loadFrameBufferNodeInMT(obj);
    }
    else {
        GThread::current()->getRunLoop()->perform(unloadFrameBufferNodeInMT, obj, 0, true);
    }

    GO::release(obj);
    
    return node->isValid();
}

void GContext::unloadFrameBufferNode(GFrameBuffer::Node* node)
{
    FBNodeUnloadObj* obj = FBNodeUnloadObj::alloc();
    obj->context = this;
    obj->nodeOut = node;

    if (GThread::current()->isMain()) {
        unloadFrameBufferNodeInMT(obj);
    }
    else {
        GThread::current()->getRunLoop()->perform(unloadFrameBufferNodeInMT, obj, 0, true);
    }
    
    GO::release(obj);
}

void GContext::unloadFrameBufferNodeInMT(GObject* obj)
{
	GContext::FBNodeUnloadObj& nodeObj = *GX_CAST_R(GContext::FBNodeUnloadObj*, obj);

	nodeObj.context->unloadFrameBufferNodeForContext(nodeObj.nodeOut);

	nodeObj.context->removeFrameBufferNodeInMT(nodeObj.nodeOut);
}


