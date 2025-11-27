#pragma once
#include <windows.h>
#include <dbghelp.h>
#pragma comment(lib, "dbghelp.lib")

class Dump
{
public:
    // 전역 예외 필터 등록
    static void Initialize()
    {
        // 전역 예외 필터 등록
        SetUnhandledExceptionFilter(ExceptionFilter);
    }

private:
    // 실제 예외 필터 함수
    static LONG WINAPI ExceptionFilter(_EXCEPTION_POINTERS* pExceptionPointers)
    {
        CreateMiniDump(pExceptionPointers);

        MessageBoxA(NULL,
            "Unhandled Exception 발생! 덤프 파일이 생성되었습니다.",
            "Crash",
            MB_OK | MB_ICONERROR);

        return EXCEPTION_EXECUTE_HANDLER;
    }

    // 덤프 파일 생성
    static void CreateMiniDump(_EXCEPTION_POINTERS* pExceptionPointers)
    {
        // 파일명: crash_YYYYMMDD_HHMMSS.dmp
        time_t now = time(NULL);
        struct tm t;
        localtime_s(&t, &now);

        char fileName[128];
        sprintf_s(fileName,
            "crash_%04d%02d%02d_%02d%02d%02d.dmp",
            t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
            t.tm_hour, t.tm_min, t.tm_sec
        );

        HANDLE hFile = CreateFileA(
            fileName,
            GENERIC_WRITE,
            FILE_SHARE_WRITE,
            NULL,
            CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL,
            NULL
        );

        if (hFile == INVALID_HANDLE_VALUE)
            return;

        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ExceptionPointers = pExceptionPointers;
        dumpInfo.ClientPointers = FALSE;

        MiniDumpWriteDump(
            GetCurrentProcess(),
            GetCurrentProcessId(),
            hFile,
            MiniDumpWithFullMemory,
            &dumpInfo,
            NULL,
            NULL
        );

        CloseHandle(hFile);
    }
};