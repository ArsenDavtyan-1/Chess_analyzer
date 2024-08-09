#include "chessBoard.h"
#include <iostream>



ChessBoard::ChessBoard()
{
	Board = new Figure** [size];
	for (int i = 0; i < size; ++i)
		Board[i] = new Figure * [size] {nullptr};
}


void ChessBoard::print() const
{
	for (int i = size; i > 0; --i)
	{
		std::cout << i << " |  ";
		for (int j = 0; j < size; ++j)
		{
			if (Board[i - 1][j] == nullptr)
				std::cout << "  *  ";
			else
				std::cout << Board[i - 1][j]->figure_name();
		}
		std::cout << std::endl << std::endl;
	}


	std::cout << "      ";
	for (char i = 'A'; i <= 'H'; ++i)
	{
		std::cout << " __" <<  "  ";
	}
	std::cout << std::endl;

	std::cout << "     ";
	for (char i = 'A'; i <= 'H'; ++i)
	{
		std::cout << "  " << i << "  ";
	}
	std::cout << std::endl << std::endl << std::endl << std::endl;;
}


void ChessBoard::set_on_board(Figure* fig)
{
	if (Board[fig->row_index - 1][fig->letter_index - 1] == nullptr)
		Board[fig->row_index - 1][fig->letter_index - 1] = fig;
	else {
		std::cout << "Non empty square, we can not put there a ";
		std::cout << fig->figure_name() << "(" << char(96 + fig->letter_index) << ",";
		std::cout << fig->row_index << ")" << std::endl << std::endl;
	}
}

void ChessBoard::board_analyze()
{
	int black_king_row;
	int black_king_letter;

	square_status MatrixBoard[size][size];
	for (int i = 0; i < size; ++i)
		for (int j = 0; j < size; ++j)
		{
			if (Board[i][j] == nullptr)
				MatrixBoard[i][j] = square_status::Free;
			else if (Board[i][j]->figure_name() == " ~K  ")
			{
				MatrixBoard[i][j] = square_status::Free;
				black_king_row = i;
				black_king_letter = j;
			}
			else
				MatrixBoard[i][j] = square_status::Occupied_not_protected;
		}


	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (MatrixBoard[i][j] == square_status::Free 
					|| MatrixBoard[i][j] == square_status::Under_attack)
				continue;
			else
			{
				if (Board[i][j]->figure_name() == "  K  ")
					for_king_on_matrix(MatrixBoard, size, Board[i][j]);
				else if(Board[i][j]->figure_name() == "  R  ")
					for_rook_on_matrix(MatrixBoard, size, Board[i][j]);
				else if(Board[i][j]->figure_name() == "  Q  ")
					for_queen_on_matrix(MatrixBoard, size, Board[i][j]);
				else if (Board[i][j]->figure_name() == "  B  ")
					for_bishop_on_matrix(MatrixBoard, size, Board[i][j]);
				else if(Board[i][j]->figure_name() == "  N  ")
					for_knight_on_matrix(MatrixBoard, size, Board[i][j]);
				else if (Board[i][j]->figure_name() == "  p  ")
					for_pawn_on_matrix(MatrixBoard, size, Board[i][j]);
			}

		}
	}


	square_status square;

	if (black_king_row + 1 < size) {
		square = MatrixBoard[black_king_row + 1][black_king_letter];
		if (square == square_status::Free || square == square_status::Occupied_not_protected)
		{
			std::cout << "Not a checkmate" << std::endl;
			return;
		}
	}

	if(black_king_row - 1 >= 0)
	{
		square = MatrixBoard[black_king_row - 1][black_king_letter];
		if (square == square_status::Free || square == square_status::Occupied_not_protected)
		{
			std::cout << "Not a checkmate" << std::endl;
			return;
		}
	}

	if (black_king_letter + 1 < size)
	{
		square = MatrixBoard[black_king_row][black_king_letter + 1];
		if (square == square_status::Free || square == square_status::Occupied_not_protected)
		{
			std::cout << "Not a checkmate" << std::endl;
			return;
		}
	}

	if (black_king_letter - 1 >= 0)
	{
		square = MatrixBoard[black_king_row][black_king_letter - 1];
		if (square == square_status::Free || square == square_status::Occupied_not_protected)
		{
			std::cout << "Not a checkmate" << std::endl;
			return;
		}
	}

	if (black_king_row + 1 < size && black_king_letter + 1 < size)
	{
		square = MatrixBoard[black_king_row + 1][black_king_letter + 1];
		if (square == square_status::Free || square == square_status::Occupied_not_protected)
		{
			std::cout << "Not a checkmate" << std::endl;
			return;
		}
	}

	if (black_king_row + 1 < size && black_king_letter - 1 >= 0)
	{
		square = MatrixBoard[black_king_row + 1][black_king_letter - 1];
		if (square == square_status::Free || square == square_status::Occupied_not_protected)
		{
			std::cout << "Not a checkmate" << std::endl;
			return;
		}
	}

	if (black_king_row - 1 >= 0 && black_king_letter + 1 < size)
	{
		square = MatrixBoard[black_king_row - 1][black_king_letter + 1];
		if (square == square_status::Free || square == square_status::Occupied_not_protected)
		{
			std::cout << "Not a checkmate" << std::endl;
			return;
		}
	}

	if (black_king_row - 1 >= 0 && black_king_letter - 1 >= 0)
	{
		square = MatrixBoard[black_king_row - 1][black_king_letter - 1];
		if (square == square_status::Free || square == square_status::Occupied_not_protected)
		{
			std::cout << "Not a checkmate" << std::endl;
			return;
		}
	}

	if (MatrixBoard[black_king_row][black_king_letter] != square_status::Free)
	{
		std::cout << "Its a checkmate" << std::endl;
		return;
	}
}



