#include "king.h"


std::string King::figure_name() const
{
	std::string name;
	if (col == Color::White)
		name = "  K  ";
	else
		name = " ~K  ";
	return name;
}


