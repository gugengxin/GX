//
// Created by Gengxin Gu on 2016/12/20.
//

#include "Game.h"

GX_OBJECT_IMPLEMENT(Game,GGame);

void Game::init()
{
    GGame::init();
    
    
}

void Game::uninit()
{
    
    GGame::uninit();
}

void Game::eventStart(GWindow* window)
{
    GGame::eventStart(window);
    
}

void Game::eventStop()
{

    GGame::eventStop();
}




void Game::idle()
{
    
}

void Game::render(GCanvas* canvas)
{
    GContext& context=getWindow()->getContext();
    
    canvas->enable3D(canvas->getWidth(), canvas->getHeight(), GX_PI / 3, 0.1f, 1000.0f);
    canvas->lookAt(0.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    //canvas->enable2D(getWidth(), getHeight());
    
    /*
    GSRGraphics* graph = context.getSRGraphics(GSRGraphics::ID_CAndCM);
    
    canvas->setColorMul(0, 1, 1, 1.0f);
    static GDataBuffer* data = NULL;
    if (!data) {
        data = GDataBuffer::alloc();
        
        typedef struct {
            GVector3 pos;
            GColor4 clr;
        } MD;
        
        MD md[3];
        
        md[0].pos.set(-100.0f, -100.0f, 0.0f);
        md[1].pos.set(100.0f, -100.0f, 0.0f);
        md[2].pos.set(0.0f, 100.0f, 0.0f);
        
        md[0].clr.set(1.0f, 0, 0, 1.0f);
        md[1].clr.set(0.0f, 1, 0, 1.0f);
        md[2].clr.set(0.0f, 0, 1, 1.0f);
        
        data->changeBytes(sizeof(md));
        void* p = data->map();
        memcpy(p, &md[0], sizeof(md));
        data->unmap();
        data->setOffset(0);
        data->setStride(sizeof(md[0]));
    }
    
    graph->draw(canvas, data, GSRGraphics::IT_Float, GX_TRIANGLES, 0, 3);
    //*/
    
    /*
    GSRTexture2D* shader=context.getSRTexture2D(false, true, GSRTexture2D::MM_None);
    canvas->setColorMul(0, 1, 0, 1.0f);
    
    static GDataBuffer* data = NULL;
    static GTexture2D* tex=NULL;
    if (!data) {
        data = GDataBuffer::alloc();
        
        typedef struct {
            GVector3 pos;
            GVector2 tc;
        } MD;
        
        MD md[4];
        
        md[0].pos.set(-100.0f, -100.0f, 0.0f);
        md[1].pos.set(100.0f, -100.0f, 0.0f);
        md[2].pos.set(-100.0f, 100.0f, 0.0f);
        md[3].pos.set(100.0f, 100.0f, 0.0f);
        
        md[0].tc.set(0.0f, 1.0f);
        md[1].tc.set(1.0f, 1.0f);
        md[2].tc.set(0.0f, 0.0f);
        md[3].tc.set(1.0f, 0.0f);
        
        data->changeBytes(sizeof(md));
        void* p = data->map();
        memcpy(p, &md[0], sizeof(md));
        data->unmap();
        data->setOffset(0);
        data->setStride(sizeof(md[0]));
        
        GReader* reader=GAppBundle::main()->openReader("lena_rgb.jpg");
        if (reader) {
            tex=context.loadTexture2D(reader, GDib::JPEG, NULL);
            GO::retain(tex);
            GAppBundle::main()->closeReader(reader);
        }
    }
    shader->draw(canvas, data, GSRTexture2D::IT_Float_Float, tex, GX_TRIANGLE_STRIP, 0, 4, NULL);
    //*/
    
    //*
    
    GSRTexture2D* shader=context.getSRTexture2D(false, true, GSRTexture2D::MM_None);
    canvas->setColorMul(1, 1, 1, 1.0f);
    
    static GFrameBuffer* fb=NULL;
    static GDataBuffer* data = NULL;
    static GTexture2D* tex=NULL;
    
    
    if (!fb) {
        fb=context.loadFrameBuffer(GX::PixelFormatRGBA8888, 200, 200, NULL, false);
        GX_ASSERT(fb!=NULL);
        GO::retain(fb);
        
        data = GDataBuffer::alloc();
        
        typedef struct {
            GVector3 pos;
            GVector2 tc;
        } MD;
        
        MD md[4];
        
        md[0].pos.set(-100.0f, -100.0f, 0.0f);
        md[1].pos.set(100.0f, -100.0f, 0.0f);
        md[2].pos.set(-100.0f, 100.0f, 0.0f);
        md[3].pos.set(100.0f, 100.0f, 0.0f);
        
        md[0].tc.set(0.0f, 1.0f);
        md[1].tc.set(1.0f, 1.0f);
        md[2].tc.set(0.0f, 0.0f);
        md[3].tc.set(1.0f, 0.0f);
        
        data->changeBytes(sizeof(md));
        void* p = data->map();
        memcpy(p, &md[0], sizeof(md));
        data->unmap();
        data->setOffset(0);
        data->setStride(sizeof(md[0]));
        
        GReader* reader=GAppBundle::main()->openReader("lena_rgb.jpg");
        if (reader) {
            tex=context.loadTexture2D(reader, GDib::JPEG, NULL);
            GO::retain(tex);
            GAppBundle::main()->closeReader(reader);
        }
    }
    
    
    
    shader->draw(canvas, data, GSRTexture2D::IT_Float_Float, tex, GX_TRIANGLE_STRIP, 0, 4, NULL);
    //*/
}
