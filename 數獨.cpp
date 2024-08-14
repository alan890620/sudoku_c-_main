#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include<Windows.h>
using namespace std;
using namespace chrono;

void draw(int** arr, int n, int n2) //輸出
{
	//┼┴┬┤├─│┌┐└┘ ═╞╪╡╔╦╗╠╬╣╚╩╝╒╤╕╘╧╛╓╥╖╟╫╢╙╨╜║
	cout << "\\ x\ny   ";
	for (int t = 1; t != n + 1; t++)
		cout << setw(4) << t;
	cout << "\n    ╔";
	for (int t = 1; t != n * 4; t++)
	{
		if (t % 4 == 0)
			if (t / 4 % n2 == 0)
				cout << "╦";
			else
				cout << "╤";
		else
			cout << "═";
	}
	cout << "╗\n ";
	for (int t = 0; t != n; t++)
	{
		if (t != 0)
			if (t % n2 == 0)
			{
				cout << "    ╠";
				for (int t = 1; t != n * 4; t++)
				{
					if (t % 4 == 0)
						if (t / 4 % n2 == 0)
							cout << "╬";
						else
							cout << "╪";
					else
						cout << "═";
				}
				cout << "╣\n ";
			}
			else
			{
				cout << "    ╟";
				for (int t = 1; t != n * 4; t++)
				{
					if (t % 4 == 0)
						if (t / 4 % n2 == 0)
							cout << "╫";
						else
							cout << "┼";
					else
						cout << "─";
				}
				cout << "╢\n ";
			}
		cout << setw(2) << t + 1 << " ║";
		for (int t2 = 0; t2 != n; t2++)
		{
			if (arr[t][t2] != 0)
				cout << setw(3) << arr[t][t2];
			else
				cout << "   ";
			if (t2 % n2 == n2 - 1)
				cout << "║";
			else
				cout << "│";
		}
		cout << endl;
	}
	cout << "    ╚";
	for (int t = 1; t != n * 4; t++)
	{
		if (t % 4 == 0)
			if (t / 4 % n2 == 0)
				cout << "╩";
			else
				cout << "╧";
		else
			cout << "═";
	}
	cout << "╝\n";
}

void numOut(int** arr, int n) //統計數量
{
	int num[10] = { 0 };
	for (int t = 0; t != n * n; t++)
		num[arr[t / n][t % 9]] ++;
	cout << "    |";
	for (int t = 0; t != n; t++)
	{
		cout << setw(2) << t + 1 << ":";
		if (num[t + 1] >= 9)
			if (num[t + 1] > 9)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
		cout << setw(2) << num[t + 1];
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "|";
	}
	cout << endl;
}


int** sudoku(int** arr) //原始版生成數獨
{
	int xy[9], xyb, res;
	for (int t = 0; t != 81; t++)
		arr[t / 9][t % 9] = 0;

	for (int t = 0; t != 9; t++)
	{
		for (int t = 0; t != 9; t++)
			xy[t] = -1;

		for (int t2 = 0; t2 != 9; t2++)
		{
			res = 0;
			bool s = false;
			xyb = rand() % 8;
			do
			{
				if (res > 9)							//用下面的方法這裡要改大,上面的用9就可
				{
					//cout << t << " " << t2 << endl;
					return NULL;
				}
				xyb++; if (xyb > 8) xyb = 0;			//上下兩種二擇一
				//xyb = rand() % 9;						//此為另一種方法
				s = false;
				if (arr[(xyb / 3) + (t2 / 3 * 3)][(xyb % 3) + (t2 % 3 * 3)] != 0)
					s = true;
				else
					for (int t3 = 0; t3 != t2; t3++)
					{
						if (t2 % 3 == t3 % 3)
							if (xyb % 3 == xy[t3] % 3)
							{
								s = true;
								break;
							}
						if (t2 / 3 == t3 / 3)
							if (xyb / 3 == xy[t3] / 3)
							{
								s = true;
								break;
							}
					}
				res++;
			} while (s);
			xy[t2] = xyb;
			arr[(xyb / 3) + (t2 / 3 * 3)][(xyb % 3) + (t2 % 3 * 3)] = t + 1;
		}
	}
	return arr;
}
bool isTrue(int** arr, int xy, int n) //檢查是否合理
{
	if (arr[xy / 9][xy % 9] != 0)
		return false;

	for (int t = 0; t != 9; t++)
		if (arr[(xy / 9 / 3) * 3 + t / 3][(xy % 9 / 3) * 3 + t % 3] == n)
			return false;

	for (int t = 0; t != 9; t++)
	{
		if (xy % 9 != t)
			if (arr[xy / 9][t] == n)
				return false;
		if (xy / 9 != t)
			if (arr[t][xy % 9] == n)
				return false;
	}

	return true;
}

