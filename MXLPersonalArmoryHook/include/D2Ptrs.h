#pragma once

#include <windows.h>
#include <D2DLLBases.h>

#define D2FUNC(DLL, NAME, RETURN, CONV, ARGS, OFFSET) typedef RETURN (CONV* DLL##_##NAME##_t) ARGS; __declspec(selectany) extern DLL##_##NAME##_t DLL##_##NAME = (DLL##_##NAME##_t)GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);
#define D2VAR(DLL, NAME, TYPE, OFFSET) typedef TYPE DLL##_##NAME##_vt; __declspec(selectany) extern DLL##_##NAME##_vt * DLL##_##NAME = (DLL##_##NAME##_vt *)GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);
#define D2PTR(DLL, NAME, OFFSET) __declspec(selectany) extern DWORD NAME = GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);

extern DWORD __fastcall GetDllOffset(const char* ModuleName, DWORD BaseAddress, int Offset);

// D2Client.dll pointers
D2FUNC(D2CLIENT, Print, void, __stdcall, (wchar_t* wMessage, int nColor), 0x7D850)