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




GX_GOBJECT_IMPLEMENT(GContext::T2DNodeLoadObjBase, NodeLoadObj);

GContext::T2DNodeLoadObjBase::T2DNodeLoadObjBase()
{
    param=NULL;
    nodeOut=NULL;
}
GContext::T2DNodeLoadObjBase::~T2DNodeLoadObjBase()
{

}

GX_GOBJECT_IMPLEMENT(GContext::T2DNodeLoadObj, T2DNodeLoadObjBase);

GContext::T2DNodeLoadObj::T2DNodeLoadObj()
{
    dib=NULL;
}
GContext::T2DNodeLoadObj::~T2DNodeLoadObj()
{

}

GX_GOBJECT_IMPLEMENT(GContext::T2DNodeLoadCreateObj, T2DNodeLoadObjBase);

GContext::T2DNodeLoadCreateObj::T2DNodeLoadCreateObj()
{
    
}
GContext::T2DNodeLoadCreateObj::~T2DNodeLoadCreateObj()
{

}

GX_GOBJECT_IMPLEMENT(GContext::T2DNodeUnloadObj, NodeUnloadObj);

GContext::T2DNodeUnloadObj::T2DNodeUnloadObj()
{
    nodeOut=NULL;
}
GContext::T2DNodeUnloadObj::~T2DNodeUnloadObj()
{
}






GX_GOBJECT_IMPLEMENT(GContext::FBNodeLoadObj, NodeLoadObj);

