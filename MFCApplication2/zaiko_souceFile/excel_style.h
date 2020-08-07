#pragma once
#include "typechange.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "ChangeArrayNumber.h"

struct Fonts {
	UINT8* biu;//Bold等？
	UINT8* sz;
	UINT8* color;
	UINT8* name;
	UINT8* family;
	UINT8* charset;
	UINT8* scheme;
	UINT8* indexed;
	UINT8* rgb;
	Fonts* next;
};

/*fill内容--------------*/
struct FillPattern
{
	UINT8* patternType;
};

struct fgcolor
{
	UINT8* theme;
	UINT8* tint;
	UINT8* rgb;
};

struct bgcolor
{
	UINT8* indexed;
};

struct Fills
{
	FillPattern* patten;
	fgcolor* fg;
	bgcolor* bg;
	Fills* next;
};

/*-----------------------*/
//ボーダー内容

struct borderstyle
{
	UINT8* style;
	UINT8* theme;
	UINT8* tint;
	UINT8* rgb;
	UINT8* index;
	UINT8* Auto;
};

struct borders
{
	UINT8* diagonalUp;
	UINT8* diagonalDown;
	borderstyle* left;
	borderstyle* right;
	borderstyle* top;
	borderstyle* bottom;
	borderstyle* diagonal;
	borders* next;
};

//cellStyleXfs 内容
struct stylexf
{
	UINT8* numFmtId;
	UINT8* fontId;
	UINT8* fillId;
	UINT8* borderId;
	UINT8* applyNumberFormat;
	UINT8* applyFont;
	UINT8* applyFill;
	UINT8* applyBorder;
	UINT8* applyAlignment;
	UINT8* applyProtection;
	UINT8* Avertical;
	UINT8* wraptext;

	stylexf* next;
};

struct cellxfs
{
	UINT8* numFmtId;
	UINT8* fontId;
	UINT8* fillId;
	UINT8* borderId;
	UINT8* xfId;
	UINT8* applyNumberFormat;
	UINT8* applyFont;
	UINT8* applyFill;
	UINT8* applyBorder;
	UINT8* applyAlignment;
	UINT8* Avertical;
	UINT8* AwrapText;
	UINT8* horizontal;
	UINT8* quotePrefix;
	cellxfs* next;
};

struct cellstyle
{
	UINT8* name;
	UINT8* xfId;
	UINT8* builtinId;
	UINT8* customBuilt;
	UINT8* xruid;
	cellstyle* next;
};

struct dxfFont
{
	UINT8* b;
	UINT8* ival;
	UINT8* theme;
	UINT8* rgb;
};

struct dxfFill
{
	UINT8* rgb;
};

struct Dxf {
	dxfFont* fon;
	dxfFill* fil;
	Dxf* next;
};

struct colors
{
	UINT8* color;
	colors* next;
};

struct numFMts
{
	UINT8* Id;
	UINT8* Code;
	numFMts* next;
};

class styleread {
public:
	const char* fonts;
	const char* Efonts;
	const char* fills;
	const char* endfil;
	const char* border;
	const char* enbor;
	const char* cellstXfs;
	const char* EncsXfs;
	const char* color;
	const char* Ecolor;
	const char* Xfs;
	const char* Exfs;
	const char* CellStyl;
	const char* Ecellsty;
	const char* dxf;
	const char* Edxf;
	const char* Endstyle;
	const char* Fmts;
	const char* Efmts;

	//書き込み用
	const char* countstr = " count=\"";
	ArrayNumber strchange;
	const char* styleSheet;
	const char* extLst = "<extLst>";
	int fontcou;
	size_t strl = 0;//文字列長さ用
	UINT64 readp;
	Fonts** fontRoot;
	Fills** fillroot;
	borders** BorderRoot;
	stylexf** cellstyleXfsRoot;
	cellxfs** cellXfsRoot;
	numFMts** numFmtsRoot;
	cellstyle** cellStyleRoot;
	Dxf** dxfRoot;
	colors* colorsRoot;

	UINT8* fontCount;
	UINT32 fontNum = 0;//フォントカウント数値変換
	UINT32 frcount = 0;
	UINT8* kFonts;
	UINT8* fillCount;
	UINT32 fillNum = 0;//フィルカウント数値変換
	UINT32 ficount = 0;
	UINT8* borderCount;
	UINT32 borderNum = 0;//ボーダーカウント数値変換
	UINT32 bocount = 0;

	UINT8* cellStyleXfsCount;
	UINT32 cellstyleXfsNum = 0;
	UINT32 csXcount = 0;

	UINT8* cellXfsCount;
	UINT32 cellXfsNum = 0;
	UINT32 cXcount = 0;

	UINT8* numFmtsCount;
	UINT32 numFmtsNum = 0;
	UINT32 nucount = 0;

	UINT8* cellstyleCount;
	UINT32 cellstyleNum = 0;
	UINT32 cscount = 0;

	UINT8* dxfsCount;
	UINT32 dxfsNm = 0;
	UINT32 dxcount = 0;

	UINT8* tablestyle;
	UINT8* styleSheetStr;
	UINT8* extLstStr;

	size_t testfontcou = 0;
	size_t testfillcou = 0;

	styleread();
	~styleread();

	void freefonts(Fonts* f);

	void freefill(Fills* f);

	void freeborder(borders* f);

	void freestylexf(stylexf* f);

	void freecellxfs(cellxfs* f);

	void freenumFMts(numFMts* f);

	void freecellstyle(cellstyle* f);

	void freeDxf(Dxf* f);

	Fonts* addfonts(Fonts* f, UINT8* b, UINT8* sz, UINT8* co, UINT8* na, UINT8* fa, UINT8* cha, UINT8* sch, UINT8* rg, UINT8* ind);

	Fills* addfill(Fills* fi, FillPattern* p, fgcolor* f, bgcolor* b);

	borders* addborder(borders* b, borderstyle* l, borderstyle* r, borderstyle* t, borderstyle* bo, borderstyle* d);

	stylexf* addstylexf(stylexf* sx, UINT8* n, UINT8* fo, UINT8* fi, UINT8* bi, UINT8* an, UINT8* ab, UINT8* aa, UINT8* ap, UINT8* av, UINT8* af, UINT8* afil);

	cellxfs* addcellxfs(cellxfs* c, UINT8* n, UINT8* fo, UINT8* fi, UINT8* bi, UINT8* an, UINT8* ab, UINT8* aa, UINT8* av, UINT8* at, UINT8* ho, UINT8* afo, UINT8* afi, UINT8* xid);

	cellstyle* addcellstyle(cellstyle* c, UINT8* n, UINT8* x, UINT8* b, UINT8* cu, UINT8* xr);

	Dxf* adddxf(Dxf* d, dxfFont* Fo, dxfFill* Fi);

	colors* addcolor(colors* c, UINT8* co);

	numFMts* addnumFmts(numFMts* n, UINT8* i, UINT8* c);

	void readfontV(UINT8* dat);

	UINT8* readfonts(UINT8* sd);

	void getfillV(UINT8* d);

	UINT8* readfill(UINT8* sd);

	fgcolor* readfillFg(UINT8* dat);

	bgcolor* readbgcolor(UINT8* dat);

	borderstyle* getborV(UINT8* dat, UINT8* endT, size_t endTlen);

	void getBorder(UINT8* d);

	UINT8* readboerder(UINT8* d);

