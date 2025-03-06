#include <iostream>
#include <math.h>
#include "parser.hpp"
#include "quadratic_solver.hpp"

using std::endl;
using std::isnan;

int main() {
    double a, b, c, d, x1, x2;
    getEquation(&a, &b, &c);
    solveQuadraticEquation(a, b, c, &x1, &x2);
    if (!(isnan(x1) || isnan(x2))) std::cout << "Ответ: " << endl << "x1 = " << x1 << endl << "x2 = " << x2 << endl;
    return 0;
}