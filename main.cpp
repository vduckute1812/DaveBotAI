#include <iostream>
#include <ctime>
#include "Matrix.h"
#include "Layer.h"

int main()
{
    Matrix A(3, 2, true);
    std::cout << A;

    Matrix B(3, 2, true);
    Matrix C = A*B;
    std::cout << C;

    Matrix D = C.T();
    std::cout << D;

    Matrix E = A.Dot(D);
    std::cout << E;

    Matrix F;
    F = E;
    std::cout<< F;

    F.Type();

    Layer lb(A, B);

    std::cout << lb.GetDatas();
    std::vector<double> tmp;
    std::vector<std::vector<double> >value;
    double k = 0.0;

    for(int i=0; i< 4; ++i)
    {
        for(int j = 0; j < 20; ++j)
        {
            tmp.push_back(k);
        }
        ++k;
    }

    value.push_back(tmp);
    Matrix label(value);
    std::cout<<label;
    label.Type();
    lb.SetLabels(label);

    std::cout<<lb.GetLabels();

    getchar();
	return 0;
}
