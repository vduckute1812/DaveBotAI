#include "Layer.h"

Layer::Layer()
{
    m_numPoints = 0;
    m_numNodes = 0;
}


// Input layer
Layer::Layer(const Matrix& pointData, int numNextNode, int indexLayer, bool isFinal)
{
    m_numNodes = pointData.GetNumRow();
    m_numPoints = pointData.GetNumCol();
    m_isFinal = isFinal;
    m_indexLayer = indexLayer;

    b = Matrix(numNextNode, 1, false);              // Z[L] = W.T[L]*A[L-1] + b[L]
    W = Matrix(m_numNodes, numNextNode, true);
    Z = W.T().Dot(pointData) + b;                           // Z = W_T.X + B

    if(isFinal){                                    // A[L] = f(Z[L])
        A = SoftMax(Z);
    }
    else{
        A = ReLuFunc(Z);
    }
}

void Layer::SetBias(const Matrix& mat)
{
    b = mat;
}

void Layer::SetWeights(const Matrix& mat)
{
    W = mat;
}

Matrix Layer::GetBias() const
{
    return b;
}

Matrix Layer::GetWeights() const
{
    return W;
}

Matrix Layer::ReLuFunc(const Matrix& mat)
{
    std::cout << "=============RECTIFY LINEAR UNIT===========";

    Matrix result = Matrix(mat.GetNumRow(), mat.GetNumCol(), false);
    double value;

    for(int i =0; i< mat.GetNumRow(); ++i)
    {
        for(int j=0; j< mat.GetNumCol(); ++j)
        {
            value = mat.GetValue(i, j);
            if(value > 0)
            {
                result.SetValue(i, j, value);
            }
        }
    }

    return result;
}

Matrix Layer::GetE() const
{
    return E;
}

// Stable Softmax
Matrix Layer::SoftMax(const Matrix& mat)
{
    std::cout << "============SOFTMAX===========";
    Matrix result = mat;
    result = result - result.MaxMatArr().T();

    double sumValue;

    for(int j =0; j< mat.GetNumCol(); ++j)
    {   sumValue = 0;

        for(int i=0; i< mat.GetNumRow(); ++i)
        {
            result.SetValue(i, j, exp(result.GetValue(i, j)));
            sumValue+=result.GetValue(i, j);
        }

        for(int i=0; i< mat.GetNumRow(); ++i)
        {
            result.SetValue(i, j, result.GetValue(i, j)/sumValue);
        }
    }
    std::cout<<result;

    return result;
}

Matrix Layer::GetActFuncVal() const
{
    return A;
}

void Layer::FeedForward(const Matrix& pointData)
{
    Z = W.T().Dot(pointData) + b;

    if(m_isFinal){                                   // A[L] = f(Z[L])
        A = SoftMax(Z);
    }
    else{
        A = ReLuFunc(Z);
    }
    std::cout << "===Z====";
    Z.Type();
    std::cout << "===A====";
    A.Type();
}

void Layer::Backpropagation(const Matrix& E_L, const Matrix& Weight_L, const Matrix& A_pre, double eta)
{

    if(m_isFinal)
    {
        E = (A - E_L) * (1.0 / m_numPoints);
    }
    else
    {
        E = ReLuFunc(Weight_L.Dot(E_L));
    }

    dW = A_pre.Dot(E.T());
    db = E.Sum(1);
    W = W - dW*eta;
    b = b - db*eta;
    std::cout << "===E====";
    E.Type();
    std::cout << "===W====";
    W.Type();
    std::cout << "===b====";
    b.Type();
}

int Layer::GetIndexLayer() const
{
    return m_indexLayer;
}
