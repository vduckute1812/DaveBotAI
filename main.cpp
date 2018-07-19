#include <iostream>
#include <ctime>
#include "Matrix.h"

int main()
{
	srand((int)time(0));
	Matrix data(3, 3, true);
	data.PrintToConsole();

	return 0;
}