#include "GCSLWMainLine.h"

GCSLWMainLine::GCSLWMainLine(QObject *parent) : GCSLWriter(parent)
{

}

bool GCSLWMainLine::compile(GCSLTokenReader &reader, GCSLError *errOut)
{
    GCSLToken::Type types[]={
        GCSLToken::T_S_Brackets_L  , // "("
        GCSLToken::T_S_Brackets_R  , // ")"
        GCSLToken::T_M_Brackets_L  , // "["
        GCSLToken::T_M_Brackets_R  , // "]"
        GCSLToken::T_B_Brackets_L  , // "{"
        GCSLToken::T_B_Brackets_R  , // "}"
        GCSLToken::T_Comma         , // ","
        GCSLToken::T_Equal         , // "="
        GCSLToken::T_EqualEqual    , // "=="
        GCSLToken::T_Plus          , // "+"
        GCSLToken::T_PlusPlus      , // "++"
        GCSLToken::T_PlusEqual     , // "+="
        GCSLToken::T_Minus         , // "-"
        GCSLToken::T_MinusMinus    , // "--"
        GCSLToken::T_MinusEqual    , // "-="
        GCSLToken::T_Multiply      , // "*"
        GCSLToken::T_MultiplyEqual , // "*="
        GCSLToken::T_Div           , // "/"
        GCSLToken::T_DivEqual      , // "/="
        GCSLToken::T_Period        , // "."
        GCSLToken::T_Lowp          , // "lowp"
        GCSLToken::T_Medi          , // "medi"
        GCSLToken::T_High          , // "high"
        GCSLToken::T_Float         , // "float"
        GCSLToken::T_Vec2          , // "vec2"
        GCSLToken::T_Vec3          , // "vec3"
        GCSLToken::T_Vec4          , // "vec4"
        GCSLToken::T_Mat2          , // "mat2"
        GCSLToken::T_Mat3          , // "mat3"
        GCSLToken::T_Mat4          , // "mat4"
        GCSLToken::T_Tex1d         , // "tex1d"
        GCSLToken::T_Tex2d         , // "tex2d"
        GCSLToken::T_gx_Position   , // "gx_Position"
        GCSLToken::T_gx_FragColor  , // "gx_FragColor"
    };

    reader.ungetToken();

    while(true) {
        GCSLToken* token=reader.getToken();

        if(token->isSemicolon()) {
            return true;
        }

        int i=0;
        for(;i<(int)(sizeof(types)/sizeof(types[0]));i++) {
            if(token->getType()==types[i]) {
                m_Tokens.append(token);
                break;
            }
        }

        if(i>=(int)(sizeof(types)/sizeof(types[0]))) {
            if(errOut) {
                errOut->setCode(GCSLError::C_UnexceptToken);
                errOut->setRC(token);
            }
            return false;
        }
    }
    return true;
}
