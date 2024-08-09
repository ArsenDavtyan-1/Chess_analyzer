#ifndef QUEEN_H_
#define QUEEN_H_

#include "figure.h"

class Queen : public Figure
{
public:
	Queen(int letter, int row, Color color) : Figure(letter, row, color)
	{}
	std::string figure_name() const override;
};




#endif // !QUEEN_H_