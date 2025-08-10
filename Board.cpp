#include"Board.h"
#include"SubPieces.h"
#include<iostream>
#include<string>
using namespace std;

#define BOARD_ROWS 8
#define BOARD_COLUMNS 8


#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

Board::Board()
{
	board = new Pieces ** [8];

	for (int i = 0; i < 8; i++)
		board[i] = new Pieces * [8]{ nullptr };
	
	 const char* colour = "Black";

	////Black pieces set up
	//board[0][0] = new Rook(colour);
	//board[0][7] = new Rook(colour);

	//board[0][1] = new Knight(colour);
	//board[0][6] = new Knight(colour);

	//board[0][2] = new Bishop(colour);
	//board[0][5] = new Bishop(colour);

	//board[0][3] = new Queen(colour);

	//board[0][4] = new King(colour);

	////White Pieces set up
	//colour = "White";

	//board[7][0] = new Rook(colour);
	//board[7][7] = new Rook(colour);

	//board[7][1] = new Knight(colour);
	//board[7][6] = new Knight(colour);

	//board[7][2] = new Bishop(colour);
	//board[7][5] = new Bishop(colour);
	//
	//board[7][3] = new Queen(colour);

	//board[7][4] = new King(colour);


	//// Pawn setup for both sides 
	//colour = "Black";

	//for (int i = 1, j = 0; j < 8; j++)
	//{
	//	board[i][j] = new Pawn(colour);
	//	if (j == 7 && i == 1)
	//	{
	//		i = 6;
	//		j = -1;
	//		colour = "White";
	//	}
	//}



	//code used for testing
	 colour = "White";
	 board[5][3] = new King(colour);
	 board[1][2] = new Pawn(colour);
	 board[1][7] = new Rook(colour);

	 colour = "black";
	 board[0][0] = new King(colour);
	 board[4][3] = new Knight(colour);
	 board[0][3] = new Rook(colour);

}


void Board::print()
{
	system("cls");
	skiplines(10);
	space(83);
	char ch = 'a';
	for (int i = 0; i < 8; i++, ch++)
		cout << RESET << ch << "  ";
		
	cout << endl;

	//75 spaces are awien hee

	space(82);
	for (int l = 0; l < 8; l++)
		cout << YELLOW << "-- " << RESET;

	cout << endl;

	for (int i = 0,k=8; i < 8; i++,k--)
	{ 
		space(79);
		cout << k << YELLOW << " |" << RESET;
		for (int j = 0; j < 8; j++)
		{
			
			if (board[i][j] != nullptr) {

				if (cmpstr(board[i][j]->colour,"Black"))
				{
					cout << CYAN << board[i][j]->type << RESET;
				}
				else
				{
					cout << WHITE << board[i][j]->type << RESET;
				}
					
			}
			else
				cout << "  ";

			cout << YELLOW << "|" << RESET;	
		}
		cout << " " << k ;
		cout << endl;
		space(81);
		for (int l = 0; l < 8; l++)
			cout << YELLOW << "---" << RESET;
		cout << endl;
	}
	space(83);
	ch = 'a';
	for (int i = 0; i < 8; i++, ch++)
		cout << ch << "  ";

	cout << endl << endl;
}

int Board::translate_move(string move, int*& fromTo)
{
	if (move.length() < 4)
		return -1;
	 // First 2 elements are source coordinates and the immediate 2 elements are the destination coordinates
	for (int i = 0,j=0; i <(int) move.length(); i++)
	{
		if (move[i] != 32) {
			//cout << alphaToNum(move[i]) << endl;
			if (alphaToNum(move[i]) >= 0)
			{
				fromTo[j] = alphaToNum(move[i]);  j++;
			}
			else
				return -1;
		}
		if ((i == move.length() - 1 && j < 4))
			return -1;
	}
	swap(fromTo[0], fromTo[1]); swap(fromTo[2], fromTo[3]);

	if (fromTo[0] == fromTo[2] && fromTo[1] == fromTo[3])
		return -1;

	return 1;
}