void ChessBoard::for_king_on_matrix
	(square_status board_status_matrix[][size], int letter_size, Figure* king)
{
	int y = king->letter_index - 1;
	int x = king->row_index - 1;
	board_status_matrix[x][y] = square_status::Occupied_not_protected;
	

	if (x + 1 < size )
	{
		if (board_status_matrix[x + 1][y] == square_status::Free)
			board_status_matrix[x + 1][y] = square_status::Under_attack;
		else if(board_status_matrix[x + 1][y] == square_status::Occupied_not_protected)
			board_status_matrix[x + 1][y] = square_status::Occupied_protected;
	}

	if (x - 1 >= 0)
	{
		if (board_status_matrix[x - 1][y] == square_status::Free)
			board_status_matrix[x - 1][y] = square_status::Under_attack;
		else if (board_status_matrix[x - 1][y] == square_status::Occupied_not_protected)
			board_status_matrix[x - 1][y] = square_status::Occupied_protected;
	}

	if (y + 1 < size)
	{
		if (board_status_matrix[x][y + 1] == square_status::Free)
			board_status_matrix[x][y + 1] = square_status::Under_attack;
		else if(board_status_matrix[x][y + 1] == square_status::Occupied_not_protected)
			board_status_matrix[x][y + 1] = square_status::Occupied_protected;
	}

	if (y - 1 >= 0)
	{
		if (board_status_matrix[x][y - 1] == square_status::Free)
			board_status_matrix[x][y - 1] = square_status::Under_attack;
		else if(board_status_matrix[x][y - 1] == square_status::Occupied_not_protected)
			board_status_matrix[x][y - 1] = square_status::Occupied_protected;
	}


	if (x + 1 < size && y + 1 < size)
	{
		if (board_status_matrix[x + 1][y + 1] == square_status::Free)
			board_status_matrix[x + 1][y + 1] = square_status::Under_attack;
		else if(board_status_matrix[x + 1][y + 1] == square_status::Occupied_not_protected)
			board_status_matrix[x + 1][y + 1] = square_status::Occupied_protected;
	}


	if (x + 1 < size && y - 1 >= 0)
	{
		if (board_status_matrix[x + 1][y - 1] == square_status::Free)
			board_status_matrix[x + 1][y - 1] = square_status::Under_attack;
		else if (board_status_matrix[x + 1][y - 1] == square_status::Occupied_not_protected)
			board_status_matrix[x + 1][y - 1] = square_status::Occupied_protected;
	}

	if (x - 1 >= 0 && y + 1 < size)
	{
		if (board_status_matrix[x - 1][y + 1] == square_status::Free)
			board_status_matrix[x - 1][y + 1] = square_status::Under_attack;
		else if (board_status_matrix[x - 1][y + 1] == square_status::Occupied_not_protected)
			board_status_matrix[x - 1][y + 1] = square_status::Occupied_protected;
	}


	if (x - 1 >= 0 && y - 1 >= 0)
	{
		if (board_status_matrix[x - 1][y - 1] == square_status::Free)
			board_status_matrix[x - 1][y - 1] = square_status::Under_attack;
		else if (board_status_matrix[x - 1][y - 1] == square_status::Occupied_not_protected)
			board_status_matrix[x - 1][y - 1] = square_status::Occupied_protected;
	}


	return;
}



