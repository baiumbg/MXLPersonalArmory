#pragma once

#include <windows.h>
#include <D2DLLBases.h>
#include <D2Structs.h>
#include <D2Helpers.h>

#pragma optimize ("", off)

#define D2FUNC(DLL, NAME, RETURN, CONV, ARGS, OFFSET) typedef RETURN (CONV* DLL##_##NAME##_t) ARGS; __declspec(selectany) extern DLL##_##NAME##_t DLL##_##NAME = (DLL##_##NAME##_t)GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);
#define D2VAR(DLL, NAME, TYPE, OFFSET) typedef TYPE DLL##_##NAME##_vt; __declspec(selectany) extern DLL##_##NAME##_vt * DLL##_##NAME = (DLL##_##NAME##_vt *)GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);
#define D2PTR(DLL, NAME, OFFSET) __declspec(selectany) extern DWORD NAME = GetDllOffset(#DLL, DLLBASE_##DLL, OFFSET);

extern DWORD __fastcall GetDllOffset(const char* ModuleName, DWORD BaseAddress, int Offset);

// D2Client.dll pointers
D2FUNC(D2CLIENT, Print, void, __stdcall, (const wchar_t* wMessage, int nColor), 0x7D850)
D2FUNC(D2CLIENT, GetPlayerUnit, UnitAny*, __stdcall, (void), 0xA4D60)
D2FUNC(D2CLIENT, GetUiVar_I, DWORD, __fastcall, (DWORD dwVarNo), 0xBE400)

// D2GFX.dll pointers
D2FUNC(D2GFX, GetHwnd, HWND, __stdcall, (void), -10048)

#pragma optimize ("", on)

#define D2CLIENT_GetUIState(dwVarNo) (D2CLIENT_GetUIVar_STUB(dwVarNo))