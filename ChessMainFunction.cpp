#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>
#include<string>
#include<ctime>
#include"Board.h"
//#include<SFML/Graphics.hpp>

using namespace std;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"


int main()
{

	int* fromTo = nullptr;
	fromTo = new int[4]{ 0 }; // fromTo[0] and fromTo[1] -> current position, fromTo[2] and fromTo[3] -> destination position 

	Board game1;
	const char* colour = "White";
	
	while (!(game1.isKingCheckMate(colour,fromTo)) && !(game1.isDraw()) && !(game1.isStaleMate(colour,fromTo)))
	{
		setUserDisplayColour(colour);

		int counter = 0;
		bool validMoveFlag = false;
		do {

			counter++;
			game1.print();

			setUserDisplayColour(colour);

			if (game1.isKingInCheck(colour,fromTo))
				cout << "Your King is in check.Do something\n\n\a";

			if (counter > 1)
				cout << "Previous move was illegal.\n";

			validMoveFlag = game1.make_move(fromTo);

		} while (game1.willKingCheck(colour, fromTo) || !validMoveFlag);

		switchColor(colour);	
	}

	/*system("cls");
	switchColor(colour);

	b.print();
	setUserDisplayColour(colour);*/
	system("pause");

	return 0;
}