#include "Pawn.h"



std::string Pawn::figure_name() const
{
	std::string name;
	if (col == Color::White)
		name = "  p  ";
	else
		name = " ~p  ";
	return name;
}