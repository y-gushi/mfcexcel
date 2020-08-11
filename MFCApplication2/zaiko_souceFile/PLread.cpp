#include "PLread.h"

PLRead::PLRead()
{
	erroritem = nullptr;
	fnlen = 0;
	shar = nullptr;
	readItem = nullptr;
	matchs = nullptr;
	errlen = 0;
	fw = nullptr;
	CDstarpos = 0;
	inputshop = nullptr;
	CDp = 0;
	inMainstr = nullptr;
	dd.getday();//時間の取得
	zip=new zipwrite(dd.times);//zipデータを作る
	localSize = 0;
	daystyle = nullptr;
	celstyle = nullptr;
	filename = nullptr;
	inFourstr = nullptr;
	inSubstr = nullptr;
	inThreestr = nullptr;
	inTwostr = nullptr;
	wb = nullptr;
	ap = nullptr;
	matchs = nullptr;
	nomatch = nullptr;
	sr = nullptr;
	Styledec = nullptr;
	cddata = nullptr;
	enc = nullptr;
	sharestr = nullptr;
	wbr = nullptr;
	cddatawb = nullptr;
	cddataap = nullptr;
	recordsum = 0;
	wfroot = nullptr;
	ER = nullptr;
	styleleng = 0;
	dr = nullptr;
}

PLRead::~PLRead()
{
	delete zip;
	//delete sr;
	freewfn();
	delete ER;
	//freeItem(erroritem);
	//free(inputshop);
}

void PLRead::freewfn() {
	writtenfilename* p;
	while (wfroot)
	{
		p = wfroot->next;
		free(wfroot->fn);
		free(wfroot);
		wfroot = p;
	}
}

UINT8* ReadWorkBookxml(char* fn) {
	std::ifstream Zr(fn, std::ios::in | std::ios::binary);
	if (!Zr)
		return nullptr;

	if (Zr)
		Zr.close();

	return nullptr;
}
//セントラルディレクトリ　コピー
CenterDerect* PLRead::copycd(CenterDerect* c) {
	CenterDerect* p = (CenterDerect*)malloc(sizeof(CenterDerect));
	p->bitflag = c->bitflag;
	p->version = c->version;
	p->minversion = c->minversion;
	p->method = c->method;
	p->zokusei = c->zokusei;
	p->gaibuzokusei = c->gaibuzokusei;
	p->localheader = c->localheader;
	p->time = 0;
	p->day = 0;
	p->size = c->size;
	p->nonsize = c->nonsize;//内容変更したら　更新必要
	p->filenameleng = c->filenameleng;
	p->filename = (char*)malloc(sizeof(char)*(c->filenameleng+1));
	strcpy_s(p->filename, c->filenameleng + 1, c->filename);
	p->fieldleng = 0;
	p->comment = nullptr;
	p->kakutyo = nullptr;
	p->fielcomment = 0;
	p->discnum = c->discnum;
	p->crc = 0;

	return p;
}

ENDrecord* PLRead::copyER(ENDrecord* e) {
	ENDrecord* p= (ENDrecord*)malloc(sizeof(ENDrecord));
	p->centralnum = e->centralnum;
	p->centralsum = e->centralsum;
	p->comment = nullptr;
	p->commentleng = 0;
	p->disccentral = e->disccentral;
	p->discnum = e->discnum;
	p->endsig = e->endsig;
	p->position = e->position;
	p->size = e->size;

	return p;
}

//最初　workbook app ファイル読み込み
int PLRead::readWorkBook(char* fn) {
	char workb[] = "xl/workbook.xml";
	char appfile[] = "docProps/app.xml";

	std::ifstream Zr(fn, std::ios::in | std::ios::binary);
	if (!Zr)
		return 0;

	//セントラルディレクトのデータ
	hr = new HeaderRead(fn);
	hr->endread(&Zr);//終端コードの読み込み
	DeflateDecode* dec= new DeflateDecode(&Zr);

	//エンドレコードの保存
	ER = copyER(hr->ER);

	bool flag = false;

	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, nullptr, &Zr);
		flag = hr->searchChara(appfile, hr->scd->filename, hr->scd->filenameleng);
		if (flag)
			break;
		hr->freeheader();
	}
	if (flag) {//ファイル名が合えばローカルヘッダー読み込み
		hr->localread(cddata->localheader, &Zr);//sharesstringsの読み込み
		dec->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}
	ap=new App_File(dec->ReadV, dec->readlen);
	ap->readappfile();
	shsize = ap->tabsize;

	//セントラルヘッダーコピー
	cddataap=copycd(cddata);
	hr->freeheader();

	delete dec;
	dec = new DeflateDecode(&Zr);
	
	hr->readpos = hr->ER->position;
	hr->filenum = 0;
	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, nullptr, &Zr);
		flag = hr->searchChara(workb, hr->scd->filename, hr->scd->filenameleng);
		if (flag)
			break;
		hr->freeheader();
	}
	if (flag) {//ファイル名が合えばローカルヘッダー読み込み
		hr->localread(cddata->localheader, &Zr);//sharesstringsの読み込み
		dec->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}

	//ワークブックの読み込み
	wb=new WorkBook_edi(dec->ReadV, dec->readlen, shsize);

	wb->readworkbook();

	//セントラルヘッダーコピー
	cddatawb = copycd(cddata);

	Zr.close();

	delete dec;
	delete hr;

	return 1;
}

