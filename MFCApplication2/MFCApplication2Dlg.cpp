
// MFCApplication2Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
//#include "resource1.h"
#include "curl/curl.h"
#include "DialogTest.h"
#include "CsvRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg ダイアログ



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
	, m_edit1(_T(""))
	, init_Edit_in1(_T(""))
	, m_edit_in1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	f = nullptr;
	fs = nullptr;
	fi = nullptr;
	fis = nullptr;
	bo = nullptr;
	bos = nullptr;
	sx = nullptr;
	sxs = nullptr;
	cx = nullptr;
	cxs = nullptr;
	nf = nullptr;
	nfs = nullptr;
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, init_Edit_in1);
	DDX_Control(pDX, IDC_EDIT2, m_edit_control1);
	DDX_Text(pDX, IDC_EDIT3, m_edit_in1);
	DDX_Control(pDX, IDC_EDIT4, m_dayinstr);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2Dlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication2Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication2Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMFCApplication2Dlg メッセージ ハンドラー

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。
	//m_edit_control1.SetWindowText(_T("PSゴシック"));
	DialogTest dlg; // バージョン情報ダイアログのインスタンスを作成
	f = dlg.f;
	fs = dlg.fs;
	fi = dlg.fi;
	fis = dlg.fis;
	bo = dlg.bo;
	bos = dlg.bos;
	sx = dlg.sx;
	sxs = dlg.sxs;
	cx = dlg.cx;
	cxs = dlg.cxs;
	nf = dlg.nf;
	nfs = dlg.nfs;
	
	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCApplication2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplication2Dlg::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	PLRead* pl = new PLRead();
	FILE* wf;
	//ファイルパスの取得
	char* hatyu;
	hatyu = CstringToChar(init_Edit_in1);

	//書き込みファイルネーム
	char* wrfn = pl->writename(hatyu, strlen(hatyu));

	char* inMainstr = (char*)calloc(50, sizeof(char));
	char* NewUid = (char*)calloc(100, sizeof(char));

	//csv読み込み
	char* filn = CstringToChar(m_edit_in1);
	CsvRead* cr = new CsvRead();
	cr->readCsv(filn);

	//品番一致シート検索
	pl->readWorkBook(hatyu);
	pl->workbookCheck(cr->csvroot);
	fopen_s(&wf, wrfn, "wb");
	if (!wf) {
		delete pl->wb;
		delete pl->ap;
		delete cr;
		delete pl;
		return;
	}

	//スタイル決定
	pl->openstyleseat(hatyu);
	UINT8* styone=pl->stylesetting(f, fi, bo, sx, cx, nf);
	UINT8* stytwo = pl->stylesetting(fs, fis, bos, sxs, cxs, nfs);
	//スタイル書き込み
	pl->sr->styledatawrite(pl->styleleng);
	//スタイル圧縮
	pl->writecompress(pl->sr->wd, pl->sr->wdlen, wf, pl->cddata);
	delete pl->sr;
	delete pl->cddata;

	//文字列入力読み込み
	CString k;
	m_dayinstr.GetWindowText(k);
	if (k.GetLength() > 0) {
		char* ds = CstringToChar(k);//char変換
		inMainstr = SJIStoUTF8(ds, inMainstr, 50);//utf8変換
	}
	else
		inMainstr[0] = '\0';

	//シェアー読み込み テキストついか
	pl->readshareAndWrite(inMainstr,hatyu);
	//シェアー新規シート用文字追加
	if(pl->nomatch)
		pl->ItemsChangeShare(pl->nomatch);

	//シェアーファイル書き込み
	pl->shar->siwrite();
	pl->writecompress((UINT8*)pl->shar->wd, pl->shar->wlen, wf,pl->cddata);//圧縮
	delete pl->hr;

	//workbookrel 更新
	pl->workbookrelsadd(pl->nomatch,hatyu);
	pl->writecompress(pl->wbr->wd, pl->wbr->wl, wf,pl->cddata);
	delete pl->wbr;
	delete pl->hr;

	//sheetdata書き込み
	pl->sheetread(hatyu, pl->matchs, wf, styone, stytwo);
	
	//new sheet
	CsvItemandRid* ro = nullptr;
	UINT8* drawid = nullptr;
	
	char* newshdata = GetResouceOne();//リソースデータ
	char* newshreldata = GetResouceTwo();//リソースデータ
	char* drawdata = GetResouceThree();//リソースデータ
	char* drawreldata = GetResouceFour();//リソースデータ
	ro = pl->nomatch;
	if (ro) {
		while (ro) {
			//uuid 作成
			GUID guid;
			CoCreateGuid(&guid);
			std::string uuid = GuidToString(guid);
			const char* uid = uuid.c_str();
			//NewUid = SJIStoUTF8(uid, NewUid, 100);//utf8変換

			//新規シート作成			
			drawid=pl->newSheetWrite((UINT8*)newshdata, (UINT8*)uid, ro, styone, stytwo, wf, hatyu, (UINT8*)newshreldata);
			
			//draw xml作成
			uuid = GuidToString(guid);
			uid = uuid.c_str();
			pl->makedrawxml((UINT8*)drawdata, ro->rid, nullptr, wf, (UINT8*)drawreldata, (UINT8*)uid);

			ro = ro->next;
		}
		//delete pl->shar;
	}
	//app workbook 圧縮
	pl->ap->writeappfile();//データ書き込み
	pl->writecompress(pl->ap->wd, pl->ap->wl, wf, pl->cddataap);

	pl->wb->writeworkbook(); 
	pl->writecompress(pl->wb->wd, pl->wb->wl, wf, pl->cddatawb);

	//app workbook 書き込み
	delete pl->wb;
	delete pl->ap;

	//content_type 更新

	pl->endrecordwrite(wf);

	cr->freematchitem(pl->matchs);
	cr->freematchitem(pl->nomatch);
	free(inMainstr);
	delete cr;
	delete pl;

	fclose(wf);

	return;
}