void ChessBoard::for_rook_on_matrix
	(square_status board_status_matrix[][size], int letter_size, Figure* rook)
{
	int y = rook->letter_index - 1;
	int x = rook->row_index - 1;
	

	for (int i = x - 1; i >= 0; --i)
	{
		if (board_status_matrix[i][y] == square_status::Free)
			board_status_matrix[i][y] = square_status::Under_attack;
		else if (board_status_matrix[i][y] == square_status::Occupied_not_protected)
		{
			board_status_matrix[i][y] = square_status::Occupied_protected;
			break;
		}
		else if (board_status_matrix[i][y] == square_status::Occupied_protected)
			break;		
	}

	for (int i = x + 1; i < size; ++i)
	{
		if (board_status_matrix[i][y] == square_status::Free)
			board_status_matrix[i][y] = square_status::Under_attack;
		else if (board_status_matrix[i][y] == square_status::Occupied_not_protected)
		{
			board_status_matrix[i][y] = square_status::Occupied_protected;
			break;
		}
		else if (board_status_matrix[i][y] == square_status::Occupied_protected)
			break;
	}

	for (int j = y - 1; j >= 0; --j)
	{
		if (board_status_matrix[x][j] == square_status::Free)
			board_status_matrix[x][j] = square_status::Under_attack;
		else if (board_status_matrix[x][j] == square_status::Occupied_not_protected)
		{
			board_status_matrix[x][j] = square_status::Occupied_protected;
			break;
		}
		else if (board_status_matrix[x][j] == square_status::Occupied_protected)
			break;
	}

	for (int j = y + 1; j < size; ++j)
	{
		if (board_status_matrix[x][j] == square_status::Free)
			board_status_matrix[x][j] = square_status::Under_attack;
		else if (board_status_matrix[x][j] == square_status::Occupied_not_protected)
		{
			board_status_matrix[x][j] = square_status::Occupied_protected;
			break;
		}
		else if (board_status_matrix[x][j] == square_status::Occupied_protected)
			break;
	}

	return;
}



void ChessBoard::for_bishop_on_matrix
	(square_status board_status_matrix[][size], int letter_size, Figure* bishop)
{
	int y = bishop->letter_index - 1;
	int x = bishop->row_index - 1;


	int i = x + 1;
	int j = y + 1;
	while (i < size && j < size)
	{
		if (board_status_matrix[i][j] == square_status::Free)
			board_status_matrix[i][j] = square_status::Under_attack;
		else if (board_status_matrix[i][j] == square_status::Occupied_not_protected)
		{
			board_status_matrix[i][j] = square_status::Occupied_protected;
			break;
		}
		else if (board_status_matrix[i][j] == square_status::Occupied_protected)
			break;
		++i;
		++j;
	}


	i = x - 1;
	j = y - 1;
	while (i >= 0 && j >= 0)
	{
		if (board_status_matrix[i][j] == square_status::Free)
			board_status_matrix[i][j] = square_status::Under_attack;
		else if (board_status_matrix[i][j] == square_status::Occupied_not_protected)
		{
			board_status_matrix[i][j] = square_status::Occupied_protected;
			break;
		}
		else if (board_status_matrix[i][j] == square_status::Occupied_protected)
			break;
		--i;
		--j;
	}


	i = x - 1;
	j = y + 1;
	while (i >= 0 && j < size)
	{
		if (board_status_matrix[i][j] == square_status::Free)
			board_status_matrix[i][j] = square_status::Under_attack;
		else if (board_status_matrix[i][j] == square_status::Occupied_not_protected)
		{
			board_status_matrix[i][j] = square_status::Occupied_protected;
			break;
		}
		else if (board_status_matrix[i][j] == square_status::Occupied_protected)
			break;
		--i;
		++j;
	}

	i = x - 1;
	j = y + 1;
	while (i >= 0 && j < size)
	{
		if (board_status_matrix[i][j] == square_status::Free)
			board_status_matrix[i][j] = square_status::Under_attack;
		else if (board_status_matrix[i][j] == square_status::Occupied_not_protected)
		{
			board_status_matrix[i][j] = square_status::Occupied_protected;
			break;
		}
		else if (board_status_matrix[i][j] == square_status::Occupied_protected)
			break;
		--i;
		++j;
	}

	i = x + 1;
	j = y - 1;
	while (i < size && j >= 0)
	{
		if (board_status_matrix[i][j] == square_status::Free)
			board_status_matrix[i][j] = square_status::Under_attack;
		else if (board_status_matrix[i][j] == square_status::Occupied_not_protected)
		{
			board_status_matrix[i][j] = square_status::Occupied_protected;
			break;
		}
		else if (board_status_matrix[i][j] == square_status::Occupied_protected)
			break;
		++i;
		--j;
	}
	

	return;
}

