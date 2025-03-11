#include <iostream>
#include "Battleship.h"
#define N 10
#ifndef _Game_h
#define _Game_h

class Game
{
private:
	char m_board[N][N];
	Battleship *m_Barr;
	static int holdedSpace;
	void clearBoard();
	bool checkPlace(int len, int x, int y, bool v) const;
	void buildBoard();
	int checkHit(char cx, int y);
	bool checkSunk(int, int) const;
	bool chekcValid(char, int) const;

public:
	Game(int num);
	~Game();
	void printBoard() const;
	void printOriginalBoard() const;
	void play();
};
#endif _Game_h
