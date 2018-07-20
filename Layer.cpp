#include "Layer.h"

// Input layer
Layer::Layer(const Matrix& pointData, const Matrix& label)
{
    Z = pointData;
    Y = label;
    m_numClass = this->GetMaxLabels();
}

// Stable softmax function
void Layer::CalcSoftmaxFunc()
{
    for(int i=0; i < Z.GetNumRow(); ++i)
    {
        for(int j=0; j < Z.GetNumCol(); ++j)
        {
            Z.SetValue(i, j, exp(Z.GetValue(i, j)));
        }
    }
}

void Layer::SetLabels(const Matrix& mat)
{
    Y = mat;
    m_numClass = GetMaxLabels();
    Y.TransToOneHot(m_numClass);
}

void Layer::SetLabels(const std::vector<double>& labels)
{
    Y = Matrix(labels);
    m_numClass = GetMaxLabels();
    Y.TransToOneHot(m_numClass);      //Get one hot
}

int Layer::GetMaxLabels() const
{
    std::cout << "Co vao day";
    int max_Class = 0;
    for(int i=0; i<Y.GetNumCol(); ++i)
    {
        if(max_Class < Y.GetValue(0, i))
        {
            max_Class = Y.GetValue(0, i);
        }
    }
    return max_Class + 1;
}


Matrix Layer::GetBias() const
{
    return b;
}

Matrix Layer::GetDatas() const
{
    return Z;
}

Matrix Layer::GetLabels() const
{
    return Y;
}

Matrix Layer::GetWeights() const
{
    return W;
}

int Layer::GetNumClass() const
{
    return m_numClass;
}

