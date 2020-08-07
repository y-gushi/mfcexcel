#include "Header.h"

HeaderRead::HeaderRead(char* name) {
    readfile = name; //読み込むファイルの指定
    readdata = 0;
    sig = 0;
    endpos = 0;
    curpos = 0;
    headerReaddata = 0;
    rootLH = nullptr;
    r = nullptr;//セントラルディレクトリのルート
    ER = new ENDrecord;
    LH = new LocalHeader;
    rootLH = LH;
    CD = new CenterDerect;
    saveLH = nullptr;
    saveCD = nullptr;
    scd = new CenterDerect;
}

HeaderRead::~HeaderRead() {
    //free(root);
    free(r);
    delete ER;
    delete LH;
    delete CD;
    free(cdfn);
    //delete scd;    
}

void HeaderRead::freeER() {
    delete[] ER->comment;
}

void HeaderRead::freeheader() {
    delete[] scd->filename;
    delete[] scd->kakutyo;
    delete[] scd->comment;
}

void HeaderRead::freeLH() {
    delete[] LH->filename;
    delete[] LH->kakutyo;
}

//ファイル名でセントラルディレクトリ　データ検索
//ローカルディレクトリの位置を返す
CenterDerect* HeaderRead::searchCENTRAL(char* s) {
    bool t = false;
    CDdataes* p = saveCD;

    while (p != nullptr) {
        t = searchChara(s, p->cdd.filename, p->cdd.filenameleng);//ファイル名部分一致検索
        if (t) {
            return &p->cdd;
        }
        else {
        }
        p = p->nextCD;
    }
    return nullptr;
}

//ファイル名検索
bool HeaderRead::searchChara(char fn[], char* cdfn, UINT16 cdfnlen)
{
    size_t i = strlen(fn); //文字列の数
    
    UINT32 isize = (UINT32)i + 1;
    char* searchfilename = new char[isize];//検索スライド用

    int slidepos = 0;

    if (searchfilename) {
        while (slidepos < cdfnlen) {
            if (i > cdfnlen) {//ファイル名が文字列より長い
                return false;
            }
            else {
                /*
                if (slidepos == 0) {//
                    for (size_t j = 0; j < i; j++) {//最初に文字列にfilenameをi分入れる
                        searchfilename[j] = cdfn[slidepos];
                        slidepos++;
                    }
                    searchfilename[i] = '\0';//文字列終端を追加
                }
                */
                //配列を一文字づつずらす
                for (int j = 0; j < i - 1; j++) {
                    searchfilename[j] = searchfilename[j + 1];
                }
                searchfilename[i - 1] = cdfn[slidepos];//最後に付け加える
                searchfilename[i] = '\0';//文字列終端を追加
                slidepos++;//位置移動
                if (strcmp(searchfilename, fn) == 0)
                {
                    //std::cout << "local filename match" << std::endl;
                    delete[] searchfilename;
                    return true;
                }
            }
        }
    }
    delete[] searchfilename;

    return false;
}

CenterDerect* HeaderRead::talloc(void) {
    return (CenterDerect*)malloc(sizeof(CenterDerect));
}

LocalHeader* HeaderRead::tallocLH()
{
    return (LocalHeader*)malloc(sizeof(LocalHeader) * 1);
}

LHDataes* HeaderRead::tallocLhData()
{
    return (LHDataes*)malloc(sizeof(LHDataes));
}


LHDataes* HeaderRead::addLhData(LHDataes* ld, LocalHeader* lhd)
{
    if (!ld) {
        ld = tallocLhData();
        ld->lhdata = lhd;
        ld->nextLH = nullptr;
    }
    else {
        ld->nextLH = addLhData(ld->nextLH, lhd);
    }

    return ld;
}

CDdataes* HeaderRead::tallocCDdataes()
{
    return (CDdataes*)malloc(sizeof(CDdataes));
}

CDdataes* HeaderRead::addCDdata(CDdataes* c, CenterDerect* cddata)
{
    if (c == NULL) {
        c = tallocCDdataes();
        c->cdd = *cddata;
        c->nextCD = nullptr;
    }
    else {
        c->nextCD = addCDdata(c->nextCD, cddata);
    }

    return c;
}

