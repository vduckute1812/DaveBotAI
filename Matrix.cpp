#include "Matrix.h"

Matrix::Matrix()
{
    this->m_numRow = 0;
    this->m_numCol = 0;
}

void Matrix::GenerateRandomData(bool isRandom)
{
	std::vector<double> tmp_datas;
	double rand_value;
	for (int i = 0; i < m_numRow; i++)
	{
		for (int j = 0; j < m_numCol; j++)
		{
			rand_value = 1.0 / double((rand() % 100 + 1.0));
			if (isRandom)
			{
				tmp_datas.push_back(rand_value);
			}
			else {
				tmp_datas.push_back(0);
			}
		}
		m_datas.push_back(tmp_datas);
		tmp_datas.clear();
	}
}

Matrix::Matrix(int numRow, int numCol, bool isRandom)
{
	m_numRow = numRow;
	m_numCol = numCol;

	GenerateRandomData(isRandom);
}

Matrix::Matrix(const std::vector<std::vector<double>>& datas)
{
	m_numRow = static_cast<int>(datas.size());
	m_numCol = static_cast<int>(datas[0].size());
	std::vector<double> tmp_datas;
	for (int i = 0; i < m_numRow; i++)
	{
		for (int j = 0; j < m_numCol; j++)
		{
			tmp_datas.push_back(datas[i][j]);
		}
		m_datas.push_back(tmp_datas);
		tmp_datas.clear();
	}
}

Matrix::Matrix(const Matrix & mat)
{
	m_numRow = mat.GetNumRow();
	m_numCol = mat.GetNumCol();
	std::vector<double> tmp_datas;
	for (size_t i = 0; i < m_numRow; i++)
	{
		for (int j = 0; j < m_numCol; j++)
		{
			tmp_datas.push_back(mat.GetValue(i, j));
		}
		m_datas.push_back(tmp_datas);
		tmp_datas.clear();
	}
}

Matrix::~Matrix()
{
}

void Matrix::SetValue(int r, int c, double data)
{
	m_datas[r][c] = data;
}

Matrix Matrix::Dot(const Matrix& mat)
{
    Matrix result(this->GetNumRow(), mat.GetNumCol(), false);
    double data;

    if (this->GetNumCol() != mat.GetNumRow())
    {
        std::cout << "Can't dot (" << this->GetNumRow() << ", " << this->GetNumCol()
            << ") * (" << mat.GetNumRow() << ", " << mat.GetNumCol() <<")" << std::endl;
        return result;
    }

    for (int i = 0; i < this->GetNumRow(); i++)
    {
        for (int j = 0; j < this->GetNumCol(); j++)
        {
            for (int k = 0; k < mat.GetNumCol(); k++)
            {
                data = result.GetValue(i, k);
                data += m_datas[i][j] * mat.GetValue(j, k);
                result.SetValue(i, k, data);
            }
        }
    }
    return result;
}

Matrix Matrix::T()
{
    Matrix result(this->GetNumCol(), this->GetNumRow(), false);

    for(int i=0; i < this->GetNumRow(); ++i)
    {
        for(int j=0; j<this->GetNumCol(); ++j)
        {
            result.SetValue(j, i, m_datas[i][j]);
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix & mat)
{
    Matrix result(this->GetNumRow(), this->GetNumCol(), false);
    double data;
    if (this->GetNumRow() != mat.GetNumRow() && this->GetNumCol() != mat.GetNumCol())
    {
        std::cout << "Can't multiply (" << this->GetNumRow() << ", " << this->GetNumCol()
            << ") * (" << mat.GetNumRow() << ", " << mat.GetNumCol() <<")" << std::endl;
        return result;
    }

    for(int i=0; i < this->GetNumRow(); ++i)
    {
        for(int j=0; j<this->GetNumCol(); ++j)
        {
            data = m_datas[i][j]*mat.GetValue(i,j);
            result.SetValue(i, j, data);
        }
    }
    return result;
}

Matrix Matrix::operator*(const double & _alpha)
{
	Matrix result = *this;
	double data;

	for (int i = 0; i < this->GetNumRow(); i++)
	{
		for (int j = 0; j < this->GetNumCol(); j++)
		{
			data = _alpha* result.GetValue(i, j);
			result.SetValue(i, j, data);
		}
	}
	return result;
}

Matrix Matrix::operator+(const Matrix & mat)
{
	Matrix result(this->GetNumRow(), this->GetNumCol(), false);
	double data;

	if (this->GetNumCol() != mat.GetNumCol() && this->GetNumRow() != mat.GetNumRow())
	{
		std::cout << "Can't add (" << this->GetNumRow() << ", " << this->GetNumCol()
			<< ") * (" << mat.GetNumRow() << ", " << mat.GetNumCol() << ")" << std::endl;
		return result;
	}

	for (int i = 0; i < this->GetNumRow(); i++)
	{
		for (int j = 0; j < this->GetNumCol(); j++)
		{
			data = this->m_datas[i][j] + mat.GetValue(i, j);
			result.SetValue(i, j, data);
		}
	}
	return result;
}

double Matrix::GetValue(int r, int c) const
{
	return m_datas[r][c];
}

int Matrix::GetNumRow() const
{
	return m_numRow;
}

int Matrix::GetNumCol() const
{
	return m_numCol;
}

void Matrix::PrintToConsole()
{
	std::cout << std::endl << "=====MATRIX VALUE======" << std::endl;
	for (int i = 0; i < m_numRow; i++)
	{
		for (int j = 0; j < m_numCol; j++)
		{
			std::cout << m_datas[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

const std::ostream &operator << (std::ostream &out, const Matrix &mat){
    out << std::endl << "=====MATRIX VALUE======" << std::endl;
    for (int i = 0; i < mat.GetNumRow(); i++)
    {
        for (int j = 0; j < mat.GetNumCol(); j++)
        {
            out << mat.GetValue(i, j) << " ";
        }
        out << std::endl;
    }
    return out;
}
