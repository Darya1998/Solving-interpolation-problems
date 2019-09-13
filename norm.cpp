#include "norm.h"
double norm_error(vector<pair<double,double>> &table_big, vector<pair<double,double>> &table_znach){
    //Найдем разницу между векторами x и x*
    double max = 0;
    
    vector<double> delta_x(table_big.size());
    
    for (int i = 0; i < table_big.size(); i++){
        delta_x[i] = fabs(table_big[i].second - table_znach[i].second);
        if (delta_x[i] > max){
            max = delta_x[i];
        }
    }
    return max;

}