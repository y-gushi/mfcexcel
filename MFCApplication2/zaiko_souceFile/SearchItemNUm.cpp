#include "SearchItemNUm.h"

searchItemNum::searchItemNum(CsvItemandRid* itemstruct, Ctags* cs) {
    its = itemstruct;
    Cels = cs;
    Mstr = MargeaSearch();
    rootMat = nullptr;
}

searchItemNum::~searchItemNum() {

}

bool searchItemNum::searchitemNumber(UINT8* uniq, char* one, char* two, char* three, char* four, char* style, char* celstyle) {
    Row* sr = nullptr;
    sr = Cels->rows;
    CsvItemandRid* Item = nullptr;
    Item = its;
    UINT8* nr = nullptr;//文字入力行　配列
    int result = 0;
    const char* SaT[] = { "s", "1127" };
    bool incellflag = false;
    UINT8* matchItem = nullptr;

    while (sr) {//品番検索
        Item = its;
        while (Item) {
            if (sr->cells) {
                if (sr->cells->si) {
                    result = strcmp((const char*)sr->cells->si, (const char*)Item->it);//品番　シートデータの比較
                    if (result == 0) {
                        matchItem = Item->it;//一致品ばんコピー
                        C* cn = nullptr;
                        cn = sr->next->cells;//品番次の行
                        //最終列検索
                        while (cn->next) {
                            cn = cn->next;
                        }
                        inputColum = cn->col;//現最終列
                        changenum.ColumnIncliment(&inputColum);//最終列　+1
                        nr = changenum.InttoChar(sr->next->r, &result);//入力行
                        incolumn = changenum.ColumnNumtoArray(inputColum, &result);//最終列　配列変換
                        startR = sr->next->r;//品番次の行
                        incellflag = true;
                        break;
                    }
                }
            }
            Item = Item->next;
        }
        if (incellflag)
            break;
        sr = sr->next;
    }

    if (!incellflag)
        return false;//品番一致なし
    else {
        UINT32 rowslide = startR;

        char* tv = (char*)malloc(2);
        strcpy_s(tv, 2, SaT[0]);

        size_t sstrl = strlen((const char*)style) + 1;
        char* sv = (char*)malloc(sstrl);
        strcpy_s(sv, sstrl, style);

        size_t vlen = strlen((const char*)uniq) + 1;
        char* vst = (char*)malloc(vlen);
        strcpy_s(vst, vlen, (const char*)uniq);

        F* nulf = nullptr;
        UINT8* nulsi = nullptr;
        Cels->addcelldata(rowslide, incolumn, (UINT8*)tv, (UINT8*)sv, (UINT8*)vst, nulf, nulsi);//最初の一回に変更 メインの日付追加
        //サブ文字列追加
        if (one) {
            rowslide--;

            char* tvs = (char*)malloc(2);
            strcpy_s(tvs, 2, SaT[0]);

            char* svs = (char*)malloc(sstrl);
            strcpy_s(svs, sstrl, style);

            size_t vlen = strlen((const char*)one) + 1;
            char* vsts = (char*)malloc(vlen);
            strcpy_s(vsts, vlen, (const char*)one);

            F* nfs = nullptr;
            UINT8* nsis = nullptr;

            Cels->addcelldata(rowslide, incolumn, (UINT8*)tvs, (UINT8*)svs, (UINT8*)vsts, nfs, nsis);
        }
        if (two) {
            rowslide--;

            char* tvs = (char*)malloc(2);
            strcpy_s(tvs, 2, SaT[0]);

            char* svs = (char*)malloc(sstrl);
            strcpy_s(svs, sstrl, style);

            size_t vlen = strlen((const char*)two) + 1;
            char* vsts = (char*)malloc(vlen);
            strcpy_s(vsts, vlen, (const char*)two);

            F* nfs = nullptr;
            UINT8* nsis = nullptr;

            Cels->addcelldata(rowslide, incolumn, (UINT8*)tvs, (UINT8*)svs, (UINT8*)vsts, nfs, nsis);
        }
        if (three) {
            rowslide--;

            char* tvs = (char*)malloc(2);
            strcpy_s(tvs, 2, SaT[0]);

            char* svs = (char*)malloc(sstrl);
            strcpy_s(svs, sstrl, style);

            size_t vlen = strlen((const char*)three) + 1;
            char* vsts = (char*)malloc(vlen);
            strcpy_s(vsts, vlen, (const char*)three);

            F* nfs = nullptr;
            UINT8* nsis = nullptr;

            Cels->addcelldata(rowslide, incolumn, (UINT8*)tvs, (UINT8*)svs, (UINT8*)vsts, nfs, nsis);
        }
        if (four) {
            rowslide--;

            char* tvs = (char*)malloc(2);
            strcpy_s(tvs, 2, SaT[0]);
            char* svs = (char*)malloc(sstrl);
            strcpy_s(svs, sstrl, style);

            size_t vlen = strlen((const char*)four) + 1;
            char* vsts = (char*)malloc(vlen);
            strcpy_s(vsts, vlen, (const char*)four);

            F* nfs = nullptr;
            UINT8* nsis = nullptr;

            Cels->addcelldata(rowslide, incolumn, (UINT8*)tvs, (UINT8*)svs, (UINT8*)vsts, nfs, nsis);
        }
    }

    Item = its;

    while (Item) {//item 品番一致　全カラー
        sr = Cels->rows;
        result = strcmp((const char*)matchItem, (const char*)Item->it);//品番　シートデータの比較
        if (result == 0) {
            colorsearch(sr, Item, Item->it, celstyle);
        }
        Item = Item->next;
    }

    return incellflag;
}