filelist* HeaderRead::addfn(filelist* f, char* fn, int h)
{
    if (!f) {
        f = (filelist*)malloc(sizeof(filelist));
        if (f) {
            UINT32 msize = (UINT32)h + 1;
            f->cfn = new char[msize];
            f->cfn = fn;
            f->hash = h;
            f->next = nullptr;
        }
    }
    else {
        f->next = addfn(f, fn, h);
    }
    return f;
}


void HeaderRead::endread(std::ifstream* fin) {
    if (!fin) {
    }

    fin->seekg(0, std::ios_base::end);//ファイル終端位置取得
    UINT64 endpos = 0;
    endpos = fin->tellg();

    curpos = endpos;
    curpos -= 1;
    fin->seekg(curpos, std::ios_base::beg);

    /*終端コード検索　ファイル終わりから*/
    while (curpos > 0) {

        fin->read((char*)&readdata, sizeof(char));
        sig = sig << 8;
        sig += readdata;

        if (sig == END_OF_CENTRAL) {
            curpos += 4;//シグネチャ分ポインタ戻す
            fin->seekg(curpos);

            //このディスクの数 2byte
            ER->discnum = 0;
            for (int i = 0; i < 2; i++) {
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                ER->discnum += readdata;
            }

            //セントラルディレクトリが開始するディスク 2byte
            ER->disccentral = 0;
            for (int i = 0; i < 2; i++) {
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                ER->disccentral += readdata;
            }

            //このディスク上のセントラルディレクトリレコードの数 2byte
            ER->centralnum = 0;
            for (int i = 0; i < 2; i++) {
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                ER->centralnum += readdata;
            }

            //セントラルディレクトリレコードの合計数 2byte
            ER->centralsum = 0;
            for (int i = 0; i < 2; i++) {
                readdata = 0;
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                ER->centralsum += readdata;
            }

            //セントラルディレクトリのサイズ (バイト) 4byte
            ER->size = 0;
            for (int i = 0; i < 4; i++) {
                fin->read((char*)&readdata, sizeof(char));
                readdata = (readdata & 0xFF) << (8 * i);
                ER->size += readdata;
            }

            //セントラルディレクトリの開始位置のオフセット 4byte
            ER->position = 0;
            for (int i = 0; i < 4; i++) {
                readdata = 0;
                fin->read((char*)&readdata, sizeof(char));
                readdata = (readdata & 0xFF) << (8 * i);
                ER->position += readdata;
            }
            readpos = ER->position;

            //セントラルディレクトリレコードの合計数 2byte
            ER->commentleng = 0;
            for (int i = 0; i < 2; i++) {
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                ER->commentleng += readdata;
            }

            //ZIPファイルのコメント nbyte
            ER->comment = nullptr;
            if (ER->commentleng > 0) {
                UINT32 msize = ((UINT32)ER->commentleng) + 1;
                ER->comment = new char[msize];
                for (int i = 0; i < ER->commentleng; i++) {
                    fin->read((char*)&readdata, sizeof(char));
                    ER->comment[i] = (readdata & 0xFF);
                }
            }            
            break;
        }
        curpos--;
        fin->seekg(curpos);
    }
}

