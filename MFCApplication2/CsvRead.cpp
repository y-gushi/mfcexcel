#include "CsvRead.h"

CsvRead::CsvRead() {
    csvroot = nullptr;
}

CsvRead::~CsvRead()
{
    free(csvroot);
}

UINT8* CsvRead::strtalloc(UINT8* a, UINT8* b) {
    size_t ms = strlen((char*)b) + 1;
    a = (UINT8*)malloc(sizeof(UINT8) * ms);
    strcpy_s((char*)a, ms, (char*)b);

    return a;
}

Sizes* CsvRead::addSize(Sizes* si, UINT8* s, UINT8* v) {
    if (!si) {
        si = (Sizes*)malloc(sizeof(Sizes));
        si->size = strtalloc(si->size, s);
        si->val = strtalloc(si->val, v);
        si->next = nullptr;
    }
    else
    {
        si->next = addSize(si->next, s, v);
    }
    return si;
}

itemColors* CsvRead::addColors(itemColors* col, UINT8* c, UINT8* s, UINT8* val) {
    if (!col) {
        col = (itemColors*)malloc(sizeof(itemColors));
        col->s = nullptr;
        col->s = addSize(col->s, s, val);
        col->color = strtalloc(col->color, c);
        col->next = nullptr;
    }
    else if (strcmp((char*)c, (char*)col->color) == 0 && col) {
        //カラー同じ
        col->s = addSize(col->s, s, val);
    }
    else {
        //new
        col->next = addColors(col->next, c, s, val);
    }
    return col;
}

CsvItemandRid* CsvRead::addCsvItem(CsvItemandRid* c, UINT8* it, UINT8* s, UINT8* col, UINT8* v) {
    if (!c) {
        c = (CsvItemandRid*)malloc(sizeof(CsvItemandRid));
        c->it = strtalloc(c->it, it);
        c->c = nullptr;
        c->c = addColors(c->c, col, s, v);
        c->rid = nullptr;
        c->Newrid = nullptr;
        c->next = nullptr;
    }
    else if (strcmp((char*)it, (char*)c->it) == 0) {
        //品番同じ
        c->c = addColors(c->c, col, s, v);
    }
    else {
        //new
        c->next = addCsvItem(c->next, it, s, col, v);
    }
    return c;
}

void CsvRead::freesize(Sizes* s) {
    Sizes* p;
    while (s) {
        p = s->next;
        free(s->size);
        free(s->val);
        free(s);
        s = p;
    }
}

void CsvRead::freecolor(itemColors* c) {
    itemColors* p;
    while (c) {
        p = c->next;
        free(c->color);
        freesize(c->s);
        free(c);
        c = p;
    }
}

void CsvRead::freeitem(CsvItemandRid* cv) {
    CsvItemandRid* p;
    while (cv) {
        p = cv->next;
        free(cv->it);
        free(cv->rid);
        free(cv->Newrid);
        freecolor(cv->c);
        free(cv);
        cv = p;
    }
}

int CsvRead::readCsv(char* fn) {
    std::ifstream fin(fn, std::ios::in | std::ios::binary);
    if (!fin)
        return 1;

    UINT8 d = 0;
    int comma = 0;
    UINT8 item[50] = { 0 };
    UINT8 siz[10] = { 0 };
    UINT8 col[256] = { 0 };
    UINT8 val[10] = { 0 };
    size_t ilen = 0;
    size_t slen = 0;
    size_t clen = 0;
    size_t vlen = 0;
    char e = '0';

    while (d != '\n') {
        fin.read((char*)&d, sizeof(char));
    }

    while (!fin.eof()) {
        fin.read((char*)&d, sizeof(char));

        if (d == ',') {
            comma++;
        }

        if (comma == 1) {
            //item列
            ilen = 0;
            fin.read((char*)&d, sizeof(char));
            if (d == '"')
                e = '"';
            else
                e = ',';

            while (d != e) {
                item[ilen] = d;
                ilen++;
                fin.read((char*)&d, sizeof(char));
            }
            item[ilen] = '\0';
            if (e == ',')
                comma++;
        }

        if (comma == 5) {
            //サイズ列
            slen = 0;
            fin.read((char*)&d, sizeof(char));
            if (d == '"')
                e = '"';
            else
                e = ',';
            while (d != e) {
                siz[slen] = d;
                slen++;
                fin.read((char*)&d, sizeof(char));
            }
            siz[slen] = '\0';
            if (e == ',')
                comma++;
        }

        if (comma == 7) {
            //カラー列
            clen = 0;
            fin.read((char*)&d, sizeof(char));
            if (d == '"')
                e = '"';
            else
                e = ',';
            while (d != e) {
                col[clen] = d;
                clen++;
                fin.read((char*)&d, sizeof(char));
            }
            col[clen] = '\0';
            if (e == ',')
                comma++;
        }

        if (comma == 10) {
            //在庫列
            vlen = 0;
            fin.read((char*)&d, sizeof(char));
            if (d == '"')
                e = '"';
            else
                e = ',';
            while (d != e) {
                val[vlen] = d;
                vlen++;
                fin.read((char*)&d, sizeof(char));
            }
            val[vlen] = '\0';
            if (e == ',')
                comma++;
        }

        if (d == '\n') {

            csvroot = addCsvItem(csvroot, item, siz, col, val);

            comma = 0;
        }
    }

    fin.close();

    return 0;
}
