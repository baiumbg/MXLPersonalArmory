#pragma once

#include <windows.h>

extern const DWORD DLLBASE_BNCLIENT;
extern const DWORD DLLBASE_D2CLIENT;
extern const DWORD DLLBASE_D2CMP;
extern const DWORD DLLBASE_D2COMMON;
extern const DWORD DLLBASE_D2DDRAW;
extern const DWORD DLLBASE_D2DIRECT3D;
extern const DWORD DLLBASE_D2GAME;
extern const DWORD DLLBASE_D2GDI;
extern const DWORD DLLBASE_D2GFX;
extern const DWORD DLLBASE_D2GLIDE;
extern const DWORD DLLBASE_D2LANG;
extern const DWORD DLLBASE_D2LAUNCH;
extern const DWORD DLLBASE_D2MCPCLIENT;
extern const DWORD DLLBASE_D2MULTI;
extern const DWORD DLLBASE_D2NET;
extern const DWORD DLLBASE_D2SOUND;
extern const DWORD DLLBASE_D2WIN;
extern const DWORD DLLBASE_FOG;
extern const DWORD DLLBASE_STORM;
extern const DWORD DLLBASE_IJL11;
extern const DWORD DLLBASE_BINKW32;
extern const DWORD DLLBASE_SMACKW32;

DWORD __fastcall GetDllOffset(const char* ModuleName, DWORD BaseAddress, int Offset);