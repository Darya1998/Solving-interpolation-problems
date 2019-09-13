#include "func.h"
#include "lagranzh.h"
#include "includes.h"
#include "norm.h"
#include "splain.h"

int main() {

	//Создаем первую функцию
	Function f1;
	f1.f = func1;
	f1.limits = make_pair(-1, 1);//границы

	//Равномерная сетка
	vector<double> x_uniform = mass_x_uniform(f1.div_count_much, f1.limits);

	//Заполняем таблицы для 1 функции/Равномерная сетка
	f1.table_init = f1.f(f1.div_count, mass_x_uniform(f1.div_count, f1.limits), f1.table_init);//первоначальная сетка

	// double extrapol = lagranzh_single(f1.table_init, 2.2);
	// cout << "Значение в точке 2.2 = " << extrapol << endl;

	// cout << "Ошибка =  " << extrapol - exp(2.2) << endl;

	//Интерполяция Лагранжом/Равномерная сетка
	f1.table_big = lagranzh_interpol(f1.div_count_much, f1.table_init, f1.table_big, x_uniform);//большая таблица
	write_file(f1.table_big, 1, 'u', 'l');//записали в файл

	//Норма погрешности
	//cout << "Норма погрешности/Интерполяция Лагранжом/Равномерная сетка" << endl;
	vector<pair<double,double>> table_zhach_uniform;
	table_zhach_uniform = f1.f(f1.div_count_much, x_uniform, table_zhach_uniform);
	double error = norm_error(f1.table_big, table_zhach_uniform);
	//cout << error << endl;

	//Интерполяция Сплайном/Равномерная сетка
	vector<vector<double>> three_diag = create_matrix(f1.div_count,f1.table_init);
	vector<vector<double>> coeff_polinom = all_coefficient( solution_coef_c(three_diag), f1.table_init);
	f1.table_big = splain_interpol(f1.div_count_much, x_uniform, f1.table_big, coeff_polinom, f1.table_init);
	write_file(f1.table_big, 1, 'u', 's');//записали в файл

	//Норма погрешности
	cout << "Норма погрешности/Интерполяция Сплайном/Равномерная сетка" << endl;
	error = norm_error(f1.table_big, table_zhach_uniform);
	cout << error << endl;

	//Чебышевская сетка
	// vector<double> x_chebyshev_init = mass_x_chebyshev(f1.div_count, f1.limits);
	// pair<double, double> scope(x_chebyshev_init[0], x_chebyshev_init[x_chebyshev_init.size()-1]);	
	// vector<double> x_chebyshev = mass_x_chebyshev(f1.div_count_much, scope);
	
	// //Заполняем таблицы для 1 функции/Чебышевская сетка
	// f1.table_init = f1.f(f1.div_count, mass_x_chebyshev(f1.div_count, f1.limits), f1.table_init);//первоначальная сетка

	// //Интерполяция Лагранжом/Чебышевская сетка
	// f1.table_big = lagranzh_interpol(f1.div_count_much, f1.table_init, f1.table_big, x_chebyshev);//большая таблица

	// write_file(f1.table_big, 1, 'c', 'l');//записали в файл

	// //Норма погрешности
	// cout << "Норма погрешности/Интерполяция Лагранжом/Чебышевская сетка" << endl;
	// vector<pair<double,double>> table_zhach_chebyshev;
	// table_zhach_chebyshev = f1.f(f1.div_count_much, x_chebyshev, table_zhach_chebyshev);
	// error = norm_error(f1.table_big, table_zhach_chebyshev);
	// cout << error << endl;

	// //Интерполяция Сплайном/Чебышевская сетка
	// three_diag = create_matrix(f1.div_count,f1.table_init);
	// coeff_polinom = all_coefficient( solution_coef_c(three_diag), f1.table_init);
	// f1.table_big = splain_interpol(f1.div_count_much, x_chebyshev, f1.table_big, coeff_polinom, f1.table_init);
	// write_file(f1.table_big, 1, 'c', 's');//записали в файл

	// //Норма погрешности
	// cout << "Норма погрешности/Интерполяция Сплайном/Чебышевская сетка" << endl;
	// error = norm_error(f1.table_big, table_zhach_chebyshev);
	// cout << error << endl;

	return 0;
}