//ローカルディレクトリのヘッダー情報
void HeaderRead::localread(UINT64 pos, std::ifstream* fin) {
    //std::ifstream fin(readfile, std::ios::in | std::ios::binary);
    if (!fin) {
        //std::cout << "ファイル ID.txt が開けません";
    }

    fin->seekg(pos, std::ios_base::beg);
    sig = 0;

    /*ローカルヘッダシグネチャを読み込む*/
    while (sig != LOCAL_HEADER) {
        //先頭コードまで読み込む
        fin->read((char*)&readdata, sizeof(char));
        sig = sig << 8;
        sig += readdata & 0xFF;
    }

    LH->version = 0;
    for (int i = 0; i < 2; i++) {
        fin->read((char*)&readdata, sizeof(char));
        readdata = ((readdata & 0xFF) << (8 * i));
        LH->version += readdata;
    }
    //std::cout << "展開に必要なバージョン" << LH->version << std::endl;

    //汎用目的のビットフラグ
    LH->bitflag = 0;
    for (int i = 0; i < 2; i++) {
        fin->read((char*)&readdata, sizeof(char));
        readdata = ((readdata & 0xFF) << (8 * i));
        LH->bitflag += readdata;
    }
    //std::cout << "汎用目的のビットフラグ" << LH->version << std::endl;

    //圧縮メソッド
    LH->method = 0;
    for (int i = 0; i < 2; i++) {
        fin->read((char*)&readdata, sizeof(char));
        readdata = ((readdata & 0xFF) << (8 * i));
        LH->method += readdata;
    }

    //ファイルの最終変更時間
    LH->time = 0;
    for (int i = 0; i < 2; i++) {
        fin->read((char*)&readdata, sizeof(char));
        readdata = ((readdata & 0xFF) << (8 * i));
        LH->time += readdata;
    }

    //ファイルの最終変更日付
    LH->day = 0;
    for (int i = 0; i < 2; i++) {
        fin->read((char*)&readdata, sizeof(char));
        readdata = ((readdata & 0xFF) << (8 * i));
        LH->day += readdata;
    }

    //CRC-32
    LH->crc = 0;
    for (int i = 0; i < 4; i++) {
        fin->read((char*)&readdata, sizeof(char));
        readdata = ((readdata & 0xFF) << (8 * i));
        LH->crc += readdata;
    }

    //圧縮サイズ
    LH->size = 0;
    for (int i = 0; i < 4; i++) {
        fin->read((char*)&readdata, sizeof(char));
        readdata = ((readdata & 0xFF) << (8 * i));
        LH->size += readdata;
    }

    //    非圧縮サイズ
    LH->nonsize = 0;
    for (int i = 0; i < 4; i++) {
        fin->read((char*)&readdata, sizeof(char));
        readdata = ((readdata & 0xFF) << (8 * i));
        LH->nonsize += readdata;
    }

    //ファイル名の長さ (n)
    LH->filenameleng = 0;
    for (int i = 0; i < 2; i++) {
        fin->read((char*)&readdata, sizeof(char));
        readdata = ((readdata & 0xFF) << (8 * i));
        LH->filenameleng += readdata;
    }

    //拡張フィールドの長さ (m)
    LH->fieldleng = 0;
    for (int i = 0; i < 2; i++) {
        fin->read((char*)&readdata, sizeof(char));
        readdata = ((readdata & 0xFF) << (8 * i));
        LH->fieldleng += readdata;
    }

    //ファイル名
    LH->filename = nullptr;
    if (LH->filenameleng > 0) {
        UINT32 msize = ((UINT32)LH->filenameleng) + 1;
        LH->filename = new char[msize];
        if (LH->filename) {
            for (UINT16 i = 0; i < LH->filenameleng; i++) {
                fin->read((char*)&readdata, sizeof(char));
                LH->filename[i] = readdata;
            }
            LH->filename[LH->filenameleng] = '\0';
        }
    }    

    //拡張フィールド
    LH->kakutyo = nullptr;
    if (LH->fieldleng > 0) {
        UINT32 msize = ((UINT32)LH->fieldleng) + 1;
        LH->kakutyo = new char[msize];
        if (LH->fieldleng > 0) {
            for (UINT16 i = 0; i < LH->fieldleng; i++) {
                fin->read((char*)&readdata, sizeof(char));
                LH->kakutyo[i] = readdata;
            }
        }
    }

    LH->pos = fin->tellg();//圧縮データの始まり
}
//セントラルディレクトリのヘッダー情報
void HeaderRead::centerread(UINT64 pos, UINT32 size, UINT16 n, std::ifstream* fin) {
    //std::cout << std::endl;

    //std::ifstream fin(readfile, std::ios::in | std::ios::binary);

    if (!fin) {
        std::cout << "not file open" << std::endl;
    }

    int j = 0;

    fin->seekg(pos, std::ios_base::beg);

    while (j < n) {

        //while (s < size) {
            /*先頭コードまで読み込む*/
        for (int i = 0; i < 4; i++) {
            fin->read((char*)&readdata, sizeof(char));
            sig = sig << 8;
            sig += readdata & 0xFF;
            //std::cout << std::hex << sig << ',';
        }

        if (sig == CENTRALSIGNATURE) { //中央ディレクトリファイルヘッダーの署名= 0x02014b50
            //std::cout << "中央ディレクトリ出力　j:" << j << std::endl;
            //CD->version = 0;
            //mac 62　windows 45
            //属性　GetFileAttributes?
            CD->version = 0;
            for (int i = 0; i < 2; i++) {
                fin->read((char*)&readdata, sizeof(char));//作成者
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->version += readdata;
            }
            //抽出に必要なバージョン（最小）
            CD->minversion = 0;
            for (int i = 0; i < 2; i++) {
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->minversion += readdata;
            }
            //std::cout << "抽出に必要なバージョン（最小：" << CD->minversion << std::endl;
            CD->bitflag = 0;
            for (int i = 0; i < 2; i++) {
                fin->read((char*)&readdata, sizeof(char));//汎用ビットフラグ
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->bitflag += readdata;
            }
            //std::cout << "汎用ビットフラグ：" << CD->bitflag << std::endl;
            CD->method = 0;
            for (int i = 0; i < 2; i++) {//    圧縮方法
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->method += readdata;
            }
            //std::cout << "圧縮方法：" << CD->method << std::endl;
            CD->time = 0;
            for (int i = 0; i < 2; i++) {//    ファイルの最終変更時刻
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->time += readdata;
            }
            //std::cout << "ファイルの最終変更時刻：" << CD->time << std::endl;
            CD->day = 0;
            for (int i = 0; i < 2; i++) {//    ファイルの最終変更日
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->day += readdata;
            }
            //std::cout << "ファイルの最終変更日：" << CD->day << std::endl;
            //crc
            CD->crc = 0;
            for (int i = 0; i < 4; i++) {
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->crc += readdata;
            }
            //std::cout << "CRC-32：" << CD->crc << std::endl;
            //    圧縮サイズ
            CD->size = 0;
            for (int i = 0; i < 4; i++) {
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->size += readdata;
            }
            //std::cout << "圧縮サイズ：" << CD->size << std::endl;
            //    非圧縮サイズ
            CD->nonsize = 0;
            for (int i = 0; i < 4; i++) {
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->nonsize += readdata;
            }
            //std::cout << "非圧縮サイズ：" << CD->nonsize << std::endl;
            //    ファイル名の長さ（n)
            CD->filenameleng = 0;
            for (int i = 0; i < 2; i++) {
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->filenameleng += readdata;
            }

            CD->fieldleng = 0;
            for (int i = 0; i < 2; i++) {//    追加フィールド長（m）
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->fieldleng += readdata;
            }

            CD->fielcomment = 0;
            for (int i = 0; i < 2; i++) {//    ファイルのコメント長（k）
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->fielcomment += readdata;
            }

            CD->discnum = 0;
            for (int i = 0; i < 2; i++) {//    ファイルが始まるディスク番号
                fin->read((char*)&readdata, sizeof(char));
                readdata = (readdata << (8 * i));
                CD->discnum += readdata;
            }
            //std::cout << "ファイルが始まるディスク番号：" << CD->discnum << std::endl;
            CD->zokusei = 0;
            for (int i = 0; i < 2; i++) {//        内部ファイル属性
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->zokusei += readdata;
            }
            //std::cout << "内部ファイル属性：" << CD->zokusei << std::endl;
            CD->gaibuzokusei = 0;
            for (int i = 0; i < 4; i++) {//    外部ファイル属性
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->gaibuzokusei += readdata;
            }
            //std::cout << "外部ファイル属性：" << CD->gaibuzokusei << std::endl;
            CD->localheader = 0;
            for (int i = 0; i < 4; i++) {//    ローカルファイルヘッダの相対オフセット
                fin->read((char*)&readdata, sizeof(char));
                readdata = ((readdata & 0xFF) << (8 * i));
                CD->localheader += readdata;
            }
            //std::cout << "ローカルファイルヘッダの相対オフセット：" << CD->localheader << std::endl;

            //std::cout << "ファイル名：";
            UINT32 msize = ((UINT32)CD->filenameleng) + 1;
            CD->filename = new char[msize];
            for (int i = 0; i < CD->filenameleng; i++) {//    ファイル名
                fin->read((char*)&headerReaddata, sizeof(char));
                CD->filename[i] = headerReaddata;
                //std::cout << CD->filename[i];
            }
            CD->filename[CD->filenameleng] = '\0';
            //std::cout << std::endl;

            //std::cout << "拡張フィールド：";
            CD->kakutyo = nullptr;            
            if (CD->fieldleng > 0) {
                msize = ((UINT32)CD->fieldleng) + 1;
                CD->kakutyo = new char[msize];
                for (int i = 0; i < CD->fieldleng; i++) {//    拡張フィールド
                    fin->read((char*)&readdata, sizeof(char));
                    CD->kakutyo[i] = readdata & 0xFF;
                }
            }

            CD->comment = nullptr;            
            if (CD->fielcomment > 0) {
                msize = ((UINT32)CD->fielcomment) + 1;
                CD->comment = new char[msize];
                for (int i = 0; i < CD->fielcomment; i++) {//ファイルコメント
                    fin->read((char*)&readdata, sizeof(char));
                    CD->comment[i] = readdata & 0xFF;
                }
            }

            sig = 0;
            //データを保持する
            //cdfn = addfn(cdfn, CD->filename, CD->filenameleng);
        }
        j++;
    }
    //fin->close();
}

