#include "Rook.h"
  

std::string Rook::figure_name() const 
{
	std::string name;
	if (col == Color::White)
		name = "  R  ";
	else
		name = " ~R  ";
	return name;
}