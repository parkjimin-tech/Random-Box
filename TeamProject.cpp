#include <iostream>
#include<conio.h>
#include<vector>
#include<Windows.h>
using namespace std;
#define HPUP 3
#define SPEEDUP 4
#define DAMAGEUP 5
#define USEDITEM 12
#define Y 0 // Y가 들어갈 인덱스
#define X 1 // X가 들어갈 인덱스
#define CHARACTER 2 // 
#define LEFT 75 // 왼쪽 방향키 아스키코드
#define RIGHT 77
#define UP 72
#define DOWN 80
#define WIDTH 20 // 맵의 가로길이
#define HEIGHT 20 // 맵의 세로길이
#define WALL 1 // 벽
#define NULL 0 // 공백
//////////////////////////////////////////////////////
#define col GetStdHandle(STD_OUTPUT_HANDLE) 
#define BLACK SetConsoleTextAttribute( col,0x0000 );
#define DARK_BLUE SetConsoleTextAttribute( col,0x0001 );
#define GREEN SetConsoleTextAttribute( col,0x0002 );
#define BLUE_GREEN SetConsoleTextAttribute( col,0x0003 );
#define BLOOD SetConsoleTextAttribute( col,0x0004 );
#define PUPPLE SetConsoleTextAttribute( col,0x0005 );
#define GOLD SetConsoleTextAttribute( col,0x0006 );			//색상 지정
#define WHITE SetConsoleTextAttribute( col,0x0007 );
#define GRAY SetConsoleTextAttribute( col,0x0008 );
#define BLUE SetConsoleTextAttribute( col,0x0009 );
#define HIGH_GREEN SetConsoleTextAttribute( col,0x000a );
#define SKY_BLUE SetConsoleTextAttribute( col,0x000b );
#define RED SetConsoleTextAttribute( col,0x000c );
#define PLUM SetConsoleTextAttribute( col,0x000d );
#define YELLOW SetConsoleTextAttribute( col,0x000e );
//////////////////////////////////////////////////////

class player
{
public:
	int hp = 100;
	int speed = 10;
	int damage = 3;
	void showStatus()
	{
		cout << "hp : " << hp << endl;
		cout << "speed : " << speed << endl;
		cout << "damage : " << damage << endl;
	}
};
class hpUp
{
public:
	int setHp(player& p, int map[HEIGHT][WIDTH])
	{ // 문제점 - 맵좌표로 갈때마다 증가됨, 값이 오른 이후 다시 이 위치에 와도 값이 오르지 않게 하려면?
		if (map[2][2] == CHARACTER) // 캐릭터가 이 위치를 지날경우 이 위치는 NULL값이 됨
		{
			if (p.hp == 100)
			{
				p.hp += 10;
				map[2][2] = USEDITEM;
				return p.hp;
			}
		}
		else
		{
			return p.hp;
		}
	}
};
class speedUp
{
public:
	int setSp(player& p, int map[HEIGHT][WIDTH])
	{
		if (map[10][17] == CHARACTER)
			{
				if (p.speed == 3)
				{
					p.speed += 5;
					map[10][17] = USEDITEM;
					return p.speed;
				}
			}
		else
		{
			return p.speed;
		}
	}
};
class damageUp
{
public:
	int setDg(player& p, int map[HEIGHT][WIDTH])
	{
		if (map[15][15] == CHARACTER)
		{
			if (p.damage == 10)
			{
				p.damage += 2;
				map[15][15] = USEDITEM;
				return p.damage;
			}
		}
		else
		{
			return p.damage;
		}
	}
};

int character[2];
int hpup[2];
int speedup[2];
int damageup[3];
int map[HEIGHT][WIDTH] = { NULL }; // 맵의 공백
void Move();
void MapDraw();
void Init();
void gotoxy(int x, int y);

int main()
{
	vector<hpUp> item_h;
	vector<speedUp> item_s;
	vector<damageUp> item_d;  // vector 컨테이너 하나에 다른함수들을 가진 클래스를 다 못넣음
	hpUp hp;
	speedUp sp;
	damageUp dg;

	item_h.push_back(hp);
	item_s.push_back(sp);
	item_d.push_back(dg);//클래스에 맞는 객체를 넣어줘야함
//생성자가 있다면 item.push_back(hp(10)); 인자값 넣어줘야함

	player ninja;

	map[10][10] = CHARACTER;//INIT보다 먼저 설정되야함
	map[2][2] = HPUP;
	map[10][17] = SPEEDUP;
	map[15][15] = DAMAGEUP;
	Init();
	for (int i = 0; i < HEIGHT; i++)//벽입력
	{
		for (int j = 0; j < WIDTH; j++)
		{
			map[0][j] = WALL; // 위 // map[y][x]
			map[HEIGHT - 1][j] = WALL; // 아래
			map[i][0] = WALL; // 왼쪽
			map[i][WIDTH - 1] = WALL;// 오른쪽
		}
	}
	while (1)
	{
		system("cls");
		MapDraw();
		if (map[2][2] == CHARACTER)
		{
			hp.setHp(ninja, map);
		}
		ninja.showStatus();
		if (kbhit())
		{
			Move(); // 키보드체크 및 값바꿈?
		}
	}
}

void Init() // 위치저장
{
	int Width = (WIDTH * 2) + 1;
	int Height = HEIGHT + 10;
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Height, Width); //배열크기에 따라 조절
	system(buf);
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == CHARACTER)
			{
				character[X] = x;
				character[Y] = y;
			}
			if (map[y][x] == HPUP)
			{
				hpup[X] = x;
				hpup[Y] = y;
			}
			if (map[y][x] == SPEEDUP)
			{
				speedup[X] = x;
				speedup[Y] = y;
			}
			if (map[y][x] == DAMAGEUP)
			{
				damageup[X] = x;
				damageup[Y] = y;
			}
		}
	}
}

void Move()
{
	int ch;
	ch = getch();

	{
		if (ch == 224)
		{
			ch = getch();
			map[character[Y]][character[X]] = NULL;
			switch (ch)
			{
			case LEFT:
				if (map[character[Y]][character[X] - 1] != WALL)
				{
					character[X]--;
				}
				break;
			case RIGHT:
				if (map[character[Y]][character[X] + 1] != WALL)
				{
					character[X]++;
				}
				break;
			case UP:
				if (map[character[Y] - 1][character[X]] != WALL)
				{
					character[Y]--;
				}
				break;
			case DOWN:
				if (map[character[Y] + 1][character[X]] != WALL)
				{
					character[Y]++;
				}
				break;
			}
		}
		map[character[Y]][character[X]] = CHARACTER;
	}
}

void MapDraw() // cout 용도
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (map[y][x] == WALL)
			{
				YELLOW
					cout << "▩";
				WHITE
			}
			else if (map[y][x] == HPUP)
			{
				GREEN
					cout << "HP";
				WHITE
			}
			else if (map[y][x] == SPEEDUP)
			{
				BLUE
					cout << "SP";
				WHITE
			}
			else if (map[y][x] == DAMAGEUP)
			{
				GOLD
					cout << "DG";
				WHITE
			}
			else if (map[y][x] == CHARACTER)
			{
				RED
					cout << "옷";
				WHITE
			}
			else if (map[y][x] == NULL)
				cout << "  ";
		}
		cout << endl;
	}
}

void gotoxy(int x, int y)
{
	COORD posXY = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), posXY);
}