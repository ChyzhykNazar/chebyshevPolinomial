/*Для функції f(x) = sin(x) + x, за допомогою поліномів Чебишева визначити
вузли, на основі яких можлива побудова інтерполяційного полінома з
мінімальною максимальною похибкою. У якості відрізка взяти [-8, -3].
Заповнити в цих вузлах нову таблицю значень для f (x) = sin (x) + x і
побудувати по ній інтерполяційний поліном Лагранжа.

/*For function f(x) = sin (x) + x, using Chebyshev polynomials to determine
dots, using this we can to build Chebyshev interpolation polinomial with minimum maximum mistake.
As a segment to take [-8, -3].Fill in these nodes a new table of values for f (x) = sin (x) + x and
build an interpolation Lagrange polynomial on it. 
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>

using namespace std;

//function
double func(double x) {
	return sin(x) + x;
}

//output of vector elements for solved methods
void print(vector<double> vec, vector<double> x) {
	for (int i = 0; i < vec.size(); i++) {
		cout << "Solution in point: " << x[i] << " = " << vec[i] << endl;
	}
	cout << endl;
}

//output of vector elements
void print(vector<double> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

//output of error between the exact and found value
void eps(vector<double> vec, vector<double> x) {
	for (int i = 0; i < vec.size(); i++) {
		cout << "Precision in point: " << x[i] << " = " << setw(10) << abs(abs(vec[i]) - abs(func(x[i]))) << endl;
	}
}

//lagrange polinomial
void polinomLagrange(vector<double> x, vector<double> _x, vector<double> _y) {
	cout << "________Answer method of Lagrange multipliers________________" << endl;
	vector<double> result;
	for (int i = 0; i < x.size(); i++) {
		double sum = 0;
		for (int j = 0; j < _x.size(); j++) {
			double mul = 1;
			for (int k = 0; k < _x.size(); k++) {
				if (j != k) {
					mul *= (x[i] - _x[k]) / (_x[j] - _x[k]);
				}
			}
			sum += _y[j] * mul;
		}
		result.push_back(sum);
	}
	print(result, x);
	eps(result, x);
}

//finding x
double getChebyshevX(double left, double right, double k, int n) {
	double t = cos(((2 * k + 1) * 3.14159265358979323846 / 2 / n));
	return (left + right) / 2 + ((right - left) * t) / 2;
}

//Chebyshev polinomial
void chebeshev(vector<double> x, vector<double> xv) {
	vector<double> _x;
	vector<double> _y;
	int size = xv.size();
	cout << endl << "______Differnce Chebysh with Lagrange multipliers____________ " << endl << endl;
	for (int i = 0; i < 4; i++) {
		_x.push_back(getChebyshevX(-8, -3, i, size));			//getting х from Chebyshev polinomialз полінома Чебешева
		_y.push_back(func(_x[i]));								//getting у substituting values into the function
	}
	cout << "New Point: " << endl;
	for (int i = 0; i < 4; i++) {
		cout << "x[ " << i << " ] " << _x[i] << " = " << _y[i] << endl;		//output new dot's and new value of the function value at the dot's
	}
	cout << endl;
	polinomLagrange(x, _x, _y);									//using Lagrange polinomial we find solution
}


int main()
{
	double xTemp;
	double yTemp;
	vector<double> _x;
	vector<double> _y;
	vector<double> x;
	ifstream file("data.txt");
	while (!file.eof()) {
		file >> xTemp >> yTemp;
		_x.push_back(xTemp);
		_y.push_back(yTemp);
	}
	file.close();
	ifstream fileEx("chebyshevPolinomial.txt");
	while (!fileEx.eof()) {
		fileEx >> xTemp;
		x.push_back(xTemp);
	}
	fileEx.close();
	cout << "x: ";
	print(_x);
	cout << "y: ";
	print(_y);
	cout << "Dots: ";
	print(x);
	cout << endl;
	chebeshev(x, _x);
}