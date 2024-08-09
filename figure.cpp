#include "figure.h"
#include <iostream>

Figure::Figure(int letter, int row, Color color)
{
	while (letter > 8 || letter < 1 || row > 8 || row < 1)
	{
		std::cout << " There are not a position - (" << char(letter + 96);
		std::cout << row << "), try again to give a position" << std::endl;
		std::cout << "letter = ";
		std::cin >> letter;
		std::cout << "row = ";
		std::cin >> row;
	}
	letter_index = letter;
	row_index = row;
	col = color;
}