UINT8* PLRead::strtalloc(UINT8* a, UINT8* b) {
	size_t ms = strlen((char*)b) + 1;
	a = (UINT8*)malloc(sizeof(UINT8) * ms);
	strcpy_s((char*)a, ms, (char*)b);

	return a;
}

Sizes* PLRead::addSize(Sizes* si, Sizes* msi) {
	if (!si) {
		si = (Sizes*)malloc(sizeof(Sizes));
		si->size = strtalloc(si->size, msi->size);
		si->val = strtalloc(si->val, msi->val);
		si->next = nullptr;
	}
	else
	{
		si->next = addSize(si->next, msi);
	}
	return si;
}

itemColors* PLRead::addColors(itemColors* col, itemColors* mcol) {
	if (!col) {
		col = (itemColors*)malloc(sizeof(itemColors));
		col->s = nullptr;
		col->s = addSize(col->s, mcol->s);
		col->color = strtalloc(col->color, mcol->color);
		col->next = nullptr;
	}
	else if (strcmp((char*)mcol->color, (char*)col->color) == 0 && col) {
		//カラー同じ
		col->s = addSize(col->s, mcol->s);
	}
	else {
		//new
		col->next = addColors(col->next, mcol);
	}
	return col;
}

CsvItemandRid* PLRead::addmatchitem(CsvItemandRid* c, CsvItemandRid* m, UINT8* rid, UINT8* nrid) {
	if (!c) {
		c = (CsvItemandRid*)malloc(sizeof(CsvItemandRid));
		c->it = m->it;
		c->c = nullptr;
		c->c = m->c;
		c->rid = rid;
		c->Newrid = nrid;
		c->next = nullptr;
	}
	else {
		c->next = addmatchitem(c->next, m, rid, nrid);
	}
	return c;
}

CsvItemandRid* PLRead::addCsvItemRid(CsvItemandRid* c, CsvItemandRid* m,UINT8* rid,UINT8* nrid) {
	if (!c) {
		c = (CsvItemandRid*)malloc(sizeof(CsvItemandRid));
		c->it = strtalloc(c->it, m->it);
		c->c = nullptr;
		c->c = addColors(c->c, m->c);
		c->rid = rid;
		c->Newrid = nrid;
		c->next = nullptr;
	}
	else if (strcmp((char*)m->it, (char*)c->it) == 0) {
		//品番同じ
		c->c = addColors(c->c, m->c);
	}
	else {
		//new
		c->next = addCsvItemRid(c->next, m,rid,nrid);
	}
	return c;
}

void PLRead::workbookCheck(CsvItemandRid* citem) {
	CsvItemandRid* roo = citem;
	int res = 0;
	UINT32 i = 0;

	while (roo) {
		i = 0;
		while (i < shsize) {
			res=strncmp((char*)roo->it, (char*)wb->wbshroot[i]->name,strlen((char*)roo->it));//(2)を避けるため長さ指定
			if (res == 0) {
				matchs= addmatchitem(matchs, roo,wb->wbshroot[i]->id,nullptr);
				break;
			}
			i++;
		}
		
		if (res != 0) {
			int pl = 0;
			UINT8* ri = numchange.InttoChar(shsize + 1, &pl);
			UINT8* im = numchange.InttoChar(wb->sheetIdMax + 1, &pl);
			nomatch = addmatchitem(nomatch, roo,ri,nullptr);//不一致データ追加

			shsize=wb->addsheets(roo->it, im, ri);//workbook 配列最後尾追加
			ap->addvector_lpstr(roo->it);//app.xml　配列最後尾追加
			//app size vt:i4 変更
			free(ap->HeadRoot->vt_i4);
			ap->HeadRoot->vt_i4 = numchange.InttoChar(shsize, &pl);
			free(ap->Tvector_size);
			ap->Tvector_size = numchange.InttoChar(shsize, &pl);

		}
		roo = roo->next;
	}

	//external rid 変更
	extReferences* er = wb->exRroot;
	UINT32 exidnum = shsize + 1;
	int pl = 0;
	if (er) {
		while (er) {
			UINT8* exrid = numchange.InttoChar(exidnum, &pl);
			//rid更新
			free(er->id);
			er->id = exrid;
			exidnum++;

			er = er->next;
		}
	}

	//active tab 変更
	//free(wb->wVroot->activeTab);
	//wb->wVroot->activeTab= numchange.InttoChar(shsize, &pl);

	//ソート	
}

int PLRead::openstyleseat(char* fn) {
	std::ifstream Zr(fn, std::ios::in | std::ios::binary);
	if (!Zr)
		return 0;

	hr = new HeaderRead(fn);
	hr->endread(&Zr);//終端コードの読み込み

	Styledec = new DeflateDecode(&Zr);
	cddata = nullptr;
	bool flag = false;

	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, nullptr , &Zr);
		flag = hr->searchChara((char*)stylefn, hr->scd->filename, hr->scd->filenameleng);
		if (flag)
			break;
		hr->freeheader();
	}
	if (cddata) {//ファイル名が合えばローカルヘッダー読み込み
		hr->localread(cddata->localheader, &Zr);//sharesstringsの読み込み
		Styledec->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}

	sr = new checkstyle();

	sr->readstyle(Styledec->ReadV, Styledec->readlen);

	styleleng = Styledec->readlen;//style 解凍データ長

	delete Styledec;
	//delete hr;
	Zr.close();

	return 1;
}

