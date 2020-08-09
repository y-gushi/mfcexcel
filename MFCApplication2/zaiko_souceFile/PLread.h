#pragma once
#include "TagAndItems.h"
#include "Header.h"
#include "shareRandW.h"
#include "RowColumn.h"
#include "ShipDataRead.h"
#include "timeget.h"
#include "encode.h"
#include "ZipFilewrite.h"
#include "SearchItemNUm.h"
#include "excel_style.h"
#include "workbookEdit.h"
#include "AppFile.h"
#include "workbook_rel_edi.h"
#include "draw_edit.h"

#define BUFSIZE 255

struct writtenfilename
{
	char* fn;
	writtenfilename* next;
};

class PLRead {
private:
	const char* ef = "file open error";
	const char* shares = "sharedStrings.xml";

	const char* ms = "magaseek";//8
	const char* be = "bee";//3
	const char* zo = "zozo";//4
	const char* sb = "smarby";//6
	const char* sl = "shoplist";//8

	const char* bS = "1012";
	const char* msS = "710";
	const char* smS = "1038";
	const char* zoS = "711";
	const char* slS = "715";

	const char* zocel = "309";
	const char* slicel = "422";
	const char* magcel = "424";
	const char* smacel = "310";
	const char* becel = "1074";

	const char* stepone = "文字列書き込み";
	const char* steptwo = "文字列書き込み中";
	const char* stepthree = "シート検索中";
	const char* stepfour = "入力アイテム確認中";

	const char* stylefn= "xl/styles.xml";

public:

	std::ifstream inf;
	Items* erroritem;
	size_t fnlen;

	char* inMainstr;
	char* inSubstr;
	char* inTwostr;
	char* inThreestr;
	char* inFourstr;
	char* filename;
	char* Hfilename;
	UINT8* shopname;

	UINT32 localSize;
	//セントラルデータの保存
	std::vector<UINT8> central;

	UINT8* sharedata;
	UINT64 shrelength;
	UINT8* inputshop;

	UINT8* daystyle;
	UINT8* celstyle;

	shareRandD* shar;//シェアデータ
	shipinfo* readItem;//アイテムリスト

	HeaderWrite hw;//ローカルヘッダの書き込み
	LHmake dd;//時間の取得
	zipwrite* zip;
	writtenfilename* wfroot;
	_Post_ _Notnull_ FILE* fw;

	ENDrecord* ER;

	//品番、カラーエラー用
	//MatchColrs* matchs;
	//MatchColrs* matchsroot;

	size_t errlen;

	UINT32 CDstarpos;

	UINT32 CDp;

	UINT8* sharestr;
	UINT32 recordsum;
	UINT32 styleleng;//スタイルデータ長
	HeaderRead* hr;//ヘッダーリード

	ArrayNumber numchange;
	WorkBook_edi* wb;//workbook インスタンス
	App_File* ap;//appfile インスタンス
	checkstyle* sr;//スタイルデータのインスタンス
	DeflateDecode* Styledec;//スタイルデコードインスタンス
	CenterDerect* cddata;
	CenterDerect* cddatawb;//workbook central
	CenterDerect* cddataap;//appfile central
	encoding* enc;//エンコード　インスタンス
	workb_rels* wbr;
	DrawEdit* dr;//draw .xml 読み込み

	CsvItemandRid* matchs;//シート一致
	CsvItemandRid* nomatch;//シートなし
	UINT32 shsize;

	PLRead();
	~PLRead();

	void freewfn();

	//Items構造体解放
	void freeItem(Items* t);
	//パッキングリスト読み込み
	char* packingread(char* fn);
	//セントラルディレクトのコピー
	CenterDerect* copycd(CenterDerect* c);
	ENDrecord* copyER(ENDrecord* e);
	//ワークブックの読み込み
	int readWorkBook(char* fn);
	UINT8* strtalloc(UINT8* a, UINT8* b);
	Sizes* addSize(Sizes* si, Sizes* msi);
	itemColors* addColors(itemColors* col, itemColors* mcol);
	
	//メモリ　確保なし
	CsvItemandRid* addmatchitem(CsvItemandRid* c, CsvItemandRid* m, UINT8* rid, UINT8* nrid);

	CsvItemandRid* addCsvItemRid(CsvItemandRid* c, CsvItemandRid* m, UINT8* rid, UINT8* nrid);

	void workbookCheck(CsvItemandRid* citem);

	int openstyleseat(char* fn);
	//セルスタイルの変更
	UINT8* stylesetting(Fonts* f, Fills* fi, borders* bo, stylexf* stx, cellxfs* cx, numFMts* fm);
	//圧縮　書き込み
	int writecompress(UINT8* d, UINT32 dl, FILE* f, CenterDerect* cd);

	char* readshareAndWrite(char* txt1, char* fn);

	void ItemsChangeShare(CsvItemandRid* citem);

	char* filenamemerge(UINT8* fno, UINT8* plusstr, UINT8* typ);
	//workbookrel
	int workbookrelsadd(CsvItemandRid* nomatch, char* fn);
	
	//シェアの更新

	//シートデータ書き込み・シェア書き込み
	char* sheetread(char* hfn, CsvItemandRid* it, FILE* inf, UINT8* styo, UINT8* styt);

	// new sheet make
	UINT8* newSheetWrite(UINT8* d, UINT8* uuid, CsvItemandRid* citem, UINT8* styleone, UINT8* styletwo, FILE* wf, char* ifn, UINT8* reld);

	void makedrawxml(UINT8* drawdata, UINT8* rid, UINT8* targetfile, FILE* f, UINT8* dreldata, UINT8* uid);

	void endrecordwrite(FILE* wf);

	//エラーアイテムの確認書き込み
	char* errorItems();

	//エラーアイテム名追加
	char* adderrorstr(char* e, UINT8* it);
	//書き込みファイル名
	char* writename(char* wfn, size_t len);
	//セントラルデータの追加
	void writeCentral(CenterDerect* c);

};