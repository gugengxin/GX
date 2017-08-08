//
//  GMShader.h
//  GX
//
//  Created by Gu Gengxin on 16/8/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GMShader_h
#define GMShader_h

#include "GXPrefix.h"
#include "GX3DAPIType.h"
#if defined(GX_METAL)
#include "GXMetal.h"
#include "GShader.h"
#include "GBuffer.h"

class GTexture;

class GMShader : public GShader {
protected:
    static void ready();
    static void done();
protected:
    GMShader(guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD);
    virtual ~GMShader();
public:
    bool load(const gchar* srcVS, const gchar* srcFP, const Macro* macro);
private:
    virtual gint getPLStateCount() = 0;
    virtual void** getPLStates() = 0;
    virtual void** getUBuffers() = 0;
    virtual void deployPLState(gint inputType,void* plStateDescriptor) = 0;
    virtual void createUniformBuffer(void* device) = 0;
protected:
    bool setUniformBuffer(gint idx,void* device,guint bufLen);
    void setFragmentTexture(void* rce,GTexture* tex,guint idx);
    void setVertexBuffer(void* rce,GBuffer* buffer,guint offset,guint index);
private:
    void* m_Library;
};

typedef GMShader GShaderBase;

#define GX_SHADER_INPUT(OU,DIL,DCB,MPS,MUB) \
private:\
    virtual gint getPLStateCount() {\
        return MPS;\
    }\
    virtual void** getPLStates() {\
        return m_PipelineStates;\
    }\
    virtual void** getUBuffers() {\
        return m_UniformBuffers;\
    }\
    void* m_PipelineStates[MPS*GX::_DBlendCount];\
    void* m_UniformBuffers[MUB]

#define GX_SHADER_INPUT_INIT() \
    memset(m_PipelineStates,0,sizeof(m_PipelineStates));\
    memset(m_UniformBuffers,0,sizeof(m_UniformBuffers))

#define GX_SHADER_INPUT_FINA() \
    for(size_t i=0;i<sizeof(m_PipelineStates)/sizeof(m_PipelineStates[0]);i++) {\
		[GX_CAST_R(id,m_PipelineStates[i]) release];\
	}\
    for(size_t i=0;i<sizeof(m_UniformBuffers)/sizeof(m_UniformBuffers[0]);i++) {\
		[GX_CAST_R(id,m_UniformBuffers[i]) release];\
	}

#endif

#endif /* GMShader_h */