UINT8* PLRead::stylesetting(Fonts* f,Fills* fi,borders* bo,stylexf* stx,cellxfs* cx,numFMts* fm) {
	
	//styke search で検索
	sr->configstyle(f,fi,bo,stx,cx,fm);

	//style設定 更新
	UINT8* sty = (UINT8*)malloc(sr->stylelen + 1);
	strcpy_s((char*)sty, sr->stylelen + 1, (const char*)sr->style);
	
	return sty;
}

int PLRead::writecompress(UINT8* d,UINT32 dl,FILE* f, CenterDerect* cd) {
	if (!f)
		return 0;

	enc = new encoding;
	enc->compress(d, dl);//データ圧縮

	crc CR;
	UINT32 sharecrc = CR.mcrc(d, dl);

	localSize = hw.localwrite(f, dd.times, sharecrc, enc->datalen, dl, cd->filenameleng, cd->filename, cd->version, cd->bitflag, cd->method);
	
	CDp = (enc->datalen) + localSize;//ローカルデータサイズ

	//セントラル情報の書き換え//
	cd->crc = sharecrc;
	cd->localheader = zip->writeposition;
	cd->day = (dd.times) & 0xFFFF;
	cd->time = (dd.times >> 16) & 0xFFFF;
	cd->size = enc->datalen;
	cd->nonsize = dl;//無圧縮サイズ
	cd->fieldleng = 0;
	cd->fielcomment = 0;
	zip->writeposition += CDp;//データ書き込み位置更新

	writeCentral(cd);

	for (UINT64 i = 0; i < enc->datalen; i++)
		fwrite(&enc->encoderv[i], sizeof(char), 1, f);

	delete enc;

	return 1;
}

char* PLRead::readshareAndWrite(char* txt1,char* fn)
{
	std::ifstream Zr(fn, std::ios::in | std::ios::binary);
	if (!Zr)
		return nullptr;

	hr = new HeaderRead(fn);
	hr->endread(&Zr);//終端コードの読み込み

	DeflateDecode* decShare = new DeflateDecode(&Zr);
	bool flag = false;

	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, (char*)shares, &Zr);
		flag = hr->searchChara((char*)shares, hr->scd->filename, hr->scd->filenameleng);
		if (flag)
			break;
		hr->freeheader();
	}
	if (cddata) {//ファイル名が合えばローカルヘッダー読み込み
		hr->localread(cddata->localheader, &Zr);//sharesstringsの読み込み
		decShare->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}

	shar = new shareRandD(decShare->ReadV, decShare->readlen);//share

	shar->getSicount();//get si count
	shar->ReadShare();//文字列読み込み

	sharestr=shar->searchSi(txt1);//文字列のSi検索　追加
	/*
	//シェアー書き込みshare書き込み　データ
	shar->siwrite();//share文字列書き込み share data更新
	shrelength = shar->wlen;
	sharedata = (UINT8*)shar->wd;
	*/	

	if (Zr)
		Zr.close();

	return (char*)stepthree;
}

void PLRead::ItemsChangeShare(CsvItemandRid* citem) {
	UINT8* stocknum = nullptr;
	//品番シェアー入力
	stocknum = shar->searchSi((char*)citem->it);
	//free(citem->it);
	citem->it = stocknum;

	//カラー名シェアー入力
	itemColors *itc = citem->c;
	itemColors* cl = citem->c;
	Sizes* sz = nullptr;
	searchItemNum* sin = new searchItemNum(nullptr,nullptr);

	while (cl) {
		sz = cl->s;
		while (sz) {
			//カラー　サイズ　結合
			//カラー utf8に
			char* Newcol = (char*)calloc(100, sizeof(char));
			sin->SJIStoUTF8((char*)cl->color, Newcol, 100);

			size_t csiz = strlen(Newcol);
			size_t ssiz = strlen((char*)sz->size);

			UINT8* mergestr = (UINT8*)malloc(sizeof(UINT8) * (csiz + ssiz + 2));
			int i = 0;
			while (Newcol[i] != '\0') {
				mergestr[i] = Newcol[i];
				i++;
			}

			mergestr[csiz] = ' '; csiz++;//スペース入れ

			i = 0;
			while (sz->size[i] != '\0') {
				mergestr[csiz + i] = sz->size[i];
				i++;
			}
			
			mergestr[csiz + i] = '\0';

			//シェアー入力
			stocknum = shar->searchSi((char*)mergestr);
			free(sz->size);//サイズ　文字列変更
			sz->size = stocknum;

			sz = sz->next;
		}
		cl = cl->next;
	}
}