void searchItemNum::colorsearch(Row* inrow, CsvItemandRid* IT, UINT8* itn, char* s) {
    const char* sizetable[] = { "090","100","110","120","130","140","150","160","F" };
    Row* color = inrow;// = (Row*)malloc(sizeof(Row))
    UINT8* nextColor = nullptr;
    UINT8* nextSize = nullptr;
    UINT8* nowColor = nullptr;
    UINT8* nowSize = nullptr;
    UINT8* beforeColor = nullptr;
    UINT8* beforeSize = nullptr;
    ColorAnSize* CandS = nullptr;
    CsvItemandRid* ite = IT;

    bool b = false;
    bool n = false;
    int result = 0;
    UINT32 i = 0;//セル文字数
    int matchflag = 0;//文字列　部分一致判定
    unitC sear;//全角変換

    while (color) {//スタート位置まで移動
        if (color->r == startR)
            break;
        color = color->next;
    }

    if (color && color->next) {
        color = color->next;//品番次の行
    }
    itemColors* co = ite->c;
    Sizes* si = ite->c->s;

    while (color) {
        if (color->cells) {
            if (color->cells->si) {//文字列　存在
                co = ite->c;
                while (co) {
                    //co->color = sear.changenumber(ite->c->color);//全角変換
                    //color->cells->si = sear.changeKana(color->cells->si);//かな変換
                    //color->cells->si = sear.changenumber(color->cells->si);
                    //co->color = sear.slipNum(co->color);//連続数字　削除
                    matchflag = Mstr.seachcharactors(co->color, color->cells->si, strlen((char*)color->cells->si), 0);//セルカラーとアイテムの比較　部分検索
                    if (matchflag != -1) {
                        CandS = Mstr.splitColor(color->cells->si);//カラーとサイズの分割
                        if (CandS->color && CandS->size) {
                            free(nowColor); free(nowSize);
                            nowColor = CandS->color; nowSize = CandS->size;
                        }
                        else {
                            nowColor = nullptr; nowSize = nullptr;
                        }

                        result = strcmp((const char*)nowColor, (const char*)co->color);//カラー比較
                        if (result == 0) {//カラー一致

                            if (nowColor && nowSize) {
                                si = co->s;
                                while (si) {
                                    result = strcmp((const char*)nowSize, (const char*)si->size);
                                    if (result == 0) {//サイズ一致                                   
                                        UINT8* itnadd = strtalloc(itn);
                                        UINT8* sv = strtalloc((UINT8*)s);
                                        UINT8* sizadd = strtalloc(si->val);
                                        UINT8* TV = nullptr;
                                        UINT8* SVI = nullptr;
                                        F* FV = nullptr;
                                        Cels->addcelldata(color->r, incolumn, TV, sv, sizadd, FV, SVI);
                                    }
                                }
                                si = si->next;
                            }
                        }
                    }                        
                    co = co->next;
                }
            }
        }
        color = color->next;
    }
    //free(beforeSize); free(beforeColor);
    //free(nextColor); free(nextSize);
    free(nowColor); free(nowSize);
}

void searchItemNum::freerootmacht(MatchColrs* m) {
    MatchColrs* p = nullptr;
    while (m) {
        p = m->next;
        free(m->color);
        free(m->itemnum);
        free(m);
        m = p;
    }
}

UINT8* searchItemNum::strtalloc(UINT8* s) {
    size_t sizlen = strlen((const char*)s) + 1;
    UINT8* sizadd = (UINT8*)malloc(sizlen);
    strcpy_s((char*)sizadd, sizlen, (const char*)s);

    return sizadd;
}

MatchColrs* searchItemNum::addmatches(MatchColrs* m, UINT8* i, UINT8* c)
{
    if (!m) {
        m = (MatchColrs*)malloc(sizeof(MatchColrs));
        if (m) {
            m->itemnum = i;
            m->color = c;
            m->next = nullptr;
        }
    }
    else {
        m->next = addmatches(m->next, i, c);
    }
    return m;
}

Items* searchItemNum::addItems(Items* base, Items* itm)
{
    if (!base) {
        base = (Items*)malloc(sizeof(Items));
        if (base) {
            base->itn = itm->itn;
            base->col = itm->col;
            base->next = nullptr;
        }
    }
    else {
        base->next = addItems(base->next, itm);
    }

    return base;
}
