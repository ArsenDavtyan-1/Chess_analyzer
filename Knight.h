#ifndef KNIGHT_H_
#define KNIGHT_H_

#include "figure.h"


class Knight : public Figure
{
public:
	Knight(int letter, int row, Color color) : Figure(letter, row, color)
	{}
	std::string figure_name() const override;

};




#endif // !KNIGHT_H_
