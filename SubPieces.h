#pragma once
#include"Pieces.h"

bool straightLineCheck(int*&, Pieces***&); // tells if there is any piece in between source and destination
bool diagonalLineCheck(int*&, Pieces***&); // tells if there is any piece in between source and destination

class Pawn :public Pieces
{
public:

	Pawn(const char* Colour = nullptr,const char* Type = "Pn");
	bool checkIfValidMove(int*&,Pieces***&) override;
	
	virtual ~Pawn();
};

class Knight :public Pieces
{
public:

	Knight(const char* Colour = nullptr, const char* Type = "Kn");
	bool checkIfValidMove(int*&, Pieces***&) override;

	virtual ~Knight();
};

class Bishop :public Pieces
{
private:

	friend bool diagonalLineCheck(int*& fromTo, Pieces***& board); // tells if there is any piece in between source and destination

public:

	Bishop(const char* Colour = nullptr, const  char* Type = "Bp");
	bool checkIfValidMove(int*&, Pieces***&) override;

	virtual ~Bishop();
};

class Rook :public Pieces
{
private:
	friend bool straightLineCheck(int*&, Pieces***&); // tells if there is any piece in between source and destination

public:

	Rook(const char* Colour = nullptr, const  char* Type = "Rk");
	bool checkIfValidMove(int*&, Pieces***&) override;

	virtual ~Rook();
};

class Queen :public Pieces
{
private:

	friend bool straightLineCheck(int*&, Pieces***&); // tells if there is any piece in between source and destination
	friend bool diagonalLineCheck(int*& fromTo, Pieces***& board); // tells if there is any piece in between source and destination

public:
	
	Queen(const char* Colour = nullptr, const  char* Type = "Qn");
	bool checkIfValidMove(int*&, Pieces***&) override;

	virtual ~Queen();
};

class King :public Pieces
{
public:

	King(const char* Colour = nullptr, const  char* Type = "Kg");
	bool checkIfValidMove(int*&, Pieces***&) override;

	virtual ~King();
};
