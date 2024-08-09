#include "Knight.h"

std::string Knight::figure_name() const
{
	std::string name;
	if (col == Color::White)
		name = "  N  ";
	else
		name = " ~N  ";
	return name;
}