#pragma once
#include"Pieces.h"

class PieceInfo
{
public:
	Pieces* p;
	int from[2];
	int to[2];

	PieceInfo(Pieces* P = nullptr, int i = 0, int j = 0, int a = -1, int b = -1);

	void setP(Pieces*&);
	void setFrom(int, int);
	void setTo(int a = -1, int b = -1);
	void operator = (PieceInfo& d);
	Pieces* getP();
	void getFromTo(int*&);

};

class Stack
{
private:
	PieceInfo* arr;
	int size;

	void expand();
	void shrink();
public:
	Stack();
	void push(Pieces*,int*&,int k=0);
	PieceInfo* pop();
	bool peekIsTherePromotedPiece();
	bool isThereEliminatedPiece();

	
	
	~Stack();
};
