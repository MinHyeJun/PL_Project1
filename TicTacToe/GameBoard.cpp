#include "StdAfx.h"
#include "GameBoard.h"

/**
	�� �� : GameBoard()
	�� �� : GameBoard Ŭ������ ������, ������ �������, 
			���� �� ���� �迭�� �������� �޸� �Ҵ�����
*/
GameBoard::GameBoard()
{
	preMoves = new Position[16];  // ���� ���� ��ġ�� ������ �迭 �Ҵ�(�� �� �����⿡�� ������ �� ���¸� �����ϴ� ����)
	board = new char*[4];  // �������� 4�� �Ҵ�
	
	// �� �࿡ 4�� �Ҵ�
	for(int i=0; i<4; i++)
	{
		board[i] = new char[4];
	}
};

/**
	�� �� : GameBoard(const GameBoard& copy)
	�� �� : ���� �����ڷν�, ��Ī�� �˻翡�� �������� �����Ҷ�,
			���� �Ҵ��� ����� ���� ���縦 �� ���ְ� ����
*/
GameBoard::GameBoard(const GameBoard& copy)
{
	preMoves = new Position[16];  // ���� ���� ��ġ�� ������ �迭 �Ҵ�
	board = new char*[4];  // �������� 4�� �Ҵ�
	
    // �� �࿡ 4�� �Ҵ�
	for(int i=0; i<4; i++)
	{
		board[i] = new char[4];
	}

	// ���ڷ� ���� �������� ������ ������
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			board[i][j] = copy.board[i][j];

	// ���ڷ� ���� �������� ���� ���� ��ġ ������ ������
	for(int i=0; i<16; i++)
	{
		preMoves[i].x = copy.preMoves[i].x;
		preMoves[i].y = copy.preMoves[i].y;
	}

	// ���ڷ� ���� �����ǿ� ���� ���� ������ ������
	moveCnt = copy.moveCnt;  // ���� �� ������ ������
	state = copy.state;  // ���� ���� ���¸� ������
	starterCom = copy.starterCom;  // ���� ������ ���� ��ǻ�� ������ ������
	oppnentCom = copy.oppnentCom;  // ���� ��ǻ�� ���� ������
	startLevel = copy.startLevel;  // ������ ������ ��ǻ���� ���� ������ ������
	oppLevel = copy.oppLevel;  // ���� ��ǻ���� ���� ������ ������
};

/**
	�� �� : GetBoardStat()
	�� �� : ������ ���� ��ȯ
*/
int GameBoard::GetBoardStat()
{
	return state;
};

/**
	�� �� : InitBoard(int startCom, int movedCnt, int nlevelA, int nlevelB)
	�� �� : �ʱ�ȭ�� �ʿ��� ������ ���ڸ� �߽����� �������� �ʱ�ȭ���ִ� �Լ�
*/
void GameBoard::InitBoard(int startCom, int movedCnt, int nlevelB)
{
	moveCnt = movedCnt;		/* ��� ° ���� ���� */

	if(startCom == 0)		/* ���� ��ǻ�Ϳ� ��ǻ�� ������ ����, ���� ��ǻ�Ͱ� A�� ��� */
	{	
		starterCom = 'X';		oppnentCom = 'O';
		startLevel = 0;	        oppLevel = nlevelB;			
	}
	else  // ���� ��ǻ�Ͱ� B�� ���		
	{
		starterCom = 'O';		oppnentCom = 'X';
		startLevel = nlevelB;	oppLevel = 0;
	}

	if(movedCnt == 0)		/* �ҷ��� �������� ���θ� �˻��ؼ� ������ �ʱ�ȭ */
	{
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				board[i][j] = ' ';
	}
};

/**
	�� �� : RandomMove(int preX, int preY)
	�� �� : �����⸦ ���������� ������ ���Ҵ� ���� �ٸ����� ������ �����ϰ� ��ǥ����
*/
void GameBoard::RandomMove()
{
	int newX, newY;  // ���Ӱ� ���� �� �ڸ��� ��ǥ
	int preX, preY;  // ������ �� ���� ��ǥ
	bool overlap = true;  // �������� ��ǥ�� �̴� while���� ����
	srand(GetTickCount());
	
	UndoMove();  // board �迭�� ���Ҵ� ���� �� �ܰ� ���� ���·� �ǵ���
	
	// ������ ������ �� ���� ��ǥ�� ������
	preX = preMoves[moveCnt].x;  
	preY = preMoves[moveCnt].y;

	while(overlap)
	{
		// �������� ���Ӱ� �� ��ǥ�� ����
		newX = rand()%4;
		newY = rand()%4;

		if(moveCnt <= 14)	/* �� ��ǥ�� 2�� �̻��϶� */
		{
			if((newX != preX) && (newY != preY))	/* �������� ������ ��ǥ�� ������ǥ�� ���ϰ� */
				if(board[newX][newY] == ' ')		/* �ش� ��ǥ�� ����ִ� �������� �˻� */
					overlap = false;  // �������� ��ǥ�� �̴� while���� ����
		}
		else   // �� ��ǥ�� 1�� ���� ��� 
		{
			if(board[newX][newY] == ' ')   // ���ο� ��ǥ�� �� ��������(���� 1���� ��ǥ����) �˻�
				overlap = false;  // �������� ��ǥ�� �̴� while���� ����
		}			
	}		
	DoMove(newX, newY);  // ���ο� ��ǥ�� ���� ��
};