CenterDerect* HeaderRead::centeroneread(UINT64 pos, UINT32 size, UINT16 n, char* fn, std::ifstream* fin)
{
    bool flag = false;

    if (!fin) {
        return nullptr;
    }

    fin->seekg(pos, std::ios_base::beg);

    /*先頭コードまで読み込む*/
    for (int i = 0; i < 4; i++) {
        fin->read((char*)&readdata, sizeof(char));
        sig = sig << 8;
        sig += readdata & 0xFF;
    }

    if (sig == CENTRALSIGNATURE) {
        scd->version = 0;
        for (int i = 0; i < 2; i++) {
            fin->read((char*)&readdata, sizeof(char));//作成者
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->version += readdata;
        }

        scd->minversion = 0;
        for (int i = 0; i < 2; i++) {
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->minversion += readdata;
        }

        scd->bitflag = 0;
        for (int i = 0; i < 2; i++) {
            fin->read((char*)&readdata, sizeof(char));//汎用ビットフラグ
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->bitflag += readdata;
        }
        scd->method = 0;
        for (int i = 0; i < 2; i++) {//    圧縮方法
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->method += readdata;
        }

        scd->time = 0;
        for (int i = 0; i < 2; i++) {//    ファイルの最終変更時刻
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->time += readdata;
        }

        scd->day = 0;
        for (int i = 0; i < 2; i++) {//    ファイルの最終変更日
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->day += readdata;
        }
        
        //crc
        scd->crc = 0;
        for (int i = 0; i < 4; i++) {
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->crc += readdata;
        }

        //    圧縮サイズ
        scd->size = 0;
        for (int i = 0; i < 4; i++) {
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->size += readdata;
        }

        //    非圧縮サイズ
        scd->nonsize = 0;
        for (int i = 0; i < 4; i++) {
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->nonsize += readdata;
        }

        //    ファイル名の長さ（n)
        scd->filenameleng = 0;
        for (int i = 0; i < 2; i++) {
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->filenameleng += readdata;
        }

        scd->fieldleng = 0;
        for (int i = 0; i < 2; i++) {//    追加フィールド長（m）
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->fieldleng += readdata;
        }

        scd->fielcomment = 0;
        for (int i = 0; i < 2; i++) {//ファイルのコメント長（k）
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->fielcomment += readdata;
        }

        scd->discnum = 0;
        for (int i = 0; i < 2; i++) {//ファイルが始まるディスク番号
            fin->read((char*)&readdata, sizeof(char));
            readdata = (readdata << (8 * i));
            scd->discnum += readdata;
        }

        scd->zokusei = 0;
        for (int i = 0; i < 2; i++) {//内部ファイル属性
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->zokusei += readdata;
        }

        scd->gaibuzokusei = 0;
        for (int i = 0; i < 4; i++) {//    外部ファイル属性
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->gaibuzokusei += readdata;
        }

        scd->localheader = 0;
        for (int i = 0; i < 4; i++) {//    ローカルファイルヘッダの相対オフセット
            fin->read((char*)&readdata, sizeof(char));
            readdata = ((readdata & 0xFF) << (8 * i));
            scd->localheader += readdata;
        }

        UINT32 msize = ((UINT32)scd->filenameleng) + 1;
        scd->filename = new char[msize];
        for (int i = 0; i < scd->filenameleng; i++) {//    ファイル名
            fin->read((char*)&headerReaddata, sizeof(char));
            scd->filename[i] = headerReaddata;
        }
        scd->filename[scd->filenameleng] = '\0';
        

        scd->kakutyo = nullptr;
        if (scd->fieldleng > 0) {
            msize = ((UINT32)scd->fieldleng) + 1;
            scd->kakutyo = new char[msize];
            for (int i = 0; i < scd->fieldleng; i++) {//    拡張フィールド
                fin->read((char*)&readdata, sizeof(char));
                scd->kakutyo[i] = readdata & 0xFF;
            }
        }
        
        scd->comment = nullptr;
        if (scd->fielcomment) {
            msize = ((UINT32)scd->fielcomment) + 1;
            scd->comment = new char[msize];
            for (int i = 0; i < scd->fielcomment; i++) {//ファイルコメント
                fin->read((char*)&readdata, sizeof(char));
                scd->comment[i] = readdata & 0xFF;
            }
        }
        
        sig = 0;
        readpos = fin->tellg();
    }
    filenum++;

    return scd;
}

