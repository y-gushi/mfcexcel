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
	dd.getday();//���Ԃ̎擾
	zip=new zipwrite(dd.times);//zip�f�[�^�����
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
//�Z���g�����f�B���N�g���@�R�s�[
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
	p->nonsize = c->nonsize;//���e�ύX������@�X�V�K�v
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

//�ŏ��@workbook app �t�@�C���ǂݍ���
int PLRead::readWorkBook(char* fn) {
	char workb[] = "xl/workbook.xml";
	char appfile[] = "docProps/app.xml";

	std::ifstream Zr(fn, std::ios::in | std::ios::binary);
	if (!Zr)
		return 0;

	//�Z���g�����f�B���N�g�̃f�[�^
	hr = new HeaderRead(fn);
	hr->endread(&Zr);//�I�[�R�[�h�̓ǂݍ���
	DeflateDecode* dec= new DeflateDecode(&Zr);

	//�G���h���R�[�h�̕ۑ�
	ER = copyER(hr->ER);

	bool flag = false;

	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, nullptr, &Zr);
		flag = hr->searchChara(appfile, hr->scd->filename, hr->scd->filenameleng);
		if (flag)
			break;
		hr->freeheader();
	}
	if (flag) {//�t�@�C�����������΃��[�J���w�b�_�[�ǂݍ���
		hr->localread(cddata->localheader, &Zr);//sharesstrings�̓ǂݍ���
		dec->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}
	ap=new App_File(dec->ReadV, dec->readlen);
	ap->readappfile();
	shsize = ap->tabsize;

	//�Z���g�����w�b�_�[�R�s�[
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
	if (flag) {//�t�@�C�����������΃��[�J���w�b�_�[�ǂݍ���
		hr->localread(cddata->localheader, &Zr);//sharesstrings�̓ǂݍ���
		dec->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}

	//���[�N�u�b�N�̓ǂݍ���
	wb=new WorkBook_edi(dec->ReadV, dec->readlen, shsize);

	wb->readworkbook();

	//�Z���g�����w�b�_�[�R�s�[
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
		//�J���[����
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
		//�i�ԓ���
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
			res=strncmp((char*)roo->it, (char*)wb->wbshroot[i]->name,strlen((char*)roo->it));//(2)������邽�ߒ����w��
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
			nomatch = addmatchitem(nomatch, roo,ri,nullptr);//�s��v�f�[�^�ǉ�

			shsize=wb->addsheets(roo->it, im, ri);//workbook �z��Ō���ǉ�
			ap->addvector_lpstr(roo->it);//app.xml�@�z��Ō���ǉ�
			//app size vt:i4 �ύX
			free(ap->HeadRoot->vt_i4);
			ap->HeadRoot->vt_i4 = numchange.InttoChar(shsize, &pl);
			free(ap->Tvector_size);
			ap->Tvector_size = numchange.InttoChar(shsize, &pl);

		}
		roo = roo->next;
	}

	//external rid �ύX
	extReferences* er = wb->exRroot;
	UINT32 exidnum = shsize + 1;
	int pl = 0;
	if (er) {
		while (er) {
			UINT8* exrid = numchange.InttoChar(exidnum, &pl);
			//rid�X�V
			free(er->id);
			er->id = exrid;
			exidnum++;

			er = er->next;
		}
	}

	//active tab �ύX
	//free(wb->wVroot->activeTab);
	//wb->wVroot->activeTab= numchange.InttoChar(shsize, &pl);

	//�\�[�g	
}

int PLRead::openstyleseat(char* fn) {
	std::ifstream Zr(fn, std::ios::in | std::ios::binary);
	if (!Zr)
		return 0;

	hr = new HeaderRead(fn);
	hr->endread(&Zr);//�I�[�R�[�h�̓ǂݍ���

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
	if (cddata) {//�t�@�C�����������΃��[�J���w�b�_�[�ǂݍ���
		hr->localread(cddata->localheader, &Zr);//sharesstrings�̓ǂݍ���
		Styledec->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}

	sr = new checkstyle();

	sr->readstyle(Styledec->ReadV, Styledec->readlen);

	styleleng = Styledec->readlen;//style �𓀃f�[�^��

	delete Styledec;
	//delete hr;
	Zr.close();

	return 1;
}

UINT8* PLRead::stylesetting(Fonts* f,Fills* fi,borders* bo,stylexf* stx,cellxfs* cx,numFMts* fm) {
	
	//styke search �Ō���
	sr->configstyle(f,fi,bo,stx,cx,fm);

	//style�ݒ� �X�V
	UINT8* sty = (UINT8*)malloc(sr->stylelen + 1);
	strcpy_s((char*)sty, sr->stylelen + 1, (const char*)sr->style);
	
	return sty;
}

