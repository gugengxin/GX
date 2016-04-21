#define _CRT_SECURE_NO_WARNINGS
#include "GCString.h"
#include <stdarg.h>
#include <stdlib.h>

namespace GC {
    
    const int utf8BOMBytes=3;
    const unsigned char utf8BOM[utf8BOMBytes]={(const unsigned char)0xEF,(const unsigned char)0xBB,(const unsigned char)0xBF};
    
    
    static void* _readFileData(const TCHAR* filePath,int& lenOut)
    {
        void* res = NULL;
        int outLen=-1;
        
        FILE* fp = _tfopen(filePath, _T("rb"));
        if (fp) {
            fseek(fp, 0, SEEK_END);
            outLen = (int)ftell(fp);
            fseek(fp, 0, SEEK_SET);
            
            if (outLen > 0) {
                res = malloc(outLen);
                if(fread(res, 1, outLen, fp)!=outLen) {
                    free(res);
                    res=NULL;
                    outLen=-1;
                }
            }
            fclose(fp);
        }
        lenOut=outLen;
        return res;
    }
    
    bool readFileString(const TCHAR* filePath,SEncoding guessEC,NString& strOut)
    {
        int len;
        void* p=_readFileData(filePath, len);
        
        if (len>=0) {
            
            if (len==0 || !p) {
                strOut.append("");
                strOut.setHasBOM(false);
                strOut.SetEncoding(guessEC);
            }
            else {
                if (len>=utf8BOMBytes && memcmp(utf8BOM, p, utf8BOMBytes)==0) {
                    strOut.setHasBOM(true);
                    strOut.SetEncoding(SEC_Utf8);
                    strOut.append(((char*)p)+utf8BOMBytes,len-utf8BOMBytes);
                }
                else {
                    strOut.setHasBOM(false);
                    strOut.SetEncoding(guessEC);
                    strOut.append((char*)p,len);
                }
            }
            if (p) {
                free(p);
            }
            return true;
        }
        return false;
    }
    bool readFileString(const TCHAR* filePath,SEncoding guessEC,WString& strOut)
    {
        int len;
        void* p=_readFileData(filePath, len);
        
        if (len>=0) {
            strOut.SetEncoding(SEC_Utf16);
            if (len==0) {
                strOut.append(L"");
            }
            else if(p) {
                strOut.append((wchar_t*)p,len);
            }
            if (p) {
                free(p);
            }
            return true;
        }
        return false;
    }

	bool _writeFileData(const TCHAR* filePath, const void* data, int len, ...)
	{
		FILE* fp = _tfopen(filePath, _T("wb"));
		if (!fp) {
			return false;
		}
		va_list va;
		va_start(va, len);
		const void* dataTemp = data;
		int dataTempLen = len;
		while (true)
		{
			fwrite(dataTemp, dataTempLen, 1, fp);

			dataTemp = va_arg(va, const void*);
			if (dataTemp) {
				dataTempLen = va_arg(va, int);
			}
			else {
				break;
			}
		}
		va_end(va);
		fclose(fp);
		return true;
	}
    
    bool writeFileString(const TCHAR* filePath, NString& str)
    {
        if (str.getHasBOM()) {
            return _writeFileData(filePath, utf8BOM, utf8BOMBytes, str.data(), (int)str.size(), NULL);
        }
        else {
            return _writeFileData(filePath, str.data(), (int)str.size(), NULL);
        }
    }
    
    bool writeFileString(const TCHAR* filePath, WString& str)
    {
        return _writeFileData(filePath, str.data(), (int)str.size(),NULL);
    }

	void replaceString(NString& str, const char* strFrom, const char* strTo, int idxStart, int idxCount)
	{
		int flen = (int)strlen(strFrom);
		int tlen = (int)strlen(strTo);
		if (flen > 0) {
			int idx = 0;
			int num = -1;
			while (true)
			{
				idx = (int)str.find(strFrom, idx);
				if (idx >= 0) {
					num++;
					if (idxCount <= 0 || (num >= idxStart && num<idxStart + idxCount)) {
						str.replace(idx, flen, strTo);
						idx += tlen;
					}
					else {
						idx += flen;
					}
				}
				else {
					break;
				}
			}
		}
	}

	void replaceString(WString& str, const wchar_t* strFrom, const wchar_t* strTo, int idxStart, int idxCount)
	{
		int flen = (int)wcslen(strFrom);
		int tlen = (int)wcslen(strTo);
		if (flen > 0) {
			int idx = 0;
            int num=-1;
			while (true)
			{
				idx = (int)str.find(strFrom, idx);
				if (idx >= 0) {
                    num++;
                    if (idxCount<=0 || (num>=idxStart && num<idxStart+idxCount)) {
                        str.replace(idx, flen, strTo);
						idx += tlen;
                    }
					else {
						idx += flen;
					}
				}
				else {
					break;
				}
			}
		}
	}


	void replaceString(NString& str, const char* strFromPre, const char* strFromSuf, const char* strTo, int idxStart, int idxCount)
	{
		int fplen = (int)strlen(strFromPre);
		int fslen = (int)strlen(strFromSuf);
		int tlen = (int)strlen(strTo);
		if (fplen > 0 && fslen > 0) {
			int i = 0;
			int idx = -1;
			while (true) {
				i = (int)str.find(strFromPre, i);
				if (i >= 0) {
					i += fplen;
					int start = i;
					i = (int)str.find(strFromSuf, i);
					if (i >= 0) {
						idx++;
						if (idxCount <= 0 || (idx >= idxStart && idx<idxStart + idxCount)) {
							int len = i - start;
							str.replace(start, len, strTo);
							i = i - (len - tlen) + fslen;
						}
						else {
							i += fslen;
						}
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
		}
	}
	void replaceString(WString& str, const wchar_t* strFromPre, const wchar_t* strFromSuf, const wchar_t* strTo, int idxStart, int idxCount)
	{
		int fplen = (int)wcslen(strFromPre);
		int fslen = (int)wcslen(strFromSuf);
		int tlen = (int)wcslen(strTo);
		if (fplen > 0 && fslen > 0) {
			int i = 0;
			int idx = -1;
			while (true) {
				i = (int)str.find(strFromPre, i);
				if (i >= 0) {
					i += fplen;
					int start = i;
					i = (int)str.find(strFromSuf, i);
					if (i >= 0) {
						idx++;
						if (idxCount <= 0 || (idx >= idxStart && idx<idxStart + idxCount)) {
							int len = i - start;
							str.replace(start, len, strTo);
							i = i - (len - tlen) + fslen;
						}
						else {
							i += fslen;
						}
					}
					else {
						break;
					}
				}
				else {
					break;
				}
			}
		}
	}
}