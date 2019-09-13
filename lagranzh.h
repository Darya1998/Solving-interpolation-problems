#ifndef _LAGRANZH_
#define _LAGRANZH_

#include "func.h"
#include "includes.h"

vector<pair<double,double>> lagranzh_interpol(int div_count_much, vector<pair<double,double>> table_init, vector<pair<double,double>> &table_big, 
											  vector<double> x);

double lagranzh_single(vector<pair<double,double>> table_init, double point);//Для одной точки

#endif