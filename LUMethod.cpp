#include "LUMethod.h"
#include <iomanip>
#include <vector>
using namespace std;

LUMethod::LUMethod(vector<vector<double>>& matrix)
{
	this->matrix = matrix;
}

vector<double> LUMethod::solve()
{
	LU();
	calculateY();
	calculateX();
	return x;
}

void LUMethod::calculateY() //Ly = d, где d - из LUx = d
{
	y.resize(matrix.size()); 
	for (int i = 0; i < matrix.size(); i++) {
		y[i] = matrix[i].back();
	}
	for (int i = 1; i < matrix.size(); i++) {
		for (int k = 0; k < i; k++) {
			y[i] -= L[i][k] * y[k];
		}
	}
}

void LUMethod::calculateX() //Ux = y
{
	x.resize(y.size());
	for (int i = 0; i < y.size(); i++) {
		x[i] = y[i];
	}
	for (int i = y.size() - 1; i >= 0; --i) {
		for (int j = i + 1; j < y.size(); j++) {
			x[i] -= U[i][j] * x[j];
		}
		x[i] /= U[i][i];
	}
}

void LUMethod::LU() //делаем матрицу и выводим
{
	L.resize(matrix.size(), vector<double>(matrix.size()));
	U.resize(matrix.size(), vector<double>(matrix.size()));
	double sum = 0;

	for (int i = 0; i < matrix.size(); i++) { //произошло определение элементов по формулам
		for (int j = 0; j < matrix.size(); j++) {
			U[0][i] = matrix[0][i];
			L[i][0] = matrix[i][0] / U[0][0];

			sum = 0;

			for (int k = 0; k < i; k++) {
				sum += L[i][k] * U[k][j];
			}
			U[i][j] = matrix[i][j] - sum;
			if (j < i) {
				L[j][i] = 0;
			}
			else {
				sum = 0;
				for (int k = 0; k < i; ++k) {
					sum += L[j][k] * U[k][i];
				}

				L[j][i] = (matrix[j][i] - sum) / U[i][i];

			}
		}
	}

	//ВЫВОД МАТРИЦ
	cout << "L" << "\n";
	cout << fixed << showpoint;
	cout << setprecision(7);

	for (vector<double> a : L) { //записываем из L в вектор a значения
		for (double f : a) {
			cout << f << "\t";
		}
		cout << "\n";
	}

	cout << "U" << "\n";

	for (vector<double> a : U) {
		for (double f : a) {
			cout << f << "\t";
		}
		cout << "\n";
	}
}