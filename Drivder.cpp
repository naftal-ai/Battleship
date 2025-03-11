#include <iostream>
#include "Game.h"
using namespace std;

int main()
{
	
	int num;
	cout << "how many Battleships do you want to place on board?" << endl;
	cin >> num;

	Game g(num);
	g.play();





	return 0;
}