	UINT8* getValue(UINT8* d);

	void getCellStyleXfsV(UINT8* d);

	void getCellXfsV(UINT8* d);

	void readCellStyleXfs(UINT8* d);

	void readCellXfs(UINT8* d);

	void getnumFmts(UINT8* dat);

	void readnumFmt(UINT8* d);

	void getcellStyle(UINT8* d);

	void readcellStyles(UINT8* d);

	dxfFont* readdxffont(UINT8* d);

	dxfFill* readdxffill(UINT8* d);

	void getdxfs(UINT8* d);

	void readdxfs(UINT8* d);

	void getcolor(UINT8* d);

	void readcolors(UINT8* d);

	void readextLst(UINT8* d);

	void readstyle(UINT8* sdata, UINT64 sdatalen);

};

class StyleWrite :public styleread
{
public:

	UINT8* wd;
	UINT64 wdlen;

	StyleWrite() {
		wd = nullptr;
		wdlen = 0;
	};
	~StyleWrite() {
		free(wd);
	};

	void styledatawrite(UINT64 dlen);

	void tablestylewrite();

	void Dxfswrite();

	void writeColors();

	void writefirst();

	void writeextLst();

	void CELLStyle();

	void cellXfswrite();

	void fontswrite();

	void fillwrite();

	void borderwrite();

	void cellstyleXfs();

	void numFmidwrite();

	void oneStrplusDoubleq(UINT8* str, UINT8* v);

	void oneStrwrite(UINT8* str);

	void writedata(UINT8* stag, UINT8* v, UINT8* etag);

private:

};

inline void StyleWrite::styledatawrite(UINT64 dlen) {

	size_t msi = (size_t)dlen + 5000;

	wd = (UINT8*)malloc(msi);

	writefirst();

	numFmidwrite();

	fontswrite();

	fillwrite();

	borderwrite();

	cellstyleXfs();

	cellXfswrite();

	CELLStyle();

	Dxfswrite();

	tablestylewrite();

	writeColors();

	writeextLst();

	oneStrwrite((UINT8*)Endstyle);

}

inline void StyleWrite::tablestylewrite() {
	oneStrwrite(tablestyle);
}

//write dxfs
inline void StyleWrite::Dxfswrite()
{
	UINT8 et[] = "/>";
	UINT8 e[] = ">";
	UINT8 stag[] = "<dxf>";
	UINT8 etag[] = "</dxf>";

	UINT8 fstag[] = "<font>";
	UINT8 fetag[] = "</font>";

	UINT8 col[] = "<color";
	UINT8 rgb[] = " rgb=\"";
	UINT8 them[] = " theme=\"";

	UINT8 sfil[] = "<fill>";
	UINT8 efil[] = "</fill>";

	UINT8 spat[] = "<patternFill>";
	UINT8 epat[] = "</patternFill>";
	UINT8 bgc[] = "<bgColor";
	UINT8 istr[] = "<i";

	UINT8 val[] = " val=\"";
	//theme="
	//<b/><i/>
	Dxf** dx = dxfRoot;
	size_t cou = 0;

	oneStrwrite((UINT8*)dxf);
	oneStrplusDoubleq((UINT8*)countstr, dxfsCount);
	oneStrwrite(e);

	while (cou < dxfsNm) {
		oneStrwrite(stag);

		if (dx[cou]->fon) {
			oneStrwrite(fstag);

			if (dx[cou]->fon->b)
				oneStrwrite(dx[cou]->fon->b);

			if (dx[cou]->fon->ival) {
				oneStrwrite(istr);
				oneStrplusDoubleq(val, dx[cou]->fon->ival);
				oneStrwrite(et);
			}
			if (dx[cou]->fon->theme || dx[cou]->fon->rgb) {
				oneStrwrite(col);
				if (dx[cou]->fon->rgb)
					oneStrplusDoubleq(rgb, dx[cou]->fon->rgb);
				if (dx[cou]->fon->theme)
					oneStrplusDoubleq(them, dx[cou]->fon->theme);
				oneStrwrite(et);
			}
			oneStrwrite(fetag);
		}

		if (dx[cou]->fil) {
			oneStrwrite(sfil);

			if (dx[cou]->fil->rgb) {
				oneStrwrite(spat);

				oneStrwrite(bgc);

				oneStrplusDoubleq(rgb, dx[cou]->fil->rgb);

				oneStrwrite(et);

				oneStrwrite(epat);
			}
			oneStrwrite(efil);
		}
		oneStrwrite(etag);
		cou++;
	}
	std::cout << "write dxfs count : " << cou << " , " << dxfsNm << std::endl;
	oneStrwrite((UINT8*)Edxf);
}

//write colors
inline void StyleWrite::writeColors()
{
	UINT8 et[] = "/>";
	UINT8 e[] = ">";

	UINT8 stag[] = "<mruColors>";
	UINT8 etag[] = "</mruColors>";

	UINT8 col[] = "<color";

	UINT8 rgb[] = " rgb=\"";

	colors* c = colorsRoot;

	if (c) {
		oneStrwrite((UINT8*)color);
		oneStrwrite(stag);

		while (c) {
			oneStrwrite(col);
			oneStrplusDoubleq(rgb, c->color);
			oneStrwrite(et);
			c = c->next;
		}

		oneStrwrite(etag);

		oneStrwrite((UINT8*)Ecolor);
	}
}

//write 最初の文字列
inline void StyleWrite::writefirst() {

	//UINT8 e[] = ">";
	oneStrwrite(styleSheetStr);
	//oneStrwrite(e);
}

//write extLst
inline void StyleWrite::writeextLst() {

	UINT8 stag[] = "<extLst>";

	oneStrwrite(stag);

	oneStrwrite(extLstStr);

}

//write cellstyle
inline void StyleWrite::CELLStyle()
{
	UINT8 et[] = "/>";
	UINT8 e[] = ">";
	UINT8 stag[] = "<cellStyle";
	UINT8 nam[] = " name=\"";
	UINT8 xfid[] = " xfId=\"";
	UINT8 xruid[] = " xr:uid=\"";
	UINT8 bui[] = " builtinId=\"";
	UINT8 cb[] = " customBuiltin=\"";
	cellstyle** cs = cellStyleRoot;

	size_t cou = 0;

	oneStrwrite((UINT8*)CellStyl);

	oneStrplusDoubleq((UINT8*)countstr, cellstyleCount);

	oneStrwrite(e);


	while (cou < cellstyleNum) {

		oneStrwrite(stag);

		if (cs[cou]->name)
			oneStrplusDoubleq(nam, cs[cou]->name);

		if (cs[cou]->xfId)
			oneStrplusDoubleq(xfid, cs[cou]->xfId);

		if (cs[cou]->xruid)
			oneStrplusDoubleq(xruid, cs[cou]->xruid);

		if (cs[cou]->builtinId)
			oneStrplusDoubleq(bui, cs[cou]->builtinId);

		if (cs[cou]->customBuilt)
			oneStrplusDoubleq(cb, cs[cou]->customBuilt);

		oneStrwrite(et);// />タグ

		cou++;

	}
	std::cout << "write cellstyle count : " << cou << " , " << cellstyleNum << std::endl;
	oneStrwrite((UINT8*)Ecellsty);
}

//write cellXfs

