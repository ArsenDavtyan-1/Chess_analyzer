#include <iostream>
#include "chessBoard.h"
#include "king.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "Pawn.h"




int main()
{

	ChessBoard A;
	King white_king(5, 8, Figure::Color::White);
	King black_king(3, 8, Figure::Color::Black);
	Queen white_queen(4, 8, Figure::Color::White);
	Bishop white_bishop(4, 5, Figure::Color::White);
	A.set_on_board(&white_king);
	A.set_on_board(&black_king);
	A.set_on_board(&white_queen);
	A.set_on_board(&white_bishop);
	A.print();
	
	
	A.board_analyze();
}