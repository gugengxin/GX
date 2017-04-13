#include "AppDge.h"


AppDge* AppDge::shared()
{
	static AppDge g_Obj;
	return &g_Obj;
}

AppDge::AppDge()
{
}


AppDge::~AppDge()
{
}

void AppDge::appDidFinishLaunching(GApplication* application)
{
    GX_UNUSED(application);
//	application->startGame(Game::gclass,initData.getOSWindowForLaunch());
    /*
	GString* str = GString::autoAlloc();
	str->format("%Hello!1234%").arg('A', 10).arg(L'新',3);
	GX_LOG_P1(PrioDEBUG, "AppDge", "%s", str->utf8String());

    //GZipReader* reader=GZipReader::alloc();
    //if(reader->open(GX_T("/ABC"))) {

    //}
    //GO::release(reader);

	GZipWriter* writer = GZipWriter::alloc();

	if (writer->open(GX_T(""), GZipWriter::ModeCreate)) {


	}

	GO::release(writer);
    //*/

    GDataWriter* writer=GDataWriter::autoAlloc();

    GData* data=GData::autoAlloc();

    if (writer->open(data)) {

        GEncoder encoder(writer);

        /*
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeB8 %d", (gint32)encoder.encodeB8(true));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeI8 %d", (gint32)encoder.encodeI8(12));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeU8 %d", (gint32)encoder.encodeU8(255));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeI16 %d", (gint32)encoder.encodeI16(1234));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeU16 %d", (gint32)encoder.encodeU16(4321));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeI32 %d", (gint32)encoder.encodeI32(123456));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeU32 %d", (gint32)encoder.encodeU32(654321));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeI64 %d", (gint32)encoder.encodeI64(12345678));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeU64 %d", (gint32)encoder.encodeU64(87654321));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeF32 %d", (gint32)encoder.encodeF32(1.123456f));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeF64 %d", (gint32)encoder.encodeF64(2.893274893274983));

        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeVI32 %d", (gint32)encoder.encodeVI32(123456));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeVU32 %d", (gint32)encoder.encodeVU32(654321));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeVI64 %d", (gint32)encoder.encodeVI64(12345678));
        GX_LOG_P1(PrioDEBUG, "AppDge", "encodeVU64 %d", (gint32)encoder.encodeVU64(87654321));
        //*/
        GX::VU64 v=1;
        for (int i=0; i<64; i++) {
            int res=(int)encoder.encodeVU64(v);
            if (res<0) {
                GX_LOG_W(PrioDEBUG, "AppDge", "encodeC Error");
            }
            else {
                GX_LOG_P2(PrioDEBUG, "AppDge", "encodeC %d 0x%llX", res,(unsigned long long)v);
                v=(v<<1)|1;
            }
        }

        GDataReader* reader=GDataReader::autoAlloc();
        if (reader->open(data)) {

            GDecoder decoder(reader);

            for (int i=0; i<64; i++) {
                int res=(int)decoder.decodeVU64(v);
                if (res<0) {
                    GX_LOG_W(PrioDEBUG, "AppDge", "decodeC Error");
                }
                else {
                    GX_LOG_P2(PrioDEBUG, "AppDge", "decodeC %d 0x%llX", res,(unsigned long long)v);
                }
            }


            //*
            {
                GX::B8 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeB8 %d %d", (gint32)decoder.decodeB8(v),(gint32)v);
            }
            {
                GX::I8 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeI8 %d %d", (gint32)decoder.decodeI8(v),(gint32)v);
            }
            {
                GX::U8 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeU8 %d %d", (gint32)decoder.decodeU8(v),(gint32)v);
            }
            {
                GX::I16 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeI16 %d %hd", (gint32)decoder.decodeI16(v),v);
            }
            {
                GX::U16 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeU16 %d %hu", (gint32)decoder.decodeU16(v),v);
            }
            {
                GX::I32 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeI32 %d %d", (gint32)decoder.decodeI32(v),v);
            }
            {
                GX::U32 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeU32 %d %u", (gint32)decoder.decodeU32(v),v);
            }
            {
                GX::I64 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeI64 %d %lld", (gint32)decoder.decodeI64(v),v);
            }
            {
                GX::U64 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeU64 %d %llu", (gint32)decoder.decodeU64(v),v);
            }
            {
                GX::F32 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeU32 %d %f", (gint32)decoder.decodeF32(v),v);
            }
            {
                GX::F64 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeI64 %d %lf", (gint32)decoder.decodeF64(v),v);
            }

            {
                GX::VI32 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeVI32 %d %d", (gint32)decoder.decodeVI32(v),v);
            }
            {
                GX::VU32 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeVU32 %d %u", (gint32)decoder.decodeVU32(v),v);
            }
            {
                GX::VI64 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeVI64 %d %lld", (gint32)decoder.decodeVI64(v),v);
            }
            {
                GX::VU64 v;
                GX_LOG_P2(PrioDEBUG, "AppDge", "decodeVU64 %d %llu", (gint32)decoder.decodeVU64(v),v);
            }
            //*/
        }

    }



//	application->addWindow(osWindow);
}