char* PLRead::filenamemerge(UINT8* fno, UINT8* plusstr,UINT8* typ) {
	size_t wfn = strlen((char*)fno);
	size_t idl = strlen((char*)plusstr);
	size_t tl = strlen((char*)typ);

	size_t nfsiz = wfn + idl + tl + 1;
	char* nf = (char*)malloc(sizeof(char)*nfsiz);

	for (size_t i = 0; i < wfn; i++) {
		nf[i] = fno[i];
	}

	for (size_t i = 0; i < idl; i++) {
		nf[wfn] = plusstr[i];
		wfn++;
	}
	
	for (size_t i = 0; i < tl; i++) {
		nf[wfn] = typ[i];
		wfn++;
	}
	nf[wfn] = '\0';

	return nf;
}

int PLRead::workbookrelsadd(CsvItemandRid* nom,char* fn) {
	//workbookrel 更新
	char workbrel[] = "xl/_rels/workbook.xml.rels";
	// <Relationship Id="rId117" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet" Target="worksheets/sheet117.xml"/>
	// <Relationship Id="rid425" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/externalLink" Target="externalLinks/externalLink2.xml"/>

	UINT8 ty[] = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet";
	UINT8 estr[] = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/externalLink";

	std::ifstream Zr(fn, std::ios::in | std::ios::binary);
	if (!Zr)
		return 0;

	cddata = nullptr;//セントラルディレクトのデータ
	hr = new HeaderRead(fn);
	hr->endread(&Zr);//終端コードの読み込み
	DeflateDecode* dec = new DeflateDecode(&Zr);
	bool flag = false;

	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, workbrel, &Zr);
		flag = hr->searchChara(workbrel, hr->scd->filename, hr->scd->filenameleng);
		if (flag)
			break;
		hr->freeheader();
	}
	if (cddata) {//ファイル名が合えばローカルヘッダー読み込み
		hr->localread(cddata->localheader, &Zr);//sharesstringsの読み込み
		dec->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}
	wbr = new workb_rels(dec->ReadV, dec->readlen);
	wbr->readwbrels();

	delete dec;
	
	//filename 作成
	UINT8 sheet[] = "worksheets/sheet";
	UINT8 filetype[] = ".xml";
	CsvItemandRid* cir = nom;

	//workbookrel 追加
	while (cir) {
		char* newfn = filenamemerge(sheet, nom->rid, filetype);
		wbr->newrelationadd(ty,nom->rid, (UINT8*)newfn);
		free(newfn);
		cir = cir->next;
	}	

	//externalLink 更新
	UINT8 extlink[] = "externalLinks/externalLink";
	UINT32 exn = 1;
	int pl = 0;

	extReferences* er = wb->exRroot;
	//workbookrel 追加
	while (er) {
		UINT8* exlinknum=numchange.InttoChar(exn, &pl);
		char* exfn = filenamemerge(extlink, exlinknum, filetype);
		wbr->newrelationadd(estr,er->id, (UINT8*)exfn);
		free(exfn);
		free(exlinknum);
		er = er->next; exn++;
	}	

	
	//workbookrel タグ付け
	wbr->writewbrel();

	Zr.close();

	//delete hr;

	return 1;
}