int** sudoku_sub(int** arr) //模組化生成數獨
{
	int xy[9], xyb, res;
	for (int t = 0; t != 81; t++)
		arr[t / 9][t % 9] = 0;

	for (int t = 0; t != 9; t++)
	{
		for (int t2 = 0; t2 != 9; t2++)
			xy[t] = -1;

		for (int t2 = 0; t2 != 9; t2++)
		{
			res = 0;
			bool s = false;
			xyb = rand() % 8;
			do
			{
				if (res > 9)							//用下面的方法這裡要改大,上面的用9就可
				{
					//cout << t << " " << t2 << endl;
					return NULL;
				}
				xyb++; if (xyb > 8) xyb = 0;			//上下兩種二擇一
				//xyb = rand() % 9;						//此為另一種方法
				s = !isTrue(arr, ((xyb / 3) + (t2 / 3 * 3)) * 9 + (xyb % 3) + (t2 % 3 * 3), t + 1);
				res++;
			} while (s);
			xy[t2] = xyb;
			arr[(xyb / 3) + (t2 / 3 * 3)][(xyb % 3) + (t2 % 3 * 3)] = t + 1;
		}
	}
	return arr;
}
/*
int** sudoku_update(int** arr) //能不整個重跑?
{
	int xy[9][9], xyb, res;
	for (int t = 0; t != 81; t++)
	{
		arr[t / 9][t % 9] = 0;
		xy[t / 9][t % 9] = 10;
	}

	for (int t = 0; t != 9; t++)
	{
		do
			xy[t][0] = rand() % 9;
		while (arr[xy[t][0] / 3][xy[t][0] % 3] != 0);

		arr[xy[t][0] / 3][xy[t][0] % 3] = t + 1;

		for (int t2 = 1; t2 != 9; t2++)
		{
			res = 0;
			bool s = false;
			xyb = rand() % 8;
			do
			{
				if (res > 9)
				{
					t--;
					t2 = 0;
					res = 0;
					break;
				}
				else
				{
					xyb++; if (xyb > 8) xyb = 0;
					s = false;
					if (arr[(xyb / 3) + (t2 / 3 * 3)][(xyb % 3) + (t2 % 3 * 3)] < t)
						s = true;
					else
						for (int t3 = 0; t3 != t2; t3++)
						{
							if (t2 % 3 == t3 % 3)
								if (xyb % 3 == xy[t][t3] % 3)
								{
									s = true;
									break;
								}
							if (t2 / 3 == t3 / 3)
								if (xyb / 3 == xy[t][t3] / 3)
								{
									s = true;
									break;
								}
						}
					res++;
				}
			} while (s);
			xy[t][t2] = xyb;
			arr[(xyb / 3) + (t2 / 3 * 3)][(xyb % 3) + (t2 % 3 * 3)] = t + 1;

		}
	}
	return arr;
}*/

void asSuduku(int** arr, int xy, int* asn) //檢查唯一解
{
	//cout << xy << endl ;
	if (xy >= 81)
	{
		*asn += 1;
		//draw(arr, 9, 3);
		return;
	}
	if (arr[xy / 9][xy % 9] != 0)
		asSuduku(arr, xy + 1, asn);
	else
		for (int t = 1; t != 10; t++)
		{
			if (isTrue(arr, xy, t))
			{
				arr[xy / 9][xy % 9] = t;
				asSuduku(arr, xy + 1, asn);
				arr[xy / 9][xy % 9] = 0;
				if (*asn > 1)
					return;
			}
		}
	//draw(arr, 9, 3);
	//cout << "error" << endl;
}
void gameDraw(int** arr, int** as, int** qs, int n, int n2) //遊戲用輸出
{
	//┼┴┬┤├─│┌┐└┘ ═╞╪╡╔╦╗╠╬╣╚╩╝╒╤╕╘╧╛╓╥╖╟╫╢╙╨╜║
	cout << "\n\\x  ";
	for (int t = 1; t != n + 1; t++)
		cout << setw(4) << t;
	cout << "\ny   ╔";
	for (int t = 1; t != n * 4; t++)
	{
		if (t % 4 == 0)
			if (t / 4 % n2 == 0)
				cout << "╦";
			else
				cout << "╤";
		else
			cout << "═";
	}
	cout << "╗\n ";
	for (int t = 0; t != n; t++)
	{
		if (t != 0)
			if (t % n2 == 0)
			{
				cout << "    ╠";
				for (int t = 1; t != n * 4; t++)
				{
					if (t % 4 == 0)
						if (t / 4 % n2 == 0)
							cout << "╬";
						else
							cout << "╪";
					else
						cout << "═";
				}
				cout << "╣\n ";
			}
			else
			{
				cout << "    ╟";
				for (int t = 1; t != n * 4; t++)
				{
					if (t % 4 == 0)
						if (t / 4 % n2 == 0)
							cout << "╫";
						else
							cout << "┼";
					else
						cout << "─";
				}
				cout << "╢\n ";
			}
		cout << setw(2) << t + 1 << " ║ ";
		for (int t2 = 0; t2 != n; t2++) //輸出文字
		{
			if (qs[t][t2] == 0)
			{
				int buff = arr[t][t2];
				arr[t][t2] = 0;
				if (/*arr[t][t2] != 0 &&*/ !isTrue(arr, (t * 9) + t2, buff))
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | FOREGROUND_RED);
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
				arr[t][t2] = buff;
			}
			if (arr[t][t2] == 0)
				cout << "  ";
			else
				cout << setw(2) << arr[t][t2];
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

			if (t2 % n2 == n2 - 1)
				cout << "║ ";
			else
				cout << "│ ";
		}
		cout << endl;
	}
	cout << "    ╚";
	for (int t = 1; t != n * 4; t++)
	{
		if (t % 4 == 0)
			if (t / 4 % n2 == 0)
				cout << "╩";
			else
				cout << "╧";
		else
			cout << "═";
	}
	cout << "╝\n";
}

