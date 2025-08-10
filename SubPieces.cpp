#include"SubPieces.h"
#include<iostream>
using namespace std;


bool diagonalLineCheck(int*& fromTo, Pieces***& board)
{
	if (((fromTo[0] > fromTo[2]) && (fromTo[1] < fromTo[3])) || ((fromTo[0] < fromTo[2]) && (fromTo[1] > fromTo[3])))
	{
		int a = fromTo[0], b = fromTo[1], i = fromTo[2], j = fromTo[3];
		if (fromTo[0] < fromTo[2]) {
			a = fromTo[2], b = fromTo[3], i = fromTo[0], j = fromTo[1];
		}

		for (a -= 1, b += 1; (a > i) && (b < j); a--, b++) {
			if (board[a][b] != nullptr)
				return false;
		}
			
	}
	else
	{
		
		int a = fromTo[0], b = fromTo[1], i = fromTo[2], j = fromTo[3];
		if (fromTo[0] > fromTo[2])
			a = fromTo[2], b = fromTo[3], i = fromTo[0], j = fromTo[1];

		for (a += 1, b += 1; a < i && b < j; a++, b++)
			if (board[a][b] != nullptr)
				return false;
	}
	
	return true;
}

bool straightLineCheck(int*& fromTo, Pieces***& board)
{
	if (fromTo[0] == fromTo[2])
	{
		int  c = fromTo[1], d = fromTo[3];
		if (fromTo[1] > fromTo[3]) {
			c = fromTo[3], d = fromTo[1];
		}

		for (c += 1; c < d; c++)
			if (board[fromTo[0]][c] != nullptr)
				return false;
	}
	else
	{
		int  c = fromTo[0], d = fromTo[2];
		if (fromTo[0] > fromTo[2]) {
			c = fromTo[2], d = fromTo[0];
		}

		for (c += 1; c < d; c++)
			if (board[c][fromTo[1]] != nullptr)
				return false;
	}
	return true;
}

//Pawn

Pawn::Pawn(const char* Colour,const char* Type ) :Pieces(Type, Colour) {};

bool Pawn::checkIfValidMove(int*& fromTo,Pieces***&board)
{
	float distance = distanceInPlane(fromTo);
	//this condition stops pawn from moving over a piece in front of it,it checks if the coordinates are appropriate for pawn
	//movenment,it also makes sure that the pawns are moving in right directions with respect to thier colors.

	if (((fromTo[1] == fromTo[3]) && (board[fromTo[2]][fromTo[3]] != nullptr)) || (distance > 2)
		|| (cmpstr(colour,"Black") && (fromTo[2] <= fromTo[0])) || (cmpstr(colour,"White") && (fromTo[2] >= fromTo[0])))
	{
		return false;
	}
		

	//  (colour == "Black" && (fromTo[2] <= fromTo[0])) this condition is true if destination is behind source
	// (colour == "White" && (fromTo[2] >= fromTo[0]))  this condition is true if destination is behind source

	if (((fromTo[0] == 1 && cmpstr(colour, "Black")) || (fromTo[0] == 6 && cmpstr(colour, "White")) || (distance==1)) && (fromTo[1] == fromTo[3]))
	{
		//cout << "**";
		return true;
	}
		

	if ((distance > 1 && distance < 2) && (board[fromTo[2]][fromTo[3]] != nullptr) && !(cmpstr(colour, board[fromTo[2]][fromTo[3]]->colour)))
	{
		//cout <<"Olla";
		return true;
	}
	

	
	return false;
};
 Pawn::~Pawn() {};



//Knight
Knight::Knight(const char* Colour, const  char* Type ) :Pieces(Type, Colour) {};

bool Knight::checkIfValidMove(int*& fromTo, Pieces***&board)
{
	float distance = distanceInPlane(fromTo);

	if ((distance > 2 && distance < 3) && ((board[fromTo[2]][fromTo[3]]==nullptr) || !(cmpstr(colour, board[fromTo[2]][fromTo[3]]->colour))))
		return true;

	return false;
};
Knight::~Knight() {};



//Bishop
Bishop::Bishop(const char* Colour, const  char* Type ) :Pieces(Type, Colour) {};


bool Bishop::checkIfValidMove(int*& fromTo, Pieces***&board)
{
	if ((slope(fromTo)==1.0) && ((board[fromTo[2]][fromTo[3]] == nullptr) || !(cmpstr(colour, board[fromTo[2]][fromTo[3]]->colour)))
		&& diagonalLineCheck(fromTo, board))
		return true;

	return false;
};
Bishop::~Bishop() {};




//Rook
Rook::Rook(const char* Colour, const  char* Type ) :Pieces(Type, Colour) {};

bool Rook::checkIfValidMove(int*& fromTo, Pieces***&board)
{
	if ((!(mov_stat) && (board[fromTo[2]][fromTo[3]] != nullptr) && cmpstr(board[fromTo[2]][fromTo[3]]->type, "Kg") &&
		cmpstr(colour, board[fromTo[2]][fromTo[3]]->colour) && !(board[fromTo[2]][fromTo[3]]->mov_stat) && straightLineCheck(fromTo, board))
		|| 
		((fromTo[0] == fromTo[2] || fromTo[1] == fromTo[3]) && ((board[fromTo[2]][fromTo[3]] == nullptr) || !(cmpstr(colour, board[fromTo[2]][fromTo[3]]->colour)))
		&& straightLineCheck(fromTo, board)))
	{
		return true;
	}
		

	return false;
};
Rook::~Rook() {};



//Queen
Queen::Queen(const char* Colour, const  char* Type ) :Pieces(Type, Colour) {};

bool Queen::checkIfValidMove(int*& fromTo, Pieces***&board)
{
	// faulty condition
	/*if((((fromTo[0] == fromTo[2]) || (fromTo[1] == fromTo[3])) || (slope(fromTo) == 1.0)) &&
		((board[fromTo[2]][fromTo[3]] == nullptr) || !(cmpstr(colour, board[fromTo[2]][fromTo[3]]->colour))) &&
		((straightLineCheck(fromTo, board)) || (diagonalLineCheck(fromTo, board))))
	{
		mov_stat = 1;
		return true;
	}*/

	if (((board[fromTo[2]][fromTo[3]]==nullptr) || !cmpstr(colour,board[fromTo[2]][fromTo[3]]->colour))
		 && ((((fromTo[0]==fromTo[2]) || (fromTo[1]==fromTo[3])) && straightLineCheck(fromTo,board))
			 || ((slope(fromTo)==1.0) && diagonalLineCheck(fromTo,board))))
	{
		mov_stat = 1;
		return true;
	}
		

	return false;
};
Queen::~Queen(){};



//King
King::King(const char* Colour, const  char* Type ) :Pieces(Type, Colour) {};

bool King::checkIfValidMove(int*& fromTo, Pieces***&board)
{
	float distance = distanceInPlane(fromTo);
	fromTo[0]; fromTo[1]; fromTo[2]; fromTo[3];

	if ((!(mov_stat) && board[fromTo[2]][fromTo[3]] != nullptr && cmpstr(board[fromTo[2]][fromTo[3]]->type, "Rk") &&
		cmpstr(colour, board[fromTo[2]][fromTo[3]]->colour) && !(board[fromTo[2]][fromTo[3]]->mov_stat) && straightLineCheck(fromTo, board))
		|| 
		(((distance == 1) || (distance > 1 && distance < 2)) && ((board[fromTo[2]][fromTo[3]] == nullptr) || !(cmpstr(board[fromTo[2]][fromTo[3]]->colour, colour)))))
	{
		
		return true;
	}
	
	return false;
};
King::~King() {}