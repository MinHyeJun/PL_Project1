
// TicTacToeDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "TicTacToe.h"
#include "TicTacToeDlg.h"
#include "afxdialogex.h"
#include "FileDlg.h"
#include <crtdbg.h>


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTicTacToeDlg 대화 상자

CTicTacToeDlg::CTicTacToeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTicTacToeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTicTacToeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_UNDO_A, m_undoA);
	DDX_Control(pDX, IDC_COMBO_B, m_comboB);
	DDX_Control(pDX, IDC_EDIT_B, m_listB);
}

BEGIN_MESSAGE_MAP(CTicTacToeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CTicTacToeDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CTicTacToeDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CTicTacToeDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CTicTacToeDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_UNDO_A, &CTicTacToeDlg::OnBnClickedButtonUndoA)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_A1, &CTicTacToeDlg::OnBnClickedA1)
	ON_BN_CLICKED(IDC_A2, &CTicTacToeDlg::OnBnClickedA2)
	ON_BN_CLICKED(IDC_A3, &CTicTacToeDlg::OnBnClickedA3)
	ON_BN_CLICKED(IDC_A4, &CTicTacToeDlg::OnBnClickedA4)
	ON_BN_CLICKED(IDC_A5, &CTicTacToeDlg::OnBnClickedA5)
	ON_BN_CLICKED(IDC_A6, &CTicTacToeDlg::OnBnClickedA6)
	ON_BN_CLICKED(IDC_A7, &CTicTacToeDlg::OnBnClickedA7)
	ON_BN_CLICKED(IDC_A8, &CTicTacToeDlg::OnBnClickedA8)
	ON_BN_CLICKED(IDC_A9, &CTicTacToeDlg::OnBnClickedA9)
	ON_BN_CLICKED(IDC_A10, &CTicTacToeDlg::OnBnClickedA10)
	ON_BN_CLICKED(IDC_A11, &CTicTacToeDlg::OnBnClickedA11)
	ON_BN_CLICKED(IDC_A12, &CTicTacToeDlg::OnBnClickedA12)
	ON_BN_CLICKED(IDC_A13, &CTicTacToeDlg::OnBnClickedA13)
	ON_BN_CLICKED(IDC_A14, &CTicTacToeDlg::OnBnClickedA14)
	ON_BN_CLICKED(IDC_A15, &CTicTacToeDlg::OnBnClickedA15)
	ON_BN_CLICKED(IDC_A16, &CTicTacToeDlg::OnBnClickedA16)
END_MESSAGE_MAP()


// CTicTacToeDlg 메시지 처리기

BOOL CTicTacToeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_hAccelTable = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));

	GetDlgItem(IDC_BUTTON_UNDO_A)->EnableWindow(false);  // 한 수 무르기 버튼의 접근을 false로 변경
	m_BKColor = CreateSolidBrush(RGB(255, 255, 255));

	m_isLoad = 0;  // 게임 로드 여부 초기화
	m_checkUndo = 0;  // 무르기 여부 초기화
	m_startCom = 0;  // 시작하는 플레이어는 사용자로 고정

	SetGame();  // 게임 셋팅
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTicTacToeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

BOOL CTicTacToeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.	 
	if (m_hAccelTable != NULL)
    {
		if (TranslateAccelerator(m_hWnd, m_hAccelTable, pMsg))
		{
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CTicTacToeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTicTacToeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

HBRUSH CTicTacToeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if(pWnd->GetDlgCtrlID() == IDC_EDIT_A)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_BKColor;
	}

	if(pWnd->GetDlgCtrlID() == IDC_EDIT_B)
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0, 0, 0));
		return m_BKColor;
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

//끝내기 버튼 클릭 시 호출 함수
void CTicTacToeDlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int conclusion;  // 메세지박스로부터 입력을 받기 위한 변수

	if (m_board.state == GameBoard::STATE_PLAY)  // 현재 게임판 상태가 플레이중이라면 
	{
		conclusion = MessageBox(L"현재 게임중입니다.\n게임을 종료 하시겠습니까?", L"게임 끝내기", MB_OKCANCEL);
		if (conclusion == IDOK)  // OK 버튼을 눌렀다면 현재 게임판 상태를 멈춤으로 변경 후 종료
		{
			m_board.state = GameBoard::STATE_STOP;
			AfxGetMainWnd()->PostMessageW(WM_QUIT);
		}
	}
	else  // 현재 게임판 상태가 플레이 중이 아니라면
	{  
		conclusion = MessageBox(L"게임을 종료 하시겠습니까?", L"게임 종료", MB_OKCANCEL);
		if(conclusion == IDOK)  // OK 버튼을 눌렀다면 프로그램을 종료함
			AfxGetMainWnd()->PostMessageW(WM_QUIT);
	}
}