int PLRead::writecompress(UINT8* d,UINT32 dl,FILE* f, CenterDerect* cd) {
	if (!f)
		return 0;

	enc = new encoding;
	enc->compress(d, dl);//�f�[�^���k

	crc CR;
	UINT32 sharecrc = CR.mcrc(d, dl);

	localSize = hw.localwrite(f, dd.times, sharecrc, enc->datalen, dl, cd->filenameleng, cd->filename, cd->version, cd->bitflag, cd->method);
	
	CDp = (enc->datalen) + localSize;//���[�J���f�[�^�T�C�Y

	//�Z���g�������̏�������//
	cd->crc = sharecrc;
	cd->localheader = zip->writeposition;
	cd->day = (dd.times) & 0xFFFF;
	cd->time = (dd.times >> 16) & 0xFFFF;
	cd->size = enc->datalen;
	cd->nonsize = dl;//�����k�T�C�Y
	cd->fieldleng = 0;
	cd->fielcomment = 0;
	zip->writeposition += CDp;//�f�[�^�������݈ʒu�X�V

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
	hr->endread(&Zr);//�I�[�R�[�h�̓ǂݍ���

	DeflateDecode* decShare = new DeflateDecode(&Zr);
	bool flag = false;

	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, (char*)shares, &Zr);
		flag = hr->searchChara((char*)shares, hr->scd->filename, hr->scd->filenameleng);
		if (flag)
			break;
		hr->freeheader();
	}
	if (cddata) {//�t�@�C�����������΃��[�J���w�b�_�[�ǂݍ���
		hr->localread(cddata->localheader, &Zr);//sharesstrings�̓ǂݍ���
		decShare->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}

	shar = new shareRandD(decShare->ReadV, decShare->readlen);//share

	shar->getSicount();//get si count
	shar->ReadShare();//������ǂݍ���

	sharestr=shar->searchSi(txt1);//�������Si�����@�ǉ�
	/*
	//�V�F�A�[��������share�������݁@�f�[�^
	shar->siwrite();//share�����񏑂����� share data�X�V
	shrelength = shar->wlen;
	sharedata = (UINT8*)shar->wd;
	*/	

	if (Zr)
		Zr.close();

	return (char*)stepthree;
}

