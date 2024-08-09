#ifndef PAWN_H_
#define PAWN_H_
#include "figure.h"


class Pawn : public Figure
{
public:
	Pawn(int letter, int row, Color color) : Figure(letter, row, color)
	{}
	std::string figure_name() const override;
};






#endif // !PAWN_H_