// 컴퓨터 A의 한 수를 무르기 버튼 클릭 시 호출 함수 
void CTicTacToeDlg::OnBnClickedButtonUndoA()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 사용자와 컴퓨터의 수를 하나씩 무르기
	m_board.UndoMove();
	m_board.UndoMove();

	m_board.order = 1;  // 수를 무른 게임판 정보를 토대로 컴퓨터의 게임판을 업데이트
	UpdateGame();

	m_board.order = 0;  // 수를 무른 게임판 정보를 토대로 사용자의 게임판을 업데이트
	UpdateGame();

	GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"한 수 무르기를 사용하였습니다.");

	if (m_board.moveCnt - m_loadMoveCnt < 2)  // 현재 게임에서 두어진 수가 2개 미만일 때 한 수 무르기 사용 불가
		m_undoA.EnableWindow(false);
}

// 게임 시작 버튼 클릭 시 호출 함수
void CTicTacToeDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int conclusion;

	if (m_board.state == GameBoard::STATE_PLAY)  // 현재 게임판 상태가 플레이중이라면 
	{
		conclusion = MessageBox(L"현재 게임중입니다.\n게임을 다시 시작하시겠습니까?", L"새 게임", MB_OKCANCEL);
		if (conclusion == IDOK)  // OK 버튼을 눌렀다면 현재 게임판 상태를 멈추고 다시 시작
		{
			m_board.state = GameBoard::STATE_STOP;
			StartGame();
		}
	}
	else
		StartGame();  // 게임 시작 함수 호출
}

// 저장하기 버튼 클릭 시 호출 함수
void CTicTacToeDlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SaveGame();  // 게임 저장 함수 호출
}

// 게임 불러오기 버튼 클릭 시 호출 함수
void CTicTacToeDlg::OnBnClickedButtonLoad()
{
	if (m_board.state == GameBoard::STATE_PLAY)  // 게임 플레이 중이라면
	{
		int conclusion = MessageBox(L"현재 게임중입니다.\n게임을 중단하고 불러오시겠습니까?", L"불러오기", MB_OKCANCEL);
		if (conclusion == IDOK)  // OK 버튼을 눌렀다면 현재 게임판 상태를 멈춤으로 변경 후 불러오기
		{
			m_board.state = GameBoard::STATE_STOP;
			m_undoA.EnableWindow(FALSE);
			LoadGame();  // 게임 불러오기 함수 호출
		}
	}
	else
	{
		LoadGame();
	}
}

//게임이 시작될 준비가 되었는지 확인하는 함수
int CTicTacToeDlg::CheckReady()
{
	UpdateData(TRUE);

	int level_b = m_comboB.GetCurSel();  // 컴퓨터의 선택된 레벨 정보 가져오기

	if(level_b == -1)  // 레벨이 선택되지 않았다면
		return -1;  // 레벨 선택이 되어 있지 않음: -1
	else if(m_startCom == -1)  // 선공 플레이어가 정해지지 않았다면
		return 0;  // 선공이 선택되지 않음: 0
	else
	{
		switch(level_b)  // 선택된 레벨 정보에 따라 컴퓨터의 레벨 셋팅
		{
		case 0 : m_levelB = 3; break;			
		case 1 : m_levelB = 5; break;			
		
		}

		return 1;  // 게임 시작 준비가 되어있음: 1
	}	
}

// 게임 시작 전 셋팅하는 함수
void CTicTacToeDlg::SetGame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 컴퓨터의 evaluate 레벨 선택 콤보박스에 레벨 셋팅
	m_comboB.AddString(L"Level 3");
	m_comboB.AddString(L"Level 5");

	// 상태창에 초기 텍스트를 셋팅
	GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"게임 시작을 위해 새 게임을 눌러주세요.");

	// 디폴트로 레벨 3
	m_comboB.SetCurSel(0);
	m_levelB = 3;
}

