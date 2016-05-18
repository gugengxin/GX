#ifndef GCSLTOKEN_H
#define GCSLTOKEN_H

#include <QObject>



class GCSLToken : public QObject
{
    Q_OBJECT
public:
    typedef enum _Type {
        T_Semicolon,    //  ;
        T_S_Brackets_L, //  ()
        T_S_Brackets_R,
        T_M_Brackets_L, //  []
        T_M_Brackets_R,
        T_B_Brackets_L, //  {}
        T_B_Brackets_R,
        T_Comma,        //  ,
        T_Equal,        //  =
        T_EqualEqual,   //  ==
        T_Plus,         //  +
        T_PlusPlus,     //  ++
        T_PlusEqual,    //  +=
        T_Minus,        //  -
        T_MinusMinus,   //  --
        T_MinusEqual,   //  -=
        T_Multiply,     //  *
        T_MultiplyEqual,//  *=
        T_Div,          //  /
        T_DivEqual,     //  /=
        T_Period,       //  .
        T_Def,          //  #def
        T_If,           //  #if
        T_Else,         //  #else
        T_Elif,         //  #elif
        T_End,          //  #end
        T_Void,         //  void
        T_Vs,           //  vs
        T_Fp,           //  fp
        T_Main,         //  main
        T_Lowp,         //  lowp
        T_Medi,         //  medi
        T_High,         //  high
        T_Float,        //  float
        T_Vec,          //  vec[2,3,4]
        T_Mat,          //  mat[2,3,4]
        T_Tex,          //  tex[1,2]d
        T_Layout,       //  layout
        T_Buffer,       //  buffer
        T_Bridge,       //  bridge
        T_POSITION,     //  POSITION[0-9]
        T_TEXCOORD,     //  TEXCOORD[0-9]
        T_COLOR,        //  COLOR[0-9]
        T_gx_Position,  //  gx_Position
        T_gx_FragColor, //  gx_FragColor

        T_Variable,
        T_Number,

    } Type;
public:
    explicit GCSLToken(QObject *parent = 0);

    void setType(Type v) {
        m_Type=v;
    }

signals:

public slots:

private:
    Type m_Type;
};

#endif // GCSLTOKEN_H