char* PLRead::sheetread(char* hfn, CsvItemandRid* it,FILE* inf,UINT8* styo,UINT8* styt)
{
	std::ifstream Zr(hfn, std::ios::in | std::ios::binary);
	if (!Zr)
		return nullptr;
	
	hr = new HeaderRead(hfn);
	encoding* shenc = new encoding;//sharestring 圧縮

	hr->endread(&Zr); // 終端コードの読み込み
		
	DeflateDecode* Hdeco;
	
	//書き込み不要ファイル
	char sharefn[] = "xl/sharedStrings.xml";
	char stylefn[] = "xl/styles.xml";
	char workbrel[] = "xl/_rels/workbook.xml.rels";
	char workb[] = "xl/workbook.xml";
	char appfile[] = "docProps/app.xml";
	char contenstr[] = "[Content_Types].xml";//[Content_Types].xml
	bool t = false;

	Ctags* mh;//発注到着　cell データ読み込み
	searchItemNum* sI = nullptr;//品番検索　＆　書き込み
	CDdataes* slideCDdata = hr->saveCD;//ファイル名検索用

	hr->readpos = hr->ER->position;//読み込み位置初期化
	hr->filenum = 0;//レコード数初期化
	int result = 0;	
	bool flag = false;

	UINT8 sheet[] = "worksheets/sheet";
	UINT8 filetype[] = ".xml";
	char* newfn = nullptr;

	CsvItemandRid* ci = it;
	while (hr->filenum < hr->ER->centralsum)
	{
		ci = it;
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, nullptr, &Zr);

		while (ci) {
			newfn = filenamemerge(sheet, it->rid, filetype);
			flag = hr->searchChara(newfn, hr->scd->filename, hr->scd->filenameleng);	

			if (flag) {
				break;
			}
			free(newfn);
			ci = ci->next;
		}

		if (flag) {//ファイル名一致
			hr->localread(cddata->localheader, &Zr);//"worksheets/sheet"に一致するファイルの中身検索

			Hdeco = new DeflateDecode(&Zr);//解凍
			Hdeco->dataread(hr->LH->pos, cddata->nonsize);//解凍　データ読み込み

			mh = new Ctags(Hdeco->ReadV, Hdeco->readlen, shar);//シートデータ読み込み
			mh->sheetread();

			sI = new searchItemNum(it, mh);
			t = sI->searchitemNumber(sharestr, shar->inputsinum[3], shar->inputsinum[2], shar->inputsinum[1], shar->inputsinum[0], (char*)styo, (char*)styt);

			if (t)
			{//品番一致
				mh->writesheetdata();//シートデータ書き込み
				
				writecompress(mh->wd, mh->p, inf, cddata);//圧縮書き込み
			}
			delete Hdeco;//デコードデータ　削除
			delete mh;
			delete sI;
			hr->freeLH();
		}
		else {//データコピー　書き込み
			flag = hr->searchChara((char*)sharefn, hr->scd->filename, hr->scd->filenameleng);
			if (!flag) {
				flag = hr->searchChara((char*)stylefn, hr->scd->filename, hr->scd->filenameleng);
				if (!flag) {
					flag = hr->searchChara((char*)workbrel, hr->scd->filename, hr->scd->filenameleng);
					if (!flag) {
						flag = hr->searchChara((char*)workb, hr->scd->filename, hr->scd->filenameleng);
						if (!flag) {
							flag = hr->searchChara((char*)appfile, hr->scd->filename, hr->scd->filenameleng);
							if (!flag) {
								flag = hr->searchChara((char*)contenstr, hr->scd->filename, hr->scd->filenameleng);
								if (!flag) {
									//cddata一旦書き込み
									UINT32 LHposstock = zip->writeposition;//ローカルヘッダーの位置更新用
									zip->LoclheadAndDatacopy(cddata->localheader, inf, &Zr);//ローカルヘッダー検索＆書き込み
									cddata->localheader = LHposstock;//ローカルヘッダー相対位置のみ変更

									writeCentral(cddata);
								}
							}
						}						
					}
				}
			}
		}
		flag = false;
		hr->freeheader();		
	}

	if (Zr)
		Zr.close();
	delete hr;

	return (char*)stepfour;
}

