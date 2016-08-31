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

#define M_LIBRARY()         GX_CAST_R(id<MTLLibrary>,m_Library)
#define M_PIPELINE_STATE()  GX_CAST_R(id<MTLRenderPipelineState>,m_PipelineState)

GMShader::GMShader(GContext* ctx,guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD) :
GShader(ctx,idxA,idxB,idxC,idxD)
{
    m_Library=NULL;
}


GMShader::~GMShader()
{
    [M_LIBRARY() release];
}

bool GMShader::load(const gchar* srcVS, const gchar* srcFP, const Macro* macro)
{
    id<MTLDevice> device=GX_CAST_R(id<MTLDevice>, getContext()->getDevice());
    
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
        
        MTLRenderPipelineDescriptor *pipelineStateDescriptor = [[MTLRenderPipelineDescriptor alloc] init];
        
        pipelineStateDescriptor.label                           = @"GMShader";
        pipelineStateDescriptor.sampleCount                     = getContext()->getSampleCount();
        pipelineStateDescriptor.vertexFunction                  = vertexProgram;
        pipelineStateDescriptor.fragmentFunction                = fragmentProgram;
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm;
        pipelineStateDescriptor.depthAttachmentPixelFormat      = (MTLPixelFormat)getContext()->getDepthPixelFormat();
        pipelineStateDescriptor.stencilAttachmentPixelFormat    = (MTLPixelFormat)getContext()->getStencilPixelFormat();
        
        for (gint i=0; i<getPLStateCount(); i++) {
            deployPLState(i, pipelineStateDescriptor);
            
            error = nil;
            id <MTLRenderPipelineState> ps = [[device newRenderPipelineStateWithDescriptor:pipelineStateDescriptor error:&error] retain];
            if(!ps) {
                NSLog(@">> ERROR: Failed Aquiring pipeline state: %@", error);
            }
            getPLStates()[i]=ps;
        }
        
        createUniformBuffer(device);
        
        return true;
    }
    else {
        NSLog(@"%s:%@",__FUNCTION__,error);
    }
    
    return false;
}

bool GMShader::setUniformBuffer(gint idx,void* device,guint bufLen)
{
    getUBuffers()[idx]=[[GX_CAST_R(id<MTLDevice>,device) newBufferWithLength:bufLen options:0] retain];

    return getUBuffers()[idx]!=nil;
}

void* GMShader::currentRenderEncoder()
{
    return getContext()->m_RenderEncoder;
}



#endif