inline void StyleWrite::cellXfswrite()
{

	UINT8 et[] = "/>";
	UINT8 e[] = ">";

	UINT8 stag[] = "<xf";
	UINT8 etag[] = "</xf>";

	UINT8 num[] = " numFmtId=\"";
	UINT8 fon[] = " fontId=\"";
	UINT8 fil[] = " fillId=\"";
	UINT8 bor[] = " borderId=\"";
	UINT8 an[] = " applyNumberFormat=\"";
	UINT8 ab[] = " applyBorder=\"";
	UINT8 aa[] = " applyAlignment=\"";
	UINT8 ap[] = " applyProtection=\"";
	UINT8 af[] = " applyFill=\"";
	UINT8 align[] = "<alignment";
	UINT8 ver[] = " vertical=\"";
	UINT8 afo[] = " applyFont=\"";
	UINT8 hor[] = " horizontal=\"";
	UINT8 wt[] = " wrapText=\"";
	UINT8 xi[] = " xfId=\"";
	UINT8 qp[] = " quotePrefix=\"";

	cellxfs** cx = cellXfsRoot;
	size_t cou = 0;

	oneStrwrite((UINT8*)Xfs);
	oneStrplusDoubleq((UINT8*)countstr, cellXfsCount);
	oneStrwrite(e);

	while (cou < cellXfsNum) {
		oneStrwrite(stag);

		if (cx[cou]->numFmtId)
			oneStrplusDoubleq(num, cx[cou]->numFmtId);

		if (cx[cou]->fontId)
			oneStrplusDoubleq(fon, cx[cou]->fontId);

		if (cx[cou]->fillId)
			oneStrplusDoubleq(fil, cx[cou]->fillId);

		if (cx[cou]->borderId)
			oneStrplusDoubleq(bor, cx[cou]->borderId);

		if (cx[cou]->applyNumberFormat)
			oneStrplusDoubleq(an, cx[cou]->applyNumberFormat);

		if (cx[cou]->quotePrefix)
			oneStrplusDoubleq(qp, cx[cou]->quotePrefix);

		if (cx[cou]->applyFont)
			oneStrplusDoubleq(afo, cx[cou]->applyFont);

		if (cx[cou]->applyFill)
			oneStrplusDoubleq(af, cx[cou]->applyFill);

		if (cx[cou]->applyBorder)
			oneStrplusDoubleq(ab, cx[cou]->applyBorder);

		if (cx[cou]->applyAlignment)
			oneStrplusDoubleq(aa, cx[cou]->applyAlignment);

		if (cx[cou]->xfId)
			oneStrplusDoubleq(xi, cx[cou]->xfId);

		if (cx[cou]->Avertical || cx[cou]->horizontal || cx[cou]->AwrapText) {
			oneStrwrite(e);// >タグ

			oneStrwrite(align);

			if (cx[cou]->Avertical)
				oneStrplusDoubleq(ver, cx[cou]->Avertical);

			if (cx[cou]->horizontal)
				oneStrplusDoubleq(hor, cx[cou]->horizontal);

			if (cx[cou]->AwrapText)
				oneStrplusDoubleq(wt, cx[cou]->AwrapText);

			oneStrwrite(et);

			oneStrwrite(etag);//align あり　終了タグ追加

		}
		else {
			oneStrwrite(et);// />タグ
		}
		cou++;
	}
	std::cout << "write cellxfs count : " << cou << " , " << cellXfsCount << std::endl;
	oneStrwrite((UINT8*)Exfs);
}

//フォント書き込み
inline void StyleWrite::fontswrite()
{
	UINT8 stag[] = "<font>";
	UINT8 etag[] = "</font>";
	UINT8 sztag[] = "<sz";
	UINT8 coltag[] = "<color";
	UINT8 namtag[] = "<name";
	UINT8 famtag[] = "<family";
	UINT8 chatag[] = "<charset";
	UINT8 schtag[] = "<scheme";

	UINT8 valtag[] = " val=\"";

	UINT8 thetag[] = " theme=\"";

	UINT8 rgbtag[] = " rgb=\"";

	UINT8 indextag[] = " indexed=\"";

	UINT8 kf[] = " x14ac:knownFonts=\"";
	UINT8 closetag[] = ">";
	UINT8 et[] = "/>";

	Fonts** f = fontRoot;

	size_t cou = 0;

	oneStrwrite((UINT8*)fonts);
	oneStrplusDoubleq((UINT8*)countstr, fontCount);

	if (kFonts)
		oneStrplusDoubleq(kf, kFonts);

	oneStrwrite(closetag);

	while (cou < frcount)
	{
		oneStrwrite(stag);
		// <b/> <i/>

		if (f[cou]->biu) {
			oneStrwrite(f[cou]->biu);
		}

		if (f[cou]->sz) {
			oneStrwrite(sztag);

			oneStrplusDoubleq(valtag, f[cou]->sz);

			oneStrwrite(et);

		}

		if (f[cou]->color) {

			oneStrwrite(coltag);

			oneStrplusDoubleq(thetag, f[cou]->color);

			oneStrwrite(et);

		}

		if (f[cou]->rgb) {

			oneStrwrite(coltag);

			oneStrplusDoubleq(rgbtag, f[cou]->rgb);

			oneStrwrite(et);

		}

		if (f[cou]->indexed) {

			oneStrwrite(coltag);

			oneStrplusDoubleq(indextag, f[cou]->indexed);

			oneStrwrite(et);

		}

		if (f[cou]->name) {

			oneStrwrite(namtag);

			oneStrplusDoubleq(valtag, f[cou]->name);

			oneStrwrite(et);

		}

		if (f[cou]->charset) {

			oneStrwrite(chatag);

			oneStrplusDoubleq(valtag, f[cou]->charset);

			oneStrwrite(et);

		}

		if (f[cou]->family) {
			oneStrwrite(famtag);
			oneStrplusDoubleq(valtag, f[cou]->family);
			oneStrwrite(et);
		}

		if (f[cou]->scheme) {
			oneStrwrite(schtag);
			oneStrplusDoubleq(valtag, f[cou]->scheme);
			oneStrwrite(et);
		}
		oneStrwrite(etag);

		cou++;

	}
	std::cout << "write font count : " << cou << " , " << fontCount << std::endl;
	oneStrwrite((UINT8*)Efonts);
}

