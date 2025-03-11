#include "Battleship.h"
#include<iostream>

using namespace std;

Battleship::Battleship() :m_length(5 - counter)
{
	if (m_length == 1)
		m_length = 3;
	counter++;
}

int Battleship::counter = 0;

