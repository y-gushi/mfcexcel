
// MFCApplication2Dlg.h : ヘッダー ファイル
//

#pragma once

#include "zaiko_souceFile/PLread.h"

// CMFCApplication2Dlg ダイアログ
class CMFCApplication2Dlg : public CDialogEx
{
// コンストラクション
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;
	

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_edit1;
	afx_msg void OnBnClickedButton1();
	//リソースの読み込み
	char* GetResouceOne();
	char* GetResouceTwo();
	
	afx_msg void OnBnClickedButton2();
	// 試し入力
	CString init_Edit_in1;
	afx_msg void OnEnChangeEdit2();
	// エディットコントロールテスト
	CEdit m_edit_control1;
	// テキストボックス入力値表示
	CString m_edit_in1;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	//設定ダイアログ　インスタンス
	Fonts* f;
	Fonts* fs;
	Fills* fi;
	Fills* fis;
	borders* bo;
	borders* bos;
	stylexf* sx;
	stylexf* sxs;
	cellxfs* cx;
	cellxfs* cxs;
	numFMts* nf;
	numFMts* nfs;
	afx_msg void OnBnClickedButton5();
	//cstring->char
	char* CstringToChar(CString cs);
	char* SJIStoUTF8(char* szSJIS, char* bufUTF8, int size);
	char* GuidToString(GUID guid);
	// 日付文字列入力
	CEdit m_dayinstr;
};
