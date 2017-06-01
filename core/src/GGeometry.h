//
//  GGeometry.h
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#ifndef GGeometry_h
#define GGeometry_h

#include "GXPrefix.h"
#include "GXMath.h"

template <typename T>
class GPoint {
public:
    static GPoint make(T xx, T yy) {
        return GPoint(xx,yy);
    }
public:
    T x,y;
    
    GPoint() : x(0),y(0) {}
    GPoint(T xx,T yy) : x(xx),y(yy) {}
    
    inline void set(T vx,T vy) {
        x=vx;
        y=vy;
    }
    
    float getDistance(GPoint& other) {
        return GX::sqrt((float(x)-float(other.x))*(float(x)-float(other.x))+
                            (float(y)-float(other.y))*(float(y)-float(other.y)));
    }
};

typedef GPoint<float> GPointF;

template <typename T>
class GSize {
public:
    GSize() : width(0), height(0){}
    GSize(T w, T h) : width(w), height(h) {}
    
    inline void set(T w,T h) {
        width=w;
        height=h;
    }
    
    GSize nextPot() const {
        unsigned int nx=(unsigned int)width,ny=(unsigned int)height;
        nx--;
        nx|=nx>>1;
        nx|=nx>>2;
        nx|=nx>>8;
        nx|=nx>>16;
        nx++;
        
        ny--;
        ny|=ny>>1;
        ny|=ny>>2;
        ny|=ny>>8;
        ny|=ny>>16;
        ny++;
        return GSize((T)nx,(T)ny);
    };
    
    T width;
    T height;
};

typedef GSize<float> GSizeF;
typedef GSize<gint32> GSizeN;


template <typename T>
class GRect {
public:
    GRect() : origin(0,0),size(0,0) {}
    GRect(GPoint<T> o,GSize<T> s) : origin(o),size(s) {}
    GRect(T x,T y,T w, T h) : origin(x,y),size(w,h) {}
    
    inline void set(T x,T y,T w, T h) {
        origin.set(x,y);
        size.set(w,h);
    }
    inline void set(GPoint<T> o,GSize<T> s) {
        origin=o;
        size=s;
    }
    void setScaleAspectFit(GSize<T> seMain,GSize<T> se) {
        if (seMain.width/(double)seMain.height>=se.width/(double)se.height) {
            size.width=(T)(seMain.height*se.width/(double)se.height);
            size.height=seMain.height;
            origin.x=(T)((seMain.width-size.width)/2);
            origin.y=0;
        }
        else {
            size.height=(T)(seMain.width*se.height/(double)se.width);
            size.width=seMain.width;
            origin.x=0;
            origin.y=(T)((seMain.height-size.height)/2);
        }
    }
    void setScaleAspectFill(GSize<T> seMain,GSize<T> se) {
        if (seMain.width/(double)seMain.height<se.width/(double)se.height) {
            size.width=(T)(seMain.height*se.width/(double)se.height);
            size.height=seMain.height;
            origin.x=(T)((seMain.width-size.width)/2);
            origin.y=0;
        }
        else {
            size.height=(T)(seMain.width*se.height/(double)se.width);
            size.width=seMain.width;
            origin.x=0;
            origin.y=(T)((seMain.height-size.height)/2);
        }
    }
    
    bool isContainPoint(GPoint<T> pt) {
        return !(pt.x<origin.x || pt.x>=origin.x+size.width || pt.y<origin.y || pt.y>=origin.y+size.height);
    }
    
    inline T getX() {
        return origin.x;
    }
    inline T getY() {
        return origin.y;
    }
    inline T getWidth() {
        return size.width;
    }
    inline T getHeight() {
        return size.height;
    }
    
    inline T getLeft() {
        return origin.x;
    }
    inline T getRight() {
        return origin.x+size.width;
    }
    inline T getTop() {
        return origin.y;
    }
    inline T getBottom() {
        return origin.y+size.height;
    }
    
    
    void operator -=(GRect rc) {
        T r=origin.x+size.width;
        T b=origin.y+size.height;
        
        if(origin.x<rc.origin.x) {
            origin.x=rc.origin.x;
        }
        if(origin.y<rc.origin.y) {
            origin.y=rc.origin.y;
        }
        
        if(r>rc.origin.x+rc.size.width) {
            r=rc.origin.x+rc.size.width;
        }
        if(b>rc.origin.y+rc.size.height) {
            b=rc.origin.y+rc.size.height;
        }
        size.width=r-origin.x;
        size.height=b-origin.y;
    }
    void operator +=(const GRect& rc) {
        T r=origin.x+size.width;
        T b=origin.y+size.height;
        
        if(origin.x>rc.origin.x) {
            origin.x=rc.origin.x;
        }
        if(origin.y>rc.origin.y) {
            origin.y=rc.origin.y;
        }
        
        if(r<rc.origin.x+rc.size.width) {
            r=rc.origin.x+rc.size.width;
        }
        if(b<rc.origin.y+rc.size.height) {
            b=rc.origin.y+rc.size.height;
        }
        size.width=r-origin.x;
        size.height=b-origin.y;
    }
    
    
    GPoint<T> origin;
    GSize<T>  size;
};

typedef GRect<float> GRectF;
typedef GRect<gint32> GRectN;

template <typename T>
class GEdge {
public:
    GEdge() : left(0), right(0), top(0), bottom(0) {}
    GEdge(T l,T r,T t,T b) : left(l), right(r), top(t), bottom(b) {}
    
    T left;
    T right;
    T top;
    T bottom;
};

//Funs
template <typename T1, typename T2>
GPoint<T1> GPointChange(GPoint<T2> v) {
    return GPoint<T1>((T1)v.x,(T1)v.y);
}

template <typename T1, typename T2>
GSize<T1> GSizeChange(GSize<T2> v) {
    return GSize<T1>((T1)v.width,(T1)v.height);
}

template <typename T1, typename T2>
GRect<T1> GRectChange(GRect<T2> v) {
    return GRect<T1>((T1)v.origin.x,(T1)v.origin.y,(T1)v.size.width,(T1)v.size.height);
}

template <typename T1, typename T2>
GEdge<T1> GEdgeChange(GEdge<T2> v) {
    return GEdge<T1>((T1)v.origin.x,(T1)v.origin.y,(T1)v.size.width,(T1)v.size.height);
}

#endif /* GGeometry_h */
