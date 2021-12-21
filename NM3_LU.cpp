#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include "LUMethod.h"

#define p 1
#define q 3
#define n 6

using namespace std;

void interpolationCoefficients(vector<vector<double>>& linearsystem, const vector<double>& x, const vector<double>& y)
{ //коэффициенты многочленов P и Q
	for (int j = 0; j < x.size(); j++) {

		for (int pN = 0; pN <= p; pN++) {
			double pNResult = pow(x[j], pN);
			linearsystem[j].push_back(pNResult);
		}

		for (int qM = p + 1; qM < n; qM++) {
			double qMResult = -y[j] * pow(x[j], qM - p);
			linearsystem[j].push_back(qMResult);
		}
		linearsystem[j].push_back(y[j]);
	}
}

double interpolationFunction(double x, vector<double> coeffs)
//функция, задающая нашу рациональную, которой мы интерполируем
{
	double value = 0;
	double up = 0; //значение Pn(x)
	for (int i = 0; i <= p; i++)
	{
		up += coeffs[i] * pow(x, i);
	}
	double down = 1;  //значение Qm(x)
	for (int i = p + 1; i < p + q + 1; i++)
	{
		down += coeffs[i] * pow(x, i - p);
	}
	value = up / down;
	return value;
}

void printResults(const vector<double>& results, const vector<double>& x,
	const vector<double>& y)
{
	double h = (x.back() - x.front()) / 100.0; //шаг интерполяции
	cout << "Our given points:" << "\n\n";

	for (int i = 0; i < n; ++i) {
		cout << "[" << x[i] << "," << y[i] << "], ";
	}
	cout << "\n" << "Interpolation points:" << "\n\n";

	for (int i = 0; i <= 100; ++i) { //всего у нас получается 100 точек для интерполирования
		cout << "[" << x[0] + i * h << "," << interpolationFunction(x[0] + i * h, results) << "], ";
	}

}

int main() {
	vector<double> x{ -2.5, -1.9, -1.3, -0.7, -0.1, 0.5 };
	vector<double> y{ -0.81098, -1.2382, -2.0801, -2.9141, -2.1555, -3.4419 };

	vector<vector<double>> linearsystem(x.size()); //создаем СЛАУ размера вектора x

	interpolationCoefficients(linearsystem, x, y);

	vector<double> results;

	LUMethod lu{linearsystem}; //передаем нашу систему в метод разложения
	results = lu.solve();
	printResults(results, x, y);
	cin.get();
}