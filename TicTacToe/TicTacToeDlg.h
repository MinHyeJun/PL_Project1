
// TicTacToeDlg.h : ��� ����
//

#pragma once

#include "TicTacToeAI.h"
#include <iostream>
#include <queue>

using namespace std;
// CTicTacToeDlg ��ȭ ����
class CTicTacToeDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTicTacToeDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TICTACTOE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonInit();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButtonUndoA();
	virtual BOOL PreTranslateMessage(MSG* pMsg);	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	HACCEL m_hAccelTable;
	CButton m_undoA;  // ��ǻ�� A�� ������ ��ư
	CComboBox m_comboB;  // ��ǻ�� B�� ���� ���� �޺��ڽ�
	CEdit m_listB;  // ��ǻ�� B�� ����â
	HBRUSH m_BKColor;

	/* ����� ���� �Լ� */

	void SetGame();			/* ���� �ʱ� ȭ�� ���� */
	int CheckReady();		/* ���� ���� �غ� ���¸� �˻� */
	int WaitUndo();			/* �����⸦ ��ٸ� */
	void UpdateGame();		/* ���� ���� ȭ�鿡 ������Ʈ */
	void ResetGame();		/* �������� �ٽ� �ʱ�ȭ */
	void PrintTreeNode(Node* root);	/* eval �� ������ ��� */
	void StartGame();			/* ���� ���� */
	void EndGame();				/* ���� ���� */
	void LoadGame();			/* ���� �ҷ����� */

	/*	����� ���� ���� */

	GameBoard m_board;		/* ���� ���� ���� */
	int m_levelB;			/* ��ǻ�� B�� LA-level */
	int m_startCom;			/* �����ϴ� COM ���� */
	int m_isLoad;			/* ������ �ε� �� ���� ���� */
	int m_checkUndo;		/* �����⸦ �ߴ��� ���� ���� */
	void PlayAI();
	afx_msg void OnBnClickedA1();
	afx_msg void OnBnClickedA2();
	afx_msg void OnBnClickedA3();
	afx_msg void OnBnClickedA4();
	afx_msg void OnBnClickedA5();
	afx_msg void OnBnClickedA6();
	afx_msg void OnBnClickedA7();
	afx_msg void OnBnClickedA8();
	afx_msg void OnBnClickedA9();
	afx_msg void OnBnClickedA10();
	afx_msg void OnBnClickedA11();
	afx_msg void OnBnClickedA12();
	afx_msg void OnBnClickedA13();
	afx_msg void OnBnClickedA14();
	afx_msg void OnBnClickedA15();
	afx_msg void OnBnClickedA16();
};