writtenfilename* wfnadd(writtenfilename* r, char* n) {
	if (!r) {
		r = (writtenfilename*)malloc(sizeof(writtenfilename));
		r->fn = n;
		r->next;
	}
	else {
		r->next = wfnadd(r->next, n);
	}
	return r;
}
//new sheet nomatchitem
UINT8* PLRead::newSheetWrite(UINT8* d, UINT8* uuid, CsvItemandRid* citem, UINT8* styleone, UINT8* styletwo,FILE* wf,char* ifn,UINT8* reld) {
	const char sharefn[] = "xl/sharedStrings.xml";
	char stylefn[] = "xl/styles.xml";
	char workbrel[] = "xl/_rels/workbook.xml.rels";
	char workb[] = "xl/workbook.xml";
	char appfile[] = "docProps/app.xml";
	UINT8 drawfilen[] = "../drawings/drawing";

	size_t datlen = strlen((char*)d);
	size_t reldatal = strlen((char*)reld);

	Ctags* mh = new Ctags(d, datlen, shar);//シートデータ読み込み
	mh->sheetread();
	mh->newSheet(nullptr, uuid, citem, styleone, styletwo, sharestr);

	mh->writesheetdata();

	UINT8 sheet[] = "xl/worksheets/sheet";
	UINT8 filetype[] = ".xml";
	char* newfn = filenamemerge(sheet, citem->rid, filetype);

	cddata->version = VERSION_LH;
	cddata->bitflag = BITFLAG_LH;
	cddata->minversion = MAKEVERSION;
	cddata->method = DEFLATE_LH_CD;
	cddata->zokusei = 0;
	cddata->gaibuzokusei = 0;
	cddata->localheader = zip->writeposition;
	cddata->time = (dd.times) & 0xFFFF;
	cddata->day = (dd.times >> 16) & 0xFFFF;
	cddata->size = 0;
	cddata->nonsize = mh->p & 0xFFFFFFFF;//内容変更したら　更新必要
	cddata->filenameleng = strlen(newfn);
	cddata->filename = newfn;
	cddata->fieldleng = 0;
	cddata->fielcomment = 0;
	
	writecompress(mh->wd, mh->p, wf, cddata);
	free(newfn);
	/*
	UINT8* drawid = nullptr;
	if (mh->drawing_id) {
		size_t idlen = strlen((char*)mh->drawing_id) + 1;
		drawid = (UINT8*)malloc(sizeof(UINT8) * idlen);
		strcpy_s((char*)drawid, idlen, (char*)mh->drawing_id);
	}
	*/
	//sheet rel 書き込み
	UINT8 shrel[] = "xl/worksheets/_rels/sheet";
	UINT8 filereltype[] = ".xml.rels";
	char* newrelfn = filenamemerge(shrel, citem->rid, filereltype);

	char* drtarget = filenamemerge(drawfilen, citem->rid, filetype);

	mh->readsheetrels(reld, reldatal);
	free(mh->relroot->target);
	mh->relroot->target = (UINT8*)drtarget;

	mh->writerels();

	cddata->version = VERSION_LH;
	cddata->bitflag = BITFLAG_LH;
	cddata->minversion = MAKEVERSION;
	cddata->method = DEFLATE_LH_CD;
	cddata->zokusei = 0;
	cddata->gaibuzokusei = 0;
	cddata->localheader = zip->writeposition;
	cddata->time = (dd.times) & 0xFFFF;
	cddata->day = (dd.times >> 16) & 0xFFFF;
	cddata->size = 0;
	cddata->nonsize = mh->wl & 0xFFFFFFFF;//内容変更したら　更新必要
	cddata->filenameleng = strlen(newrelfn);
	cddata->filename = newrelfn;
	cddata->fieldleng = 0;
	cddata->fielcomment = 0;

	writecompress(mh->rwd, mh->wl, wf, cddata);

	delete mh;
	delete shar;

	return nullptr;
}
//content type 追加
int PLRead::makecontentType(char* fn, CsvItemandRid* r,FILE* wf) {
	// <Override PartName="/xl/worksheets/sheet425.xml" ContentType="application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml"/>
	// <Override PartName="/xl/drawings/drawing425.xml" ContentType="application/vnd.openxmlformats-officedocument.drawing+xml"/>
	UINT8 partsh[] = "/xl/worksheets/sheet";
	UINT8 ftype[] = ".xml";
	UINT8 typesh[] = "application/vnd.openxmlformats-officedocument.spreadsheetml.worksheet+xml";

	UINT8 partdr[] = "/xl/drawings/drawing";
	UINT8 typedr[] = "application/vnd.openxmlformats-officedocument.drawing+xml";

	char contentstr[] = "[Content_Types].xml";

	std::ifstream Zr(fn, std::ios::in | std::ios::binary);
	if (!Zr)
		return 0;

	cddata = nullptr;//セントラルディレクトのデータ
	hr = new HeaderRead(fn);
	hr->endread(&Zr);//終端コードの読み込み
	DeflateDecode* dec = new DeflateDecode(&Zr);
	bool flag = false;

	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, nullptr, &Zr);
		flag = hr->searchChara(contentstr, hr->scd->filename, hr->scd->filenameleng);
		if (flag)
			break;
		hr->freeheader();
	}
	if (cddata) {//ファイル名が合えばローカルヘッダー読み込み
		hr->localread(cddata->localheader, &Zr);//sharesstringsの読み込み
		dec->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}
	contentEdit* ce = new contentEdit(dec->ReadV, dec->readlen);
	ce->contentread();

	CsvItemandRid* p = r;
	while (p) {
		char* newsh = filenamemerge(partsh, p->rid, ftype);
		char* newdr = filenamemerge(partdr, p->rid, ftype);

		UINT8* shnewty = (UINT8*)calloc(74, sizeof(UINT8));
		strcpy_s((char*)shnewty, 74, (char*)typesh);

		UINT8* drnewty = (UINT8*)calloc(58, sizeof(UINT8));
		strcpy_s((char*)drnewty, 58, (char*)typedr);

		ce->oroot = ce->addove(ce->oroot, (UINT8*)newsh, shnewty, 0);
		ce->oroot = ce->addove(ce->oroot, (UINT8*)newdr, drnewty, 0);

		p = p->next;
	}

	ce->contentwrite();

	writecompress(ce->wd, ce->wl, wf, cddata);

	hr->freeheader();

	delete dec;
	delete ce;

	return 1;
}

void PLRead::makedrawxml(UINT8* drawdata, UINT8* rid,UINT8* targetfile,FILE* f,UINT8* dreldata,UINT8* uid) {
	size_t datlen = strlen((char*)drawdata);

	dr = new DrawEdit(drawdata, datlen);
	dr->readdraw();
	/*
	* free(dr->Anroot->p->p->Pr->exLst->a16->id);

	size_t nidlen = strlen((char*)uid) + 3;
	UINT8* nid = (UINT8*)malloc(sizeof(UINT8) * nidlen);
	nidlen = 0;
	nid[nidlen] = '{'; nidlen++;
	for (nidlen; nidlen < strlen((char*)uid); nidlen++) {
		nid[nidlen] = uid[nidlen - 1];
	}
	nid[nidlen] = '}'; nidlen++;
	nid[nidlen] = '\0';

	dr->Anroot->p->p->Pr->exLst->a16->id = nid;
	*/	
	dr->drawWrite();

	UINT8 drn[] = "xl/drawings/drawing";
	UINT8 filetype[] = ".xml";
	char* newfn = filenamemerge(drn, rid, filetype);

	cddata->version = VERSION_LH;
	cddata->bitflag = BITFLAG_LH;
	cddata->minversion = MAKEVERSION;
	cddata->method = DEFLATE_LH_CD;
	cddata->zokusei = 0;
	cddata->gaibuzokusei = 0;
	cddata->localheader = zip->writeposition;
	cddata->time = (dd.times) & 0xFFFF;
	cddata->day = (dd.times >> 16) & 0xFFFF;
	cddata->size = 0;
	cddata->nonsize = dr->wl;//内容変更したら　更新必要
	cddata->filenameleng = strlen(newfn);
	cddata->filename = newfn;
	cddata->fieldleng = 0;
	cddata->fielcomment = 0;

	writecompress(dr->wd, dr->wl, f, cddata);
	free(newfn);
	
	datlen = strlen((char*)dreldata);
	dr->readdrawrels(dreldata, datlen);

	dr->writerels();

	UINT8 drel[] = "xl/drawings/_rels/drawing";
	UINT8 filetyperel[] = ".xml.rels";
	newfn = filenamemerge(drel, rid, filetyperel);

	cddata->version = VERSION_LH;
	cddata->bitflag = BITFLAG_LH;
	cddata->minversion = MAKEVERSION;
	cddata->method = DEFLATE_LH_CD;
	cddata->zokusei = 0;
	cddata->gaibuzokusei = 0;
	cddata->localheader = zip->writeposition;
	cddata->time = (dd.times) & 0xFFFF;
	cddata->day = (dd.times >> 16) & 0xFFFF;
	cddata->size = 0;
	cddata->nonsize = dr->rwl;//内容変更したら　更新必要
	cddata->filenameleng = strlen(newfn);
	cddata->filename = newfn;
	cddata->fieldleng = 0;
	cddata->fielcomment = 0;

	writecompress(dr->rwd, dr->rwl, f, cddata);
	free(newfn);

	delete dr;
}

