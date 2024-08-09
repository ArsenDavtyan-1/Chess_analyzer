#ifndef FIGURE_H_
#define FIGURE_H_
#include <string>

class Figure
{
public:
	enum class Color{ White, Black};
	Color col;
	int letter_index;
	int row_index;
public:
	Figure(int letter, int row, Color color);
	virtual ~Figure()
	{}

	virtual std::string figure_name() const = 0;
	
	
};



#endif // !FIGURE_H_

