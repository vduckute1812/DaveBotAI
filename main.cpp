#include <iostream>
#include <ctime>
#include "Matrix.h"

int main()
{
    Matrix A(3, 2, true);
    Matrix B(3, 2, true);
    Matrix C = A*B;
    std::cout << C;

    Matrix D = C.T();
    std::cout << D;

    Matrix E = A.Dot(D);
    std::cout << E;

    getchar();
	return 0;
}
