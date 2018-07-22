#include <iostream>
#include <ctime>
#include "Matrix.h"
#include "Layer.h"
#include "NeuralNetwork.h"

int main()
{
    Matrix X(2, 5, true);
    std::vector<double> labels;
    labels.push_back(0);
    labels.push_back(0);
    labels.push_back(1);
    labels.push_back(1);
    labels.push_back(2);

    Matrix W(2, 10, true);
    Matrix b(10, 1, true);

    Matrix A =  W.T().Dot(X) + b;
    std::cout << W.T().Dot(X);
    std::cout << b;
    std::cout << A;
    A.Type();

    std::vector<int> hiddenNode;
    hiddenNode.push_back(10);
    hiddenNode.push_back(3);

    Matrix _labels = Matrix(labels);

    NeuralNetwork NN(X, _labels, hiddenNode);
    NN.CheckAlgorithm();
    std::cout << NN.GetLabels();
    getchar();
	return 0;
}
