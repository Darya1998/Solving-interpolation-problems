#include "func.h"


//Массив x (первоначальнй/,большой) для равномерной сетки
vector<double> mass_x_uniform(int n, pair<double,double> limits){
	vector<double> x(n);
	double h = fabs(limits.second- limits.first)/(n - 1);
	for (int i = 0; i < (n - 1); i ++){
		x[i] = limits.first + h * i;
	}
	x[n - 1] = limits.second;

	return x;
}

//Массив x (первоначальнй/,большой) для чебышевской сетки
vector<double> mass_x_chebyshev(int n, pair<double,double> limits){
	vector<double> x(n);
	for (int i = 0; i < (n); i++){
		x[i] = (limits.first + limits.second)/2 + (limits.second - limits.first)/2 * cos((2*i + 1) * PI/(2*(n)));
	}
	return x;
}


//Первоначальная таблица аргументов и функций для 1ой функции
vector<pair<double,double>> func1(int n, vector<double> x, vector<pair<double,double>> &table_init){
	table_init.resize(n);
	for (int i = 0; i < x.size(); i++){
		table_init[i].first = x[i];
		table_init[i].second = pow(x[i], 2);
	}
	return table_init;
}

//Первоначальная таблица аргументов и функций для 2ой функции
vector<pair<double,double>> func2(int n, vector<double> x, vector<pair<double,double>> &table_init){
	table_init.resize(n);
	for (int i = 0; i < x.size(); i++){
		table_init[i].first = x[i];
		//table_init[i].second = exp(x[i]);
		table_init[i].second = 1/(1 + 25*pow(x[i], 2));
	}

	return table_init;
}

//Первоначальная таблица аргументов и функций для 3ей функции
vector<pair<double,double>> func3(int n, vector<double> x, vector<pair<double,double>> &table_init){
	table_init.resize(n);
	for (int i = 0; i < x.size(); i++){
		table_init[i].first = x[i];
		table_init[i].second = 1/atan(1 + 10 * pow(x[i], 2));
	}
	return table_init;
}

//Первоначальная таблица аргументов и функций для 4ой функции
vector<pair<double,double>> func4(int n, vector<double> x, vector<pair<double,double>> &table_init){
	table_init.resize(n);
	for (int i = 0; i < x.size(); i++){
		table_init[i].first = x[i];
		table_init[i].second = pow((4 * pow(x[i],3) + 2 * pow(x[i],2) - 4 * x[i] + 2), sqrt(2)) + asin(1/(5 + x[i] - pow(x[i],2))) - 5;
	}

	return table_init;
}

//Функция записывания в файл
void write_file(vector<pair<double,double>> &table_big, int number, char mesh, char interpol){
	string name = "coordinates.dat";
	switch(number){
		case 1: {
			switch(mesh){
				case 'u':{
					switch(interpol){
						case 'l':{
							name = "test1_uniform_lagranzh.dat";
							break;
						}

						case 's':{
							name = "test1_uniform_splain.dat";
							break;
						}
					}
					break;

				}

				case 'c':{
					switch(interpol){
						case 'l':{
							name = "test1_chebyshev_lagranzh.dat";
							break;
						}

						case 's':{
							name = "test1_chebyshev_splain.dat";
							break;
						}
					}
					break;	
				}
			}
			break;
		}	
		case 2:{
			switch(mesh){
				case 'u':{
					switch(interpol){
						case 'l':{
							name = "test2_uniform_lagranzh.dat";
							break;
						}

						case 's':{
							name = "test2_uniform_splain.dat";
							break;
						}
					}
					break;

				}

				case 'c':{
					switch(interpol){
						case 'l':{
							name = "test2_chebyshev_lagranzh.dat";
							break;
						}

						case 's':{
							name = "test2_chebyshev_splain.dat";
							break;
						}
					}
					break;	
				}
				
			}
			break;
		}
		case 3:{
			switch(mesh){
				case 'u':{
					switch(interpol){
						case 'l':{
							name = "test3_uniform_lagranzh.dat";
							break;
						}

						case 's':{
							name = "test3_uniform_splain.dat";
							break;
						}
					}
					break;

				}

				case 'c':{
					switch(interpol){
						case 'l':{
							name = "test3_chebyshev_lagranzh.dat";
							break;
						}

						case 's':{
							name = "test3_chebyshev_splain.dat";
							break;
						}
					}
					break;	
				}
				
			}
			break;
		}
		case 4:{
			switch(mesh){
				case 'u':{
					switch(interpol){
						case 'l':{
							name = "test4_uniform_lagranzh.dat";
							break;
						}

						case 's':{
							name = "test4_uniform_splain.dat";
							break;
						}
					}
					break;

				}

				case 'c':{
					switch(interpol){
						case 'l':{
							name = "test4_chebyshev_lagranzh.dat";
							break;
						}

						case 's':{
							name = "test4_chebyshev_splain.dat";
							break;
						}
					}
					break;	
				}
			}
			break;
		}
	
	}

	ofstream fout (name);
	for (int i = 0; i < table_big.size(); i ++){
		fout << table_big[i].first << "\t" << table_big[i].second << endl;
	}
	fout.close();
}