bool Board::make_move(int*&fromTo)
{
	string move="";
	space(83);
	cout << "Enter move: "; 

	if (cin.peek() == '\n')
		cin.ignore();

	getline(cin, move);

	if (translate_move(move, fromTo)>0) {

		if (movePiecesOnBoard(fromTo) > 0)
		{
			if (board[fromTo[2]][fromTo[3]]!=nullptr && cmpstr(board[fromTo[2]][fromTo[3]]->type, "Pn") && (fromTo[2] == 0 || fromTo[2] == 8))
			{
				pawnPromotion(fromTo);
			}
			if (board[fromTo[0]][fromTo[1]] != nullptr)
			board[fromTo[0]][fromTo[1]]->mov_stat = 1;
			if (board[fromTo[2]][fromTo[3]] != nullptr)
				board[fromTo[2]][fromTo[3]]->mov_stat = 1;
			return true;
		}
		
	}
	return false;
}


int Board::movePiecesOnBoard(int*& fromTo)
{
	fromTo[0], fromTo[1], fromTo[2], fromTo[3];

	if (board[fromTo[0]][fromTo[1]] != nullptr && board[fromTo[0]][fromTo[1]]->checkIfValidMove(fromTo, board))
	{
		if (board[fromTo[2]][fromTo[3]] != nullptr && ((cmpstr(board[fromTo[0]][fromTo[1]]->type, "Kg") && cmpstr(board[fromTo[2]][fromTo[3]]->type, "Rk"))
			|| (cmpstr(board[fromTo[2]][fromTo[3]]->type, "Kg") && cmpstr(board[fromTo[0]][fromTo[1]]->type, "Rk")))
			&& (cmpstr(board[fromTo[0]][fromTo[1]]->colour, board[fromTo[2]][fromTo[3]]->colour)))
		{
			castle(fromTo);
			return 1;
		}
			
		if (board[fromTo[2]][fromTo[3]] != nullptr)
			stack.push(board[fromTo[2]][fromTo[3]], fromTo, -1);

		board[fromTo[2]][fromTo[3]] = board[fromTo[0]][fromTo[1]];
		stack.push(board[fromTo[0]][fromTo[1]], fromTo);
		board[fromTo[0]][fromTo[1]] = nullptr;
		return 1;
	}
	return 0;
}

void Board::pawnPromotion(int*&fromTo)
{
	int opt = 0, count = 0;

	do{
		count++;

		system("cls");
		print();
		const char* s = board[fromTo[2]][fromTo[3]]->colour;
		setUserDisplayColour(s);

		if (count > 1)
			cout << "Previous input was illegal.\n\n";

		cout << "Your Pawn has reached the Respective Promotion Row of board.\n\nYou want your pawn to be promoted to...\n"
			<< "1. To Queen\n"
			<< "2. To Rook\n"
			<< "3. To Bishop\n"
			<< "4. To Knight\n\n"
			<< "Enter your choice : "; cin >> opt;
	} while (opt<=0 || opt>4);
	
	fromTo[0] = fromTo[2]; fromTo[1] = fromTo[3];
	stack.push(board[fromTo[2]][fromTo[3]], fromTo, -1);

	if (opt == 1)
		board[fromTo[2]][fromTo[3]] = new Queen(board[fromTo[2]][fromTo[3]]->colour);
	else if (opt == 2)
		board[fromTo[2]][fromTo[3]] = new Rook(board[fromTo[2]][fromTo[3]]->colour);
	else if(opt==3)
		board[fromTo[2]][fromTo[3]] = new Bishop(board[fromTo[2]][fromTo[3]]->colour);
	else
		board[fromTo[2]][fromTo[3]] = new Knight(board[fromTo[2]][fromTo[3]]->colour);

	stack.push(board[fromTo[2]][fromTo[3]], fromTo);
}


