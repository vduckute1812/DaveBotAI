#ifndef LAYER_H
#define LAYER_H
#include "Matrix.h"

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
public:
    // Input Layer
    Layer(Matrix pointData, Matrix label);
};

#endif // LAYER_H
