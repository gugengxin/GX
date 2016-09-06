#ifndef GCSLTOKEN_H
#define GCSLTOKEN_H

#include <QObject>
#include "GCSLReader.h"


class GCSLToken : public QObject
{
    Q_OBJECT
public:
    typedef enum _Type {
        T_Unknown    =-1,
        T_Semicolon  =0 , // ";"
        T_S_Brackets_L  , // "("
        T_S_Brackets_R  , // ")"
        T_M_Brackets_L  , // "["
        T_M_Brackets_R  , // "]"
        T_B_Brackets_L  , // "{"
        T_B_Brackets_R  , // "}"
        T_Comma         , // ","
        T_Equal         , // "="
        T_EqualEqual    , // "=="
        T_Plus          , // "+"
        T_PlusPlus      , // "++"
        T_PlusEqual     , // "+="
        T_Minus         , // "-"
        T_MinusMinus    , // "--"
        T_MinusEqual    , // "-="
        T_Multiply      , // "*"
        T_MultiplyEqual , // "*="
        T_Div           , // "/"
        T_DivEqual      , // "/="
        T_Period        , // "."
        T_And           , // "&&"
        T_Or            , // "||"
        T_Not           , // "!"
        T_Colon         , // ":"
        T_HT_Def        , // "#def"
        T_HT_If         , // "#if"
        T_HT_Else       , // "#else"
        T_HT_Elif       , // "#elif"
        T_HT_End        , // "#end"
        T_Vs            , // "vs"
        T_Fp            , // "fp"
        T_Main          , // "main"
        T_Lowp          , // "lowp"
        T_Medi          , // "medi"
        T_High          , // "high"
        T_Float         , // "float"
        T_Vec2          , // "vec2"
        T_Vec3          , // "vec3"
        T_Vec4          , // "vec4"
        T_Mat2          , // "mat2"
        T_Mat3          , // "mat3"
        T_Mat4          , // "mat4"
        T_Tex1d         , // "tex1d"
        T_Tex2d         , // "tex2d"
        T_Layout        , // "layout"
        T_Buffer        , // "buffer"
        T_Bridge        , // "bridge"
        T_Texture       , // "texture"

        T_HL_POSITION      , // "hl_POSITION"
        T_HL_TEXCOORD      , // "hl_TEXCOORD"
        T_HL_COLOR         , // "hl_COLOR"
        T_M_ATTRIBUTE      , // "m_attribute",

        T_gx_Position   , // "gx_Position"
        T_gx_FragColor  , // "gx_FragColor"

        T_Mul           , // "mul"

        T_Variable      ,
        T_Integer       ,
        T_Floating      ,

        T_EOF,
    } Type;
public:
    explicit GCSLToken(QObject *parent = 0);

    void setType(Type v,const char* ID) {
        m_Type=v;
        m_ID=ID;
    }
    void setType(Type v,const QString& ID) {
        m_Type=v;
        m_ID=ID;
    }
    void setRC(int row,int col) {
        m_Row=row;
        m_Column=col;
    }
    void setRC(GCSLReader& reader) {
        m_Row=reader.getRow();
        m_Column=reader.getColumn();
    }

    Type getType() {
        return m_Type;
    }
    QString& getID() {
        return m_ID;
    }

    int getRow() {
        return m_Row;
    }
    int getColumn() {
        return m_Column;
    }

    bool isHT() {
        return m_Type==T_HT_Def     ||
               m_Type==T_HT_If      ||
               m_Type==T_HT_Else    ||
               m_Type==T_HT_Elif    ||
               m_Type==T_HT_End;
    }
    bool isLMH() {
        return m_Type==T_Lowp     ||
               m_Type==T_Medi      ||
               m_Type==T_High;
    }
    bool isSemantic() {
        return m_Type==T_HL_POSITION     ||
               m_Type==T_HL_TEXCOORD      ||
               m_Type==T_HL_COLOR;
    }
    bool isAttribute() {
        return m_Type==T_M_ATTRIBUTE;
    }

    bool isSemicolon() {
        return m_Type==T_Semicolon;
    }
    bool isVec() {
        return m_Type==T_Vec2     ||
               m_Type==T_Vec3      ||
               m_Type==T_Vec4;
    }
    bool isMat() {
        return m_Type==T_Mat2     ||
               m_Type==T_Mat3      ||
               m_Type==T_Mat4;
    }
    bool isFloat() {
        return m_Type==T_Float;
    }
    bool isTex() {
        return m_Type==T_Tex1d || m_Type==T_Tex2d;
    }
    bool isSymbol() {
        return m_Type<T_HT_Def;
    }

private:
    Type    m_Type;
    QString m_ID;
    int     m_Row;
    int     m_Column;
};

#endif // GCSLTOKEN_H