/**
	�� �� : DoMove(int x, int y)
	�� �� :	�Է¹��� ��ǥ������ �����ǿ� ���� ��
*/
void GameBoard::DoMove(int x, int y)
{
	if( moveCnt%2 == 0 )			/* ���� �������� �˻��Ͽ� �ش� ��ǥ�� �ش� ���� ��ǻ���� ���� board �迭�� �� */
		board[x][y] = starterCom;
	else
		board[x][y] = oppnentCom;
	
	//���� ���� ��ǥ�� �����ϴ� �迭���� ���Ӱ� �� ���� ��ǥ�� ����
	preMoves[moveCnt].x = x;
	preMoves[moveCnt].y = y;

	moveCnt++;						/* ���� ���� ���� ��Ŵ */
};

/**
	�� �� : UndoMove()
	�� �� : ���Ҵ� ���� �Ѵܰ� �������·� �������� �Լ�
*/
void GameBoard::UndoMove()
{
	moveCnt--;  // ���� �� �ϳ� ����
	board[preMoves[moveCnt].x][preMoves[moveCnt].y] = ' ';  // �� ���� board �迭 �󿡼� �ʱ�ȭ
}

/**
	�� �� : CheckState()
	�� �� : ���� �������� ����, �����̰����, �������� �˻��ؼ� ���°��� �������ִ� �Լ�
*/
void GameBoard::CheckState()
{
	char temp[4][4];
	int i;

	for(i=0; i<4; i++)				
	{	
		/* ���� ������ �˻� */
		if(board[i][0]!=' ')  // i���� ù ���� ������� �ʴٸ�
		{
			if((board[i][0]=='X') && (board[i][1]=='X') && (board[i][2]=='X') && (board[i][3]=='X'))  // i���� ��� X�� ���
			{
				state = STATE_WINA;  // ��ǻ�� A�� ��
				return;
			}
			if((board[i][0]=='O') && (board[i][1]=='O') && (board[i][2]=='O') && (board[i][3]=='O'))  // i���� ��� O�� ���
			{
				state = STATE_WINB;  // ��ǻ�� B�� ��
				return;
			}
		}

		/* ���� ������ �˻� */
		if(board[0][i]!=' ')  // i���� ù ���� ������� �ʴٸ�
		{
			if((board[0][i]=='X') && (board[1][i]=='X') && (board[2][i]=='X') && (board[3][i]=='X'))  // i���� ��� X�� ���
			{
				state = STATE_WINA;  // ��ǻ�� A�� ��
				return;
			}
			if((board[0][i]=='O') && (board[1][i]=='O') && (board[2][i]=='O') && (board[3][i]=='O'))  // i���� ��� O�� ���
			{
				state = STATE_WINB;  // ��ǻ�� B�� ��
				return;
			}
		}
	}
		
	if((board[0][0]!=' ')&&(board[0][0]==board[1][1])&&(board[0][0]==board[2][2])&&(board[0][0]==board[3][3]))	/* ù��° �밢���� ��� ������ Text�� ������ �ִٸ� */
	{
		if(board[0][0]=='X')  // �� Text�� X���
		{
			state = STATE_WINA;  // ��ǻ�� A�� ��
			return;
		}
		else  // �� Text�� O���
		{
			state = STATE_WINB;  // ��ǻ�� B�� ��
			return;
		}
	}
	
	if((board[0][3]!=' ')&&(board[0][3]==board[1][2])&&(board[0][3]==board[2][1])&&(board[0][3]==board[3][0])) /* �ι�° �밢���� ��� ������ Text�� ������ �ִٸ� */
	{
		if(board[0][3]=='X')  // �� Text�� X���
		{
			state = STATE_WINA;  // ��ǻ�� A�� ��
			return;
		}
		else  // �� Text�� O���
		{
			state = STATE_WINB;  // ��ǻ�� B�� ��
			return;
		}
	}

	if( moveCnt > 15 )  // ���� ���ǿ� ��� �ش����� ������ ��� ���� �ξ����� ��
	{
		state = STATE_DRAW;		/* ��� */
	}
};