inputtxt* HeaderRead::addtxt(inputtxt* intx, char* tx, inputtxt* par) {

    if (!intx) {
        intx = new inputtxt;
        intx->parrent = par;
        intx->txt = (UINT8*)tx;
        intx->sinum = nullptr;
        intx->next = nullptr;
    }
    else {
        intx->next = addtxt(intx->next, tx, intx);
    }
        

    return intx;
}

void HeaderRead::freetxt(inputtxt* p) {
    inputtxt* q;
    while (p) {
        q = p->next;
        delete(p);
        p = q;
    }
}

inputtxt* HeaderRead::slipInputText(char* ins,inputtxt* it) {
    size_t i = 0;

    while (ins[i] != '\0') {
        if (ins[i] == ',')//改行数 コメント数　改行で行分ける
            intxtCount++;
        else
            std::cout << ins[i] << ",";
        i++;
    }

    intxtCount++;//最終行プラス

    char** instrs = (char**)malloc(intxtCount);
    //char instrs[5][255] = { 0 };

    int j = 0;
    i = 0;
    int stockpos = 0;
    while (j < intxtCount) {
        while (ins[i] != ',' && ins[i] != '\0')
            i++;
        
        size_t strleng = i - stockpos;
        size_t msize = strleng + 1;

        char *inst = new char[msize];
        std::cout << "文字数：" << i << "," << msize << std::endl;
        if (!inst)
            return nullptr;

        for (int t = 0; t < strleng; t++)
            inst[t] = ins[stockpos + t];
        inst[strleng] = '\0';
        it = addtxt(it, inst,nullptr);
        //instrs[j] = inst;
        //std::cout << "入力テキスト：" << instrs[j] << " " << strleng << std::endl;
        i++;//改行　スキップ
        stockpos = i;//スタート位置更新

        j++;
    }

    return it;
}