/**
	함 수 : StartGame()
	기 능 : 게임 시작 버튼을 눌렀을때 실행하는 함수로써, 기본적으로
			게임이 시작되기전 옵션 설정이 준비되었는지 체크하고, 추가적으로 불러온 
			게임판인지 여부를 검사해서 게임판을 초기화 시켜줌. 
			설정이 완료되면 게임이 끝날때까지 게임판을 진행 함
*/
void CTicTacToeDlg::StartGame()
{
	int checkErr;				/* 에러 종류를 알려주는 변수 */

	checkErr = CheckReady();	/* 게임을 시작할 준비 되었는지 검사 */
	if(checkErr == 1)			/* 리턴값이 1이면 준비 완료 */
	{
		if(m_isLoad!=0)			/* 불러온 게임이라면, */
		{						/* 불러온 게임 정보로 보드판 초기화 */
			m_board.InitBoard(m_startCom, m_isLoad, m_levelB);	
			m_isLoad = 0;  // 게임 로드상태 초기화(다음 불러오기를 위해)
		}
		else
		{
			m_board.InitBoard(m_startCom, 0, m_levelB);	/* 아니라면, 새로운 판으로 초기화 */
			m_board.order = 0;  // 사용자부터 게임을 시작하기 때문에 게임 순서 사용자로 셋팅
			m_loadMoveCnt = 0;  // 불러오기를 통해 불러온 수가 없으므로 0으로 초기화
		}

		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"게임을 시작합니다.");
		UpdateGame();  // 게임판을 화면으로 보여주는 함수 호출

		m_undoA.EnableWindow(FALSE);  // 한 수 무르기 버튼 접근 불가

		m_board.state = GameBoard::STATE_PLAY;						/* 보드판 상태를 플레이 중으로 변경 */

		if(m_board.order == 1)  // 게임 순서가 컴퓨터라면
			PlayAI();  // 컴퓨터 AI 플레이
	}
	else if(checkErr == -1)	/* 레벨 설정이 안되어있을때 오류 출력 */
	{
		MessageBox(L"ERROR : LA-Level 설정을 확인하세요!", L"Error!", MB_ICONERROR);
	}
	else					/* 시작 순서 설정이 안되어있을때 오류 출력 */
		MessageBox(L"ERROR : 시작순서 설정을 확인하세요!", L"Error!", MB_ICONERROR);
}

// 컴퓨터가 플레이하기 위한 함수
void CTicTacToeDlg::PlayAI()
{
	m_undoA.EnableWindow(false);

	TicTacToeAI* tttAI = new TicTacToeAI(m_board);	/* 새로운 AI 객체를 생성 */

	tttAI->GetBestMove();							/* 최적의 좌표를 구함 */
	m_board.DoMove(tttAI->bestX, tttAI->bestY);		/* 해당 좌표에 수를 둠 */

	Node* node = tttAI->GetRootNode();			/* 최적의 좌표를 구하는동안 저장한 트리 중 루트노드 반환 */
	this->PrintTreeNode(node);					/* 트리 출력 */

	UpdateGame();							/* 게임판 업데이트 */

	delete node;  // 위에서 생성한 node 객체 반환
	delete tttAI;  // 위에서 생성한 AI 객체 반환

	m_board.CheckState();			/* 게임판 상태를 점검 */
	if (m_board.state != GameBoard::STATE_PLAY)  // 게임이 끝났다면
	{
		EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
		UpdateGame();	/* 상대방 보드판에도 출력 */
	}
	else  // 게임이 끝나지 않았다면
	{
		m_board.order = 0;  // 사용자의 플레이 차례
		UpdateGame();  // 사용자의 게임판의 정보를 업데이트
		m_undoA.EnableWindow(true);
	}
}

