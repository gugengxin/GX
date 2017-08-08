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
    {
        GTexture::Node* p=GX_CAST_R(GTexture::Node*, m_Textures.last());
        while (p) {
            GTexture::Node* pTemp=GX_CAST_R(GTexture::Node*, p->getPrev());
            unloadTextureNodeForContext(p);
            m_Textures.remove(p,false);
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

GTexture2D* GContext::loadTexture2D(GReader* reader,GDib::FileType suggestFT,GTexture2D::Parameter* param)
{
    GDib* dib=GDib::load(reader, suggestFT);
    if (dib) {
        return loadTexture2D(dib, param);
    }
    return NULL;
}

GTexture2D* GContext::loadTexture2D(GDib* dib,GTexture2D::Parameter* param)
{
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
    return NULL;
}

GTexture2D* GContext::loadTexture2D(GString* name,GDib::FileType suggestFT,GTexture2D::Parameter* param)
{
    GTexture2D* res=GX_CAST_R(GTexture2D*, findInMap(MapTex2D, name));
    if (!res) {
        GBundle* bundle=NULL;
        GReader* reader=openReader(name, bundle);
        if (reader) {
            res=loadTexture2D(reader, suggestFT, param);
            closeReader(reader, bundle);
            
            if (res) {
                addToMap(MapTex2D, name, res);
            }
        }
    }
    return res;
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

GFrameBuffer* GContext::loadFrameBuffer(gint32 width, gint32 height, GTexture2D::Parameter* param, GFrameBuffer::Use use)
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
    if (loadFrameBufferNode(node, texTarget, use)) {
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


