#include "MPQStats.h"
#include "D2Ptrs.h"

MPQTable BaseStatTable[] = {
    //DWORD dwEntry, DWORD dwMaxEntriesOffset, BinField* pTable, char szTableName, WORD wTableSize, WORD wUnknown
    {0xBCC,			0xBD4,		itemstatcostTable,	"itemstatcost",	ARRAYSIZE(itemstatcostTable),	0xFFFF},
    {0}
};

DWORD GetBaseTable(int table, int row)
{
    DWORD dwResult = NULL;
    DWORD dwD2MPQTable = NULL;

    if (table < sizeof(BaseStatTable))
    {
        DWORD dwTableOffset = BaseStatTable[table].dwEntry;

        if (dwTableOffset <= 0xFFFF)
            dwD2MPQTable = (*D2COMMON_sgptDataTable);
        else dwD2MPQTable = NULL;

        DWORD dwMaxEntriesOffset = BaseStatTable[table].dwMaxEntriesOffset;

        DWORD dwMaxEntries;
        if (dwMaxEntriesOffset)
            dwMaxEntries = *(DWORD*)(dwMaxEntriesOffset + dwD2MPQTable);
        else dwMaxEntries = 0xFF;

        if ((DWORD)row < dwMaxEntries)
        {
            DWORD dwMultiplicator = BaseStatTable[table].pTable[BaseStatTable[table].wTableSize - 1].dwFieldOffset;
            DWORD dwTable = row * dwMultiplicator;
            dwResult = *(DWORD*)(dwTableOffset + dwD2MPQTable) + dwTable;
        }
    }

    return dwResult;
}


bool FillBaseStat(const char* szTable, int row, const char* szStat, void* result, size_t size)
{
    int table = -1;
    for (int i = 0; BaseStatTable[i].pTable != NULL; i++)
        if (!_strcmpi(szTable, BaseStatTable[i].szTableName))
        {
            table = i;
            break;
        }

    if (table == -1)
        return false;

    return FillBaseStat(table, row, szStat, result, size);
}

bool FillBaseStat(const char* szTable, int row, int column, void* result, size_t size)
{
    int table = -1;
    for (int i = 0; BaseStatTable[i].pTable != NULL; i++)
        if (!_strcmpi(szTable, BaseStatTable[i].szTableName))
        {
            table = i;
            break;
        }

    if (table == -1)
        return false;

    return FillBaseStat(table, row, column, result, size);
}

bool FillBaseStat(int table, int row, const char* szStat, void* result, size_t size)
{
    BinField* pTable = BaseStatTable[table].pTable;

    int column = -1;
    for (int i = 0; i < BaseStatTable[table].wTableSize; i++)
        if (!_strcmpi(szStat, pTable[i].szFieldName))
        {
            column = i;
            break;
        }

    if (column == -1)
        return false;

    return FillBaseStat(table, row, column, result, size);
}

bool FillBaseStat(int table, int row, int column, void* result, size_t size)
{
    BinField* pTable = BaseStatTable[table].pTable;
    DWORD dwRetValue = GetBaseTable(table, row);

    if (!dwRetValue || column > BaseStatTable[table].wTableSize)
        return false;

    DWORD dwHelperSize = pTable[column + 1].dwFieldOffset - pTable[column].dwFieldOffset;
    if (dwHelperSize > 4)
        dwHelperSize = 4;
    switch (pTable[column].eFieldType)
    {
    case FIELDTYPE_DATA_ASCII:
        if (size < pTable[column].dwFieldLength)
            return false;
        memcpy_s(result, pTable[column].dwFieldLength, (BYTE*)(dwRetValue + pTable[column].dwFieldOffset), pTable[column].dwFieldLength);
        break;
    case FIELDTYPE_DATA_DWORD:
        memcpy(result, (LPVOID)(dwRetValue + pTable[column].dwFieldOffset), sizeof(DWORD));
        break;
    case FIELDTYPE_CALC_TO_DWORD:
    case FIELDTYPE_NAME_TO_DWORD:
    case FIELDTYPE_DATA_DWORD_2:
        memcpy(result, (LPVOID)(dwRetValue + pTable[column].dwFieldOffset), sizeof(DWORD));
        break;
    case FIELDTYPE_UNKNOWN_11:
        memcpy(result, (LPVOID)(dwRetValue + pTable[column].dwFieldOffset), sizeof(DWORD));
        break;
    case FIELDTYPE_NAME_TO_INDEX_2:
    case FIELDTYPE_NAME_TO_WORD_2:
        memcpy(result, (LPVOID)(dwRetValue + pTable[column].dwFieldOffset), sizeof(WORD));
        if (((WORD)result) >= 0xFFFF)
            *(WORD*)result = (((WORD)result) - 0xFFFF) * -1;
        break;
    case FIELDTYPE_NAME_TO_INDEX:
    case FIELDTYPE_NAME_TO_WORD:
    case FIELDTYPE_KEY_TO_WORD:
    case FIELDTYPE_DATA_WORD:
    case FIELDTYPE_CODE_TO_WORD:
        memcpy(result, (LPVOID)(dwRetValue + pTable[column].dwFieldOffset), sizeof(WORD));
        break;
    case FIELDTYPE_CODE_TO_BYTE:
    case FIELDTYPE_DATA_BYTE_2:
    case FIELDTYPE_DATA_BYTE:
        memcpy(result, (LPVOID)(dwRetValue + pTable[column].dwFieldOffset), dwHelperSize);
        break;
    case FIELDTYPE_DATA_BIT:
        memcpy(result, (LPVOID)(dwRetValue + pTable[column].dwFieldOffset), sizeof(DWORD));
        *(BOOL*)result = (*(BOOL*)result & (1 << pTable[column].dwFieldLength)) ? 1 : 0;
        break;
    case FIELDTYPE_ASCII_TO_CODE:
    case FIELDTYPE_DATA_RAW:
        if (size != 5)
            return false;
        memcpy(result, (LPVOID)(dwRetValue + pTable[column].dwFieldOffset), size - 1);
        break;
    case FIELDTYPE_MONSTER_COMPS:
        // ..? :E
        return false;
    }

    return true;
}