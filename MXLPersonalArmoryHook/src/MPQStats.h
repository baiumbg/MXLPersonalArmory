#pragma once

#include <windows.h>

enum
{
    FIELDTYPE_END = 0,
    FIELDTYPE_DATA_ASCII = 1,
    FIELDTYPE_DATA_DWORD = 2,
    FIELDTYPE_DATA_WORD = 3,
    FIELDTYPE_DATA_BYTE = 4,
    FIELDTYPE_UNKNOWN_5 = 5,
    FIELDTYPE_DATA_BYTE_2 = 6,
    FIELDTYPE_DATA_DWORD_2 = 8,
    FIELDTYPE_DATA_RAW = 9,
    FIELDTYPE_ASCII_TO_CODE = 10,
    FIELDTYPE_UNKNOWN_11 = 11,
    FIELDTYPE_UNKNOWN_12 = 12,
    FIELDTYPE_CODE_TO_BYTE = 13,
    FIELDTYPE_UNKNOWN_14 = 14,
    FIELDTYPE_CODE_TO_WORD = 15,
    FIELDTYPE_UNKNOWN_16 = 16,
    FIELDTYPE_NAME_TO_INDEX = 17,
    FIELDTYPE_NAME_TO_INDEX_2 = 18,
    FIELDTYPE_NAME_TO_DWORD = 19,
    FIELDTYPE_NAME_TO_WORD = 20,
    FIELDTYPE_NAME_TO_WORD_2 = 21,
    FIELDTYPE_KEY_TO_WORD = 22,
    FIELDTYPE_MONSTER_COMPS = 23,
    FIELDTYPE_UNKNOWN_24 = 24,
    FIELDTYPE_CALC_TO_DWORD = 25,
    FIELDTYPE_DATA_BIT = 26,
};

struct BinField
{
    char szFieldName[64];
    DWORD eFieldType;
    DWORD dwFieldLength;
    DWORD dwFieldOffset;
};

struct MPQTable
{
    DWORD dwEntry; // if > 0xFFFF it is not located in the exported mpq data..
    DWORD dwMaxEntriesOffset; // ""
    BinField* pTable;
    char szTableName[15];
    WORD wTableSize;
    WORD wUnknown;
};

DWORD GetBaseTable(int nBaseStat, int nClassId);
bool FillBaseStat(const char* szTable, int row, const char* szStat, void* result, size_t size);
bool FillBaseStat(const char* szTable, int row, int column, void* result, size_t size);
bool FillBaseStat(int table, int row, const char* szStat, void* result, size_t size);
bool FillBaseStat(int table, int row, int column, void* result, size_t size);

static BinField itemstatcostTable[] = {
    {"stat", FIELDTYPE_NAME_TO_INDEX, 0x0, 0x0},
    {"send other", FIELDTYPE_DATA_BIT, 0x0, 0x4},
    {"signed", FIELDTYPE_DATA_BIT, 0x1, 0x4},
    {"damagerelated", FIELDTYPE_DATA_BIT, 0x2, 0x4},
    {"itemspecific", FIELDTYPE_DATA_BIT, 0x3, 0x4},
    {"direct", FIELDTYPE_DATA_BIT, 0x4, 0x4},
    {"updateanimrate", FIELDTYPE_DATA_BIT, 0x9, 0x4},
    {"fmin", FIELDTYPE_DATA_BIT, 0xa, 0x4},
    {"fcallback", FIELDTYPE_DATA_BIT, 0xb, 0x4},
    {"saved", FIELDTYPE_DATA_BIT, 0xc, 0x4},
    {"csvsigned", FIELDTYPE_DATA_BIT, 0xd, 0x4},
    {"send bits", FIELDTYPE_DATA_BYTE, 0x0, 0x8},
    {"send param bits", FIELDTYPE_DATA_BYTE, 0x0, 0x9},
    {"csvbits", FIELDTYPE_DATA_BYTE, 0x0, 0xa},
    {"csvparam", FIELDTYPE_DATA_BYTE, 0x0, 0xb},
    {"divide", FIELDTYPE_DATA_DWORD, 0x0, 0xc},
    {"multiply", FIELDTYPE_DATA_DWORD_2, 0x0, 0x10},
    {"add", FIELDTYPE_DATA_DWORD, 0x0, 0x14},
    {"valshift", FIELDTYPE_DATA_BYTE, 0x0, 0x18},
    {"save bits", FIELDTYPE_DATA_BYTE, 0x0, 0x19},
    {"1.09-save bits", FIELDTYPE_DATA_BYTE, 0x0, 0x1a},
    {"save add", FIELDTYPE_DATA_DWORD_2, 0x0, 0x1c},
    {"1.09-save add", FIELDTYPE_DATA_DWORD_2, 0x0, 0x20},
    {"save param bits", FIELDTYPE_DATA_DWORD, 0x0, 0x24},
    {"minaccr", FIELDTYPE_DATA_DWORD, 0x0, 0x2c},
    {"encode", FIELDTYPE_DATA_BYTE, 0x0, 0x30},
    {"maxstat", FIELDTYPE_NAME_TO_WORD, 0x0, 0x32},
    {"descpriority", FIELDTYPE_DATA_WORD, 0x0, 0x34},
    {"descfunc", FIELDTYPE_DATA_BYTE, 0x0, 0x36},
    {"descval", FIELDTYPE_DATA_BYTE, 0x0, 0x37},
    {"descstrpos", FIELDTYPE_KEY_TO_WORD, 0x0, 0x38},
    {"descstrneg", FIELDTYPE_KEY_TO_WORD, 0x0, 0x3a},
    {"descstr2", FIELDTYPE_KEY_TO_WORD, 0x0, 0x3c},
    {"dgrp", FIELDTYPE_DATA_WORD, 0x0, 0x3e},
    {"dgrpfunc", FIELDTYPE_DATA_BYTE, 0x0, 0x40},
    {"dgrpval", FIELDTYPE_DATA_BYTE, 0x0, 0x41},
    {"dgrpstrpos", FIELDTYPE_KEY_TO_WORD, 0x0, 0x42},
    {"dgrpstrneg", FIELDTYPE_KEY_TO_WORD, 0x0, 0x44},
    {"dgrpstr2", FIELDTYPE_KEY_TO_WORD, 0x0, 0x46},
    {"itemevent1", FIELDTYPE_NAME_TO_WORD, 0x0, 0x48},
    {"itemevent2", FIELDTYPE_NAME_TO_WORD, 0x0, 0x4a},
    {"itemeventfunc1", FIELDTYPE_DATA_WORD, 0x0, 0x4c},
    {"itemeventfunc2", FIELDTYPE_DATA_WORD, 0x0, 0x4e},
    {"keepzero", FIELDTYPE_DATA_BYTE, 0x0, 0x50},
    {"op", FIELDTYPE_DATA_BYTE, 0x0, 0x54},
    {"op param", FIELDTYPE_DATA_BYTE, 0x0, 0x55},
    {"op base", FIELDTYPE_NAME_TO_WORD, 0x0, 0x56},
    {"op stat1", FIELDTYPE_NAME_TO_WORD, 0x0, 0x58},
    {"op stat2", FIELDTYPE_NAME_TO_WORD, 0x0, 0x5a},
    {"op stat3", FIELDTYPE_NAME_TO_WORD, 0x0, 0x5c},
    {"stuff", FIELDTYPE_DATA_DWORD, 0x0, 0x140},
    {"end", FIELDTYPE_END, 0x0, 0x144},
};