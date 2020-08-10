#include "zaiko_souceFile/RowColumn.h"

// <row r="12" spans="1:2" ht="52.9" customHeight="1">
UINT8* Ctags::newSheet(UINT8* rid, UINT8* uuid,CsvItemandRid* citem,UINT8* styleone,UINT8* styletwo) {
	UINT32 itemnumrow = 11;
	UINT8 scellcol[] = "A";
	UINT8 stockvalue[] = "F";//F�񂩂�
	UINT8 tv[] = "s";

	//�i�Ԓǉ�
	UINT8* tval = (UINT8*)malloc(sizeof(UINT8) * 2);
	strcpy_s((char*)tval, 2, (char*)tv);

	size_t ssiz = strlen((char*)styleone)+1;
	UINT8* sv= (UINT8*)malloc(sizeof(UINT8) * ssiz);
	strcpy_s((char*)sv, ssiz, (char*)styleone);

	ssiz = strlen((char*)citem->it) + 1;
	UINT8* val = (UINT8*)malloc(sizeof(UINT8) * ssiz);
	strcpy_s((char*)val, ssiz, (char*)citem->it);

	addcelldata(itemnumrow, scellcol, tval, sv, val, nullptr, nullptr);

	itemnumrow++;//���̍s��
	itemnumrow++;//���̍s��

	itemColors* cl = citem->c;
	Sizes* sz = nullptr;
	while (cl) {
		sz = cl->s;
		while (sz) {
			//�J���[������
			tval = (UINT8*)malloc(sizeof(UINT8) * 2);
			strcpy_s((char*)tval, 2, (char*)tv);

			ssiz = strlen((char*)styletwo) + 1;
			sv = (UINT8*)malloc(sizeof(UINT8) * ssiz);
			strcpy_s((char*)sv, ssiz, (char*)styletwo);

			ssiz = strlen((char*)sz->size) + 1;
			val = (UINT8*)malloc(sizeof(UINT8) * ssiz);
			strcpy_s((char*)val, ssiz, (char*)sz->size);
			
			addcelldata(itemnumrow, scellcol, tval, sv, val, nullptr, nullptr);

			//�l�̓���
			tval = nullptr;

			ssiz = strlen((char*)styletwo) + 1;
			sv = (UINT8*)malloc(sizeof(UINT8) * ssiz);
			strcpy_s((char*)sv, ssiz, (char*)styletwo);

			ssiz = strlen((char*)sz->val) + 1;
			val = (UINT8*)malloc(sizeof(UINT8) * ssiz);
			strcpy_s((char*)val, ssiz, (char*)sz->val);

			addcelldata(itemnumrow, stockvalue, tval, sv, val, nullptr, nullptr);

			itemnumrow++;
			sz = sz->next;
		}
		cl = cl->next;
	}

	//uuid�@�ύX
	size_t idlen = strlen((char*)uuid) + 3;
	UINT8* newuuid = (UINT8*)malloc(sizeof(UINT8) * idlen);
	size_t i = 0;
	newuuid[i] = '{'; i++;
	for (i; i < strlen((char*)uuid); i++) {
		newuuid[i] = uuid[i - 1];
	}
	newuuid[i] = '}'; i++;
	newuuid[i] = '\0';

	free(wsV->uid);
	wsV->uid = newuuid;

	//draw id �ύX
	//free(drawing_id);
	//drawing_id = nullptr;

	return drawing_id;
}

// printersetting draw ���������Ȃ���OK!
void makenewsheetrels(UINT8* rid) {

}