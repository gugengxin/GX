//
// Created by Gengxin Gu on 16/5/9.
//

#include "GContext.h"
#include "GLog.h"
#include "GThread.h"
#include "GFontManager.h"


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

GMap<GString, GObject>* GContext::getMap(gint index)
{
    return &m_Maps[index];
}

void GContext::didReceivedMemoryWarning()
{
    //TODO
}

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


GTex2DFont* GContext::loadTex2DFont(GString* name, gint32 size, gint32 outlineSize)
{
    if (size<=0) {
        size=12;
    }
    if (outlineSize<0) {
        outlineSize=0;
    }
    GString* key=GString::alloc();
    key->format("%@_%@_%@").arg(name).arg(size).arg(outlineSize).end();
    
    GTex2DFont* res=GX_CAST_R(GTex2DFont*, findInMap(MapTex2DFont, key));
    if (!res) {
        GFTFont* ftFont=GFontManager::shared()->loadFTFont(name, size, outlineSize);
        if (ftFont) {
            res=GTex2DFont::alloc();
            res->create(ftFont, this);
            addToMap(MapTex2DFont, key, res);
            GO::autorelease(res);
        }
    }
    
    GO::release(key);
    return res;
}