inline void StyleWrite::fillwrite()
{

	UINT8 cou[] = " count=\"";

	UINT8 et[] = "/>";
	UINT8 e[] = ">";

	UINT8 sz[] = "<sz";
	UINT8 col[] = "<color";
	UINT8 na[] = "<name";
	UINT8 fa[] = "<family";

	UINT8 stag[] = "<fill>";
	UINT8 etag[] = "</fill>";

	UINT8 pat[] = "<patternFill";
	UINT8 epat[] = "</patternFill>";
	UINT8 patT[] = " patternType=\"";

	UINT8 fg[] = "<fgColor";
	UINT8 rgb[] = " rgb=\"";
	UINT8 bg[] = "<bgColor";
	UINT8 theme[] = " theme=\"";
	UINT8 tint[] = " tint=\"";
	UINT8 ind[] = " indexed=\"";

	oneStrwrite((UINT8*)fills);
	oneStrplusDoubleq(cou, fillCount);
	oneStrwrite(e);

	Fills** fi = fillroot;
	size_t nu = 0;

	while (nu < fillNum)
	{
		oneStrwrite(stag);

		if (fi[nu]->patten) {
			oneStrwrite(pat);
			oneStrplusDoubleq(patT, fi[nu]->patten->patternType);
		}

		if (!fi[nu]->fg && !fi[nu]->bg) {
			oneStrwrite(et);
		}

		else {
			oneStrwrite(e);
		}

		if (fi[nu]->fg) {
			oneStrwrite(fg);
			if (fi[nu]->fg->rgb)
				oneStrplusDoubleq(rgb, fi[nu]->fg->rgb);

			if (fi[nu]->fg->theme)
				oneStrplusDoubleq(theme, fi[nu]->fg->theme);

			if (fi[nu]->fg->tint)
				oneStrplusDoubleq(tint, fi[nu]->fg->tint);

			oneStrwrite(et);
		}

		if (fi[nu]->bg) {
			oneStrwrite(bg);
			if (fi[nu]->bg->indexed)
				oneStrplusDoubleq(ind, fi[nu]->bg->indexed);
			oneStrwrite(et);
		}

		if (fi[nu]->fg || fi[nu]->bg) {
			oneStrwrite(epat);
		}
		oneStrwrite(etag);

		nu++;
	}
	std::cout << "write fill count : " << nu << " , " << fillCount << std::endl;

	oneStrwrite((UINT8*)endfil);
}

inline void StyleWrite::borderwrite()
{
	borders** bor = BorderRoot;

	UINT8 stag[] = "<border";
	UINT8 etag[] = "</border>";

	UINT8 l[] = "<left";
	UINT8 r[] = "<right";
	UINT8 t[] = "<top";
	UINT8 b[] = "<bottom";
	UINT8 d[] = "<diagonal";

	UINT8 el[] = "</left>";
	UINT8 er[] = "</right>";
	UINT8 eto[] = "</top>";
	UINT8 eb[] = "</bottom>";
	UINT8 ed[] = "</diagonal>";

	UINT8 au[] = " auto=\"";
	UINT8 sty[] = " style=\"";
	UINT8 colo[] = "<color";
	UINT8 ind[] = " indexed=\"";
	UINT8 tin[] = " tint=\"";
	UINT8 rg[] = " rgb=\"";
	UINT8 them[] = " theme=\"";

	UINT8 et[] = "/>";
	UINT8 e[] = ">";

	UINT8 digu[] = " diagonalUp=\"";
	UINT8 digd[] = " diagonalDown=\"";
	UINT8 dq[] = "\"";

	oneStrwrite((UINT8*)border);
	oneStrplusDoubleq((UINT8*)countstr, borderCount);
	oneStrwrite(e);

	size_t co = 0;
	std::cout << "border read count" << bocount << std::endl;
	while (co < borderNum)
	{
		oneStrwrite(stag);

		if (bor[co]->diagonalUp)
			oneStrplusDoubleq(digu, bor[co]->diagonalUp);

		if (bor[co]->diagonalDown)
			oneStrplusDoubleq(digd, bor[co]->diagonalDown);

		oneStrwrite(e);

		if (bor[co]->left) {
			oneStrwrite(l);

			if (bor[co]->left->style) {
				oneStrplusDoubleq(sty, bor[co]->left->style);
				oneStrwrite(e);// >タグ
			}

			if (bor[co]->left->Auto || bor[co]->left->index || bor[co]->left->rgb || bor[co]->left->theme || bor[co]->left->tint)
				oneStrwrite(colo);

			if (bor[co]->left->Auto)
				oneStrplusDoubleq(au, bor[co]->left->Auto);

			if (bor[co]->left->index)
				oneStrplusDoubleq(ind, bor[co]->left->index);

			if (bor[co]->left->rgb)
				oneStrplusDoubleq(rg, bor[co]->left->rgb);

			if (bor[co]->left->theme)
				oneStrplusDoubleq(them, bor[co]->left->theme);

			if (bor[co]->left->tint)
				oneStrplusDoubleq(tin, bor[co]->left->tint);

			oneStrwrite(et);
			oneStrwrite(el);
		}
		else {
			oneStrwrite(l);
			oneStrwrite(et);
		}

		if (bor[co]->right) {
			oneStrwrite(r);
			if (bor[co]->right->style) {
				oneStrplusDoubleq(sty, bor[co]->right->style);
				oneStrwrite(e);// >タグ
			}

			if (bor[co]->right->Auto || bor[co]->right->index || bor[co]->right->rgb || bor[co]->right->theme || bor[co]->right->tint)
				oneStrwrite(colo);

			if (bor[co]->right->Auto)
				oneStrplusDoubleq(au, bor[co]->right->Auto);

			if (bor[co]->right->index)
				oneStrplusDoubleq(ind, bor[co]->right->index);

			if (bor[co]->right->rgb)
				oneStrplusDoubleq(rg, bor[co]->right->rgb);

			if (bor[co]->right->theme)
				oneStrplusDoubleq(them, bor[co]->right->theme);

			if (bor[co]->right->tint)
				oneStrplusDoubleq(tin, bor[co]->right->tint);

			oneStrwrite(et);
			oneStrwrite(er);
		}
		else {
			oneStrwrite(r);
			oneStrwrite(et);
		}

		if (bor[co]->top) {
			oneStrwrite(t);

			if (bor[co]->top->style) {
				oneStrplusDoubleq(sty, bor[co]->top->style);
				oneStrwrite(e);// >タグ
			}

			if (bor[co]->top->Auto || bor[co]->top->index || bor[co]->top->rgb || bor[co]->top->theme || bor[co]->top->tint)
				oneStrwrite(colo);

			if (bor[co]->top->Auto)
				oneStrplusDoubleq(au, bor[co]->top->Auto);

			if (bor[co]->top->index)
				oneStrplusDoubleq(ind, bor[co]->top->index);

			if (bor[co]->top->rgb)
				oneStrplusDoubleq(rg, bor[co]->top->rgb);

			if (bor[co]->top->theme)
				oneStrplusDoubleq(them, bor[co]->top->theme);

			if (bor[co]->top->tint)
				oneStrplusDoubleq(tin, bor[co]->top->tint);

			oneStrwrite(et);
			oneStrwrite(eto);
		}
		else {
			oneStrwrite(t);
			oneStrwrite(et);
		}

		if (bor[co]->bottom) {
			oneStrwrite(b);
			if (bor[co]->bottom->style) {
				oneStrplusDoubleq(sty, bor[co]->bottom->style);
				oneStrwrite(e);// >タグ
			}
			if (bor[co]->bottom->Auto || bor[co]->bottom->index || bor[co]->bottom->rgb || bor[co]->bottom->theme || bor[co]->bottom->tint)
				oneStrwrite(colo);

			if (bor[co]->bottom->Auto)
				oneStrplusDoubleq(au, bor[co]->bottom->Auto);

			if (bor[co]->bottom->index)
				oneStrplusDoubleq(ind, bor[co]->bottom->index);

			if (bor[co]->bottom->rgb)
				oneStrplusDoubleq(rg, bor[co]->bottom->rgb);

			if (bor[co]->bottom->theme)
				oneStrplusDoubleq(them, bor[co]->bottom->theme);

			if (bor[co]->bottom->tint)
				oneStrplusDoubleq(tin, bor[co]->bottom->tint);

			oneStrwrite(et);
			oneStrwrite(eb);
		}
		else {
			oneStrwrite(b);
			oneStrwrite(et);
		}

		if (bor[co]->diagonal) {
			oneStrwrite(d);
			if (bor[co]->diagonal->style) {
				oneStrplusDoubleq(sty, bor[co]->diagonal->style);
				oneStrwrite(e);// >タグ
			}
			if (bor[co]->diagonal->Auto || bor[co]->diagonal->index || bor[co]->diagonal->rgb || bor[co]->diagonal->theme || bor[co]->diagonal->tint)
				oneStrwrite(colo);

			if (bor[co]->diagonal->Auto)
				oneStrplusDoubleq(au, bor[co]->diagonal->Auto);

			if (bor[co]->diagonal->index)
				oneStrplusDoubleq(ind, bor[co]->diagonal->index);

			if (bor[co]->diagonal->rgb)
				oneStrplusDoubleq(rg, bor[co]->diagonal->rgb);

			if (bor[co]->diagonal->theme)
				oneStrplusDoubleq(them, bor[co]->diagonal->theme);

			if (bor[co]->diagonal->tint)
				oneStrplusDoubleq(tin, bor[co]->diagonal->tint);

			oneStrwrite(et);
			oneStrwrite(ed);
		}
		else {
			oneStrwrite(d);
			oneStrwrite(et);
		}

		oneStrwrite(etag);
		co++;
	}
	std::cout << "write border count : " << co << " , " << borderCount << std::endl;
	oneStrwrite((UINT8*)enbor);
}

