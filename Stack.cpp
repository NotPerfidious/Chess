#include"Stack.h"

Stack::Stack() :arr(nullptr), size(0) {};

void Stack::expand()
{
	PieceInfo* temp = new PieceInfo  [size + 1];

	for (int i = 0; i < size; i++)
		temp[i] = arr[i];
	size++;
	arr = temp;
	temp = nullptr;
}

void Stack::shrink()
{
	PieceInfo* temp = new PieceInfo[size - 1];
	size--;
	for (int i = 0; i < size; i++)
		temp[i] = arr[i];

	arr = temp;
	temp = nullptr;
}

void Stack::push(Pieces* p,int*&fromTo,int k)
{
	expand();
	arr[size-1].setP(p);
	
	if (k != -1)
	{
		arr[size - 1].setFrom(fromTo[0], fromTo[1]);
		arr[size - 1].setTo(fromTo[2], fromTo[3]);
		return;
	}
	arr[size - 1].setFrom(fromTo[2], fromTo[3]);
	arr[size - 1].setTo();
}

PieceInfo* Stack::pop()
{
	PieceInfo *p= &arr[size - 1];
	shrink();
	return p;
}

bool Stack::peekIsTherePromotedPiece()
{
	if((arr[size-1].from[0]==arr[size-1].to[0]) && (arr[size-1].from[1]==arr[size-1].to[1]))
	return true;

	return false;
}

bool Stack::isThereEliminatedPiece()
{
	if (size >= 1)
	{
		if (arr[size - 1].to[0] == -1)
			return true;
	}
	
	return false;
}


void PieceInfo::operator=(PieceInfo& d)
{
	p=d.p;
	from[0]=d.from[0]; from[1] = d.from[1];
	to[0] = d.to[0]; to[1] = d.to[1];
}

Stack::~Stack() {};

PieceInfo::PieceInfo(Pieces* P,int i,int j,int a,int b):p(P)
{
	from[0] = i, from[1] = j; to[0] = a, to[1] = b;
}

void PieceInfo::setP(Pieces*&P)
{
	p = P;
}

void PieceInfo::setFrom(int i, int j)
{
	from[0] = i, from[1] = j;
}

void PieceInfo::setTo(int a, int b)
{
	to[0] = a, to[1] = b;
}

Pieces* PieceInfo::getP()
{
	return p;
}

void PieceInfo::getFromTo(int*& fromTo)
{
	fromTo[0] = from[0]; fromTo[1] = from[1];
	fromTo[2] = to[0]; fromTo[3] = to[1];
}
