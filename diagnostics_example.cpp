#include <cmath>
#include <iomanip>
#include <string>
#include "diagnostics.hpp"

using namespace std;

void solve_quadratic_equation(double a, double b, double c) {

	double discr = sqrt(b*b - 4*a*c);

	double x1 = (-b + discr)/(2*a);

	double residual = a*x1*x1 + b*x1 + c;

	double eps = 1.0e-4;

	// Comment out the line below to make a "bug" on purpose
	residual = 0.05;

	ASSERT2((residual>-eps)&&(residual<eps), "residual = " << scientific << residual << ", x1 = " << x1);
}

void expects_input_length_two(const string& s) {

	RT_CHECK(s.size()==2, "expected size is 2, actual size = " << s.size() << ", content: " << s);
}

void diagnostics_example() {

	// (x-1)*(x-2) = x^2 - 3x + 2
	solve_quadratic_equation(1, -3, 2);

	expects_input_length_two("some dummy string"); // assume some user-entered string

}
