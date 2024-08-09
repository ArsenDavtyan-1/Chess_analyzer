#include "Bishop.h"


std::string Bishop::figure_name() const
{
	std::string name;
	if (col == Color::White)
		name = "  B  ";
	else
		name = " ~B  ";
	return name;
}