void PLRead::endrecordwrite(FILE* wf) {

	ER->centralnum = recordsum;//ディスク上のセントラルレコード数
	ER->centralsum = recordsum;//セントラルレコード数

	for (size_t i = 0; i < central.size(); i++)
		fwrite(&central[i], sizeof(char), 1, wf);

	hw.eocdwrite(wf, ER->discnum, ER->disccentral, ER->centralnum, ER->centralsum, zip->writeposition, central.size());

	central.clear();
}

char* PLRead::errorItems() {
	searchItemNum* sI = new searchItemNum(nullptr, nullptr);

	//matchsroot = matchs;
	unitC un;
	int matchor = 1;
	int matchcol = 1;
	char* EItems = nullptr;

	//シートがない品番、カラーを比較
	Items* eitem = readItem->its;
	if (matchs) {
		EItems = (char*)calloc(3000, sizeof(char));
		if (!EItems)
			return nullptr;
		while (eitem) {
			eitem->col = un.slipNum(eitem->col);
			while (matchs) {
				//matchor = strcmp((const char*)eitem->itn, (const char*)matchs->itemnum);
				if (matchor == 0) {//品番、いろ一致入力
					//matchcol = strcmp((const char*)eitem->col, (const char*)matchs->color);
					if (matchcol == 0) {
						break;
					}
				}
				else {
					matchcol = 1;
				}
				matchs = matchs->next;
			}
			if (matchor == 0 && matchcol == 0) {//品番、いろ一致入力
			}
			else {
				//エラー　シートなし
				//char *ei=sI->CharChenge(eitem->itn);//shift jis変換
				EItems=adderrorstr(EItems, eitem->itn);
				EItems[errlen] = ' '; errlen++;

				char* ec = sI->CharChenge(eitem->col);//shift jis変換
				//eitem->col = (UINT8*)ec;
				EItems = adderrorstr(EItems, (UINT8*)ec);
				delete[] ec;

				EItems[errlen] = '\r'; errlen++;
				EItems[errlen] = '\n'; errlen++;
			}
			//matchs = matchsroot;//初期化
			eitem = eitem->next;
		}
		EItems[errlen] = '\0';
	}	
	
	//マッチアイテムリスト解放
	//sI->freerootmacht(matchsroot);
	delete sI;
	delete readItem;

	return EItems;
}

char* PLRead::adderrorstr(char* e,UINT8* it) {
	size_t i = 0;

	while (it[i] != '\0') {
		e[errlen] = it[i];
		errlen++;
		i++;
	}
	//delete[] it;

	return e;
}

char* PLRead::writename(char* wfn, size_t len)
{
	char* fn = (char*)malloc(250);
	char c[] = "Centraldata";//11
	size_t i = 0;

	int slashnum = 0;
	int centerlen = 0;
	char onetimefn[255] = { 0 };

	char* fpath = nullptr;
	size_t pathlen = 0;

	if (fn) {
		while (wfn[i] != '.' && i < len) {
			fn[i] = wfn[i];
			i++;
		}

		fn[i] = '2';// .記入
		i++;
		fn[i] = wfn[i - 1];// .記入
		i++;

		fn[i] = 'x'; i++;
		fn[i] = 'l'; i++;
		fn[i] = 's'; i++;
		fn[i] = 'x'; i++;
		fn[i] = '\0'; i++;
	}
	return fn;
}

