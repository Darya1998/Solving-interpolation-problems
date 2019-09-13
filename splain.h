#ifndef _SPLAIN_
#define _SPLAIN_

#include "func.h"
#include "includes.h"

vector<vector<double>> create_matrix(int div_count, vector<pair<double,double>> table_init);
vector<double> solution_coef_c(vector<vector<double>> matrix);
vector<vector<double>> all_coefficient(vector<double> coef_c, vector<pair<double,double>> table_init);
vector<pair<double,double>> splain_interpol(int div_count_much, vector<double> x, vector<pair<double,double>> &table_big, 
                                            vector<vector<double>> matrix_coeff, vector<pair<double,double>> &table_init);




#endif