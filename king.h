#ifndef KING_H_
#define KING_H_
#include "figure.h"


class King : public Figure
{
public:
	King(int letter, int row, Color color) : Figure(letter,row,color)
	{}
	std::string figure_name() const override;
};






#endif // !KING_H_
