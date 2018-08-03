#include <iostream>
#include <ctime>

#include "Matrix.h"
#include "Layer.h"
#include "inputreader.h"
#include "NeuralNetwork.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
int main()
{
    Matrix X(3, 12, false);
    X.SetValue(0, 0, -1);
    X.SetValue(1, 0, 5);
    X.SetValue(2, 0, 0);
    X.SetValue(0, 1, -2);
    X.SetValue(1, 1, -1);
    X.SetValue(2, 1, 0);
    X.SetValue(0, 2, -1);
    X.SetValue(1, 2, 1);
    X.SetValue(2, 2, 0);
    X.SetValue(0, 3, -2);
    X.SetValue(1, 3, 1);
    X.SetValue(2, 3, 0);
    X.SetValue(0, 4, -0.5);
    X.SetValue(1, 4, 0);
    X.SetValue(2, 4, 0);
    X.SetValue(0, 5, -0.2);
    X.SetValue(1, 5, 0.2);
    X.SetValue(2, 5, 0);

    X.SetValue(0, 6, 1);
    X.SetValue(1, 6, 5);
    X.SetValue(2, 6, 1);
    X.SetValue(0, 7, 2);
    X.SetValue(1, 7, -1);
    X.SetValue(2, 7, 1);
    X.SetValue(0, 8, 1);
    X.SetValue(1, 8, 1);
    X.SetValue(2, 8, 1);
    X.SetValue(0, 9, 2);
    X.SetValue(1, 9, 1);
    X.SetValue(2, 9, 1);
    X.SetValue(0, 10, 0.5);
    X.SetValue(1, 10, 0);
    X.SetValue(2, 10, 1);
    X.SetValue(0, 11, 0.2);
    X.SetValue(1, 11, 0.2);
    X.SetValue(2, 11, 1);

    std::vector<double> labels;
    labels.push_back(0);
    labels.push_back(0);
    labels.push_back(0);
    labels.push_back(0);
    labels.push_back(0);
    labels.push_back(0);
    labels.push_back(1);
    labels.push_back(1);
    labels.push_back(1);
    labels.push_back(1);
    labels.push_back(1);
    labels.push_back(1);

    std::vector<int> hiddenNode;
    hiddenNode.push_back(10);

    hiddenNode.push_back(2);    // Final


    Matrix _labels = Matrix(labels);

    NeuralNetwork NN(X, _labels, hiddenNode);

    NN.Train(20, 1.0);

    return 0;
}
