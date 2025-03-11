#include <iostream>
#ifndef _Battleship_h
#define _Battleship_h

using namespace std;
class Battleship
{
private:
	int m_length;
	static int counter;

public:
	Battleship();
	int getSize() const { return m_length; }
	int getCtr() const { return counter; }
};

#endif _Battleship_h
