//
// Created by Gengxin Gu on 16/5/9.
//

#ifndef AS_GCONTEXT_H
#define AS_GCONTEXT_H

#include "GXPrefix.h"
#include "GOGLContext.h"
#include "GD3DContext.h"
#include "GMTLContext.h"
#include "GXContext.h"
#include "GReader.h"
#include "GTexture2D.h"
#include "GFrameBuffer.h"
#include "GResourceManager.h"
#include "GString.h"
#include "GTex2DFont.h"

#include "GXGObject.h"

class GContext : public GX_CONTEXT_BASE, public GResourceManager
{
    friend class GX_CONTEXT_BASE;
    friend class GWindow;
    friend class GFrameBuffer;
private:
    class NodeLoadObj : public GObject {
        GX_GOBJECT(NodeLoadObj);
    public:
        GContext* context;
    };
    class NodeUnloadObj : public GObject {
        GX_GOBJECT(NodeUnloadObj);
    public:
        GContext* context;
    };

    class FBNodeLoadObj : public NodeLoadObj {
        GX_GOBJECT(FBNodeLoadObj);
    public:
        GFrameBuffer::Node* nodeOut;

        GFrameBuffer::Use use;
        GTexture* texTarget;
    };
    class FBNodeUnloadObj : public NodeUnloadObj {
        GX_GOBJECT(FBNodeUnloadObj);
    public:
        GFrameBuffer::Node* nodeOut;
    };

private:
    static void initialize();
private:
    GContext();
	virtual ~GContext();
private:
    virtual bool create(GWindow* win);
    virtual void destroy();
#if defined(GX_OS_ANDROID)
private:
	virtual void androidDestroy();
	virtual void androidRecreate(GWindow* win);
#endif
//Resource Manager
private:
    typedef enum _Map {
        MapTex2D,
        MapTex2DFont,
        MapCount,
    } Map;
    virtual gint getMapCount() {
        return MapCount;
    }
    virtual GMap<GString, GObject>* getMap(gint index);
protected:
    virtual void didReceivedMemoryWarning();
private:
    GMap<GString,GObject> m_Maps[MapCount];
//FrameBuffer
public:
    GFrameBuffer* loadFrameBuffer(gint32 width, gint32 height, GTexture2D::Parameter* param, GFrameBuffer::Use use);
private:
    void addFrameBufferNodeInMT(GFrameBuffer::Node* node);
    void removeFrameBufferNodeInMT(GFrameBuffer::Node* node);
	bool loadFrameBufferNode(GFrameBuffer::Node* node, GTexture* texTarget, GFrameBuffer::Use use);
    void unloadFrameBufferNode(GFrameBuffer::Node* node);
	static void unloadFrameBufferNodeInMT(GObject* obj);
//Tex2DFont
public:
    GTex2DFont* loadTex2DFont(GString* name, gint32 size, gint32 outlineSize);
private:
    GDataList<GFrameBuffer::Handle> m_FrameBuffers;
};

#include "GXGObjectUD.h"

#endif //AS_GCONTEXT_H