char* CMFCApplication2Dlg::GetResouceOne() {
	HRSRC hrc;
	HGLOBAL hgb;
	LPVOID p;
	char* cs;

	hrc = FindResourceA(NULL, MAKEINTRESOURCEA(IDR_TEXT1), "TEXT");
	
	hgb = LoadResource(NULL, hrc);
	p = LockResource(hgb);

	cs = (char*)p;

	return cs;
}
//sheetrel テンプレート　読み込み
char* CMFCApplication2Dlg::GetResouceTwo() {
	HRSRC hrc;
	HGLOBAL hgb;
	LPVOID p;
	char* cs;

	hrc = FindResourceA(NULL, MAKEINTRESOURCEA(IDR_TEXT3), "TEXT");

	hgb = LoadResource(NULL, hrc);
	p = LockResource(hgb);

	cs = (char*)p;

	return cs;
}
//draw xml 読み込み
char* CMFCApplication2Dlg::GetResouceThree() {
	HRSRC hrc;
	HGLOBAL hgb;
	LPVOID p;
	char* cs;

	hrc = FindResourceA(NULL, MAKEINTRESOURCEA(IDR_TEXT2), "TEXT");

	hgb = LoadResource(NULL, hrc);
	p = LockResource(hgb);

	cs = (char*)p;

	return cs;
}
//drawrel xml 読み込み
char* CMFCApplication2Dlg::GetResouceFour() {
	HRSRC hrc;
	HGLOBAL hgb;
	LPVOID p;
	char* cs;

	hrc = FindResourceA(NULL, MAKEINTRESOURCEA(IDR_TEXT4), "TEXT");

	hgb = LoadResource(NULL, hrc);
	p = LockResource(hgb);

	cs = (char*)p;

	return cs;
}

void CMFCApplication2Dlg::OnBnClickedButton2()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	int i = 1;
	char urL[] = "https://image.rakuten.co.jp/kodomo-bee/cabinet/new95/shh01801-600r.jpg";
	char fn[] = "C:/Users/ryo19/OneDrive/デスクトップ/testcurlsystem.jpg";
	FILE* fp;

	CURL* curl;
	CURLcode res;
	char error[CURL_ERROR_SIZE];
	CString fv=_T("file_save");

	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, urL);

	fopen_s(&fp, fn, "wb");
	if (!fp) {
		perror("fopen");
	}
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error);

	// CURLOPT_WRITEFUNCTION が設定されてない //
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

	res = curl_easy_perform(curl);
	// curl 変数がクリアされていない //
	curl_easy_cleanup(curl);

	// fp2 は都度閉じないとリークする //
	fclose(fp);

	if (res != CURLE_OK) {
		fprintf(stderr, error);
	}
	fclose(fp);

	m_edit1 = fv;

	UpdateData(FALSE);

	return;
}


void CMFCApplication2Dlg::OnEnChangeEdit2()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。

	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
}


void CMFCApplication2Dlg::OnBnClickedButton3()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CFileDialog     plDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, NULL);

	if (plDlg.DoModal() == IDOK)
	{
		m_edit_in1 = plDlg.GetPathName();
		UpdateData(FALSE);
	}

	return;
}


void CMFCApplication2Dlg::OnBnClickedButton4()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	DialogTest dlg; // バージョン情報ダイアログのインスタンスを作成
	
	dlg.DoModal(); // モーダルで表示 
	f = dlg.f;
	fs = dlg.fs;
	fi = dlg.fi;
	fis = dlg.fis;
	bo = dlg.bo;
	bos = dlg.bos;
	sx = dlg.sx;
	sxs = dlg.sxs;
	cx = dlg.cx;
	cxs = dlg.cxs;
}


void CMFCApplication2Dlg::OnBnClickedButton5()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CFileDialog     plDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, NULL);

	if (plDlg.DoModal() == IDOK)
	{
		init_Edit_in1 = plDlg.GetPathName();
		UpdateData(FALSE);
	}

	return;
}

char* CMFCApplication2Dlg::CstringToChar(CString cs) {
	//CStringをTCHARにコピー
	size_t textSize = (cs.GetLength() * 2) + 1;
	//TCHARをcharに変換
	char* lpcText = new char[textSize];

	//TCHARにコピーを省略
	WideCharToMultiByte(CP_ACP, 0, cs.GetBuffer(), -1, lpcText, textSize, NULL, NULL);

	cs.ReleaseBuffer();//※忘れちゃダメ
	//delete[] tchrText;//TCHAR 解放

	return lpcText;
}

char* CMFCApplication2Dlg::SJIStoUTF8(char* szSJIS, char* bufUTF8, int size) {
	wchar_t bufUnicode[BUFSIZE];
	int lenUnicode = MultiByteToWideChar(CP_ACP, 0, szSJIS, strlen(szSJIS) + 1, bufUnicode, BUFSIZE);
	WideCharToMultiByte(CP_UTF8, 0, bufUnicode, lenUnicode, bufUTF8, size, NULL, NULL);
	return bufUTF8;
}
//uuid生成
std::string CMFCApplication2Dlg::GuidToString(GUID guid)
{
	// https://gist.github.com/vincenthsu/8fab51834e3a04074a57

	char guid_cstr[37];
	snprintf(guid_cstr, sizeof(guid_cstr),
		"%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
		guid.Data1, guid.Data2, guid.Data3,
		guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return std::string(guid_cstr);
}
