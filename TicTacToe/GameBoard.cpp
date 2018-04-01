#include "StdAfx.h"
#include "GameBoard.h"

/**
	함 수 : GameBoard()
	기 능 : GameBoard 클래스의 생성자, 게임판 멤버변수, 
			이전 수 저장 배열을 동적으로 메모리 할당해줌
*/
GameBoard::GameBoard()
{
	preMoves = new Position[16];  // 이전 수의 위치를 저장할 배열 할당(한 수 무르기에서 무르기 전 상태를 저장하는 역할)
	board = new char*[4];  // 게임판의 4행 할당
	
	// 각 행에 4열 할당
	for(int i=0; i<4; i++)
	{
		board[i] = new char[4];
	}
};

/**
	함 수 : GameBoard(const GameBoard& copy)
	기 능 : 복사 생성자로써, 대칭성 검사에서 게임판을 복사할때,
			동적 할당을 고려한 깊은 복사를 할 수있게 해줌
*/
GameBoard::GameBoard(const GameBoard& copy)
{
	preMoves = new Position[16];  // 이전 수의 위치를 저장할 배열 할당
	board = new char*[4];  // 게임판의 4행 할당
	
    // 각 행에 4열 할당
	for(int i=0; i<4; i++)
	{
		board[i] = new char[4];
	}

	// 인자로 들어온 게임판의 정보를 복사함
	for(int i=0; i<4; i++)
		for(int j=0; j<4; j++)
			board[i][j] = copy.board[i][j];

	// 인자로 들어온 게임판의 이전 수의 위치 정보를 복사함
	for(int i=0; i<16; i++)
	{
		preMoves[i].x = copy.preMoves[i].x;
		preMoves[i].y = copy.preMoves[i].y;
	}

	// 인자로 들어온 게임판에 대한 세부 정보를 복사함
	moveCnt = copy.moveCnt;  // 현재 수 개수를 복사함
	state = copy.state;  // 현재 게임 상태를 복사함
	starterCom = copy.starterCom;  // 현재 게임의 시작 컴퓨터 정보를 복사함
	oppnentCom = copy.oppnentCom;  // 상대방 컴퓨터 정보 복사함
	startLevel = copy.startLevel;  // 게임을 시작한 컴퓨터의 레벨 정보를 복사함
	oppLevel = copy.oppLevel;  // 상대방 컴퓨터의 레벨 정보를 복사함
};

/**
	함 수 : GetBoardStat()
	기 능 : 게임판 상태 반환
*/
int GameBoard::GetBoardStat()
{
	return state;
};

/**
	함 수 : InitBoard(int startCom, int movedCnt, int nlevelA, int nlevelB)
	기 능 : 초기화에 필요한 정보를 인자를 중심으로 게임판을 초기화해주는 함수
*/
void GameBoard::InitBoard(int startCom, int movedCnt, int nlevelB)
{
	moveCnt = movedCnt;		/* 몇번 째 수를 저장 */

	if(startCom == 0)		/* 시작 컴퓨터와 컴퓨터 레벨을 설정, 시작 컴퓨터가 A인 경우 */
	{	
		starterCom = 'X';		oppnentCom = 'O';
		startLevel = 0;	        oppLevel = nlevelB;			
	}
	else  // 시작 컴퓨터가 B인 경우		
	{
		starterCom = 'O';		oppnentCom = 'X';
		startLevel = nlevelB;	oppLevel = 0;
	}

	if(movedCnt == 0)		/* 불러온 게임인지 여부를 검사해서 보드판 초기화 */
	{
		for(int i=0; i<4; i++)
			for(int j=0; j<4; j++)
				board[i][j] = ' ';
	}
};

/**
	함 수 : RandomMove(int preX, int preY)
	기 능 : 무르기를 시전했을때 이전에 놓았던 수와 다른곳에 놓도록 랜덤하게 좌표생성
*/
void GameBoard::RandomMove()
{
	int newX, newY;  // 새롭게 수를 둘 자리의 좌표
	int preX, preY;  // 이전에 둔 수의 좌표
	bool overlap = true;  // 랜덤으로 좌표를 뽑는 while문을 제어
	srand(GetTickCount());
	
	UndoMove();  // board 배열을 놓았던 수를 한 단계 이전 상태로 되돌림
	
	// 무르기 직전에 둔 수의 좌표를 저장함
	preX = preMoves[moveCnt].x;  
	preY = preMoves[moveCnt].y;

	while(overlap)
	{
		// 랜덤으로 새롭게 둘 좌표를 구함
		newX = rand()%4;
		newY = rand()%4;

		if(moveCnt <= 14)	/* 빈 좌표가 2개 이상일때 */
		{
			if((newX != preX) && (newY != preY))	/* 랜덤으로 생성한 좌표와 이전좌표를 비교하고 */
				if(board[newX][newY] == ' ')		/* 해당 좌표가 비어있는 공간인지 검사 */
					overlap = false;  // 랜덤으로 좌표를 뽑는 while문을 멈춤
		}
		else   // 빈 좌표가 1개 뿐인 경우 
		{
			if(board[newX][newY] == ' ')   // 새로운 좌표가 빈 공간인지(남은 1개의 좌표인지) 검사
				overlap = false;  // 랜덤으로 좌표를 뽑는 while문을 멈춤
		}			
	}		
	DoMove(newX, newY);  // 새로운 좌표로 수를 둠
};

