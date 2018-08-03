#include "NeuralNetwork.h"

NeuralNetwork::NeuralNetwork(const Matrix& datas, const Matrix& labels, std::vector<int> numNodeHidden)
{
    X = datas;
    m_numClass = numNodeHidden.at(numNodeHidden.size() - 1);        // Final layer
    // Input Layer
    m_listLayer.push_back(Layer(datas, numNodeHidden.at(0), 0));
    bool isFinal = false;
    for(int i = 1; i< static_cast<int>(numNodeHidden.size()); ++i)      // ignore input and output layer
    {
        if(i == static_cast<int>(numNodeHidden.size()) - 1)
        {
            isFinal = true;
        }
        m_listLayer.push_back(Layer((m_listLayer.end()-1)->GetActFuncVal(), numNodeHidden.at(i), i, isFinal));
    }
    Y = labels;
    TransToOneHot(m_numClass);
    std::cout<<Y;
    m_eta = 0.1;
}


NeuralNetwork::~NeuralNetwork()
{
}


Matrix NeuralNetwork::GetLabels() const
{
    return Y;
}

void NeuralNetwork::TransToOneHot(int numClasses)
{
    if( Y.GetNumRow() != 1)
    {
        std::cout<<"Can't transform this matrix to OneHotLabel";
    }
    else
    {
        Matrix result(numClasses, Y.GetNumCol(), false);
        for(int i=0; i < Y.GetNumCol(); ++i)
        {
            result.SetValue(Y.GetValue(0, i), i, 1.0);
        }
        Y = result;
    }
}

int NeuralNetwork::GetMaxLabels() const
{
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

void NeuralNetwork::SetLabels(const Matrix& mat)
{
    Y = mat;
    TransToOneHot(m_numClass);
}

void NeuralNetwork::SetLabels(const std::vector<double>& labels)
{
    Y = Matrix(labels);
    TransToOneHot(m_numClass);      //Get one hot
}

int NeuralNetwork::GetNumClass() const
{
    return m_numClass;
}

void NeuralNetwork::CheckAlgorithm() const
{
    std::cout << std::endl << "SIZE: " <<  m_listLayer.size();
    for(int i=0; i< static_cast<int>(m_listLayer.size()); ++i)
    {
        m_listLayer[i].GetWeights().Type();
    }
}

void NeuralNetwork::CalFeedForward()
{
    std::cout << "Layer" <<m_listLayer[0].GetIndexLayer()<<std::endl;
    //Input layer -> input = X
    m_listLayer[0].FeedForward(X);
    // Another layer -> input = A[L-1]
    for(int i = 0; i< static_cast<int>(m_listLayer.size()) - 1; ++i)      // ignore input and output layer
    {
        std::cout << "Layer" <<m_listLayer[i+1].GetIndexLayer()<<std::endl;
        m_listLayer[i+1].FeedForward(m_listLayer[i].GetActFuncVal());
    }
}

void NeuralNetwork::CalBackpropa()
{
    int idx_final = static_cast<int>(m_listLayer.size()) - 1;
    std::cout << "Layer " <<m_listLayer[idx_final].GetIndexLayer()<<std::endl;
    m_listLayer[idx_final].Backpropagation(Y, Matrix(), m_listLayer[idx_final-1].GetActFuncVal(), m_eta);
    for(int i = idx_final - 1; i >= 1 ; --i)      // ignore input and output layer
    {
        std::cout << "Layer " <<m_listLayer[i].GetIndexLayer()<<std::endl;
        m_listLayer[i].Backpropagation(m_listLayer[i+1].GetE(), m_listLayer[i+1].GetWeights(),
                m_listLayer[i-1].GetActFuncVal(), m_eta);
    }
    std::cout << "Layer " <<m_listLayer[0].GetIndexLayer()<<std::endl;
    m_listLayer[0].Backpropagation(m_listLayer[1].GetE(), m_listLayer[1].GetWeights(),
            X, m_eta);
}

void NeuralNetwork::Train(int numStep, double eta)
{
    m_eta = eta;
    for(int i=0; i<numStep;++i)
    {
        std::cout << "========FEED FORWARD======="<<std::endl;
        this->CalFeedForward();
        std::cout << "Data value = " << this->GetCost() << std::endl;
        std::cout << "========BACKPROPAGATION=======" <<std::endl;
        this->CalBackpropa();
    }
}

double NeuralNetwork::GetCost()
{
    int idxFinalLayer = static_cast<int>(m_listLayer.size()) - 1;

    std::cout << "Get cost" << std::endl;
    std::cout << m_listLayer[idxFinalLayer].GetActFuncVal();
    std::cout << m_listLayer[idxFinalLayer].GetActFuncVal().logarit();
    std::cout << Y *m_listLayer[idxFinalLayer].GetActFuncVal().logarit();
    double result =  -(Y * m_listLayer[idxFinalLayer].GetActFuncVal().logarit()).SumAllElem();

    return result;
}
