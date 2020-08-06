// DialogTest.cpp : 実装ファイル
//

#include "pch.h"
#include "MFCApplication2.h"
#include "DialogTest.h"
#include "afxdialogex.h"


// DialogTest ダイアログ

IMPLEMENT_DYNAMIC(DialogTest, CDialogEx)

DialogTest::DialogTest(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	font_siz = _T("11");
	font_theme = _T("1");
	font_name = _T("ＭＳ Ｐゴシック");
	font_rgb = _T("");
	font_family = _T("2");
	font_charset = _T("128");
	font_scheme = _T("minor");
	f = (Fonts*)malloc(sizeof(Fonts));
	f->sz= (UINT8*)CstringToChar(font_siz);
	f->color = (UINT8*)CstringToChar(font_theme);
	char* s = CstringToChar(font_name);
	char* ut8 = (char*)calloc(50, sizeof(char));
	ut8 = SJIStoUTF8(s, ut8, 50);//shift-jis utf8変換
	f->name = (UINT8*)ut8;
	//delete[] s;

	f->rgb = nullptr;
	f->family = (UINT8*)CstringToChar(font_family);
	f->charset = (UINT8*)CstringToChar(font_charset);
	f->scheme = (UINT8*)CstringToChar(font_scheme);
	f->biu = nullptr;
	f->indexed = nullptr;
	
	fonts_siz = _T("11");
	fonts_theme = _T("1");
	fonts_name = _T("ＭＳ Ｐゴシック");
	fonts_rgb = _T("");
	fonts_family = _T("2");
	fonts_charset = _T("128");
	fonts_scheme = _T("minor");
	fs = (Fonts*)malloc(sizeof(Fonts));
	fs->sz = (UINT8*)CstringToChar(fonts_siz);
	fs->color = (UINT8*)CstringToChar(fonts_theme);
	char* ss = CstringToChar(font_name);
	char* ut8s = (char*)calloc(50, sizeof(char));
	ut8s = SJIStoUTF8(ss, ut8s, 50);//shift-jis utf8変換
	fs->name = (UINT8*)ut8s;
	//delete[] ss;

	fs->rgb = nullptr;
	fs->family = (UINT8*)CstringToChar(fonts_family);
	fs->charset = (UINT8*)CstringToChar(fonts_charset);
	fs->scheme = (UINT8*)CstringToChar(fonts_scheme);
	fs->biu = nullptr;
	fs->indexed = nullptr;

	fill_paterntype = _T("none");
	fill_theme = _T("");
	fill_rgb = _T("");
	fill_tint = _T("");
	fill_indexed = _T("");
	fi= (Fills*)malloc(sizeof(Fills));
	fi->patten = (FillPattern*)malloc(sizeof(FillPattern));
	fi->patten->patternType= (UINT8*)CstringToChar(fill_paterntype);
	fi->fg = (fgcolor*)malloc(sizeof(fgcolor));
	fi->fg->theme = nullptr;
	fi->fg->rgb = nullptr;
	fi->fg->tint = nullptr;
	fi->bg = (bgcolor*)malloc(sizeof(bgcolor));
	fi->bg->indexed = nullptr;

	fills_paterntype = _T("none");
	fills_theme = _T("");
	fills_rgb = _T("");
	fills_tint = _T("");
	fills_indexed = _T("");
	fis = (Fills*)malloc(sizeof(Fills));
	fis->patten = (FillPattern*)malloc(sizeof(FillPattern));
	fis->patten->patternType = (UINT8*)CstringToChar(fills_paterntype);
	fis->fg = (fgcolor*)malloc(sizeof(fgcolor));
	fis->fg->theme = nullptr;
	fis->fg->rgb = nullptr;
	fis->fg->tint = nullptr;
	fis->bg = (bgcolor*)malloc(sizeof(bgcolor));
	fis->bg->indexed = nullptr;

	border_top = _T("");
	border_bottom = _T("");
	border_left = _T("");
	border_right = _T("");
	border_diaglam = _T("");
	bo = (borders*)malloc(sizeof(borders));
	bo->bottom = nullptr;
	bo->diagonal = nullptr;
	bo->diagonalDown = nullptr;
	bo->diagonalUp = nullptr;
	bo->left = nullptr;
	bo->right = nullptr;
	bo->top = nullptr;

	borders_top = _T("");
	borders_bottom = _T("");
	borders_left = _T("");
	borders_right = _T("");
	borders_diaglam = _T("");	
	bos = (borders*)malloc(sizeof(borders));
	bos->bottom = nullptr;
	bos->diagonal = nullptr;
	bos->diagonalDown = nullptr;
	bos->diagonalUp = nullptr;
	bos->left = nullptr;
	bos->right = nullptr;
	bos->top = nullptr;
	
	cellstyle_name = _T("");
	cellstyles_name = _T("");
	//cs = (cellstyle*)malloc(sizeof(cellstyle));
	//cs->builtinId = nullptr;
	cs = nullptr;
	css = nullptr;

	stylexfs_applyNumber = _T("");
	stylexfs_applyborder = _T("");
	stylexfs_applyalin = _T("");
	stylexfs_appliProtect = _T("");
	stylexfs_applyFont = _T("");
	stylexfs_applyfill = _T("");
	stylexfs_wraptext = _T("");
	stylexfs_avertical = "center";

	stylexfss_applyNumber = _T("");
	stylexfss_applyborder = _T("");
	stylexfss_applyalin = _T("");
	stylexfss_appliProtect = _T("");
	stylexfss_applyFont = _T("");
	stylexfss_applyfill = _T("");
	stylexfss_wraptext = _T("");
	stylexfss_avertical = "center";

	s_fmts = _T("[$$-409]#,##0;[$$-409]#,##0");
	nf = (numFMts*)malloc(sizeof(numFMts));
	nf->Code = (UINT8*)CstringToChar(s_fmts);
	nf->Id = (UINT8*)malloc(sizeof(UINT8)*4);
	strcpy_s((char*)nf->Id, 4, (char*)nid);
	
	sx = (stylexf*)malloc(sizeof(stylexf));
	sx->numFmtId = nullptr;
	sx->applyNumberFormat = nullptr;
	sx->applyBorder = nullptr;
	sx->applyFill = nullptr;
	sx->applyAlignment = nullptr;
	sx->applyProtection = nullptr;
	sx->applyFont = nullptr;
	sx->wraptext = nullptr;
	sx->Avertical = (UINT8*)CstringToChar(stylexfs_avertical);

	v_fmts = _T("[$$-409]#,##0;[$$-409]#,##0");
	nfs = (numFMts*)malloc(sizeof(numFMts));
	nfs->Code = (UINT8*)CstringToChar(v_fmts);
	nfs->Id = (UINT8*)malloc(sizeof(UINT8) * 4);
	strcpy_s((char*)nfs->Id, 4, (char*)nid);

	sxs = (stylexf*)malloc(sizeof(stylexf));
	sxs->numFmtId = nullptr;
	sxs->applyNumberFormat = nullptr;
	sxs->applyBorder = nullptr;
	sxs->applyFill = nullptr;
	sxs->applyAlignment = nullptr;
	sxs->applyProtection = nullptr;
	sxs->applyFont = nullptr;
	sxs->wraptext = nullptr;
	sxs->Avertical = (UINT8*)CstringToChar(stylexfss_avertical);

	xfs_numfmtId = "0";
	xfs_horizontal = "left";
	xfs_quotePrefix = _T("");
	xfs_applyNumberformat = "1";
	xfs_vertical = "center";
	xfs_applyalingment = "1";
	cx = (cellxfs*)malloc(sizeof(cellxfs));
	cx->numFmtId = (UINT8*)CstringToChar(xfs_numfmtId);
	cx->horizontal = (UINT8*)CstringToChar(xfs_horizontal);
	cx->quotePrefix = nullptr;
	cx->applyNumberFormat = (UINT8*)CstringToChar(xfs_applyNumberformat);
	cx->Avertical = (UINT8*)CstringToChar(xfs_vertical);
	cx->applyAlignment = (UINT8*)CstringToChar(xfs_applyalingment);
	cx->applyBorder = nullptr;
	cx->applyFill = nullptr;
	cx->applyFont = nullptr;
	cx->AwrapText = nullptr;
	cx->xfId = nullptr;
	cx->fontId = nullptr;
	cx->fillId = nullptr;
	cx->borderId = nullptr;

	xfss_numfmtId = "0";
	xfss_horizontal = _T("");
	xfss_quotePrefix = _T("");
	xfss_applyNumberformat = "1";
	xfss_vertical = "center";
	xfss_applyalingment = _T("");
	cxs = (cellxfs*)malloc(sizeof(cellxfs));
	cxs->numFmtId = (UINT8*)CstringToChar(xfss_numfmtId);
	cxs->horizontal = nullptr;
	cxs->quotePrefix = nullptr;
	cxs->applyNumberFormat = (UINT8*)CstringToChar(xfss_applyNumberformat);
	cxs->Avertical = (UINT8*)CstringToChar(xfss_vertical);
	cxs->applyAlignment = nullptr;
	cxs->applyBorder = nullptr;
	cxs->applyFill = nullptr;
	cxs->applyFont = nullptr;
	cxs->AwrapText = nullptr;
	cxs->xfId = nullptr;
	cxs->fontId = nullptr;
	cxs->fillId = nullptr;
	cxs->borderId = nullptr;
}

