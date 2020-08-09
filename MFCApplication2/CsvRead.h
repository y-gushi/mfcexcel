#pragma once
#include <fstream>
#include "zaiko_souceFile/TagAndItems.h"

typedef unsigned char UINT8;

class CsvRead
{
public:
    CsvItemandRid* csvroot;

    CsvRead();
    ~CsvRead();

    UINT8* strtalloc(UINT8* a, UINT8* b);
    Sizes* addSize(Sizes* si, UINT8* s, UINT8* v);
    itemColors* addColors(itemColors* col, UINT8* c, UINT8* s, UINT8* val);
    CsvItemandRid* addCsvItem(CsvItemandRid* c, UINT8* it, UINT8* s, UINT8* col, UINT8* v);
    void freesize(Sizes* s);
    void freecolor(itemColors* c);
    void freeitem(CsvItemandRid* cv);
    void freematchitem(CsvItemandRid* cv);
    int readCsv(char* fn);
};