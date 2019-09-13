#include "splain.h"


//Составили трехдиагональную матрицу
vector<vector<double>> create_matrix(int div_count, vector<pair<double,double>> table_init){
    int n = div_count - 2;
    vector<vector<double>> matrix(4, vector<double> (n));
    
    for (int i = 0; i < (n); i ++){
        matrix[0][i] = table_init[i + 1].first - table_init[i].first;
        if (n == 1){//обрабатываем случа, когда 3 узла
            double h1 = table_init[i + 2].first - table_init[i + 1].first;
            double y1 = table_init[i + 2].second - table_init[i + 1].second;
            double h2 = table_init[i + 1].first - table_init[i].first;
            double y2 = table_init[i + 1].second - table_init[i].second;
            matrix[0][i] = 2 * (h1 + h2);
            matrix[i + 1][i] = 3 * (y1/h1 - y2/h2);//вектор правой части
            matrix.resize(2, vector<double> (n));
            return matrix;
        }

        matrix[1][i] = 2 * ((table_init[i + 1].first - table_init[i].first) + (table_init[i + 2].first - table_init[i + 1].first));
        matrix[2][i] = table_init[i + 2].first - table_init[i + 1].first;
        double h1 = table_init[i + 2].first - table_init[i + 1].first;
        double y1 = table_init[i + 2].second - table_init[i + 1].second;
        double h2 = table_init[i + 1].first - table_init[i].first;
        double y2 = table_init[i + 1].second - table_init[i].second;
        matrix[3][i] = 3 * (y1/h1 - y2/h2);
    }

    matrix[0][0] = 0;
    matrix[2][n-1] = 0;

    return matrix;
}

//Методом прогонки найдем коэффициенты С
vector<double> solution_coef_c(vector<vector<double>> matrix){
    int n = matrix[0].size();
    vector<double> coef_c(n);

    double y;
    int n1 = n - 1;
    vector<double> alpha(n);
    vector<double> beta(n);
    y = matrix[1][0];
    //Обрабатываем случай, когда 3 узла, и матрица 1 на 1
    if (n == 1){
        coef_c.resize(1);
        coef_c[0] = matrix[1][0]/matrix[0][0];
        return coef_c;
    }

    alpha[0] = -matrix[0][1]/y;
    beta[0] = matrix[3][0]/y;

    //ПРЯМОЙ ХОД/ЗАПОЛНЯЕМ МАССИВЫ:АЛЬФА, БЕТА
    for (int i = 1; i < n1; i ++){
        y = matrix[1][i] + matrix[2][i - 1] * alpha[i-1];
        alpha[i] = -matrix[0][i]/y;
        beta[i] = (matrix[3][i]-matrix[2][i] * beta[i-1])/y;
    }

    //ОБРАТНЫЙ ХОД
    coef_c[n1] = (matrix[3][n1] - matrix[2][n1-1]*beta[n1 - 1])/(matrix[1][n1] + matrix[2][n1-1] * alpha[n1 - 1]);
    for (int i = n1 - 1; i >=0; i--){
        coef_c[i] = alpha[i] * coef_c[i + 1] + beta[i];
    }
    return coef_c;
}

//Найдем другие коэффициенты(a,b,d)
vector<vector<double>> all_coefficient(vector<double> coef_c, vector<pair<double,double>> table_init){
    double m = coef_c.size()-1;
    double p = table_init.size()-1;
    double h1 = table_init[1].first - table_init[0].first;
    double g1 = (table_init[1].second - table_init[0].second)/(table_init[1].first - table_init[0].first);
    double gn = (table_init[p].second - table_init[p-1].second)/(table_init[p].first - table_init[p-1].first);
    double c1 = 3/2 * (g1+2)/(h1)-coef_c[0]/2;
    double cn = -2*coef_c[m]+3*(gn-2)/h1;
    coef_c.push_back(1);//вставили элемент на позиции с_0 с_n+1
    coef_c.insert(coef_c.begin(),1);
    coef_c[1] = 1;//Отдельно рассматриваю случай для x^2(это был доп вопрос, к основной программе не имеет отношения)
    int n = table_init.size()-1;
    vector<vector<double>> matrix_coeff(4, vector<double> (n));
    for (int i = 0; i < n; i ++){
        matrix_coeff[0][i] = table_init[i].second; //коэффициенты а
        double g = (table_init[i+1].second - table_init[i].second)/(table_init[i+1].first - table_init[i].first);
        double h = table_init[i+1].first - table_init[i].first;
        matrix_coeff[1][i] = g - (coef_c[i+1] + 2 * coef_c[i])*h/3; //коэффициенты b
        matrix_coeff[3][i] = (coef_c[i+1] - coef_c[i])/(3 * h); //коэффициенты d
    }


    //Перепишем коэффициенты c
    for(int i = 0; i < n; i ++){
        matrix_coeff[2][i] = coef_c[i];
    }
    cout << "Размерность массива с  "<< coef_c.size() << endl;

    for (const auto &v: matrix_coeff){
        for (const auto &n:v){
            cout << n << "   ";
        }
        cout << endl;
    }
    cout << endl;
    return matrix_coeff;
}


vector<pair<double,double>> splain_interpol(int div_count_much, vector<double> x, vector<pair<double,double>> &table_big, 
                                            vector<vector<double>> matrix_coeff, vector<pair<double,double>> &table_init){
    int pos;
    table_big.resize(div_count_much);
    for (int k = 0; k < x.size(); k ++){
        table_big[k].first = x[k];

        //запоминаем, в каком интервале лежит точка
        int i = 0;
        int pos = 0;
        bool result = false;
        while(result == false){
            if (((x[k] >= table_init[i].first) && (x[k] <= table_init[i+1].first)) || ((x[k] <= table_init[i].first) && (x[k] >= table_init[i+1].first))){
                pos = i + 1;
                result = true;                                                 
            }

            i++;
        }
        
        //вычисляем значение кубического полинома в каждой точке.(Береме (pos-1) так как индексация с нуля начинается)
        table_big[k].second = matrix_coeff[0][pos - 1] +  matrix_coeff[1][pos - 1] * (table_big[k].first - table_init[pos - 1].first) + 
                              matrix_coeff[2][pos - 1] * pow((table_big[k].first - table_init[pos - 1].first),2) +
                              matrix_coeff[3][pos - 1] * pow((table_big[k].first - table_init[pos - 1].first),3);




    }


    return table_big;

}