void PLRead::writeCentral(CenterDerect* c)
{
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (CENTRALSIGNATURE >> (24 - (8 * i))) & 0xFF;
		central.push_back(ce);//シグネチャの書き込み
	}

	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->version >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//抽出に必要なバージョン（最小）//読み取りでは2d
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->minversion >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//std::cout << "抽出に必要なバージョン
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->bitflag >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//    圧縮方法
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->method >> (8 * i)) & 0xFF;
		central.push_back(ce);//圧縮方式の書き込み2バイト　ローカルヘッダと同じ
	}
	//    ファイルの最終変更時刻
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->time >> (8 * i)) & 0xFF;
		central.push_back(ce);//時間2バイトの書き込み
	}
	//    ファイルの最終変更日
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->day >> (8 * i)) & 0xFF;
		central.push_back(ce);//日付2バイトの書き込み
	}
	//crc
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (c->crc >> (8 * i)) & 0xFF;
		central.push_back(ce);//crc 4byte 書き込み（ローカルファイルの値をcrc？）
	}
	//    圧縮サイズ
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (c->size >> (8 * i)) & 0xFF;
		central.push_back(ce);//圧縮サイズ 書き込み
	}
	//std::cout << "圧縮サイズ 4バイト" << cd.size << std::endl;
	//    非圧縮サイズ
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (c->nonsize >> (8 * i)) & 0xFF;
		central.push_back(ce);//圧縮前サイズ 書き込み
	}
	//std::cout << "非圧縮サイズ 4バイト" << cd.nonsize << std::endl;
	//    ファイル名の長さ（n)
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->filenameleng >> (8 * i)) & 0xFF;
		central.push_back(ce);//ファイル名の長さ2バイト 書き込み
	}
	// 追加フィールド長（m）
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->fieldleng >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//ファイルのコメント長（k）
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->fielcomment >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}

	//    ファイルが始まるディスク番号
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->discnum >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//内部ファイル属性（コピー）2バイト 書き込み
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->zokusei >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//外部ファイル属性（コピー）4バイト 書き込み
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (c->gaibuzokusei >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//ローカルヘッダ相対オフセット4バイト 書き込み
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (c->localheader >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}

	//ファイル名の書き込み
	for (int i = 0; i < c->filenameleng; i++) {
		central.push_back(c->filename[i]);
	}
	//拡張フィールド
	if (c->fieldleng > 0) {
		for (int i = 0; i < c->fieldleng; i++) {
			central.push_back(c->kakutyo[i]);
		}
	}
	//ファイルコメント　なし
	if (c->fielcomment > 0) {
		for (int i = 0; i < c->fielcomment; i++) {
			central.push_back(c->comment[i]);
		}
	}
	recordsum++;
}

void PLRead::freeItem(Items* t) {
	struct Items* q;
	while (t != NULL) {
		q = t->next;  /* 次へのポインタを保存 */
		free(t->itn);
		free(t->col);
		free(t->s100);
		free(t->s110);
		free(t->s120);
		free(t->s130);
		free(t->s140);
		free(t->s150);
		free(t->s160);
		free(t->sF);
		free(t->s90);
		free(t);
		t = q;
	}
}

char* PLRead::packingread(char* fn)
{
	std::ifstream inf(fn, std::ios::in | std::ios::binary);

	if (!inf) {
		return nullptr;
	}

	HeaderRead* hr = new HeaderRead(fn);
	CenterDerect* cddata = nullptr;//セントラルディレクトのデータ
	hr->endread(&inf);//終端コードの読み込み
	hr->freeER();

	//-----------------------//
	//シェアー文字列読み込み
	//-----------------------//

	DeflateDecode* decShare = new DeflateDecode(&inf);//sharestring ファイルの保存用
	//share セントラル取得
	while (hr->filenum < hr->ER->centralsum) {//cddata mallocなし
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralsum, (char*)shares, &inf);
		if (cddata) {
			break;
		}
		hr->freeheader();
	}
	if (cddata) {//ファイル名が合えばローカルヘッダー読み込み
		hr->localread(cddata->localheader, &inf);//sharesstringsの読み込み
		decShare->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}
	hr->freeheader();	
	
	shareRandD* sharray = new shareRandD(decShare->ReadV, decShare->readlen);//share string read to array

	sharray->getSicount();//get si count
	sharray->ReadShare();//文字列読み込み デコードデータ削除OK

	delete decShare;
	
	//-------------------------------//
	//パッキングリストシート読み込み
	//-------------------------------//
	
	char sheetname[] = "worksheets/sheet1.xml";//ファイル位置　ファイル名部分一致検索
	DeflateDecode* decsheet = new DeflateDecode(&inf);

	hr->filenum = 0;//レコード数初期化
	hr->readpos = hr->ER->position;
	cddata = nullptr;
	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralsum, sheetname, &inf);//セントラルディレクトのデータ
		if (cddata) {
			break;
		}
		hr->freeheader();
	}
	if (cddata) {//ファイル名が合えばローカルヘッダー読み込み
		hr->localread(cddata->localheader, &inf);//sharesstringsの読み込み
		decsheet->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}
	hr->freeheader();//cddata解放
	Ctags* Isheet = nullptr;//アイテムシートデータ
	Isheet = new Ctags(decsheet->ReadV, decsheet->readlen, sharray);

	Isheet->sheetread();

	delete decsheet;//デコードデータ削除

	readItem = new shipinfo(Isheet->rows);//シートデータ参照　freeなし
	readItem->GetItems();//mallocなし　シートとセット

	delete sharray;	
	delete Isheet;
	delete hr;

	inf.close();

	return (char*)stepone;//sg->its;//get item list
}
