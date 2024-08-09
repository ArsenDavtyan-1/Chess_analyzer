#include "Queen.h"

std::string Queen::figure_name() const
{
	std::string name;
	if (col == Color::White)
		name = "  Q  ";
	else
		name = " ~Q  ";
	return name;
}