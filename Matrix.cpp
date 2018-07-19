#include "Matrix.h"

void Matrix::GenerateRandomData()
{
	for (int i = 0; i < m_numRow ; i++)
	{
		for (int j = 0; j < m_numCol; j++)
		{
			m_datas[i][j] = 1.0 / double((rand() % 100 + 1.0));
		}
	}
}

Matrix::Matrix(int numRow, int numCol, bool isRandom)
{
	m_numRow = numRow;
	m_numCol = numCol;
	if (isRandom)
	{
		GenerateRandomData();
	}
}

Matrix::~Matrix()
{
}

void Matrix::SetValue(int r, int c, double data)
{
	m_datas[r][c] = data;
}

double Matrix::GetValue(int r, int c)
{
	return m_datas[r][c];
}

int Matrix::GetNumRow()
{
	return m_numRow;
}

int Matrix::GetNumCol()
{
	return m_numCol;
}

void Matrix::PrintToConsole()
{
	for (int i = 0; i < m_numRow; i++)
	{
		for (int j = 0; j < m_numCol; j++)
		{
			std::cout << m_datas[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
