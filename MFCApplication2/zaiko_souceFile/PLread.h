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

	const char* stepone = "�����񏑂�����";
	const char* steptwo = "�����񏑂����ݒ�";
	const char* stepthree = "�V�[�g������";
	const char* stepfour = "���̓A�C�e���m�F��";

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
	//�Z���g�����f�[�^�̕ۑ�
	std::vector<UINT8> central;

	UINT8* sharedata;
	UINT64 shrelength;
	UINT8* inputshop;

	UINT8* daystyle;
	UINT8* celstyle;

	shareRandD* shar;//�V�F�A�f�[�^
	shipinfo* readItem;//�A�C�e�����X�g

	HeaderWrite hw;//���[�J���w�b�_�̏�������
	LHmake dd;//���Ԃ̎擾
	zipwrite* zip;
	writtenfilename* wfroot;
	_Post_ _Notnull_ FILE* fw;

	ENDrecord* ER;

	//�i�ԁA�J���[�G���[�p
	//MatchColrs* matchs;
	//MatchColrs* matchsroot;

	size_t errlen;

	UINT32 CDstarpos;

	UINT32 CDp;

	UINT8* sharestr;
	UINT32 recordsum;
	UINT32 styleleng;//�X�^�C���f�[�^��
	HeaderRead* hr;//�w�b�_�[���[�h

	ArrayNumber numchange;
	WorkBook_edi* wb;//workbook �C���X�^���X
	App_File* ap;//appfile �C���X�^���X
	checkstyle* sr;//�X�^�C���f�[�^�̃C���X�^���X
	DeflateDecode* Styledec;//�X�^�C���f�R�[�h�C���X�^���X
	CenterDerect* cddata;
	CenterDerect* cddatawb;//workbook central
	CenterDerect* cddataap;//appfile central
	encoding* enc;//�G���R�[�h�@�C���X�^���X
	workb_rels* wbr;
	DrawEdit* dr;//draw .xml �ǂݍ���

	CsvItemandRid* matchs;//�V�[�g��v
	CsvItemandRid* nomatch;//�V�[�g�Ȃ�
	UINT32 shsize;

	PLRead();
	~PLRead();

	void freewfn();

	//Items�\���̉��
	void freeItem(Items* t);
	//�p�b�L���O���X�g�ǂݍ���
	char* packingread(char* fn);
	//�Z���g�����f�B���N�g�̃R�s�[
	CenterDerect* copycd(CenterDerect* c);
	ENDrecord* copyER(ENDrecord* e);
	//���[�N�u�b�N�̓ǂݍ���
	int readWorkBook(char* fn);
	UINT8* strtalloc(UINT8* a, UINT8* b);
	Sizes* addSize(Sizes* si, Sizes* msi);
	itemColors* addColors(itemColors* col, itemColors* mcol);
	
	//�������@�m�ۂȂ�
	CsvItemandRid* addmatchitem(CsvItemandRid* c, CsvItemandRid* m, UINT8* rid, UINT8* nrid);

	CsvItemandRid* addCsvItemRid(CsvItemandRid* c, CsvItemandRid* m, UINT8* rid, UINT8* nrid);

	void workbookCheck(CsvItemandRid* citem);

	int openstyleseat(char* fn);
	//�Z���X�^�C���̕ύX
	UINT8* stylesetting(Fonts* f, Fills* fi, borders* bo, stylexf* stx, cellxfs* cx, numFMts* fm);
	//���k�@��������
	int writecompress(UINT8* d, UINT32 dl, FILE* f, CenterDerect* cd);

	char* readshareAndWrite(char* txt1, char* fn);

	void ItemsChangeShare(CsvItemandRid* citem);

	char* filenamemerge(UINT8* fno, UINT8* plusstr, UINT8* typ);
	//workbookrel
	int workbookrelsadd(CsvItemandRid* nomatch, char* fn);
	
	//�V�F�A�̍X�V

	//�V�[�g�f�[�^�������݁E�V�F�A��������
	char* sheetread(char* hfn, CsvItemandRid* it, FILE* inf, UINT8* styo, UINT8* styt);

	// new sheet make
	UINT8* newSheetWrite(UINT8* d, UINT8* uuid, CsvItemandRid* citem, UINT8* styleone, UINT8* styletwo, FILE* wf, char* ifn, UINT8* reld);

	void makedrawxml(UINT8* drawdata, UINT8* rid, UINT8* targetfile, FILE* f, UINT8* dreldata, UINT8* uid);

	void endrecordwrite(FILE* wf);

	//�G���[�A�C�e���̊m�F��������
	char* errorItems();

	//�G���[�A�C�e�����ǉ�
	char* adderrorstr(char* e, UINT8* it);
	//�������݃t�@�C����
	char* writename(char* wfn, size_t len);
	//�Z���g�����f�[�^�̒ǉ�
	void writeCentral(CenterDerect* c);

};