GContext::FBNodeLoadObj::FBNodeLoadObj()
{
    enableDepth=false;
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
    memset(m_Shaders, 0, sizeof(m_Shaders));
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
    {
        GTexture::Node* p=GX_CAST_R(GTexture::Node*, m_Textures.last());
        while (p) {
            GTexture::Node* pTemp=GX_CAST_R(GTexture::Node*, p->getPrev());
            unloadTextureNodeForContext(p);
            m_Textures.remove(p,false);
            p=pTemp;
        }
    }
    for (gint i = 0; i < SRIDCount; i++) {
        readyShader();
        delete m_Shaders[i];
        m_Shaders[i]=NULL;
        doneShader();
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

GSRGraphics* GContext::getSRGraphics(GSRGraphics::ID srID)
{
    //GX_LOG_W(PrioINFO,"GContext","getSRGraphics");
	if (!m_Shaders[SRID_Graphics + srID]) {
        readyShader();
        m_Shaders[SRID_Graphics + srID] = new GSRGraphics(this,srID);
        doneShader();
	}
	return (GSRGraphics*)m_Shaders[SRID_Graphics + srID];
}

GSRTexture2D* GContext::getSRTexture2D(bool alphaOnly,bool colorMul,GSRTexture2D::MaskMode mm)
{
    gint idx=(alphaOnly*2+colorMul)*GSRTexture2D::MMCount+mm;
    if (!m_Shaders[SRID_Texture2D+idx]) {
        readyShader();
        m_Shaders[SRID_Texture2D + idx] = new GSRTexture2D(this,alphaOnly,colorMul,mm);
        doneShader();
    }
    return (GSRTexture2D*)m_Shaders[SRID_Texture2D + idx];
}


GTexture2D* GContext::loadTexture2D(GReader* reader,GDib::FileType suggestFT,GTexture2D::Parameter* param)
{
    GDib* dib=GDib::load(reader, suggestFT);
    if (dib) {
        GTexture::Node* node=new GTexture::Node();
        if(loadTexture2DNode(node, dib, param)) {
            GTexture2D* res=GTexture2D::alloc();
            res->config(node, dib, param);
            GO::autorelease(res);
            return res;
        }
        else {
            delete node;
        }
    }
    return NULL;
}

void GContext::addTextureNodeInMT(GTexture::Node* node)
{
	m_Textures.add(node);
}

void GContext::removeTextureNodeInMT(GTexture::Node* node)
{
	m_Textures.remove(node, false);
}

bool GContext::loadTexture2DNode(GTexture::Node* node, GDib* dib, GTexture2D::Parameter* param)
{
	dib = loadTexture2DNodeReadyDib(dib);
	if (!dib) {
		return false;
	}
	T2DNodeLoadObj* obj = T2DNodeLoadObj::alloc();
	obj->context = this;
	obj->dib = dib;
	obj->param = param;
	obj->nodeOut = node;
	if (GThread::current()->isMain()) {
		loadTexture2DNodeInMT(obj);
	}
	else {
		GThread::current()->getRunLoop()->perform(loadTexture2DNodeInMT, obj, 0, true);
	}
	GO::release(obj);

	return node->isValid();
}

bool GContext::loadTexture2DNode(GTexture::Node* node, GX::PixelFormat pixelFormat, gint32 width, gint32 height, GTexture2D::Parameter* param)
{
	T2DNodeLoadCreateObj* obj=T2DNodeLoadCreateObj::alloc();
	obj->context = this;
	obj->pixelFormat = pixelFormat;
	obj->width = width;
	obj->height = height;
	obj->param = param;
	obj->nodeOut = node;
	if (GThread::current()->isMain()) {
		loadTexture2DNodeInMT(obj);
	}
	else {
		GThread::current()->getRunLoop()->perform(loadTexture2DNodeInMT, obj, 0, true);
	}
	GO::release(obj);

	return node->isValid();
}

void GContext::unloadTextureNode(GTexture::Node* node)
{
	T2DNodeUnloadObj* obj = T2DNodeUnloadObj::alloc();
	obj->context = this;
	obj->nodeOut = node;

	if (GThread::current()->isMain()) {
		unloadTextureNodeInMT(obj);
	}
	else {
		GThread::current()->getRunLoop()->perform(unloadTextureNodeInMT, obj, 0, true);
	}

	GO::release(obj);
}

void GContext::unloadTextureNodeInMT(GObject* obj)
{
	GContext::T2DNodeUnloadObj& nodeObj = *GX_CAST_R(GContext::T2DNodeUnloadObj*, obj);

	nodeObj.context->unloadTextureNodeForContext(nodeObj.nodeOut);

	nodeObj.context->removeTextureNodeInMT(nodeObj.nodeOut);
}

GFrameBuffer* GContext::loadFrameBuffer(gint32 width, gint32 height, GTexture2D::Parameter* param, bool enableDepth)
{
    GTexture2D* texTarget=NULL;
    {
        GTexture::Node* node = new GTexture::Node();
        GX::PixelFormat pixelFormat=getPixelFormatForFB();
        if (loadTexture2DNode(node, pixelFormat, width, height, param)) {
            texTarget = GTexture2D::alloc();
            texTarget->config(node, pixelFormat, width, height, param);
            GO::autorelease(texTarget);
        }
        else {
            delete node;
            return NULL;
        }
    }
    GFrameBuffer::Node* node = new GFrameBuffer::Node();
    if (loadFrameBufferNode(node, texTarget, enableDepth)) {
        GFrameBuffer* res = GFrameBuffer::alloc();
        res->config(node);
        GO::autorelease(res);
        return res;
    }
    else {
        delete node;
    }
    return NULL;
}


void GContext::addFrameBufferNodeInMT(GFrameBuffer::Node* node)
{
    m_FrameBuffers.add(node);
}

void GContext::removeFrameBufferNodeInMT(GFrameBuffer::Node* node)
{
    m_FrameBuffers.remove(node,false);
}

bool GContext::loadFrameBufferNode(GFrameBuffer::Node* node, GTexture* texTarget, bool enableDepth)
{
    FBNodeLoadObj* obj = FBNodeLoadObj::alloc();

    obj->context = this;
	obj->nodeOut = node;
	obj->texTarget = texTarget;
	obj->enableDepth = enableDepth;

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



