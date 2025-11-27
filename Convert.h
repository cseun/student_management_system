#pragma once
#include <string>    // std::string 사용
#include <codecvt>
#include <locale>
#include <atlconv.h>
#include <afx.h>
#include "Convert.h"

class Convert {
public:
    static std::string CStringToStdString(const CString& cstr)
    {
        CW2A convert(cstr, CP_UTF8);
        return std::string(convert);
        //return std::string(CW2A(cstr));
    }
    static CString StdStringToCString(const std::string& str)
    {
        return CString(CA2W(str.c_str(), CP_UTF8));
    }
};
