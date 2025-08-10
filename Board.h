#pragma once
#include "SubPieces.h"
#include"Stack.h"


class Board
{
private:
	Stack stack;

	bool validCoordinate(int,int);
	int translate_move(string,int*&);
	void findKing(const char*, int*&);
	void restorePreviousPositions();
	int movePiecesOnBoard(int*&);
	void pawnPromotion(int*&);
	void castle(int*&);
	void moveDueToCastle(int*&);

	bool anyPieceBwKingandOpp(const char*,int*&);

public:
	Pieces*** board;


	Board();
	void print();
	bool make_move(int*&);

	bool isKingInCheck(const char* colour,int*&);

	bool isKingCheckMate(const char* colour,int*&);

	bool willKingCheck(const char*,int*&);

	bool anyValidMove(const char*,int*&);

	bool canKingMove(const char*,int*&,int,int);

	bool isStaleMate(const char*,int*&);

	bool isDraw();
	//~Board();
};