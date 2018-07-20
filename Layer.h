#ifndef LAYER_H
#define LAYER_H
#include "Matrix.h"
#include <math.h>

struct Node
{
    Node() {}
};

class Layer
{
private:
    // Z = W.T*X + b
    // A = f(Z)
    Matrix b;       // [d(l), 1] We separate it in W. It's useful with weight decay way for avoiding overfitting.
    Matrix W;       // [d(l-1), d(l)] It's a matrix
    Matrix Z;       // [d(l), 1] It's a vector with d(l) elements
    Matrix A;       // [d(l), 1] It's a vector with d(l) elements
    Matrix Y;       // [d(l), 1] It's a vector with d(l) elements
    int m_numClass;
    int GetMaxLabels() const;
public:
    // Input Layer
    Layer(const Matrix& pointData, const Matrix& label);
    void CalcSoftmaxFunc();

    void SetLabels(const Matrix& mat);
    void SetLabels(const std::vector<double>& labels);
    Matrix GetBias() const;
    Matrix GetDatas() const;
    Matrix GetLabels() const;
    Matrix GetWeights() const;
    int GetNumClass() const;
};

#endif // LAYER_H