DialogTest::~DialogTest()
{
}

void DialogTest::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_scell_numfmts);
	DDX_Control(pDX, IDC_EDIT18, m_vcell_numfmts);
	DDX_Control(pDX, IDC_EDIT2, scell_fontsize);
	DDX_Control(pDX, IDC_EDIT10, scell_fontrgb);
	DDX_Control(pDX, IDC_EDIT74, scell_fonttheme);
	DDX_Control(pDX, IDC_EDIT73, scell_fontname);
	DDX_Control(pDX, IDC_EDIT37, scell_fontfamily);
	DDX_Control(pDX, IDC_EDIT5, scell_charset);
	DDX_Control(pDX, IDC_EDIT6, scell_fontscheme);
	DDX_Control(pDX, IDC_EDIT19, vcell_fontsize);
	DDX_Control(pDX, IDC_EDIT20, vcell_fonttheme);
	DDX_Control(pDX, IDC_EDIT21, vcell_fontrgb);
	DDX_Control(pDX, IDC_EDIT22, vcell_fontname);
	DDX_Control(pDX, IDC_EDIT38, vcell_charset);
	DDX_Control(pDX, IDC_EDIT24, vcell_fontscheme);
	DDX_Control(pDX, IDC_EDIT7, scell_fillpattern);
	DDX_Control(pDX, IDC_EDIT8, scell_filltheme);
	DDX_Control(pDX, IDC_EDIT11, scell_fillrgb);
	DDX_Control(pDX, IDC_EDIT9, scell_filltint);
	DDX_Control(pDX, IDC_EDIT12, scell_fillindexed);
	DDX_Control(pDX, IDC_EDIT25, vcell_fillpattern);
	DDX_Control(pDX, IDC_EDIT26, vcell_theme);
	DDX_Control(pDX, IDC_EDIT27, vcell_fillrgb);
	DDX_Control(pDX, IDC_EDIT28, vcell_filltint);
	DDX_Control(pDX, IDC_EDIT29, vcell_fillindexed);
	DDX_Control(pDX, IDC_EDIT13, scell_bordertop);
	DDX_Control(pDX, IDC_EDIT14, scell_borderleft);
	DDX_Control(pDX, IDC_EDIT15, scell_borderright);
	DDX_Control(pDX, IDC_EDIT16, scell_borderbottom);
	DDX_Control(pDX, IDC_EDIT43, scell_borderdiagram);
	DDX_Control(pDX, IDC_EDIT30, vcell_bordertop);
	DDX_Control(pDX, IDC_EDIT31, vcell_borderleft);
	DDX_Control(pDX, IDC_EDIT32, vcell_borderright);
	DDX_Control(pDX, IDC_EDIT33, vcell_borderbottom);
	DDX_Control(pDX, IDC_EDIT42, vcell_borderdiagram);
	DDX_Control(pDX, IDC_EDIT17, scell_stylename);
	DDX_Control(pDX, IDC_EDIT34, vcell_stylename);
	DDX_Control(pDX, IDC_EDIT44, scell_applynumformat);
	DDX_Control(pDX, IDC_EDIT52, scell_applyborder);
	DDX_Control(pDX, IDC_EDIT53, scell_applyalin);
	DDX_Control(pDX, IDC_EDIT55, scell_avertical);
	DDX_Control(pDX, IDC_EDIT56, scell_applyfont);
	DDX_Control(pDX, IDC_EDIT57, scell_applyfill);
	DDX_Control(pDX, IDC_EDIT58, scell_wraptext);
	DDX_Control(pDX, IDC_EDIT41, vcell_applyNUmberformat);
	DDX_Control(pDX, IDC_EDIT45, vcell_applyborder);
	DDX_Control(pDX, IDC_EDIT46, vcell_applyalin);
	DDX_Control(pDX, IDC_EDIT47, vcell_appliProtection);
	DDX_Control(pDX, IDC_EDIT48, vcell_avertical);
	DDX_Control(pDX, IDC_EDIT49, vcell_applyfont);
	DDX_Control(pDX, IDC_EDIT50, vcell_applyfill);
	DDX_Control(pDX, IDC_EDIT51, vcell_wraptext);
	DDX_Control(pDX, IDC_EDIT39, s_xfs_horizen);
	DDX_Control(pDX, IDC_EDIT40, s_xfs_quotePrefix);
	DDX_Control(pDX, IDC_EDIT59, s_xfs_numfmtId);
	DDX_Control(pDX, IDC_EDIT66, s_xfs_applyNumFormat);
	DDX_Control(pDX, IDC_EDIT67, s_xfs_applyaling);
	DDX_Control(pDX, IDC_EDIT68, s_xfs_vertical);
	DDX_Control(pDX, IDC_EDIT60, v_xfs_horizontal);
	DDX_Control(pDX, IDC_EDIT61, v_xfs_quotePrefix);
	DDX_Control(pDX, IDC_EDIT62, v_xfs_numfmtId);
	DDX_Control(pDX, IDC_EDIT63, v_xfs_applyNumfor);
	DDX_Control(pDX, IDC_EDIT64, v_xfs_applyaling);
	DDX_Control(pDX, IDC_EDIT65, v_xfs_vertical);
	DDX_Control(pDX, IDC_EDIT23, vcell_fontfamily);
	DDX_Control(pDX, IDC_EDIT54, scell_appliProtection);

	m_scell_numfmts.SetWindowText(s_fmts);
	m_vcell_numfmts.SetWindowText(v_fmts);

	scell_fontsize.SetWindowText(font_siz);
	scell_fonttheme.SetWindowText(font_theme);
	scell_fontname.SetWindowText(font_name);
	scell_fontfamily.SetWindowText(font_family);
	scell_charset.SetWindowText(font_charset);
	scell_fontscheme.SetWindowText(font_scheme);

	vcell_fontsize.SetWindowText(font_siz);
	vcell_fonttheme.SetWindowText(font_theme);
	vcell_fontname.SetWindowText(font_name);
	vcell_fontfamily.SetWindowText(font_family);
	vcell_charset.SetWindowText(font_charset);
	vcell_fontscheme.SetWindowText(font_scheme);

	scell_fillpattern.SetWindowText(fill_paterntype);
	scell_filltheme.SetWindowText(fill_theme);
	scell_fillrgb.SetWindowText(fill_rgb);
	scell_filltint.SetWindowText(fill_tint);
	scell_fillindexed.SetWindowText(fill_indexed);

	vcell_fillpattern.SetWindowText(fills_paterntype);
	vcell_theme.SetWindowText(fills_theme);
	vcell_fillrgb.SetWindowText(fills_rgb);
	vcell_filltint.SetWindowText(fills_tint);
	vcell_fillindexed.SetWindowText(fills_indexed);

	scell_bordertop.SetWindowText(border_top);
	scell_borderleft.SetWindowText(border_bottom);
	scell_borderright.SetWindowText(border_left);
	scell_borderbottom.SetWindowText(border_right);
	scell_borderdiagram.SetWindowText(border_diaglam);

	vcell_bordertop.SetWindowText(borders_top);
	vcell_borderleft.SetWindowText(borders_bottom);
	vcell_borderright.SetWindowText(borders_left);
	vcell_borderbottom.SetWindowText(borders_right);
	vcell_borderdiagram.SetWindowText(borders_diaglam);

	scell_stylename.SetWindowText(cellstyle_name);
	vcell_stylename.SetWindowText(cellstyles_name);

	scell_applynumformat.SetWindowText(stylexfs_applyNumber);
	scell_applyborder.SetWindowText(stylexfs_applyborder);
	scell_applyalin.SetWindowText(stylexfs_applyalin);
	scell_avertical.SetWindowText(stylexfs_avertical);
	scell_appliProtection.SetWindowText(stylexfs_appliProtect);
	scell_applyfont.SetWindowText(stylexfs_applyFont);
	scell_applyfill.SetWindowText(stylexfs_applyfill);
	scell_wraptext.SetWindowText(stylexfs_wraptext);

	vcell_applyNUmberformat.SetWindowText(stylexfss_applyNumber);
	vcell_applyborder.SetWindowText(stylexfss_applyborder);
	vcell_applyalin.SetWindowText(stylexfss_applyalin);
	vcell_avertical.SetWindowText(stylexfss_avertical);
	vcell_appliProtection.SetWindowText(stylexfss_appliProtect);
	vcell_applyfont.SetWindowText(stylexfss_applyFont);
	vcell_applyfill.SetWindowText(stylexfss_applyfill);
	vcell_wraptext.SetWindowText(stylexfss_wraptext);

	s_xfs_horizen.SetWindowText(xfs_horizontal);
	s_xfs_quotePrefix.SetWindowText(xfs_quotePrefix);
	s_xfs_numfmtId.SetWindowText(xfs_numfmtId);
	s_xfs_applyNumFormat.SetWindowText(xfs_applyNumberformat);
	s_xfs_applyaling.SetWindowText(xfs_applyalingment);
	s_xfs_vertical.SetWindowText(xfs_vertical);

	v_xfs_horizontal.SetWindowText(xfss_horizontal);
	v_xfs_quotePrefix.SetWindowText(xfss_quotePrefix);
	v_xfs_numfmtId.SetWindowText(xfss_numfmtId);
	v_xfs_applyNumfor.SetWindowText(xfss_applyNumberformat);
	v_xfs_applyaling.SetWindowText(xfss_applyalingment);
	v_xfs_vertical.SetWindowText(xfss_vertical);
	
}


