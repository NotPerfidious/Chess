#pragma once
//#include<iostream>
#include"SomeTrivialShit.h"
#include<string>
using namespace std;



class Pieces
{
public:

	char* type;
	char* colour;
	int mov_stat;

public:

	Pieces(const char* Type = nullptr,const char* Colour = nullptr);

	string getType();
	const char* getColour();

	virtual bool checkIfValidMove(int*&,Pieces***&) = 0;

	 ~Pieces();
};