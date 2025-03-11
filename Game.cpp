#include "Game.h"
#include <iostream>
#include <time.h>

using namespace std;

Game::Game(int num)
{
	if (num < 6 && num > 0)
	{
		m_Barr = new Battleship[num];
		for (int i = 0; i < num; i++)
			holdedSpace += m_Barr[i].getSize();
	}

	else
	{
		m_Barr = new Battleship;
		holdedSpace += 5;
	}
	buildBoard();
}
Game::~Game()
{
	delete[] m_Barr;
}

int Game::holdedSpace = 0;

void Game::clearBoard()
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			m_board[i][j] = '_';
}

void Game::printOriginalBoard() const
{
	cout << "   ";

	for (int i = 0; i < N; i++)
		cout << char('A' + i) << " ";
	cout << endl;

	for (int i = 0; i < N; i++)
	{
		cout << 1 + i << " ";
		if (i < 9)
			cout << " ";
		for (int j = 0; j < N; j++)
			cout << m_board[i][j] << " ";
		cout << endl;
	}
}

bool Game::checkPlace(int len, int x, int y, bool vertical) const
{
	int mx, my, px, py;
	if (vertical)
	{
		if ((N - 1 - y) < len)
			return false;

		mx = x - 1, my = y - 1, px = x + 1, py = y + len + 1;
		if (x == 0)
			mx = x;
		else if (x == N - 1)
			px = x;
		if (y == 0)
			my = y;
		else if (py == N - 1)
			py -= 1;
	}

	else
	{
		if (N - 1 - x < len)
			return false;

		mx = x - 1, my = y - 1, px = x + len + 1, py = y + 1;

		if (x == 0)
			mx = x;
		else if (px == N - 1)
			px -= 1;
		if (y == 0)
			my = y;
		else if (y == N - 1)
			py = y;
	}

	for (int i = my; i <= py; i++)
		for (int j = mx; j <= px; j++)
			if (m_board[i][j] == 's')
				return false;
	return true;
}

void Game::buildBoard()
{
	srand((unsigned)time(NULL));
	clearBoard();
	int arrLen = m_Barr[0].getCtr();
	for (int i = 0; i < arrLen; i++)
	{
		int x, y, len = m_Barr[i].getSize();
		bool isVertical;
		do
		{
			x = rand() % 10;
			y = rand() % 10;
			isVertical = (rand() % 100) % 2 == 0;
		} while (!(checkPlace(len, x, y, isVertical)));

		if (isVertical)
			for (int i = 0; i < len; i++)
				m_board[y + i][x] = 's';

		else
			for (int i = 0; i < len; i++)
				m_board[y][x + i] = 's';
	}
}

void Game::printBoard() const
{
	cout << "   ";

	for (int i = 0; i < N; i++)
		cout << char('A' + i) << " ";
	cout << endl;

	for (int i = 0; i < N; i++)
	{
		cout << 1 + i << " ";
		if (i < 9)
			cout << " ";
		for (int j = 0; j < N; j++)
			cout << (m_board[i][j] == '@' || m_board[i][j] == 'x' ? m_board[i][j] : '_') << " "; // print only hits or fisfusim
		cout << endl;
	}
}

int Game::checkHit(char cx, int y)
{
	int x = cx - 'a';
	y -= 1;
	if (m_board[y][x] == '@' || m_board[y][x] == 'x')
	{
		cout << "you have chosen this point already.\npleas choose another one." << endl;
		return -1;
	}

	if (m_board[y][x] == 's')
	{
		cout << "Hit!!!" << endl;
		m_board[y][x] = '@';
		holdedSpace--;
		if (checkSunk(x, y))
			cout << "Battleship Sunk!!!" << endl;
		return 0;
	}

	cout << "almost Hit." << endl;
	m_board[y][x] = 'x';
	return 1;
}

bool Game::checkSunk(int x, int y) const
{
	// 1.find the direction of a battleship
	bool vertical = false;

	if (y != 0 && m_board[y - 1][x] == 's' || m_board[y - 1][x] == '@')
		vertical = true;
	if (y < N - 1 && m_board[y + 1][x] == 's' || m_board[y + 1][x] == '@')
		vertical = true;

	if (vertical)
	{ // check down
		for (int ty = y + 1; ty < N; ty++)
		{
			if (m_board[ty][x] == 's')
				return false;
			if (m_board[ty][x] == 'x' || m_board[ty][x] == '_')
				break;
		}

		// check up

		for (int ty = y - 1; ty > -1; ty--)
		{
			if (m_board[ty][x] == 's')
				return false;
			if (m_board[ty][x] == 'x' || m_board[ty][x] == '_')
				break;
		}
	}
	else
	{
		// check right
		for (int tx = x + 1; tx < N; tx++)
		{
			if (m_board[y][tx] == 's')
				return false;
			if (m_board[y][tx] == 'x' || m_board[y][tx] == '_')
				break;
		}

		// check left
		for (int tx = x - 1; tx > -1; tx--)
		{
			if (m_board[y][tx] == 's')
				return false;
			if (m_board[y][tx] == 'x' || m_board[y][tx] == '_')
				break;
		}
	}

	return true;
}

bool Game::chekcValid(char cx, int y) const
{
	if (cx > 'j' || cx < 'a' || y < 1 || y > 10)
	{
		cout << "invalid input." << endl;
		return false;
	}

	return true;
}

void Game::play()
{
	int ctr = 0;
	cout << "do you want a hint?  [y/n]" << endl;
	char answer;
	cin >> answer;
	if (answer == 'y')
	{
		printOriginalBoard();
		cout << "memorize the board and press enter to start the game..." << endl;
		cin.ignore();
		while (cin.get() != '\n')
			;

		system("cls");
		system("clear");
	}
	while (holdedSpace)
	{
		char cx = '0';
		int y = 0;
		printBoard();

		cout << "enter guess: x y (to exit use 0 0)" << endl;
		cin >> cx >> y;
		if (y == 0 && cx == '0')
		{
			cout << "by by!";
			return;
		}

		while (!chekcValid(cx, y))
		{
			cin.clear();
			cin.ignore();
			cin >> cx >> y;
		}

		if (checkHit(cx, y) != -1)
			ctr++;
	}

	cout << "you won!!" << endl;
	cout << "you had " << ctr << " rounds total." << endl;
	printOriginalBoard();
}