//
//  GMShader.cpp
//  GX
//
//  Created by Gu Gengxin on 16/8/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#include "GMShader.h"
#if defined(GX_METAL)
#include "GContext.h"
#import <QuartzCore/QuartzCore.h>
#include "GMTLContext.h"

#define M_LIBRARY()         GX_CAST_R(id<MTLLibrary>,m_Library)
#define M_PIPELINE_STATE()  GX_CAST_R(id<MTLRenderPipelineState>,m_PipelineState)


void GMShader::ready()
{
    GMTLContext::readyShader();
}

void GMShader::done()
{
    GMTLContext::doneShader();
}

GMShader::GMShader(guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD) :
GShader(idxA,idxB,idxC,idxD)
{
    m_Library=NULL;
}


GMShader::~GMShader()
{
    [M_LIBRARY() release];
}

bool GMShader::load(const gchar* srcVS, const gchar* srcFP, const Macro* macro)
{
    id<MTLDevice> device=GX::metalDevice();
    
    NSString* strSrc=[[NSString alloc] initWithUTF8String:srcVS];
    MTLCompileOptions* co=[[MTLCompileOptions alloc] init];
    
    NSMutableDictionary* coMs=[[NSMutableDictionary alloc] initWithCapacity:8];
    const Macro* pSM = macro;
    while (pSM->name) {
        NSString* key=[[NSString alloc] initWithUTF8String:pSM->name];
        [coMs setObject:@"" forKey:key];
        [key release];
        pSM++;
    }
    co.preprocessorMacros=coMs;
    [coMs release];
    
    NSError* error=nil;
    m_Library= [[device newLibraryWithSource:strSrc options:co error:&error] retain];
    [strSrc release];
    [co release];
    
    if (m_Library) {
        // get the vertex function from the library
        id <MTLFunction> vertexProgram = [M_LIBRARY() newFunctionWithName:@"mainVS"];
        if(!vertexProgram)
            NSLog(@">> ERROR: Couldn't load vertex function from default library");
        
        // get the fragment function from the library
        id <MTLFunction> fragmentProgram = [M_LIBRARY() newFunctionWithName:@"mainFP"];
        if(!fragmentProgram)
            NSLog(@">> ERROR: Couldn't load fragment function from default library");
        
        MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[[MTLRenderPipelineDescriptor alloc] init] autorelease];
        
        pipelineStateDescriptor.label                           = @"GMShader";
        pipelineStateDescriptor.sampleCount                     = GMTLContext::sampleCount();
        pipelineStateDescriptor.vertexFunction                  = vertexProgram;
        pipelineStateDescriptor.fragmentFunction                = fragmentProgram;
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = (MTLPixelFormat)GMTLContext::layerPixelFormat();
        pipelineStateDescriptor.depthAttachmentPixelFormat      = (MTLPixelFormat)GMTLContext::depthPixelFormat();
        pipelineStateDescriptor.stencilAttachmentPixelFormat    = (MTLPixelFormat)GMTLContext::stencilPixelFormat();
        
        for (gint i=0; i<getPLStateCount(); i++) {
            deployPLState(i, pipelineStateDescriptor);
            
            MTLRenderPipelineColorAttachmentDescriptor* cad=pipelineStateDescriptor.colorAttachments[0];
            cad.sourceAlphaBlendFactor=MTLBlendFactorOne;
            cad.destinationAlphaBlendFactor=MTLBlendFactorOne;
            
            {
                cad.blendingEnabled=NO;
                error = nil;
                id <MTLRenderPipelineState> ps = [[device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error] retain];
                if(!ps) {
                    NSLog(@"ERROR: Failed Aquiring pipeline state: %@", error);
                }
                getPLStates()[i*GX::_DBlendCount+GX::DBlendNone]=ps;
            }
            {
                cad.blendingEnabled=YES;
                cad.sourceRGBBlendFactor=MTLBlendFactorSourceAlpha;
                cad.destinationRGBBlendFactor=MTLBlendFactorOneMinusSourceAlpha;
                error = nil;
                id <MTLRenderPipelineState> ps = [[device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error] retain];
                if(!ps) {
                    NSLog(@"ERROR: Failed Aquiring pipeline state: %@", error);
                }
                getPLStates()[i*GX::_DBlendCount+GX::DBlendSsaAddD1msa]=ps;
            }
            {
                cad.blendingEnabled=YES;
                cad.sourceRGBBlendFactor=MTLBlendFactorOne;
                cad.destinationRGBBlendFactor=MTLBlendFactorOne;
                error = nil;
                id <MTLRenderPipelineState> ps = [[device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error] retain];
                if(!ps) {
                    NSLog(@"ERROR: Failed Aquiring pipeline state: %@", error);
                }
                getPLStates()[i*GX::_DBlendCount+GX::DBlendS1AddD1]=ps;
            }
        }
        
        return true;
    }
    else {
        NSLog(@"%s:%@",__FUNCTION__,error);
    }
    
    return false;
}

void GMShader::setFragmentTexture(void* rce,GTexture* tex,guint idx)
{
    [GX_CAST_R(id<MTLRenderCommandEncoder>, rce) setFragmentTexture:GX_CAST_R(id<MTLTexture>,tex->getTexture())
                                                            atIndex:idx];
    [GX_CAST_R(id<MTLRenderCommandEncoder>, rce) setFragmentSamplerState:GX_CAST_R(id<MTLSamplerState>,tex->getSamplerState())
                                                                 atIndex:idx];
}

void GMShader::setVertexBuffer(void* rce,GBuffer* buffer,guint offset,guint index)
{
    [GX_CAST_R(id<MTLRenderCommandEncoder>, rce) setVertexBuffer:GX_CAST_R(id<MTLBuffer>, buffer->getBuffer())
                                                          offset:offset
                                                         atIndex:index];
}


#endif
