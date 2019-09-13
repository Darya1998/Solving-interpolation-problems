#ifndef _FUNC_
#define _FUNC_


#include "includes.h"

struct Function{
	Function(){};
	vector<pair<double,double>> (*f)(int n, vector<double> x, vector<pair<double,double>> &table_init) = nullptr;
	pair<double,double> limits;
	int div_count = 3;
	vector<pair<double,double>> table_init;
	int div_count_much = 100;
	vector<pair<double,double>> table_big;

};

vector<double> mass_x_uniform(int n, pair<double,double> limits);
vector<double> mass_x_chebyshev(int n, pair<double,double> limits);
vector<pair<double,double>> func1(int n, vector<double> x, vector<pair<double,double>> &table_init);
vector<pair<double,double>> func2(int n, vector<double> x, vector<pair<double,double>> &table_init);
vector<pair<double,double>> func3(int n, vector<double> x, vector<pair<double,double>> &table_init);
vector<pair<double,double>> func4(int n, vector<double> x, vector<pair<double,double>> &table_init);
void write_file(vector<pair<double,double>> &table_big, int number, char mesh, char interpol);
#endif