/**
	함 수 : PrintTreeNode(Node* root)
	기 능 : AI를 통해서 최적의 좌표를 구하는동안의 Eval 값을 저장한 노드들로 구성된
		   트리를 자료구조 큐를 이용해 너비우선 탐색으로 Edit Box에 출력해주는 함수
*/
void CTicTacToeDlg::PrintTreeNode(Node* root)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int preDepth = 0;			/* 이전 노드의 깊이 */
	bool preParent = false;		/* 부모가 같은지 여부 점검 */
	Node *pNode = root;			/* 루트노드를 복사 */
	CString temp, temp2;        // temp: 출력할 문자열, temp2: temp에 evaluation 값을 넣는 것을 도와줄 문자열
	queue <Node* > que;			/* 큐 생성 */

	que.push(pNode);			/* 큐에 루트노드를 넣고 */
	while (!que.empty())			/* 큐가 비어있을 때 까지 출력 */
	{
		pNode = que.front();	/* 앞에서 꺼내서 */
		que.pop();
		if (pNode != NULL)		/* NULL 값이 아니고 */
		{
			if (preDepth != pNode->depth)	/* 이전 노드값과 깊이가 다르면 */
				temp = temp + (L"\r\n");	/* 개행 */

			if (preParent)					/* 부모노드가 같으면 */
				temp = temp + (L", ");		/* 이어서 출력 */
			else
				temp = temp + (L"(");		/* 다르면 '(' 로 구분 */

			temp2.Format(L"%d", pNode->eval);
			temp = temp + temp2;

			preParent = true;

			if (pNode->childCnt != 0)		/* 자식노드 개수가 0이 아니면 */
			{
				que.push(NULL);				/* NULL 값으로 부모노드 구분 해주고 */
				for (int j = 0; j < pNode->childCnt; j++)
					que.push(pNode->next[j]);		/* 자식노드를 큐에 넣음 */

			}
			preDepth = pNode->depth;				/* 노드 깊이를 변경 */
		}
		else							/* 큐에서 꺼낸게 NULL 값 이라면 */
		{
			temp = temp + (L")");		/* ')' 로 부모노드를 구분 */
			preParent = false;
		}
	}
	temp = temp + (L")");

	if (m_board.order == 0)  // 시작한 플레이어가 사용자라면
	{
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"<게임 트리>");
	}
	else  // 시작한 플레이어가 컴퓨터라면
	{
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(temp);
	}
}

/**
	함 수 : ResetGame()
	기 능 : 게임판을 재 초기화 시키는 함수
*/
void CTicTacToeDlg::ResetGame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString tempStr, str;
	int count = 0;  // 게임 보드판의 버튼을 숫자로 바꾸기 위해 숫자를 담는 변수

	m_startCom = 0;  // 시작한 플레이어 종류 초기화
	m_board.order = 0;  // 현재 게임 차례를 사용자로 초기화
	UpdateData(FALSE);

	m_board.state = GameBoard::STATE_INIT;  // 게임 상태를 초기화로 지정
	m_board.InitBoard(m_startCom, 0, m_levelB);  // 게임 보드판 상태를 초기화

	// 게임보드판 버튼을 O,X에서 다시 숫자로 변경
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			str.Format(L"%d", count+1);
			SetDlgItemText(1001+count, str);
			SetDlgItemText(1017+count, str);
			count++;
		}
	}

	// 게임 상태창 초기화
	GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"<게임 트리>");
	// 한 수 무르기 버튼의 접근을 false로 변경
	m_undoA.EnableWindow(FALSE);
	// 컴퓨터 레벨 선택 초기화
	m_comboB.SetCurSel(0);
	m_levelB = 3;
}

/**
	함 수 : EndGame()
	기 능 : 게임을 종료시키고 해당 게임판 상태에따라 Edit Box에 결과값을
		    출력해주는 함수 
*/
void CTicTacToeDlg::EndGame()
{
	switch(m_board.state)  // 게임의 상태를 체크하여 결과를 출력
	{
	case GameBoard::STATE_WINA :  // 플레이어가 이긴 경우
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"게임에 이겼습니다.");
		break;

	case GameBoard::STATE_WINB :  // 컴퓨터가 이긴 경우
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"게임에 졌습니다.");
		break;
		
	case GameBoard::STATE_DRAW :  // 비긴 경우
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"게임에 비겼습니다.");
		break;

	case GameBoard::STATE_INIT :  // 게임을 초기화 한 경우
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"<게임 트리>");
		break;
	
	case GameBoard::STATE_STOP :  // 게임을 중단한 경우
		GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"게임이 중단됬습니다.");
		break;		
	}
	// 게임이 끝났으므로 한 수 무르기 버튼의 접근을 False로 변경
	m_undoA.EnableWindow(FALSE);
}

