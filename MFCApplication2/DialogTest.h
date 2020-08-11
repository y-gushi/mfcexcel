#pragma once
#include "zaiko_souceFile/PLread.h"

// DialogTest ダイアログ

class DialogTest : public CDialogEx
{
	DECLARE_DYNAMIC(DialogTest)

public:
	DialogTest(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~DialogTest();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	Fonts* f;
	Fills* fi;
	borders* bo;
	cellstyle* cs;
	cellxfs* cx;
	stylexf* sx;
	numFMts* nf;
	UINT8 nid[4] = "180";//187

	Fonts* fs;
	Fills* fis;
	borders* bos;
	cellstyle* css;
	cellxfs* cxs;
	stylexf* sxs;
	numFMts* nfs;

	CString s_fmts;//fmtname id 決まっている
	CString v_fmts;

	//文字列セル　フォント
	CString font_siz;
	CString font_theme;
	CString font_name;
	CString font_rgb;
	CString font_family;
	CString font_charset;
	CString font_scheme;
	//数値セル　フォント
	CString fonts_siz;
	CString fonts_theme;
	CString fonts_name;
	CString fonts_rgb;
	CString fonts_family;
	CString fonts_charset;
	CString fonts_scheme;
	//文字列セル　フィル
	CString fill_paterntype;
	CString fill_theme;
	CString fill_rgb;
	CString fill_tint;
	CString fill_indexed;
	//数値セル　フィル
	CString fills_paterntype;
	CString fills_theme;
	CString fills_rgb;
	CString fills_tint;
	CString fills_indexed;
	//文字列セル　ボーダー
	CString border_top;
	CString border_bottom;
	CString border_left;
	CString border_right;
	CString border_diaglam;
	//数値セル　ボーダー
	CString borders_top;
	CString borders_bottom;
	CString borders_left;
	CString borders_right;
	CString borders_diaglam;
	//文字列セル　cellstyle name
	CString cellstyle_name;
	//数値セル　cellstyle name
	CString cellstyles_name;
	//文字列セル　ボーダー
	CString stylexfs_applyNumber;
	CString stylexfs_applyborder;
	CString stylexfs_applyalin;
	CString stylexfs_appliProtect;
	CString stylexfs_avertical;
	CString stylexfs_applyFont;
	CString stylexfs_applyfill;
	CString stylexfs_wraptext;
	//数値セル　ボーダー
	CString stylexfss_applyNumber;
	CString stylexfss_applyborder;
	CString stylexfss_applyalin;
	CString stylexfss_appliProtect;
	CString stylexfss_avertical;
	CString stylexfss_applyFont;
	CString stylexfss_applyfill;
	CString stylexfss_wraptext;
	//文字列セル　xfs
	CString xfs_numfmtId;
	CString xfs_horizontal;
	CString xfs_quotePrefix;
	CString xfs_applyNumberformat;
	CString xfs_applyalingment;
	CString xfs_vertical;

	//数値セル　xfs
	CString xfss_numfmtId;
	CString xfss_horizontal;
	CString xfss_quotePrefix;
	CString xfss_applyNumberformat;
	CString xfss_applyalingment;
	CString xfss_vertical;

	//追加列　幅
	CString col_width;

	afx_msg void OnBnClickedOk();
	char* CstringToChar(CString cs);
	char* SJIStoUTF8(char* szSJIS, char* bufUTF8, int size);
	UINT8* StrCopyandCheck(CString c, UINT8* bs);
	UINT8* StrCopyCheckAndJis(CString c);
	// 文字列　表示形式
	CEdit m_scell_numfmts;
	// 数値セル 表示形式
	CEdit m_vcell_numfmts;
	// フォントサイズ
	CEdit scell_fontsize;
	CEdit scell_fontrgb;
	CEdit scell_fonttheme;
	CEdit scell_fontname;
	CEdit scell_fontfamily;
	CEdit scell_charset;
	CEdit scell_fontscheme;
	// 数値フォント
	CEdit vcell_fontsize;
	CEdit vcell_fonttheme;
	CEdit vcell_fontrgb;
	CEdit vcell_fontname;
	CEdit vcell_charset;
	CEdit vcell_fontscheme;
	// フィルパターン
	CEdit scell_fillpattern;
	CEdit scell_filltheme;
	CEdit scell_fillrgb;
	CEdit scell_filltint;
	CEdit scell_fillindexed;
	// 数値セル　フィル
	CEdit vcell_fillpattern;
	CEdit vcell_theme;
	CEdit vcell_fillrgb;
	CEdit vcell_filltint;
	CEdit vcell_fillindexed;
	// 文字列　ボーダー
	CEdit scell_bordertop;
	CEdit scell_borderleft;
	CEdit scell_borderright;
	CEdit scell_borderbottom;
	CEdit scell_borderdiagram;
	// 数値ボーダー
	CEdit vcell_bordertop;
	CEdit vcell_borderleft;
	CEdit vcell_borderright;
	CEdit vcell_borderbottom;
	CEdit vcell_borderdiagram;
	// スタイル名前
	CEdit scell_stylename;
	CEdit vcell_stylename;
	// cellstylexfs
	CEdit scell_applynumformat;
	CEdit scell_applyborder;
	CEdit scell_applyalin;
	CEdit scell_appliProtection;
	CEdit scell_avertical;
	CEdit scell_applyfont;
	CEdit scell_applyfill;
	CEdit scell_wraptext;
	CEdit vcell_applyNUmberformat;
	CEdit vcell_applyborder;
	CEdit vcell_applyalin;
	CEdit vcell_appliProtection;
	CEdit vcell_avertical;
	CEdit vcell_applyfont;
	CEdit vcell_applyfill;
	CEdit vcell_wraptext;
	// xfs 文字列
	CEdit s_xfs_horizen;
	CEdit s_xfs_quotePrefix;
	CEdit s_xfs_numfmtId;
	CEdit s_xfs_applyNumFormat;
	CEdit s_xfs_applyaling;
	CEdit s_xfs_vertical;
	// xfs 数値
	CEdit v_xfs_horizontal;
	CEdit v_xfs_quotePrefix;
	CEdit v_xfs_numfmtId;
	CEdit v_xfs_applyNumfor;
	CEdit v_xfs_applyaling;
	CEdit v_xfs_vertical;
	CEdit vcell_fontfamily;
	
};