inline void StyleWrite::cellstyleXfs()
{
	UINT8 et[] = "/>";
	UINT8 e[] = ">";
	UINT8 stag[] = "<xf";
	UINT8 etag[] = "</xf>";

	UINT8 num[] = " numFmtId=\"";
	UINT8 fon[] = " fontId=\"";
	UINT8 fil[] = " fillId=\"";
	UINT8 bor[] = " borderId=\"";
	UINT8 an[] = " applyNumberFormat=\"";
	UINT8 ab[] = " applyBorder=\"";
	UINT8 aa[] = " applyAlignment=\"";
	UINT8 ap[] = " applyProtection=\"";
	UINT8 af[] = " applyFill=\"";
	UINT8 align[] = "<alignment";
	UINT8 ver[] = " vertical=\"";
	UINT8 afo[] = " applyFont=\"";
	UINT8 wtx[] = " wrapText=\"";

	stylexf** csx = cellstyleXfsRoot;
	size_t co = 0;

	oneStrwrite((UINT8*)cellstXfs);
	oneStrplusDoubleq((UINT8*)countstr, cellStyleXfsCount);

	oneStrwrite(e);

	while (co < cellstyleXfsNum)
	{
		oneStrwrite(stag);

		if (csx[co]->numFmtId)
			oneStrplusDoubleq(num, csx[co]->numFmtId);

		if (csx[co]->fontId)
			oneStrplusDoubleq(fon, csx[co]->fontId);

		if (csx[co]->fillId)
			oneStrplusDoubleq(fil, csx[co]->fillId);

		if (csx[co]->borderId)
			oneStrplusDoubleq(bor, csx[co]->borderId);

		if (csx[co]->applyNumberFormat)
			oneStrplusDoubleq(an, csx[co]->applyNumberFormat);

		if (csx[co]->applyFont)
			oneStrplusDoubleq(afo, csx[co]->applyFont);

		if (csx[co]->applyFill)
			oneStrplusDoubleq(af, csx[co]->applyFill);

		if (csx[co]->applyBorder)
			oneStrplusDoubleq(ab, csx[co]->applyBorder);

		if (csx[co]->applyAlignment)
			oneStrplusDoubleq(aa, csx[co]->applyAlignment);

		if (csx[co]->applyProtection)
			oneStrplusDoubleq(ap, csx[co]->applyProtection);

		if (csx[co]->wraptext || csx[co]->Avertical) {
			// <alignment  >タグの中
			oneStrwrite(e);// >タグ
			oneStrwrite(align);
			if (csx[co]->Avertical)
				oneStrplusDoubleq(ver, csx[co]->Avertical);
			if (csx[co]->wraptext)
				oneStrplusDoubleq(wtx, csx[co]->wraptext);
			oneStrwrite(et);
			oneStrwrite(etag);// alignment　あり　</xf>追加
		}
		else {
			oneStrwrite(et);// alignment なし />タグ 
		}
		co++;
	}
	std::cout << "write cellstylexfs count : " << co << " , " << cellstyleXfsNum << std::endl;
	oneStrwrite((UINT8*)EncsXfs);
}

//numFmt 書き込み
inline void StyleWrite::numFmidwrite()
{
	UINT8 st[] = "<numFmt";
	UINT8 id[] = " numFmtId=\"";
	UINT8 code[] = " formatCode=\"";
	UINT8 cou[] = " count=\"";
	UINT8 et[] = "/>";
	UINT8 e[] = ">";

	oneStrwrite((UINT8*)Fmts);
	oneStrplusDoubleq(cou, numFmtsCount);
	oneStrwrite((UINT8*)e);

	numFMts** n = numFmtsRoot;
	size_t co = 0;

	while (co < numFmtsNum) {
		oneStrwrite(st);
		if (n[co]->Id) {
			std::cout << "numfmts id" << n[co]->Id << std::endl;
			oneStrplusDoubleq(id, n[co]->Id);
		}

		if (n[co]->Code)
			oneStrplusDoubleq(code, n[co]->Code);

		oneStrwrite(et);

		co++;
	}
	std::cout << "write numfmts count : " << co << " , " << numFmtsNum << std::endl;
	oneStrwrite((UINT8*)Efmts);
}

//xx="~" 書き込み
inline void StyleWrite::oneStrplusDoubleq(UINT8* str, UINT8* v) {

	int i = 0;
	UINT8 d = '"';

	while (str[i] != '\0') {
		wd[wdlen] = str[i];
		i++;
		wdlen++;
	}
	i = 0;

	while (v[i] != '\0') {
		wd[wdlen] = v[i];
		i++; wdlen++;
	}

	wd[wdlen] = d;
	wdlen++;
}

//tag書き込み
inline void StyleWrite::oneStrwrite(UINT8* str) {

	int i = 0;

	while (str[i] != '\0') {
		wd[wdlen] = str[i];
		i++;
		wdlen++;
	}
}

inline void StyleWrite::writedata(UINT8* stag, UINT8* v, UINT8* etag)
{
	int i = 0;

	while (stag[i] != '\0') {
		wd[wdlen] = stag[i];
		i++;
		wdlen++;
	}
	i = 0;

	while (v[i] != '\0') {
		wd[wdlen] = v[i];
		i++;
		wdlen++;
	}
	i = 0;

	while (etag[i] != '\0') {
		wd[wdlen] = etag[i];
		i++;
		wdlen++;
	}

}


class checkstyle :public StyleWrite
{
public:
	UINT8* style = nullptr;//s 決定
	size_t stylelen = 0;

	int searchfonts(Fonts* fs);
	int searchcellstylexfs(stylexf* fs);
	int searchcellxfs(cellxfs* fs);
	int searchcellstyle(cellstyle* fs);
	int searchfills(Fills* fs);
	bool searchborderstyle(borderstyle* f, borderstyle* fs);
	int searchborders(borders* fs);
	void CountincIiment(UINT8* cstr);
	UINT8* searchnumFmts(numFMts* fs);
	int strcompare(UINT8* sl, UINT8* sr);
	int configstyle(Fonts* fo, Fills* fi, borders* bd, stylexf* csx, cellxfs* cx, numFMts* nf);
	//char* SJIStoUTF8(char* szSJIS, char* bufUTF8, int size);

private:
	const char* zo = "zozo";
	const char* sm = "smarby";
	const char* sh = "shoplist";
	const char* be = "bee";
	const char* ms = "magaseek";
};