void PLRead::ItemsChangeShare(CsvItemandRid* citem) {
	UINT8* stocknum = nullptr;
	//�i�ԃV�F�A�[����
	stocknum = shar->searchSi((char*)citem->it);
	//free(citem->it);
	citem->it = stocknum;

	//�J���[���V�F�A�[����
	itemColors *itc = citem->c;
	itemColors* cl = citem->c;
	Sizes* sz = nullptr;
	searchItemNum* sin = new searchItemNum(nullptr,nullptr);

	while (cl) {
		sz = cl->s;
		while (sz) {
			//�J���[�@�T�C�Y�@����
			//�J���[ utf8��
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

			mergestr[csiz] = ' '; csiz++;//�X�y�[�X����

			i = 0;
			while (sz->size[i] != '\0') {
				mergestr[csiz + i] = sz->size[i];
				i++;
			}
			
			mergestr[csiz + i] = '\0';

			//�V�F�A�[����
			stocknum = shar->searchSi((char*)mergestr);
			free(sz->size);//�T�C�Y�@������ύX
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
	//workbookrel �X�V
	char workbrel[] = "xl/_rels/workbook.xml.rels";
	// <Relationship Id="rId117" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet" Target="worksheets/sheet117.xml"/>
	// <Relationship Id="rid425" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/externalLink" Target="externalLinks/externalLink2.xml"/>

	UINT8 ty[] = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/worksheet";
	UINT8 estr[] = "http://schemas.openxmlformats.org/officeDocument/2006/relationships/externalLink";

	std::ifstream Zr(fn, std::ios::in | std::ios::binary);
	if (!Zr)
		return 0;

	cddata = nullptr;//�Z���g�����f�B���N�g�̃f�[�^
	hr = new HeaderRead(fn);
	hr->endread(&Zr);//�I�[�R�[�h�̓ǂݍ���
	DeflateDecode* dec = new DeflateDecode(&Zr);
	bool flag = false;

	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, workbrel, &Zr);
		flag = hr->searchChara(workbrel, hr->scd->filename, hr->scd->filenameleng);
		if (flag)
			break;
		hr->freeheader();
	}
	if (cddata) {//�t�@�C�����������΃��[�J���w�b�_�[�ǂݍ���
		hr->localread(cddata->localheader, &Zr);//sharesstrings�̓ǂݍ���
		dec->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}
	wbr = new workb_rels(dec->ReadV, dec->readlen);
	wbr->readwbrels();

	delete dec;
	
	//filename �쐬
	UINT8 sheet[] = "worksheets/sheet";
	UINT8 filetype[] = ".xml";
	CsvItemandRid* cir = nom;

	//workbookrel �ǉ�
	while (cir) {
		char* newfn = filenamemerge(sheet, nom->rid, filetype);
		wbr->newrelationadd(ty,nom->rid, (UINT8*)newfn);
		free(newfn);
		cir = cir->next;
	}	

	//externalLink �X�V
	UINT8 extlink[] = "externalLinks/externalLink";
	UINT32 exn = 1;
	int pl = 0;

	extReferences* er = wb->exRroot;
	//workbookrel �ǉ�
	while (er) {
		UINT8* exlinknum=numchange.InttoChar(exn, &pl);
		char* exfn = filenamemerge(extlink, exlinknum, filetype);
		wbr->newrelationadd(estr,er->id, (UINT8*)exfn);
		free(exfn);
		free(exlinknum);
		er = er->next; exn++;
	}	

	
	//workbookrel �^�O�t��
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
	encoding* shenc = new encoding;//sharestring ���k

	hr->endread(&Zr); // �I�[�R�[�h�̓ǂݍ���
		
	DeflateDecode* Hdeco;
	
	//�������ݕs�v�t�@�C��
	char sharefn[] = "xl/sharedStrings.xml";
	char stylefn[] = "xl/styles.xml";
	char workbrel[] = "xl/_rels/workbook.xml.rels";
	char workb[] = "xl/workbook.xml";
	char appfile[] = "docProps/app.xml";
	char contenstr[] = "[Content_Types].xml";//[Content_Types].xml
	bool t = false;

	Ctags* mh;//���������@cell �f�[�^�ǂݍ���
	searchItemNum* sI = nullptr;//�i�Ԍ����@���@��������
	CDdataes* slideCDdata = hr->saveCD;//�t�@�C���������p

	hr->readpos = hr->ER->position;//�ǂݍ��݈ʒu������
	hr->filenum = 0;//���R�[�h��������
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

		if (flag) {//�t�@�C������v
			hr->localread(cddata->localheader, &Zr);//"worksheets/sheet"�Ɉ�v����t�@�C���̒��g����

			Hdeco = new DeflateDecode(&Zr);//��
			Hdeco->dataread(hr->LH->pos, cddata->nonsize);//�𓀁@�f�[�^�ǂݍ���

			mh = new Ctags(Hdeco->ReadV, Hdeco->readlen, shar);//�V�[�g�f�[�^�ǂݍ���
			mh->sheetread();

			sI = new searchItemNum(it, mh);
			t = sI->searchitemNumber(sharestr, shar->inputsinum[3], shar->inputsinum[2], shar->inputsinum[1], shar->inputsinum[0], (char*)styo, (char*)styt);

			if (t)
			{//�i�Ԉ�v
				mh->writesheetdata();//�V�[�g�f�[�^��������
				
				writecompress(mh->wd, mh->p, inf, cddata);//���k��������
			}
			delete Hdeco;//�f�R�[�h�f�[�^�@�폜
			delete mh;
			delete sI;
			hr->freeLH();
		}
		else {//�f�[�^�R�s�[�@��������
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
									//cddata��U��������
									UINT32 LHposstock = zip->writeposition;//���[�J���w�b�_�[�̈ʒu�X�V�p
									zip->LoclheadAndDatacopy(cddata->localheader, inf, &Zr);//���[�J���w�b�_�[��������������
									cddata->localheader = LHposstock;//���[�J���w�b�_�[���Έʒu�̂ݕύX

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

	Ctags* mh = new Ctags(d, datlen, shar);//�V�[�g�f�[�^�ǂݍ���
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
	cddata->nonsize = mh->p & 0xFFFFFFFF;//���e�ύX������@�X�V�K�v
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
	//sheet rel ��������
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
	cddata->nonsize = mh->wl & 0xFFFFFFFF;//���e�ύX������@�X�V�K�v
	cddata->filenameleng = strlen(newrelfn);
	cddata->filename = newrelfn;
	cddata->fieldleng = 0;
	cddata->fielcomment = 0;

	writecompress(mh->rwd, mh->wl, wf, cddata);

	delete mh;
	delete shar;

	return nullptr;
}
//content type �ǉ�
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

	cddata = nullptr;//�Z���g�����f�B���N�g�̃f�[�^
	hr = new HeaderRead(fn);
	hr->endread(&Zr);//�I�[�R�[�h�̓ǂݍ���
	DeflateDecode* dec = new DeflateDecode(&Zr);
	bool flag = false;

	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralnum, nullptr, &Zr);
		flag = hr->searchChara(contentstr, hr->scd->filename, hr->scd->filenameleng);
		if (flag)
			break;
		hr->freeheader();
	}
	if (cddata) {//�t�@�C�����������΃��[�J���w�b�_�[�ǂݍ���
		hr->localread(cddata->localheader, &Zr);//sharesstrings�̓ǂݍ���
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
	cddata->nonsize = dr->wl;//���e�ύX������@�X�V�K�v
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
	cddata->nonsize = dr->rwl;//���e�ύX������@�X�V�K�v
	cddata->filenameleng = strlen(newfn);
	cddata->filename = newfn;
	cddata->fieldleng = 0;
	cddata->fielcomment = 0;

	writecompress(dr->rwd, dr->rwl, f, cddata);
	free(newfn);

	delete dr;
}

