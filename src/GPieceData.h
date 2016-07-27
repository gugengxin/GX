﻿//
//  GPieceData.h
//  GX
//
//  Created by Gengxin Gu on 16/4/27.
//  Copyright © 2016年 Gengxin Gu. All rights reserved.
//

#ifndef GPieceData_h
#define GPieceData_h

#include "GXPrefix.h"
#include "GData.h"


#include "GXGObject.h"

class GPieceData : public GData {
    template <typename,typename> friend class GDataArray;
	template<typename> friend class GArray;
    friend class GString;
    friend class GRBReader;
    GX_GOBJECT(GPieceData);
protected:
	GPieceData(guint32 pieceSize);
public:
	bool setPieceSize(guint32 v);

	virtual bool changeBytes(guint toSize);
	virtual void freeSelf();
	virtual bool robOther(GData* other);

private:
	guint32 m_PieceSize;
	guint32 m_PieceCount;
};

#include "GXGObjectUD.h"

#endif /* GPieceData_h */
