#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>

using namespace std;

class function_t
{
private:
	string function = "f(x) = exp(-0.1*x)*sin(x)-2 ";
	float a = -3;
	float b = 0;
public:
	function_t()
	{
	}

	function_t(float a_different, float b_different)
	{
		a = a_different;
		b = b_different;
	}

	float solve_function_for(float x)
	{
		float y = exp(-0.1 * x) * sin(x) - 2; 
		return y;
	}

	float optimal_passive_search_for_N_dotes(int N)
	{
		float current_minimal_y = solve_function_for(a);
		float x_k_constpart = (b - a) / (N + 1);
		float x_k;
		float current_minimal_x = a;
		for (unsigned int k = 1; k <= N; k++)
		{
			x_k = a + x_k_constpart * k;
			if (solve_function_for(x_k) < current_minimal_y)
			{
				current_minimal_y = solve_function_for(x_k);
				current_minimal_x = x_k;
			}
			/*	else
				{
					break;
				}  */
		}
		return current_minimal_x;
	}



	ostream& write_defaults(ostream& stream) 
	{
		stream << endl << "исходная функция: " << function << endl;
		stream << "левое значение интервала: " << a << endl;
		stream << "правое значение интервала: " << b << endl;
		stream << "значение функции на левом конце интервала: " << solve_function_for(a) << endl;
		stream << "значение функции на правом конце интервала: " << solve_function_for(b) << endl;

		return stream;
	}

	ostream& optimal_passive_search(ostream& stream) 
	{
		stream << endl << "_____________________________________________" << endl;
		stream << "|Количество точек (N)| Значение х в минимуме|" << endl;
		for (unsigned int i = 1; i <= 50; i++)
		{
			float x_k_constpart = (b - a) / (i + 1);
			stream  << "|" << setw(20) << i
				<< "|" << setw(9)
				<< floor(optimal_passive_search_for_N_dotes(i) * 100)/100 
				<< setw(2) << " +- " << setw(9) << floor(x_k_constpart * 100)/100
				<< "|" << endl;
		}
		return stream;
	}

	ostream& dichotomy_search(ostream& stream)
	{
		stream << endl << 
				  "_____________________________________________________________" << endl;
		stream << "|  Начало   |   Конец   |   Длина   |           |           |" << endl;
		stream << "| интервала | интервала | интервала |    f(ak)  |    f(bk)  |" << endl;
		stream << "|   (ak)    |   (bk)    |    (l)    |           |           |" << endl;
		stream << "-------------------------------------------------------------" << endl;

		float epsilon_ = 0.1;
		float increment = (epsilon_ * 0.8) / 2;
		float x_left_side, x_right_side;

		float a_temp = a;
		float b_temp = b;

		do
		{
			x_left_side = (a_temp + b_temp) / 2 - increment;
			x_right_side = (a_temp + b_temp) / 2 + increment;

			if (solve_function_for(x_left_side) >= solve_function_for(x_right_side))
			{
				a_temp = x_left_side;
			}
			else
			{
				b_temp = x_right_side;
			}
			stream << "|" << setw(11) << a_temp << "|" << setw(11) << b_temp
				<< "|" << setw(11) << b_temp - a_temp << "|" << setw(11)
				<< solve_function_for(a_temp) << "|" << setw(11)
				<< solve_function_for(b_temp) << "|" << endl;
		} while ((b_temp - a_temp) > epsilon_);
		stream << "_____________________________________________________________" << endl;
		return stream;
	}
	
};

int main()
{
	setlocale(LC_ALL, "Russian");
	function_t main_function;
	main_function.write_defaults(cout);
	main_function.optimal_passive_search(cout);
	main_function.dichotomy_search(cout);
	return 0;

}
