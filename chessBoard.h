#ifndef CHESSBOARD_H_
#define CHESSBOARD_H_
#include "figure.h"
#include "king.h"


extern enum class square_status{Under_attack,
	Occupied_protected, Occupied_not_protected, Free };


class ChessBoard
{
private:
	static const int size = 8;
	Figure*** Board;

	void for_king_on_matrix(square_status board_status_matrix[][size], int letter_size, Figure* king);
	void for_rook_on_matrix(square_status board_status_matrix[][size], int letter_size, Figure* rook);
	void for_bishop_on_matrix
	(square_status board_status_matrix[][size], int letter_size, Figure* bishop);
	void for_queen_on_matrix
	(square_status board_status_matrix[][size], int letter_size, Figure* queen);
	void for_knight_on_matrix
	(square_status board_status_matrix[][size], int letter_size, Figure* knight);
	void for_pawn_on_matrix
	(square_status board_status_matrix[][size], int letter_size, Figure* pawn);

public:
	ChessBoard();
	void print() const;
	void set_on_board(Figure* fig);
	
	void board_analyze();
};



#endif // !CHESSBOARD_H_