#pragma once
#include <vector>
#include <iostream>
using namespace std;

class LUMethod
{
public:
	LUMethod(vector<vector<double>>& matrix);
	vector<double> solve();
private:
	vector<vector<double>> matrix;
	vector<vector<double>> L;
	vector<vector<double>> U;

	vector<double> y;
	vector<double> x;

	void calculateY();
	void calculateX();
	void LU();
};