/**
	함 수 : DoMove(int x, int y)
	기 능 :	입력받은 좌표값으로 게임판에 수를 둠
*/
void GameBoard::DoMove(int x, int y)
{
	if( moveCnt%2 == 0 )			/* 누구 순서인지 검사하여 해당 좌표에 해당 순서 컴퓨터의 수를 board 배열에 둠 */
		board[x][y] = starterCom;
	else
		board[x][y] = oppnentCom;
	
	//이전 수의 좌표를 저장하는 배열에도 새롭게 둔 수의 좌표를 저장
	preMoves[moveCnt].x = x;
	preMoves[moveCnt].y = y;

	moveCnt++;						/* 현재 수를 증가 시킴 */
};

/**
	함 수 : UndoMove()
	기 능 : 놓았던 수를 한단계 이전상태로 돌려놓는 함수
*/
void GameBoard::UndoMove()
{
	moveCnt--;  // 현재 수 하나 감소
	board[preMoves[moveCnt].x][preMoves[moveCnt].y] = ' ';  // 둔 수를 board 배열 상에서 초기화
}

/**
	함 수 : CheckState()
	기 능 : 현재 보드판의 상태, 누가이겼는지, 비겼는지를 검사해서 상태값을 변경해주는 함수
*/
void GameBoard::CheckState()
{
	char temp[4][4];
	int i;

	for(i=0; i<4; i++)				
	{	
		/* 가로 방향을 검사 */
		if(board[i][0]!=' ')  // i행의 첫 열이 비어있지 않다면
		{
			if((board[i][0]=='X') && (board[i][1]=='X') && (board[i][2]=='X') && (board[i][3]=='X'))  // i행이 모두 X인 경우
			{
				state = STATE_WINA;  // 컴퓨터 A의 승
				return;
			}
			if((board[i][0]=='O') && (board[i][1]=='O') && (board[i][2]=='O') && (board[i][3]=='O'))  // i행이 모두 O인 경우
			{
				state = STATE_WINB;  // 컴퓨터 B의 승
				return;
			}
		}

		/* 새로 방향을 검사 */
		if(board[0][i]!=' ')  // i열의 첫 행이 비어있지 않다면
		{
			if((board[0][i]=='X') && (board[1][i]=='X') && (board[2][i]=='X') && (board[3][i]=='X'))  // i열이 모두 X인 경우
			{
				state = STATE_WINA;  // 컴퓨터 A의 승
				return;
			}
			if((board[0][i]=='O') && (board[1][i]=='O') && (board[2][i]=='O') && (board[3][i]=='O'))  // i열이 모두 O인 경우
			{
				state = STATE_WINB;  // 컴퓨터 B의 승
				return;
			}
		}
	}
		
	if((board[0][0]!=' ')&&(board[0][0]==board[1][1])&&(board[0][0]==board[2][2])&&(board[0][0]==board[3][3]))	/* 첫번째 대각선이 모두 동일한 Text를 가지고 있다면 */
	{
		if(board[0][0]=='X')  // 그 Text가 X라면
		{
			state = STATE_WINA;  // 컴퓨터 A의 승
			return;
		}
		else  // 그 Text가 O라면
		{
			state = STATE_WINB;  // 컴퓨터 B의 승
			return;
		}
	}
	
	if((board[0][3]!=' ')&&(board[0][3]==board[1][2])&&(board[0][3]==board[2][1])&&(board[0][3]==board[3][0])) /* 두번째 대각선이 모두 동일한 Text를 가지고 있다면 */
	{
		if(board[0][3]=='X')  // 그 Text가 X라면
		{
			state = STATE_WINA;  // 컴퓨터 A의 승
			return;
		}
		else  // 그 Text가 O라면
		{
			state = STATE_WINB;  // 컴퓨터 B의 승
			return;
		}
	}

	if( moveCnt > 15 )  // 위의 조건에 모두 해당하지 않지만 모든 수가 두어졌을 때
	{
		state = STATE_DRAW;		/* 비김 */
	}
};