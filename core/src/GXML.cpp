//
//  GXML.cpp
//  GX
//
//  Created by GuGengxin.
//  Copyright by gxengine.com
//

#include "GXML.h"
//Down include other h file
#include <expat_config.h>
#include <expat.h>
//Up include other h file
#include "GXGObject.h"


GX_GOBJECT_IMPLEMENT(GXML::Data, GObject);

GXML::Data::Data()
{
    
}

GXML::Data::~Data()
{
    
}



//static int Depth;
//
//static void XMLCALL
//start(void *data, const XML_Char *el, const XML_Char **attr)
//{
//    int i;
//    (void)data;
//    
//    for (i = 0; i < Depth; i++)
//        printf("  ");
//    
//    printf("%s", el);
//    
//    for (i = 0; attr[i]; i += 2) {
//        printf(" %s='%s'", attr[i], attr[i + 1]);
//    }
//    
//    printf("\n");
//    Depth++;
//}
//
//static void XMLCALL
//end(void *data, const XML_Char *el)
//{
//    (void)data;
//    (void)el;
//    
//    Depth--;
//}
//
//static void XMLCALL
//characterData(void *userData, const XML_Char *s, int len)
//{
//    for (int i=0; i<len; i++) {
//        printf("%c",s[i]);
//    }
//}
//
//static void XMLCALL
//processingInstruction(void *userData, const XML_Char *target, const XML_Char *data)
//{
//    printf("%s %s",target,data);
//}
//
//GMap<GString, GString>* GXML::read(GReader* reader)
//{
//    XML_Parser p = XML_ParserCreate(NULL);
//    if (!p) {
//        return NULL;
//    }
//    
//    XML_SetElementHandler(p, start, end);
//    XML_SetCharacterDataHandler(p,characterData);
//    XML_SetProcessingInstructionHandler(p, processingInstruction);
//    char buff[2048];
//    
//    GMap<GString, GString>* res=GMap<GString, GString>::alloc();
//    XML_SetUserData(p, res);
//    
//    Depth=0;
//    
//    while (true) {
//        gint len=reader->read(buff, sizeof(buff));
//        int done=0;
//        
//        if (len<0) {
//            GO::release(res);
//            XML_ParserFree(p);
//            return NULL;
//        }
//        else if(len<sizeof(buff)) {
//            done=1;
//        }
//        
//        if (XML_Parse(p, buff, GX_CAST_S(int, len), done) == XML_STATUS_ERROR) {
////            fprintf(stderr, "Parse error at line %" XML_FMT_INT_MOD "u:\n%s\n",
////                    XML_GetCurrentLineNumber(p),
////                    XML_ErrorString(XML_GetErrorCode(p)));
//            GO::release(res);
//            XML_ParserFree(p);
//            return NULL;
//        }
//        
//        if (done) {
//            break;
//        }
//    }
//    
//    XML_ParserFree(p);
//    GO::autorelease(res);
//    return res;
//}