/**
	함 수 : UpdateGame()
	기 능 : 해당 게임판을 화면으로 업데이트 해주는 함수
*/
void CTicTacToeDlg::UpdateGame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int count = 0;  // 텍스트정보를 변경할 버튼 지정하기 위한 일종의 index
	int comButton = 0;  // 변경할 게임판의 첫번째 버튼 아이디 정보를 저장하기 위한 변수
	CString str;

	// 게임판 정보를 화면에 업데이트할 플레이어 게임판 버튼의 첫번째 버튼 아이디정보를 얻어옴
	if (m_board.order == 0)  // 플레이할 차례가 사용자라면
		comButton = IDC_A1;
	else  // 시작한 플레이어가 컴퓨터라면
		comButton = IDC_B1;

	// 게임판 보드 정보를 게임판 버튼에 적용, 숫자 -> O or X
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_board.board[i][j] == 'X')  // X인 경우 count번째 버튼의 text를 X로 변경
				SetDlgItemText(comButton + count, L"X");
			else if (m_board.board[i][j] == 'O')  // O인 경우 count번째 버튼의 text를 O로 변경
				SetDlgItemText(comButton + count, L"O");
			else  // X나 O가 아니라면 다시 숫자로 적용
			{
				str.Format(L"%d", count + 1);
				SetDlgItemText(comButton + count, str);
			}
			count++;
		}
	}

	// 게임이 플레이 상태가 아닐 경우, 게임판 정보를 사용자, 플레이어 둘 다 동일하게 적용
	// 위와 동일한 방법
	count = 0;
	if (m_board.state != GameBoard::STATE_PLAY)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				if (m_board.board[i][j] == 'X')
				{
					SetDlgItemText(IDC_A1 + count, L"X");
					SetDlgItemText(IDC_B1 + count, L"X");
				}
				else if (m_board.board[i][j] == 'O')
				{
					SetDlgItemText(IDC_A1 + count, L"O");
					SetDlgItemText(IDC_B1 + count, L"O");
				}
				else
				{
					str.Format(L"%d", count + 1);
					SetDlgItemText(IDC_A1 + count, str);
					SetDlgItemText(IDC_B1 + count, str);
				}
				count++;
			}
		}
	}
}

// 게임판 정보를 파일로 저장하는 함수
void CTicTacToeDlg::SaveGame()
{
	CFileDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		FILE *fp;						/* 파일 포인터 선언 */
		CStringA name(dlg.m_fileStr);

		if (!(fp = fopen(name, "w")))  // 파일을 열 수 없을 때
		{
			MessageBox(L"파일을 저장할 수 없습니다! 파일명을 확인하세요.", L"ERROR", MB_ICONERROR);
			return;
		}
		else		/* 제대로 열린 파일이라면 */
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					if (m_board.board[i][j] == 'X')  // 해당 위치의 정보가 X라면
						fprintf(fp, "X");  // X를 파일에 출력
					else if (m_board.board[i][j] == 'O')  // 해당 위치의 정보가 O라면
						fprintf(fp, "O");  // O를 파일에 출력
					else  // X도, O도 아니라면
						fprintf(fp, "B");  // B를 파일에 출력
				}
				fprintf(fp, "\n");  // 한 행의 정보가 다 입력되면 개행 입력
			}
			fclose(fp);
			GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"게임을 저장했습니다.");
		}
	}
}


/**
	함 수 : LoadGame()
	기 능 : 게임을 불러왔을때 해당 게임판 정보를 화면에 업데이트 해주는 함수
*/
void CTicTacToeDlg::LoadGame()
{
	CFileDlg dlg;

	if(m_board.state == GameBoard::STATE_PLAY)	/* 불러오는 시점이 게임중인지를 검사 */
	{
		MessageBox(L"지금은 게임중입니다! 종료하고 시도하세요.", L"경 고", MB_ICONEXCLAMATION);
		return;
	}

	if(dlg.DoModal()==IDOK)
	{		
		m_board.state = GameBoard::STATE_STOP;  //게임을 중지상태로 변경

		FILE *fp;						/* 파일 포인터 선언 */
		CStringA name(dlg.m_fileStr);

		if(!(fp = fopen(name, "r")))  // 파일을 열 수 없을 때
		{
			MessageBox(L"파일을 열 수 없습니다! 파일명을 확인하세요.", L"ERROR", MB_ICONERROR);
			return;
		}
		else		/* 제대로 열린 파일이라면 */
		{
			int i, j, stoneCount=0;
			int Acnt = 0 , Bcnt = 0;  // 사용자와 컴퓨터가 둔 수의 개수를 비교하기 위한 변수
			char temp[5];  // 파일에 저장된 내용을 읽어들이기 위한 문자열

			for(i=0; i<4; i++)
			{
				fscanf_s(fp, "%s", temp, 5);	/* 해당파일에서 한줄을 읽은뒤 */
				for(j=0; j<4; j++)				/* 문자에 맞게 게임판에 입력 */
				{				
					if(temp[j] == 'X')			
					{
						m_board.board[i][j] = 'X';
						Acnt++;
					}						
					else if(temp[j] == 'O')
					{
						m_board.board[i][j] = 'O';
						Bcnt++;
					}
					else
						m_board.board[i][j] = ' ';
				}
			}

			UpdateData(FALSE);
			m_loadMoveCnt = m_isLoad = Acnt + Bcnt;  // 게임 로드 여부 저장
			m_board.moveCnt = m_isLoad;
			UpdateGame();  // 게임판 정보를 버튼에 적용
			// 두 게임 상태창을 초기화

			
			m_board.CheckState();  // 불러온 게임이 이미 종료된 게임인지 확인

			if (m_board.state != GameBoard::STATE_DRAW && m_board.state != GameBoard::STATE_WINA && m_board.state != GameBoard::STATE_WINB)  // 게임이 끝나지 않았다면
			{
				GetDlgItem(IDC_EDIT_B)->SetWindowTextW(L"게임을 불러왔습니다.");
				

				if (Acnt > Bcnt)			/* 'X'와 'O' 문자 개수를 비교 */
				{
					m_board.order = 1;      /* A가 크면 컴퓨터의 차례*/
				}
				else
				{
					m_board.order = 0;          /* 동일하면 사용자의 차례 */
				}
			}
			else  // 이미 끝난 게임이라면
			{
				EndGame(); 
				m_isLoad = 0;
			}

			fclose(fp);
		}
	}
}

