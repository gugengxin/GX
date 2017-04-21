#ifndef GShader_h
#define GShader_h


#include "GXPrefix.h"

class GContext;

class GShader
{
	friend class GContext;
protected:
	typedef struct _Macro
	{
		const gchar* name;
		const gchar* definition;
	} Macro;
protected:
	GShader(GContext* ctx,guint8 idxA, guint8 idxB, guint8 idxC, guint8 idxD);
	virtual ~GShader();

	inline guint8 getIndex0() {
		return m_Index[0];
	}
	inline guint8 getIndex1() {
		return m_Index[1];
	}
	inline guint8 getIndex2() {
		return m_Index[2];
	}
	inline guint8 getIndex3() {
		return m_Index[3];
	}
	inline guint8 getIndexA() {
		return m_Index[0];
	}
	inline guint8 getIndexB() {
		return m_Index[1];
	}
	inline guint8 getIndexC() {
		return m_Index[2];
	}
	inline guint8 getIndexD() {
		return m_Index[3];
	}
    
    inline GContext* getContext() {
        return m_Context;
    }

private:
    GContext*   m_Context;
    guint8      m_Index[4];
};

#endif