inline int checkstyle::searchfonts(Fonts* fs) {
	Fonts** f = fontRoot;
	int result = 0;
	UINT32 count = 0;
	bool flag = false;

	//std::cout << "fs theme : " << fs->color << std::endl;
	while (count < frcount) {
		result = strcompare(f[count]->sz, fs->sz);
		if (result == 0) {
			result = strcompare(f[count]->rgb, fs->rgb);
			if (result == 0) {
				result = strcompare(f[count]->charset, fs->charset);
				if (result == 0) {
					result = strcompare(f[count]->scheme, fs->scheme);
					if (result == 0) {
						result = strcompare(f[count]->color, fs->color);
						if (result == 0) {
							result = strcompare(f[count]->name, fs->name);
							if (result == 0) {
								result = strcompare(f[count]->family, fs->family);
								if (result == 0) {
									flag = true;
									return count;
								}
							}
						}
					}
				}
			}
		}
		count++;
	}
	return -1;
}

inline int checkstyle::searchcellstylexfs(stylexf* fs)
{
	stylexf** f = cellstyleXfsRoot;
	int result = 0;
	UINT32 count = 0;
	bool flag = false;

	//std::cout << "fs aA : " << fs->fillId << " " << f->fillId << std::endl;
	while (count < csXcount) {
		result = strcompare(f[count]->applyAlignment, fs->applyAlignment);
		if (result == 0) {
			result = strcompare(f[count]->applyBorder, fs->applyBorder);
			if (result == 0) {
				result = strcompare(f[count]->applyFont, fs->applyFont);
				if (result == 0) {
					result = strcompare(f[count]->applyNumberFormat, fs->applyNumberFormat);
					if (result == 0) {
						result = strcompare(f[count]->applyProtection, fs->applyProtection);
						if (result == 0) {
							result = strcompare(f[count]->Avertical, fs->Avertical);
							if (result == 0) {
								result = strcompare(f[count]->borderId, fs->borderId);
								if (result == 0) {
									result = strcompare(f[count]->fillId, fs->fillId);
									if (result == 0) {
										result = strcompare(f[count]->fontId, fs->fontId);
										if (result == 0) {
											result = strcompare(f[count]->numFmtId, fs->numFmtId);
											if (result == 0) {
												flag = true;
												return count;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		count++;
	}

	return -1;
}

inline int checkstyle::searchcellxfs(cellxfs* fs)
{
	cellxfs** f = cellXfsRoot;
	int result = 0;
	UINT32 count = 0;

	bool flag = false;

	//std::cout << "fs aA : " << fs->fontId << " " << f->fontId << std::endl;
	while (count < cXcount) {
		result = strcompare(f[count]->applyAlignment, fs->applyAlignment);
		if (result == 0) {
			result = strcompare(f[count]->applyBorder, fs->applyBorder);
			if (result == 0) {
				result = strcompare(f[count]->applyFont, fs->applyFont);
				if (result == 0) {
					result = strcompare(f[count]->applyNumberFormat, fs->applyNumberFormat);
					if (result == 0) {
						result = strcompare(f[count]->applyFill, fs->applyFill);
						if (result == 0) {
							result = strcompare(f[count]->Avertical, fs->Avertical);
							if (result == 0) {
								result = strcompare(f[count]->borderId, fs->borderId);
								if (result == 0) {
									result = strcompare(f[count]->fillId, fs->fillId);
									if (result == 0) {
										result = strcompare(f[count]->fontId, fs->fontId);
										if (result == 0) {
											result = strcompare(f[count]->numFmtId, fs->numFmtId);
											if (result == 0) {
												result = strcompare(f[count]->AwrapText, fs->AwrapText);
												if (result == 0) {
													result = strcompare(f[count]->xfId, fs->xfId);
													if (result == 0) {
														result = strcompare(f[count]->horizontal, fs->horizontal);
														if (result == 0) {
															return count;
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		count++;
	}
	return -1;
}

//cellstyle 検索　xfid戻り
inline int checkstyle::searchcellstyle(cellstyle* fs)
{
	cellstyle** f = cellStyleRoot;
	int result = 0;
	UINT32 count = 0;
	bool flag = false;

	while (count < cscount) {
		
		if (f[count]->name) {
			result = strcompare(f[count]->name, fs->name);
			if (result == 0) {
				flag = true;
				return count;
			}
		}
		count++;
	}
	return -1;
}

inline int checkstyle::searchfills(Fills* fs)
{
	Fills** f = fillroot;
	int result = 0;
	UINT32 count = 0;
	bool flag = false;
	bool fgflag = false;
	bool bgflag = false;

	while (count < ficount) {
		if (f[count]->patten && fs->patten) {
			result = strcompare(f[count]->patten->patternType, fs->patten->patternType);
			if (result == 0)
				flag = true;
		}
		else if (!f[count]->patten && !fs->patten) {
			flag = true;
		}
		else {
			flag = false;
		}

		if (f[count]->fg && fs->fg) {
			result = strcompare(f[count]->fg->rgb, fs->fg->rgb);
			if (result == 0) {
				result = strcompare(f[count]->fg->theme, fs->fg->theme);
				if (result == 0) {
					result = strcompare(f[count]->fg->tint, fs->fg->tint);
					if (result == 0)
						fgflag = true;
				}
			}
		}
		else if (!f[count]->fg && !fs->fg)
		{
			fgflag = true;
		}
		else {
			fgflag = false;
		}

		if (f[count]->bg && fs->bg) {
			result = strcompare(f[count]->bg->indexed, fs->bg->indexed);
			if (result == 0) {
				bgflag = true;
			}
		}
		else if (!f[count]->bg && !fs->bg)
		{
			bgflag = true;
		}
		else {
			bgflag = false;
		}

		if (flag && fgflag && bgflag)
			break;

		count++;
	}

	if (!flag || !fgflag || !bgflag) {
		count = -1;
	}

	return count;
}

inline bool checkstyle::searchborderstyle(borderstyle* f, borderstyle* fs) {
	bool flag = false;
	int result = 0;

	if (f && fs) {
		result = strcompare(f->rgb, fs->rgb);
		if (result == 0) {
			result = strcompare(f->Auto, fs->Auto);
			if (result == 0) {
				result = strcompare(f->index, fs->index);
				if (result == 0) {
					result = strcompare(f->style, fs->style);
					if (result == 0) {
						result = strcompare(f->theme, fs->theme);
						if (result == 0) {
							result = strcompare(f->tint, fs->tint);
							if (result == 0) {
								flag = true;
							}
						}
					}
				}
			}
		}
	}
	else if (!f && !fs) {
		flag = true;
	}
	return flag;
}

inline int checkstyle::searchborders(borders* fs)
{
	borders** f = BorderRoot;
	int result = 0;
	UINT32 count = 0;
	bool lflag = false;
	bool rflag = false;
	bool bflag = false;
	bool tflag = false;
	bool dflag = false;

	while (count < bocount) {

		lflag = searchborderstyle(f[count]->left, fs->left);
		rflag = searchborderstyle(f[count]->right, fs->right);
		bflag = searchborderstyle(f[count]->bottom, fs->bottom);
		tflag = searchborderstyle(f[count]->top, fs->top);
		dflag = searchborderstyle(f[count]->diagonal, fs->diagonal);

		if (lflag && rflag && bflag && tflag && dflag)
			break;

		count++;

	}

	if (!lflag || !rflag || !tflag || !bflag || !dflag) {
		count = -1;
	}

	return count;
}

inline void checkstyle::CountincIiment(UINT8* cstr)
{
	int l = 0;
	UINT32 count = 0;
	while (cstr[l] != '\0')
		l++;

	count = strchange.RowArraytoNum(cstr, l);
	count++;
	cstr = strchange.InttoChar(count, &l);
}

inline UINT8* checkstyle::searchnumFmts(numFMts* fs)
{
	//numFMts* f = numFmtsRoot;
	int result = 0;
	UINT32 count = 0;
	bool flag = false;
	UINT8* nu = nullptr;

	//std::cout << "fs sz : " << fs->sz << std::endl;
	while (count < nucount) {
		result = strcompare(numFmtsRoot[count]->Code, fs->Code);
		if (result == 0) {
			flag = true;
			break;
		}
		count++;
	}

	if (!flag) {
		nu = (UINT8*)malloc(1); nu = nullptr;
		return nu;
	}

	size_t leng = strlen((const char*)numFmtsRoot[count]->Id) + 1;
	nu = (UINT8*)malloc(leng);
	memcpy(nu, numFmtsRoot[count]->Id, leng);

	return nu;
}

inline int checkstyle::strcompare(UINT8* sl, UINT8* sr)
{
	int result = 1;

	if (sl && sr)
		result = strcmp((const char*)sl, (const char*)sr);
	else if (!sl && !sr)
		result = 0;
	else
		result = 1;

	return result;
}
//shiftjis変換した文字を入れる
inline int checkstyle::configstyle(Fonts* fo, Fills* fi,borders* bd,stylexf* csx,cellxfs* cx,numFMts* nf)
{
	int fontnumb = 0;//検索番号
	int place = 0;//検索番号　桁数

	//numFmid 検索
	csx->numFmtId = searchnumFmts(nf);//numFmt検索 ID加える

	if (csx->numFmtId) {
		free(nf->Code); free(nf->Id); free(nf);
	}
	else {
		//numFmts 加える
		//フォント設定追加　必要
		size_t resiz = (size_t)numFmtsNum + 1;
		numFMts** rexfs = nullptr;

		rexfs = (numFMts**)realloc(numFmtsRoot, sizeof(numFMts*) * resiz);
		numFmtsRoot = rexfs;

		UINT8* numID = numFmtsRoot[numFmtsNum - 1]->Id;//最後のID取得
		int numidLen = 0;
		while (numID[numidLen] != '\0')
			numidLen++;
		UINT32 idnumb = strchange.RowArraytoNum(numID, numidLen);//ID 数次に
		idnumb++;

		rexfs[numFmtsNum] = (numFMts*)malloc(sizeof(numFMts));
		rexfs[numFmtsNum]->Id = strchange.InttoChar(idnumb, &place);//ID 入力

		rexfs[numFmtsNum]->Code = (UINT8*)malloc(strlen((char*)nf->Code) + 1);
		strcpy_s((char*)rexfs[numFmtsNum]->Code, strlen((char*)nf->Code) + 1, (char*)nf->Code);//numfmts code入力

		numFmtsNum++; nucount++;
		//free(numFmtsCount);
		numFmtsCount = strchange.InttoChar(numFmtsNum, &place);

		//free(nf->Code); free(nf->Id); free(nf);
	}
		
	/*フォントidの検索*/
	fontnumb = searchfonts(fo);
	if (fontnumb != -1) {
		cx->fontId = strchange.InttoChar(fontnumb, &place);//一致番号入力　fontID 加える
		csx->fontId = strchange.InttoChar(fontnumb, &place);
		free(fo->sz); free(fo->rgb); free(fo->family); free(fo->charset); free(fo->scheme); free(fo->color); free(fo);
	}
	else {
		//フォント設定追加　必要
		size_t resiz = (size_t)fontNum + 1;
		Fonts** rexfs = nullptr;
		rexfs = (Fonts**)realloc(fontRoot, sizeof(Fonts*) * resiz);

		fontRoot = rexfs;

		if (!rexfs)
			return 2;//error memory

		rexfs[fontNum] = (Fonts*)malloc(sizeof(Fonts));
		rexfs[fontNum]->sz = fo->sz;
		rexfs[fontNum]->name = fo->name;
		rexfs[fontNum]->rgb = fo->rgb;
		rexfs[fontNum]->indexed = fo->indexed;
		rexfs[fontNum]->family = fo->family;
		rexfs[fontNum]->charset = fo->charset;
		rexfs[fontNum]->scheme = fo->scheme;
		rexfs[fontNum]->color = fo->color;
		rexfs[fontNum]->biu = fo->biu;

		frcount++; fontNum++;//ボーダー数プラス

		free(fontCount);
		fontCount = strchange.InttoChar(fontNum, &place);

		cx->fontId = strchange.InttoChar(fontNum - 1, &place);
		csx->fontId = strchange.InttoChar(fontNum - 1, &place);
	}

	/*フィルidの検索*/
	fontnumb = searchfills(fi);
	if (fontnumb != -1)
	{
		cx->fillId = strchange.InttoChar(fontnumb, &place);//一致番号入力 フィルID加える
		csx->fillId = strchange.InttoChar(fontnumb, &place);

		free(fi->patten->patternType);
		if (fi->fg) {
			free(fi->fg->rgb); free(fi->fg->theme); free(fi->fg->tint);
		}
		if (fi->bg)
			free(fi->bg->indexed);
		free(fi->fg); free(fi->bg);
		free(fi->patten); free(fi);
	}
	else {
		//フィル設定追加　必要
		size_t resiz = (size_t)fillNum + 1;
		Fills** rexfs = nullptr;

		rexfs = (Fills**)realloc(fillroot, sizeof(Fills*) * resiz);
		fillroot = rexfs;

		if (!rexfs)
			return 2;//error memory

		rexfs[fillNum] = (Fills*)malloc(sizeof(Fills));
		rexfs[fillNum]->patten = (FillPattern*)malloc(sizeof(FillPattern));
		rexfs[fillNum]->patten->patternType = fi->patten->patternType;
		rexfs[fillNum]->fg = (fgcolor*)malloc(sizeof(fgcolor));
		rexfs[fillNum]->fg->rgb = fi->fg->rgb;
		rexfs[fillNum]->fg->theme = fi->fg->theme;
		rexfs[fillNum]->fg->tint = fi->fg->tint;
		rexfs[fillNum]->bg = (bgcolor*)malloc(sizeof(bgcolor));
		rexfs[fillNum]->bg->indexed = fi->bg->indexed;

		ficount++; fillNum++;//ボーダー数プラス

		free(fillCount);
		fillCount = strchange.InttoChar(fillNum, &place);
		cx->fillId = strchange.InttoChar(fillNum - 1, &place);
		csx->fillId = strchange.InttoChar(fillNum - 1, &place);
	}

	/*ボーダーidの検索*/
	fontnumb = searchborders(bd);
	if (fontnumb != -1)
	{
		cx->borderId = strchange.InttoChar(fontnumb, &place);//一致番号入力 ボーダー設定加える
		csx->borderId = strchange.InttoChar(fontnumb, &place);

		free(bd->left); free(bd->right); free(bd->top); free(bd->bottom); free(bd->diagonal); free(bd);
	}
	else {//ボーダー設定追加　必要
		size_t resiz = (size_t)borderNum + 1;
		borders** rexfs = nullptr;

		rexfs = (borders**)realloc(BorderRoot, sizeof(borders) * resiz);
		BorderRoot = rexfs;

		if (!rexfs)
			return 2;//error memory

		rexfs[borderNum] = (borders*)malloc(sizeof(borders));
		rexfs[borderNum]->left = bd->left;
		rexfs[borderNum]->right = bd->right;
		rexfs[borderNum]->top = bd->top;
		rexfs[borderNum]->left = bd->left;
		rexfs[borderNum]->bottom = bd->bottom;
		rexfs[borderNum]->diagonal = bd->diagonal;

		bocount++; borderNum++;//ボーダー数プラス
		free(borderCount);

		borderCount = strchange.InttoChar(borderNum, &place);
		cx->borderId = strchange.InttoChar(borderNum - 1, &place);
		csx->borderId = strchange.InttoChar(borderNum - 1, &place);
	}


	//cellstyle xfs 番号取得
	fontnumb = searchcellstylexfs(csx);
	if (fontnumb != -1) {
		cx->xfId = strchange.InttoChar(fontnumb, &place);//一致番号入力 bee以外はこっち
		free(csx->applyAlignment); free(csx->applyBorder); free(csx->applyFont); free(csx->applyNumberFormat); free(csx->applyProtection);
		free(csx->Avertical); free(csx->numFmtId); free(csx->applyFill); free(csx);
		//free(cs->builtinId); free(cs->customBuilt); free(cs->name); free(cs->xruid);
	}
	else {
		//cellstyle xfs 設定追加　必要
		size_t resiz = (size_t)cellstyleXfsNum + 1;
		stylexf** rexfs = nullptr;
		rexfs = (stylexf**)realloc(cellstyleXfsRoot, sizeof(stylexf*) * resiz);//元オブジェクト解放される
		cellstyleXfsRoot = rexfs;
		if (!rexfs) {
			std::cout << "not keep memory" << std::endl;
		}
		rexfs[csXcount] = (stylexf*)malloc(sizeof(stylexf));
		rexfs[csXcount]->numFmtId = csx->numFmtId;
		rexfs[csXcount]->fontId = csx->fontId;
		rexfs[csXcount]->fillId = csx->fillId;
		rexfs[csXcount]->borderId = csx->borderId;
		rexfs[csXcount]->applyNumberFormat = csx->applyNumberFormat;
		rexfs[csXcount]->applyBorder = csx->applyBorder;
		rexfs[csXcount]->applyAlignment = csx->applyAlignment;
		rexfs[csXcount]->applyProtection = csx->applyProtection;
		rexfs[csXcount]->Avertical = csx->Avertical;//alignment vertical
		rexfs[csXcount]->applyFont = csx->applyFont;
		rexfs[csXcount]->applyFill = csx->applyFill;
		rexfs[csXcount]->wraptext = csx->wraptext;

		csXcount++; cellstyleXfsNum++;

		free(cellStyleXfsCount);
		cellStyleXfsCount = strchange.InttoChar(cellstyleXfsNum, &place);

		cx->xfId = strchange.InttoChar(cellstyleXfsNum - 1, &place);

		//--------- cellstyle (ユーザー定義)設定追加 --------//
		/*cs->xfId = strchange.InttoChar(cellstyleXfsNum - 1, &place);

		resiz = (size_t)cellstyleNum + 1;
		cellstyle** csre = nullptr;
		csre = (cellstyle**)realloc(cellStyleRoot, sizeof(cellstyle) * resiz);
		cellStyleRoot = csre;

		csre[cscount] = (cellstyle*)malloc(sizeof(cellstyle));
		csre[cscount]->builtinId = cs->builtinId;
		csre[cscount]->customBuilt = cs->customBuilt;
		csre[cscount]->name = cs->name;
		csre[cscount]->xfId = cs->xfId;
		csre[cscount]->xruid = cs->xruid;

		cscount++; cellstyleNum++;

		free(cellstyleCount);
		cellstyleCount = strchange.InttoChar(cellstyleNum, &place);*/
	}

	//style 決定
	fontnumb = searchcellxfs(cx);

	if (fontnumb != -1)
	{
		style = strchange.InttoChar(fontnumb, &place);//一致番号入力　style 決定
		stylelen = place;

		free(cx->fontId); free(cx->fillId); free(cx->applyAlignment); free(cx->applyBorder); free(cx->applyFill); free(cx->applyFont);
		free(cx->applyNumberFormat);  free(cx->borderId);
		free(cx->numFmtId); free(cx->xfId); free(cx->AwrapText); free(cx->Avertical);
		free(cx);
	}
	else {
		//xfID 設定追加　必要
		size_t resiz = (size_t)cellXfsNum + 1;
		cellxfs** rexfs = nullptr;

		rexfs = (cellxfs**)realloc(cellXfsRoot, (sizeof(cellxfs*) * resiz));

		cellXfsRoot = rexfs;
		if (!rexfs)
			return 2;

		rexfs[cellXfsNum] = (cellxfs*)malloc(sizeof(cellxfs));
		rexfs[cellXfsNum]->fontId = cx->fontId;
		rexfs[cellXfsNum]->fillId = cx->fillId;
		rexfs[cellXfsNum]->applyAlignment = cx->applyAlignment;
		rexfs[cellXfsNum]->applyBorder = cx->applyBorder;
		rexfs[cellXfsNum]->applyFill = cx->applyFill;
		rexfs[cellXfsNum]->applyFont = cx->applyFont;
		rexfs[cellXfsNum]->applyNumberFormat = cx->applyNumberFormat;
		rexfs[cellXfsNum]->borderId = cx->borderId;
		rexfs[cellXfsNum]->numFmtId = cx->numFmtId;
		rexfs[cellXfsNum]->xfId = cx->xfId;
		rexfs[cellXfsNum]->AwrapText = cx->AwrapText;
		rexfs[cellXfsNum]->Avertical = cx->Avertical;
		rexfs[cellXfsNum]->horizontal = cx->horizontal;
		rexfs[cellXfsNum]->quotePrefix = cx->quotePrefix;

		cellXfsNum++; cXcount++;
		free(cellXfsCount);
		cellXfsCount = strchange.InttoChar(cellXfsNum, &place);

		style = strchange.InttoChar(cellXfsNum - 1, &place);
		//style 番号
		stylelen = place;

		//std::cout << "style : " << style << std::endl;
	}

	//UINT32 stylenum = strchange.RowArraytoNum(num, strlen((const char*)num));//style 番号　数字に変換
	return 1;
}
/*
inline char* checkstyle::SJIStoUTF8(char* szSJIS, char* bufUTF8, int size)
{
	wchar_t bufUnicode[100];
	int lenUnicode = MultiByteToWideChar(CP_ACP, 0, szSJIS, strlen(szSJIS) + 1, bufUnicode, 100);
	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenUnicode, bufUTF8, size, NULL, NULL);

	return bufUTF8;
}
*/