void Board::castle(int*&fromTo)
{
	if (cmpstr(board[fromTo[0]][fromTo[1]]->type, "Rk"))
	{
		swap(fromTo[0], fromTo[2]); swap(fromTo[1], fromTo[3]);
	}
	int* temp = new int[4]{ fromTo[0],fromTo[1],fromTo[2],fromTo[3] };

	if (temp[0] == 0)
	{
		if (temp[3] == 0)
		{
			fromTo[0] = 0; fromTo[1] = 4;
			fromTo[2] = 0; fromTo[3] = 2;
			moveDueToCastle(fromTo);
			fromTo[0] = 0; fromTo[1] = 0;
			fromTo[2] = 0; fromTo[3] = 3;
			moveDueToCastle(fromTo);
		}
		else
		{
			fromTo[0] = 0; fromTo[1] = 4;
			fromTo[2] = 0; fromTo[3] = 6;
			moveDueToCastle(fromTo);
			fromTo[0] = 0; fromTo[1] = 7;
			fromTo[2] = 0; fromTo[3] = 5;
			moveDueToCastle(fromTo);
		}
	}
	else
	{
		if (temp[3] == 0)
		{
			fromTo[0] = 7; fromTo[1] = 4;
			fromTo[2] = 7; fromTo[3] = 2;
			moveDueToCastle(fromTo);
			fromTo[0] = 7; fromTo[1] = 0;
			fromTo[2] = 7; fromTo[3] = 3;
			moveDueToCastle(fromTo);
		}
		else
		{
			fromTo[0] = 7; fromTo[1] = 4;
			fromTo[2] = 7; fromTo[3] = 6;
			moveDueToCastle(fromTo);
			fromTo[0] = 7; fromTo[1] = 7;
			fromTo[2] = 7; fromTo[3] = 5;
			moveDueToCastle(fromTo);
		}
	}

	delete[] temp;
	return;
}

void Board::moveDueToCastle(int*&fromTo)
{
	board[fromTo[2]][fromTo[3]] = board[fromTo[0]][fromTo[1]];
	board[fromTo[0]][fromTo[1]] = nullptr;
	stack.push(board[fromTo[2]][fromTo[3]], fromTo);
}





bool Board::isKingInCheck(const char* colour,int*&fromTo)
{
	findKing(colour, fromTo);
	
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if ((board[i][j] != nullptr)   && !(cmpstr(colour, board[i][j]->colour)))
			{
				fromTo[0] = i, fromTo[1] = j;

				if (board[i][j]->checkIfValidMove(fromTo, board)) 
					return true;	
			}
		}
	
	return false;
}



bool Board::willKingCheck(const char* colour, int*& fromTo)
{
	if (isKingInCheck(colour, fromTo))
	{
		restorePreviousPositions();
		return true;
	}

	return false;
}

bool Board::anyValidMove(const char*colour,int*&fromTo)
{
	for(int i=0;i<8;i++)
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != nullptr && cmpstr(colour, board[i][j]->colour) && !(cmpstr("Kg",board[i][j]->type)))
			{
				fromTo[0] = i; fromTo[1] = j;
				for(int m=0;m<8;m++)
					for (int n = 0; n < 8; n++)
					{
						fromTo[2] = m; fromTo[3] = n;
						if ((m != i || n != j) && (board[m][n] == nullptr || !(cmpstr(colour, board[m][n]->colour))) && (board[i][j]->checkIfValidMove(fromTo, board)))
						{
							fromTo[0]; fromTo[1]; fromTo[2]; fromTo[3];
							return true;
						}
							
					}
			}
		}
	return false;
}


bool Board::anyPieceBwKingandOpp(const char*colour, int*&fromTo)
{
	int curr_i = fromTo[2], curr_j = fromTo[3];

	int p_i = fromTo[0], p_j = fromTo[1]; // coordinates of piece which has put the King in check

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == nullptr)
			{
				swap(board[i][j], board[curr_i][curr_j]);

				if (isKingInCheck(colour, fromTo) && (fromTo[0] == p_i && fromTo[1] == p_j))
				{
					swap(board[i][j], board[curr_i][curr_j]);

					fromTo[2] = i, fromTo[3] = j;

					for (int m = 0; m < 8; m++)
						for (int n = 0; n < 8; n++)
						{
							fromTo[0] = m; fromTo[1] = n;
							if (board[m][n] != nullptr && cmpstr(colour, board[m][n]->colour) && (m != curr_i || n != curr_j) && board[m][n]->checkIfValidMove(fromTo, board))
							{
								movePiecesOnBoard(fromTo);

								if (!(willKingCheck(colour, fromTo)))
								{
									restorePreviousPositions();
									return true;
								}
							}
						}
				}
				else
					swap(board[i][j], board[curr_i][curr_j]);
			}
		}

	return false;
}