bool fin(int** arr, int** as, int n)
{
	for (int t = 0; t != n * n; t++)
		if (arr[t / n][t % n] != as[t / n][t % n])
			return false;
	return true;
}

void game(int** arr, int** as, int n, int n2) //遊戲
{
	//arr 遊戲用陣列 qs 原始題目 as 原始終盤
	int** qs = new int* [9], x, y, in;
	for (int t = 0; t != 9; t++)
		qs[t] = new int[9];
	for (int t = 0; t != 81; t++)
		qs[t / 9][t % 9] = arr[t / 9][t % 9];

	while (!fin(arr, as, n))
	{
		do
		{
			cout << "輸入x(0~" << n << ")\n";
			do
			{
				cin >> x;
			} while ((x <= n) != (x > 0));
			cout << "輸入y(0~" << n << ")\n";
			do
			{
				cin >> y;
			} while ((y <= n) != (y > 0));
			if (!qs[y - 1][x - 1] == 0)
				cout << "輸入不允許之位置,請重新輸入\n";
		} while (!qs[y - 1][x - 1] == 0);
		cout << "輸入數字(0~" << n << ")\n";
		do
		{
			cin >> in;
		} while ((in <= n) != (in >= 0));
		arr[y - 1][x - 1] = in;
		gameDraw(arr, as, qs, 9, 3);
		numOut(arr, n);
	}
	cout << "你贏了!\n";
	system("pause");
}

int main() //主程式
{
	int ts = 0;
	int** starr = new int* [9];
	//int buff[9][9];
	int** arr = NULL;
	for (int t = 0; t != 9; t++)
		starr[t] = new int[9];

	srand(time(NULL));
	auto start = high_resolution_clock::now();

	for (; arr == NULL; ts++) //生成
		//arr = sudoku( starr );
		arr = sudoku_sub(starr);

	auto stop = high_resolution_clock::now();
	duration<double> diff = stop - start;

	//draw(arr , 9 , 3 );
	cout << "ok\n共生成了" << ts << "次\n花費" << diff.count() << "秒\n";
	//system( "pause" );

	int** as = new int* [9]; //出題前處理
	for (int t = 0; t != 9; t++)
		as[t] = new int[9];

	for (int t = 0; t != 81; t++)
		as[t / 9][t % 9] = arr[t / 9][t % 9];

	int asn, t0 = 0, space;
	cout << "#不建議輸入大於50的數\n";
	do
	{
		cout << "輸入欲挖空之格數:(1~60)\n";
		cin >> space;
	} while ((space <= 60) != (space > 0));

	do //出題
	{
		for (int t = 0; t != space;)
		{
			int r = rand() % 81;
			if (arr[r / 9][r % 9] != 0)
			{
				t++;
				arr[r / 9][r % 9] = 0;
			}
			//cout << t << endl ;
		}
		asn = 0;
		asSuduku(arr, 0, &asn);
		//cout << asn << endl;
		if (asn == 1)
			break;
		else
		{
			for (int t = 0; t != 81; t++)
				arr[t / 9][t % 9] = as[t / 9][t % 9];
			t0++;
			//cout << t0;
			if (t0 > 500 - asn * 7)
			{
				t0 = 0;
				space--;
				cout << space << endl;
			}
		}
	} while (true);


	cout << "挖空了" << space << "格\n";
	cout << "題目:\n";
	//draw(arr, 9, 3);
	gameDraw(arr, as, arr, 9, 3);
	numOut(arr, 9);
	//cout <<答案:\n";
	//draw(qs, 9, 3);
	//system("pause");

	//gameDraw(arr, as, arr, 9, 3);

	game(arr, as, 9, 3); //開始玩
}