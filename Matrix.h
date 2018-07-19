#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <iostream>

class Matrix
{
private:
	std::vector<std::vector<double>> m_datas;
	int m_numRow;
	int m_numCol;
	void GenerateRandomData();
public:
	Matrix(int numRow, int numCol, bool isRandom);
	~Matrix();
	int GetNumRow();
	int GetNumCol();
	void PrintToConsole();
	void SetValue(int r, int c, double data);
	double GetValue(int r, int c);
};

#endif