bool Board::canKingMove(const char*colour,int*&fromTo,int curr_i,int curr_j)
{
	for (int i = curr_i - 1; i < curr_i + 2; i++)
		for (int j = curr_j - 1; j < curr_j + 2; j++)
		{
			if (validCoordinate(i, j) && (curr_i != i || curr_j != j) && ((board[i][j] == nullptr) || !(cmpstr(colour, board[i][j]->colour))))
			{
				fromTo[0] = curr_i, fromTo[1] = curr_j;
				fromTo[2] = i; fromTo[3] = j;

				movePiecesOnBoard(fromTo);
				if (!(willKingCheck(colour, fromTo)))
				{
					restorePreviousPositions();
					return true;

				}
			}
		}

	return false;
}

bool Board::isStaleMate(const char*colour, int*&fromTo)
{
	if (!(isKingInCheck(colour, fromTo)) && !(canKingMove(colour, fromTo, fromTo[2], fromTo[3])) && !(anyValidMove(colour, fromTo)))
	{
		system("cls");
		print();
		cout << RED << "Game Ended in Draw By STALEMATE.\n\n";
		return true;
	}
	return false;
}

bool Board::isDraw()
{
	int count = 0;

	for(int i=0;i<8;i++)
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] != nullptr)
				count++;
		}
	if (count == 2)
	{
		system("cls");
		print();
		cout << RED << "Game Ended in Draw.\n\n";
		return true;
	}
		

	return false;
}


bool Board:: canAnyPieceElminateKingsEnemy(const char* colour, int*& fromTo)
{
	//fromTo[0], fromTo[1] has the attacking piece position
	//fromTo[2], fromTo[3] -> has the king position
	int kingCurr_i = fromTo[2], kingCurr_j = fromTo[3];

	swap(fromTo[0], fromTo[2]);
	swap(fromTo[1], fromTo[3]);

	// now fromTo[2], fromTo[3] has the attacking piece position

	for(int i=0;i<BOARD_ROWS;i++)
		for (int j = 0; j < BOARD_COLUMNS; j++)
		{
			if (board[i][j] != nullptr && cmpstr(colour, board[i][j]->colour) && (i != kingCurr_i || j != kingCurr_j))
			{
				fromTo[0] = i;
				fromTo[1] = j;

				if (board[i][j]->checkIfValidMove(fromTo, board))
				{
					return true;
				}
			}
		}

	return false;
}


bool Board::isKingCheckMate(const char* colour,int*&fromTo)
{

	int* temp = nullptr;

	if (isKingInCheck(colour, fromTo))
	{
		temp = new int[4]{ fromTo[0],fromTo[1],fromTo[2],fromTo[3] };
		cout << fromTo[0] << "," << fromTo[1] << " " << fromTo[2] << "," << fromTo[3] << endl;

		int kingCurr_i = fromTo[2], kingCurr_j = fromTo[3];
		if ((canKingMove(colour, fromTo, kingCurr_i, kingCurr_j)) || canAnyPieceElminateKingsEnemy(colour, temp)
			|| (anyPieceBwKingandOpp(colour,fromTo)))
			return false;

		delete[] temp;
	}
	else
		return false;
		
	system("cls");
	print();
	switchColor(colour);
	setUserDisplayColour(colour);

	space(50);
	cout << colour << " Won By CHECKMATE.\n\n";
	
	return true;
}



bool Board::validCoordinate(int i, int j)
{
	if ((i >= 0 && i < 8) && (j >= 0 && j < 8))
		return true;

	return false;
}




void Board::findKing(const char* colour, int*& fromTo)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((board[i][j] != nullptr) && cmpstr(board[i][j]->type, "Kg") && cmpstr(board[i][j]->colour, colour))
			{
				fromTo[2] = i; fromTo[3] = j;
				return; // terminates the loop
			}
		}
	}
}



void Board::restorePreviousPositions()
{
	if (!(stack.peekIsTherePromotedPiece())) //if works only if there is no promoted piece on top of the stack
	{
		PieceInfo* lastp = stack.pop();
		board[lastp->from[0]][lastp->from[1]] = lastp->p;
		board[lastp->to[0]][lastp->to[1]] = nullptr;

		if (stack.isThereEliminatedPiece() && !(stack.peekIsTherePromotedPiece()))
		{
			lastp = stack.pop();
			board[lastp->from[0]][lastp->from[1]] = lastp->p;
				
		}
	}
	
}