void ChessBoard::for_queen_on_matrix
	(square_status board_status_matrix[][size], int letter_size, Figure* queen)
{
	for_rook_on_matrix(board_status_matrix, letter_size, queen);
	for_bishop_on_matrix(board_status_matrix, letter_size, queen);
	return;
}

void ChessBoard::for_knight_on_matrix
	(square_status board_status_matrix[][size], int letter_size, Figure* knight)
{
	int y = knight->letter_index - 1;
	int x = knight->row_index - 1;

	if (x + 2 < size && y + 1 < size)
	{
		if (board_status_matrix[x + 2][y + 1] == square_status::Free)
			board_status_matrix[x + 2][y + 1] = square_status::Under_attack;
		else if (board_status_matrix[x + 2][y + 1] == square_status::Occupied_not_protected)
			board_status_matrix[x + 2][y + 1] = square_status::Occupied_protected;
	}

	if (x + 2 < size && y - 1 >= 0)
	{
		if (board_status_matrix[x + 2][y - 1] == square_status::Free)
			board_status_matrix[x + 2][y - 1] = square_status::Under_attack;
		else if (board_status_matrix[x + 2][y - 1] == square_status::Occupied_not_protected)
			board_status_matrix[x + 2][y - 1] = square_status::Occupied_protected;
	}

	if (x - 2 >= 0 && y + 1 < size)
	{
		if (board_status_matrix[x - 2][y + 1] == square_status::Free)
			board_status_matrix[x - 2][y + 1] = square_status::Under_attack;
		else if (board_status_matrix[x - 2][y + 1] == square_status::Occupied_not_protected)
			board_status_matrix[x - 2][y + 1] = square_status::Occupied_protected;
	}

	if (x - 2 >= 0 && y - 1 >= 0)
	{
		if (board_status_matrix[x - 2][y - 1] == square_status::Free)
			board_status_matrix[x - 2][y - 1] = square_status::Under_attack;
		else if (board_status_matrix[x - 2][y - 1] == square_status::Occupied_not_protected)
			board_status_matrix[x - 2][y - 1] = square_status::Occupied_protected;
	}



	if (x + 1 < size && y + 2 < size)
	{
		if (board_status_matrix[x + 1][y + 2] == square_status::Free)
			board_status_matrix[x + 1][y + 2] = square_status::Under_attack;
		else if (board_status_matrix[x + 1][y + 2] == square_status::Occupied_not_protected)
			board_status_matrix[x + 1][y + 2] = square_status::Occupied_protected;
	}


	if (x + 1 < size && y - 2 >= 0)
	{
		if (board_status_matrix[x + 1][y - 2] == square_status::Free)
			board_status_matrix[x + 1][y - 2] = square_status::Under_attack;
		else if (board_status_matrix[x + 1][y - 2] == square_status::Occupied_not_protected)
			board_status_matrix[x + 1][y - 2] = square_status::Occupied_protected;
	}


	if (x - 1 >= 0 && y + 2 < size)
	{
		if (board_status_matrix[x - 1][y + 2] == square_status::Free)
			board_status_matrix[x - 1][y + 2] = square_status::Under_attack;
		else if (board_status_matrix[x - 1][y + 2] == square_status::Occupied_not_protected)
			board_status_matrix[x - 1][y + 2] = square_status::Occupied_protected;
	}


	if (x - 1 >= 0 && y - 2 >= 0)
	{
		if (board_status_matrix[x - 1][y - 2] == square_status::Free)
			board_status_matrix[x - 1][y - 2] = square_status::Under_attack;
		else if (board_status_matrix[x - 1][y - 2] == square_status::Occupied_not_protected)
			board_status_matrix[x - 1][y - 2] = square_status::Occupied_protected;
	}


	return;
}

void ChessBoard::for_pawn_on_matrix
		(square_status board_status_matrix[][size], int letter_size, Figure* pawn)
{

	int y = pawn->letter_index - 1;
	int x = pawn->row_index - 1;

	if (x - 1 >= 0 && y + 1 < size)
	{
		if (board_status_matrix[x - 1][y + 1] == square_status::Free)
			board_status_matrix[x - 1][y + 1] = square_status::Under_attack;
		else if (board_status_matrix[x - 1][y + 1] == square_status::Occupied_not_protected)
			board_status_matrix[x - 1][y + 1] = square_status::Occupied_protected;
	}

	if (x + 1 < size && y + 1 < size)
	{
		if (board_status_matrix[x + 1][y + 1] == square_status::Free)
			board_status_matrix[x + 1][y + 1] = square_status::Under_attack;
		else if (board_status_matrix[x + 1][y + 1] == square_status::Occupied_not_protected)
			board_status_matrix[x + 1][y + 1] = square_status::Occupied_protected;
	}


	return;
}




 