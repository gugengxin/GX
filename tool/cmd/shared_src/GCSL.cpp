#include "GCSL.h"

/*
gxsl(GX Shading Language) 将被翻译成 glsl或hlsl

lowp medi high
float
vec2 vec3 vec4
mat2 mat3 mat4
tex1d tex2d
input
buffer
bridge
POSITION[0-9]
TEXCOORD[0-9]
register(b0,t0)


#def
#if
#else
#elif
#endif
void
#vs
fp
main

gx_Position
gx_FragColor

;
()
[]
{}
,
=
+
-
*
/

x.x






vs {
input {
    vec4 pos:POSITION;
    vec2 tex:TEXCOORD0;
    vec2 texMask:TEXCOORD0;
}
buffer {
    mat4 mvpMatrix;
}
bridge {

}

void main()
{

}
}
fp {
buffer {

}

void main()
{

}
}
//*/







GCSL::GCSL(QObject *parent) : QObject(parent)
{

}