BEGIN_MESSAGE_MAP(DialogTest, CDialogEx)
	ON_BN_CLICKED(IDOK, &DialogTest::OnBnClickedOk)
END_MESSAGE_MAP()


// DialogTest メッセージ ハンドラー


void DialogTest::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	
	scell_fontsize.GetWindowText(font_siz);
	scell_fonttheme.GetWindowText(font_theme);
	scell_fontname.GetWindowText(font_name);
	scell_fontfamily.GetWindowText(font_family);
	scell_charset.GetWindowText(font_charset);
	scell_fontscheme.GetWindowText(font_scheme);	
	StrCopyandCheck(font_siz, f->sz);
	StrCopyandCheck(font_theme, f->color);
	free(f->name);
	f->name = nullptr;
	if (font_name.GetLength() > 0)
		f->name = StrCopyCheckAndJis(font_name);//jis変換 char変換
	f->rgb = nullptr;
	StrCopyandCheck(font_family, f->family);
	StrCopyandCheck(font_charset, f->charset);
	StrCopyandCheck(font_scheme, f->scheme);
	f->biu = nullptr;
	f->indexed = nullptr;

	vcell_fontsize.GetWindowText(fonts_siz);
	vcell_fonttheme.GetWindowText(fonts_theme);
	vcell_fontname.GetWindowText(fonts_name);
	vcell_fontfamily.GetWindowText(fonts_family);
	vcell_charset.GetWindowText(fonts_charset);
	vcell_fontscheme.GetWindowText(fonts_scheme);
	StrCopyandCheck(fonts_siz, fs->sz);
	StrCopyandCheck(fonts_theme, fs->color);
	free(fs->name);
	fs->name = nullptr;
	if (fonts_name.GetLength() > 0)
		fs->name = StrCopyCheckAndJis(fonts_name);//jis変換 char変換
	fs->rgb = nullptr;
	StrCopyandCheck(fonts_family, fs->family);
	StrCopyandCheck(fonts_charset, fs->charset);
	StrCopyandCheck(fonts_scheme, fs->scheme);
	fs->biu = nullptr;
	fs->indexed = nullptr;

	scell_fillpattern.GetWindowText(fill_paterntype);
	scell_filltheme.GetWindowText(fill_theme);
	scell_fillrgb.GetWindowText(fill_rgb);
	scell_filltint.GetWindowText(fill_tint);
	scell_fillindexed.GetWindowText(fill_indexed);
	StrCopyandCheck(fill_paterntype, fi->patten->patternType);
	StrCopyandCheck(fill_paterntype, fi->fg->theme);
	StrCopyandCheck(fill_tint, fi->fg->tint);
	StrCopyandCheck(fill_rgb, fi->fg->rgb);
	StrCopyandCheck(fill_indexed, fi->bg->indexed);

	vcell_fillpattern.GetWindowText(fills_paterntype);
	vcell_theme.GetWindowText(fills_theme);
	vcell_fillrgb.GetWindowText(fills_rgb);
	vcell_filltint.GetWindowText(fills_tint);
	vcell_fillindexed.GetWindowText(fills_indexed);
	StrCopyandCheck(fills_paterntype, fis->patten->patternType);
	StrCopyandCheck(fills_paterntype, fis->fg->theme);
	StrCopyandCheck(fills_tint, fis->fg->tint);
	StrCopyandCheck(fills_rgb, fis->fg->rgb);
	StrCopyandCheck(fills_indexed, fis->bg->indexed);

	scell_bordertop.GetWindowText(border_top);
	scell_borderleft.GetWindowText(border_bottom);
	scell_borderright.GetWindowText(border_left);
	scell_borderbottom.GetWindowText(border_right);
	scell_borderdiagram.GetWindowText(border_diaglam);

	vcell_bordertop.GetWindowText(borders_top);
	vcell_borderleft.GetWindowText(borders_bottom);
	vcell_borderright.GetWindowText(borders_left);
	vcell_borderbottom.GetWindowText(borders_right);
	vcell_borderdiagram.GetWindowText(borders_diaglam);

	scell_stylename.GetWindowText(cellstyle_name);
	vcell_stylename.GetWindowText(cellstyles_name);

	scell_applynumformat.GetWindowText(stylexfs_applyNumber);
	scell_applyborder.GetWindowText(stylexfs_applyborder);
	scell_applyalin.GetWindowText(stylexfs_applyalin);
	scell_avertical.GetWindowText(stylexfs_avertical);
	scell_appliProtection.GetWindowText(stylexfs_appliProtect);
	scell_applyfont.GetWindowText(stylexfs_applyFont);
	scell_applyfill.GetWindowText(stylexfs_applyfill);
	scell_wraptext.GetWindowText(stylexfs_wraptext);

	m_scell_numfmts.GetWindowText(s_fmts);
	StrCopyandCheck(stylexfs_applyNumber, sx->applyNumberFormat);
	StrCopyandCheck(stylexfs_applyborder, sx->applyBorder);
	StrCopyandCheck(stylexfs_applyalin, sx->applyAlignment);
	StrCopyandCheck(stylexfs_avertical, sx->Avertical);
	StrCopyandCheck(stylexfs_appliProtect, sx->applyProtection);
	StrCopyandCheck(stylexfs_applyFont, sx->applyFont);
	StrCopyandCheck(stylexfs_applyfill, sx->applyFill);
	StrCopyandCheck(stylexfs_wraptext, sx->wraptext);
	
	StrCopyandCheck(s_fmts, nf->Code);//numfmt name

	vcell_applyNUmberformat.GetWindowText(stylexfss_applyNumber);
	vcell_applyborder.GetWindowText(stylexfss_applyborder);
	vcell_applyalin.GetWindowText(stylexfss_applyalin);
	vcell_avertical.GetWindowText(stylexfss_avertical);
	vcell_appliProtection.GetWindowText(stylexfss_appliProtect);
	vcell_applyfont.GetWindowText(stylexfss_applyFont);
	vcell_applyfill.GetWindowText(stylexfss_applyfill);
	vcell_wraptext.GetWindowText(stylexfss_wraptext);
	
	m_vcell_numfmts.GetWindowText(v_fmts);
	StrCopyandCheck(stylexfss_applyNumber, sxs->applyNumberFormat);
	StrCopyandCheck(stylexfss_applyborder, sxs->applyBorder);
	StrCopyandCheck(stylexfss_applyalin, sxs->applyAlignment);
	StrCopyandCheck(stylexfss_avertical, sxs->Avertical);
	StrCopyandCheck(stylexfss_appliProtect, sxs->applyProtection);
	StrCopyandCheck(stylexfss_applyFont, sxs->applyFont);
	StrCopyandCheck(stylexfss_applyfill, sxs->applyFill);
	StrCopyandCheck(stylexfss_wraptext, sxs->wraptext);
	
	StrCopyandCheck(v_fmts, nfs->Code);//numfmid

	s_xfs_horizen.GetWindowText(xfs_horizontal);
	s_xfs_quotePrefix.GetWindowText(xfs_quotePrefix);
	s_xfs_numfmtId.GetWindowText(xfs_numfmtId);
	s_xfs_applyNumFormat.GetWindowText(xfs_applyNumberformat);
	s_xfs_applyaling.GetWindowText(xfs_applyalingment);
	s_xfs_vertical.GetWindowText(xfs_vertical);
	StrCopyandCheck(xfs_horizontal, cx->horizontal);
	StrCopyandCheck(xfs_quotePrefix, cx->quotePrefix);
	StrCopyandCheck(xfs_numfmtId, cx->numFmtId);
	StrCopyandCheck(xfs_applyNumberformat, cx->applyNumberFormat);
	StrCopyandCheck(xfs_applyalingment, cx->applyAlignment);
	StrCopyandCheck(xfs_vertical, cx->Avertical);

	v_xfs_horizontal.GetWindowText(xfss_horizontal);
	v_xfs_quotePrefix.GetWindowText(xfss_quotePrefix);
	v_xfs_numfmtId.GetWindowText(xfss_numfmtId);
	v_xfs_applyNumfor.GetWindowText(xfss_applyNumberformat);
	v_xfs_applyaling.GetWindowText(xfss_applyalingment);
	v_xfs_vertical.GetWindowText(xfss_vertical);
	StrCopyandCheck(xfss_horizontal, cxs->horizontal);
	StrCopyandCheck(xfss_quotePrefix, cxs->quotePrefix);
	StrCopyandCheck(xfss_numfmtId, cxs->numFmtId);
	StrCopyandCheck(xfss_applyNumberformat, cxs->applyNumberFormat);
	StrCopyandCheck(xfss_applyalingment, cxs->applyAlignment);
	StrCopyandCheck(xfss_vertical, cxs->Avertical);

	CDialogEx::OnOK();
}