// OnBnClickedA1~16 사용자가 플레이하기 위해 게임판 버튼의 클릭 함수
void CTicTacToeDlg::OnBnClickedA1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[0][0] == ' ')
	{
		GetDlgItem(IDC_A1)->SetWindowTextW(L"X");
		m_board.DoMove(0, 0);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}

void CTicTacToeDlg::OnBnClickedA2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[0][1] == ' ')
	{
		GetDlgItem(IDC_A2)->SetWindowTextW(L"X");
		m_board.DoMove(0, 1);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[0][2] == ' ')
	{
		GetDlgItem(IDC_A3)->SetWindowTextW(L"X");
		m_board.DoMove(0, 2);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[0][3] == ' ')
	{
		GetDlgItem(IDC_A4)->SetWindowTextW(L"X");
		m_board.DoMove(0, 3);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA5()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[1][0] == ' ')
	{
		GetDlgItem(IDC_A5)->SetWindowTextW(L"X");
		m_board.DoMove(1, 0);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA6()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[1][1] == ' ')
	{
		GetDlgItem(IDC_A6)->SetWindowTextW(L"X");
		m_board.DoMove(1, 1);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA7()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[1][2] == ' ')
	{
		GetDlgItem(IDC_A7)->SetWindowTextW(L"X");
		m_board.DoMove(1, 2);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA8()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[1][3] == ' ')
	{
		GetDlgItem(IDC_A8)->SetWindowTextW(L"X");
		m_board.DoMove(1, 3);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA9()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[2][0] == ' ')
	{
		GetDlgItem(IDC_A9)->SetWindowTextW(L"X");
		m_board.DoMove(2, 0);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA10()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[2][1] == ' ')
	{
		GetDlgItem(IDC_A10)->SetWindowTextW(L"X");
		m_board.DoMove(2, 1);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA11()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[2][2] == ' ')
	{
		GetDlgItem(IDC_A11)->SetWindowTextW(L"X");
		m_board.DoMove(2, 2);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA12()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[2][3] == ' ')
	{
		GetDlgItem(IDC_A12)->SetWindowTextW(L"X");
		m_board.DoMove(2, 3);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA13()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[3][0] == ' ')
	{
		GetDlgItem(IDC_A13)->SetWindowTextW(L"X");
		m_board.DoMove(3, 0);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA14()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[3][1] == ' ')
	{
		GetDlgItem(IDC_A14)->SetWindowTextW(L"X");
		m_board.DoMove(3, 1);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA15()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[3][2] == ' ')
	{
		GetDlgItem(IDC_A15)->SetWindowTextW(L"X");
		m_board.DoMove(3, 2);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}


void CTicTacToeDlg::OnBnClickedA16()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_board.state == GameBoard::STATE_PLAY && m_board.order == 0 && m_board.board[3][3] == ' ')
	{
		GetDlgItem(IDC_A16)->SetWindowTextW(L"X");
		m_board.DoMove(3, 3);
		UpdateGame();

		m_board.CheckState();			/* 게임판 상태를 점검 */
		if (m_board.state != GameBoard::STATE_PLAY)
		{
			EndGame();					/* 플레이 중이 아닌 상태면 게임 종료 */
			UpdateGame();	/* 상대방 보드판에도 출력 */
		}
		else
		{
			m_board.order = 1;
			PlayAI();
		}
	}
}

