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
    UINT8* nr = nullptr;//�������͍s�@�z��
    int result = 0;
    const char* SaT[] = { "s", "1127" };
    bool incellflag = false;
    UINT8* matchItem = nullptr;

    while (sr) {//�i�Ԍ���
        Item = its;
        while (Item) {
            if (sr->cells) {
                if (sr->cells->si) {
                    result = strcmp((const char*)sr->cells->si, (const char*)Item->it);//�i�ԁ@�V�[�g�f�[�^�̔�r
                    if (result == 0) {
                        matchItem = Item->it;//��v�i�΂�R�s�[
                        C* cn = nullptr;
                        cn = sr->next->cells;//�i�Ԏ��̍s
                        //�ŏI�񌟍�
                        while (cn->next) {
                            cn = cn->next;
                        }
                        inputColum = cn->col;//���ŏI��
                        changenum.ColumnIncliment(&inputColum);//�ŏI��@+1
                        nr = changenum.InttoChar(sr->next->r, &result);//���͍s
                        incolumn = changenum.ColumnNumtoArray(inputColum, &result);//�ŏI��@�z��ϊ�
                        startR = sr->next->r;//�i�Ԏ��̍s
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
        return false;//�i�Ԉ�v�Ȃ�
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
        Cels->addcelldata(rowslide, incolumn, (UINT8*)tv, (UINT8*)sv, (UINT8*)vst, nulf, nulsi);//�ŏ��̈��ɕύX ���C���̓��t�ǉ�
        //�T�u������ǉ�
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

    while (Item) {//item �i�Ԉ�v�@�S�J���[
        sr = Cels->rows;
        result = strcmp((const char*)matchItem, (const char*)Item->it);//�i�ԁ@�V�[�g�f�[�^�̔�r
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
    UINT32 i = 0;//�Z��������
    int matchflag = 0;//������@������v����
    unitC sear;//�S�p�ϊ�

    while (color) {//�X�^�[�g�ʒu�܂ňړ�
        if (color->r == startR)
            break;
        color = color->next;
    }

    if (color && color->next) {
        color = color->next;//�i�Ԏ��̍s
    }
    itemColors* co = ite->c;
    Sizes* si = ite->c->s;

    while (color) {
        if (color->cells) {
            if (color->cells->si) {//������@����
                co = ite->c;
                while (co) {
                    //co->color = sear.changenumber(ite->c->color);//�S�p�ϊ�
                    //color->cells->si = sear.changeKana(color->cells->si);//���ȕϊ�
                    //color->cells->si = sear.changenumber(color->cells->si);
                    //co->color = sear.slipNum(co->color);//�A�������@�폜
                    matchflag = Mstr.seachcharactors(co->color, color->cells->si, strlen((char*)color->cells->si), 0);//�Z���J���[�ƃA�C�e���̔�r�@��������
                    if (matchflag != -1) {
                        CandS = Mstr.splitColor(color->cells->si);//�J���[�ƃT�C�Y�̕���
                        if (CandS->color && CandS->size) {
                            free(nowColor); free(nowSize);
                            nowColor = CandS->color; nowSize = CandS->size;
                        }
                        else {
                            nowColor = nullptr; nowSize = nullptr;
                        }

                        result = strcmp((const char*)nowColor, (const char*)co->color);//�J���[��r
                        if (result == 0) {//�J���[��v

                            if (nowColor && nowSize) {
                                si = co->s;
                                while (si) {
                                    result = strcmp((const char*)nowSize, (const char*)si->size);
                                    if (result == 0) {//�T�C�Y��v                                   
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
