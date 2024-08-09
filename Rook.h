#ifndef ROOK_H_
#define ROOK_H_

#include "figure.h"

class Rook : public Figure
{
public:
	Rook(int letter, int row, Color color) : Figure(letter, row, color)
	{}
	std::string figure_name() const override;
};






#endif // !ROOK_H_