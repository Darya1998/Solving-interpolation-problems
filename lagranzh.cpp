#include "lagranzh.h"

vector<pair<double,double>> lagranzh_interpol(int div_count_much, vector<pair<double,double>> table_init, vector<pair<double,double>> &table_big, vector<double> x){
    //Оптимизируем Лагранжа
    vector<double> c(table_init.size());
    for (int i = 0 ; i < table_init.size(); i++){
        c[i] = 1;
    }

    for (int i = 0; i < table_init.size(); i ++){
        for (int j = 0; j < table_init.size(); j++){
            if(j != i){
                c[i] = c[i] * (table_init[i].first - table_init[j].first);
            }
        }
    }

    table_big.resize(div_count_much);
    for(int k = 0; k < x.size(); k++){
        table_big[k].first = x[k];
        double sum = 0; //Значение функции
        for (int i = 0; i < table_init.size(); i ++){
            double mul = 1.0;
            for (int j = 0; j < table_init.size(); j++){
                if(j != i){
                    mul *= (table_big[k].first - table_init[j].first);
                }
            }
            sum += table_init[i].second * mul/c[i];
        }

        
        table_big[k].second = sum;
    }


    // table_big.resize(div_count_much);
    // for(int k = 0; k < x.size(); k++){
    //     table_big[k].first = x[k];
    //     double sum = 0; //Значение функции
    //     for (int i = 0; i < table_init.size(); i ++){
    //         double mul = 1.0;
    //         for (int j = 0; j < table_init.size(); j++){
    //             if(j != i){
    //                 mul *= (table_big[k].first - table_init[j].first)/(table_init[i].first - table_init[j].first);
    //             }
    //         }
    //         sum += table_init[i].second * mul;
    //     }

        
    //     table_big[k].second = sum;
    // }
    return table_big;
}

double lagranzh_single(vector<pair<double,double>> table_init, double point){
    double sum = 0; //Значение функции
    for (int i = 0; i < table_init.size(); i ++){
        double mul = 1.0;
        for (int j = 0; j < table_init.size(); j++){
            if(j != i){
                mul *= (point - table_init[j].first)/(table_init[i].first - table_init[j].first);
            }
        }
        sum += table_init[i].second * mul;
    }

    
    point = sum;

return point;
}