#ifndef BISHOP_H_
#define BISHOP_H_

#include "figure.h"


class Bishop : public Figure
{
public:
	Bishop(int letter, int row, Color color) : Figure(letter, row, color)
	{}
	std::string figure_name() const override;

};




#endif // !BISHOP_H_