void PLRead::endrecordwrite(FILE* wf) {

	ER->centralnum = recordsum;//�f�B�X�N��̃Z���g�������R�[�h��
	ER->centralsum = recordsum;//�Z���g�������R�[�h��

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

	//�V�[�g���Ȃ��i�ԁA�J���[���r
	Items* eitem = readItem->its;
	if (matchs) {
		EItems = (char*)calloc(3000, sizeof(char));
		if (!EItems)
			return nullptr;
		while (eitem) {
			eitem->col = un.slipNum(eitem->col);
			while (matchs) {
				//matchor = strcmp((const char*)eitem->itn, (const char*)matchs->itemnum);
				if (matchor == 0) {//�i�ԁA�����v����
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
			if (matchor == 0 && matchcol == 0) {//�i�ԁA�����v����
			}
			else {
				//�G���[�@�V�[�g�Ȃ�
				//char *ei=sI->CharChenge(eitem->itn);//shift jis�ϊ�
				EItems=adderrorstr(EItems, eitem->itn);
				EItems[errlen] = ' '; errlen++;

				char* ec = sI->CharChenge(eitem->col);//shift jis�ϊ�
				//eitem->col = (UINT8*)ec;
				EItems = adderrorstr(EItems, (UINT8*)ec);
				delete[] ec;

				EItems[errlen] = '\r'; errlen++;
				EItems[errlen] = '\n'; errlen++;
			}
			//matchs = matchsroot;//������
			eitem = eitem->next;
		}
		EItems[errlen] = '\0';
	}	
	
	//�}�b�`�A�C�e�����X�g���
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

		fn[i] = '2';// .�L��
		i++;
		fn[i] = wfn[i - 1];// .�L��
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
		central.push_back(ce);//�V�O�l�`���̏�������
	}

	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->version >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//���o�ɕK�v�ȃo�[�W�����i�ŏ��j//�ǂݎ��ł�2d
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->minversion >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//std::cout << "���o�ɕK�v�ȃo�[�W����
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->bitflag >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//    ���k���@
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->method >> (8 * i)) & 0xFF;
		central.push_back(ce);//���k�����̏�������2�o�C�g�@���[�J���w�b�_�Ɠ���
	}
	//    �t�@�C���̍ŏI�ύX����
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->time >> (8 * i)) & 0xFF;
		central.push_back(ce);//����2�o�C�g�̏�������
	}
	//    �t�@�C���̍ŏI�ύX��
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->day >> (8 * i)) & 0xFF;
		central.push_back(ce);//���t2�o�C�g�̏�������
	}
	//crc
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (c->crc >> (8 * i)) & 0xFF;
		central.push_back(ce);//crc 4byte �������݁i���[�J���t�@�C���̒l��crc�H�j
	}
	//    ���k�T�C�Y
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (c->size >> (8 * i)) & 0xFF;
		central.push_back(ce);//���k�T�C�Y ��������
	}
	//std::cout << "���k�T�C�Y 4�o�C�g" << cd.size << std::endl;
	//    �񈳏k�T�C�Y
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (c->nonsize >> (8 * i)) & 0xFF;
		central.push_back(ce);//���k�O�T�C�Y ��������
	}
	//std::cout << "�񈳏k�T�C�Y 4�o�C�g" << cd.nonsize << std::endl;
	//    �t�@�C�����̒����in)
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->filenameleng >> (8 * i)) & 0xFF;
		central.push_back(ce);//�t�@�C�����̒���2�o�C�g ��������
	}
	// �ǉ��t�B�[���h���im�j
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->fieldleng >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//�t�@�C���̃R�����g���ik�j
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->fielcomment >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}

	//    �t�@�C�����n�܂�f�B�X�N�ԍ�
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->discnum >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//�����t�@�C�������i�R�s�[�j2�o�C�g ��������
	for (int i = 0; i < 2; i++) {
		unsigned char ce = (c->zokusei >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//�O���t�@�C�������i�R�s�[�j4�o�C�g ��������
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (c->gaibuzokusei >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}
	//���[�J���w�b�_���΃I�t�Z�b�g4�o�C�g ��������
	for (int i = 0; i < 4; i++) {
		unsigned char ce = (c->localheader >> (8 * i)) & 0xFF;
		central.push_back(ce);
	}

	//�t�@�C�����̏�������
	for (int i = 0; i < c->filenameleng; i++) {
		central.push_back(c->filename[i]);
	}
	//�g���t�B�[���h
	if (c->fieldleng > 0) {
		for (int i = 0; i < c->fieldleng; i++) {
			central.push_back(c->kakutyo[i]);
		}
	}
	//�t�@�C���R�����g�@�Ȃ�
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
		q = t->next;  /* ���ւ̃|�C���^��ۑ� */
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
	CenterDerect* cddata = nullptr;//�Z���g�����f�B���N�g�̃f�[�^
	hr->endread(&inf);//�I�[�R�[�h�̓ǂݍ���
	hr->freeER();

	//-----------------------//
	//�V�F�A�[������ǂݍ���
	//-----------------------//

	DeflateDecode* decShare = new DeflateDecode(&inf);//sharestring �t�@�C���̕ۑ��p
	//share �Z���g�����擾
	while (hr->filenum < hr->ER->centralsum) {//cddata malloc�Ȃ�
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralsum, (char*)shares, &inf);
		if (cddata) {
			break;
		}
		hr->freeheader();
	}
	if (cddata) {//�t�@�C�����������΃��[�J���w�b�_�[�ǂݍ���
		hr->localread(cddata->localheader, &inf);//sharesstrings�̓ǂݍ���
		decShare->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}
	hr->freeheader();	
	
	shareRandD* sharray = new shareRandD(decShare->ReadV, decShare->readlen);//share string read to array

	sharray->getSicount();//get si count
	sharray->ReadShare();//������ǂݍ��� �f�R�[�h�f�[�^�폜OK

	delete decShare;
	
	//-------------------------------//
	//�p�b�L���O���X�g�V�[�g�ǂݍ���
	//-------------------------------//
	
	char sheetname[] = "worksheets/sheet1.xml";//�t�@�C���ʒu�@�t�@�C����������v����
	DeflateDecode* decsheet = new DeflateDecode(&inf);

	hr->filenum = 0;//���R�[�h��������
	hr->readpos = hr->ER->position;
	cddata = nullptr;
	while (hr->filenum < hr->ER->centralsum) {
		cddata = hr->centeroneread(hr->readpos, hr->ER->size, hr->ER->centralsum, sheetname, &inf);//�Z���g�����f�B���N�g�̃f�[�^
		if (cddata) {
			break;
		}
		hr->freeheader();
	}
	if (cddata) {//�t�@�C�����������΃��[�J���w�b�_�[�ǂݍ���
		hr->localread(cddata->localheader, &inf);//sharesstrings�̓ǂݍ���
		decsheet->dataread(hr->LH->pos, cddata->nonsize);
		hr->freeLH();
	}
	hr->freeheader();//cddata���
	Ctags* Isheet = nullptr;//�A�C�e���V�[�g�f�[�^
	Isheet = new Ctags(decsheet->ReadV, decsheet->readlen, sharray);

	Isheet->sheetread();

	delete decsheet;//�f�R�[�h�f�[�^�폜

	readItem = new shipinfo(Isheet->rows);//�V�[�g�f�[�^�Q�Ɓ@free�Ȃ�
	readItem->GetItems();//malloc�Ȃ��@�V�[�g�ƃZ�b�g

	delete sharray;	
	delete Isheet;
	delete hr;

	inf.close();

	return (char*)stepone;//sg->its;//get item list
}