char* DialogTest::CstringToChar(CString cs) {
	size_t textSize = (cs.GetLength() * 2) + 1;
	char* lpcText = (char*)calloc(textSize,sizeof(char));
	WideCharToMultiByte(CP_ACP, 0, cs.GetBuffer(), -1, lpcText, textSize, NULL, NULL);
	cs.ReleaseBuffer();//※忘れちゃダメ

	return lpcText;
}

char* DialogTest::SJIStoUTF8(char* szSJIS, char* bufUTF8, int size) {
	wchar_t bufUnicode[BUFSIZE];
	int lenUnicode = MultiByteToWideChar(CP_ACP, 0, szSJIS, strlen(szSJIS) + 1, bufUnicode, BUFSIZE);
	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenUnicode, bufUTF8, size, NULL, NULL);
	return bufUTF8;
}

UINT8* DialogTest::StrCopyandCheck(CString c,UINT8* bs) {
	free(bs);
	bs = nullptr;

	if (c.GetLength() > 0)
		bs = (UINT8*)CstringToChar(c);		

	return bs;
}

UINT8* DialogTest::StrCopyCheckAndJis(CString c) {
	char* s = CstringToChar(c);
	char* ut8 = (char*)calloc(50, sizeof(char));
	ut8 = SJIStoUTF8(s, ut8, 50);//shift-jis utf8変換	
	//delete[] s;

	return (UINT8*)ut8;
}

