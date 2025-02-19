/**
 * @file quadratic_solver.cpp
 * @brief Решение квадратного уравнения вида ax^2 + bx + c = 0
 * @author [Воронцов Александр]
 * @date [07.02.25]
 */


#include <iostream>
#include "quadratic_solver.hpp"
#include <math.h>

using std::cout;
using std::endl;

/**
 * @brief Вычисляет дискриминант квадратного уравнения.
 * @param a Коэффициент перед x^2.
 * @param b Коэффициент перед x.
 * @param c Свободный член.
 * @return Значение дискриминанта: D = b^2 - 4ac.
 */

double getDiscriminant(double const a, double const b, double const c) {
    return b * b - 4.0 * a * c;
}

/**
 * @brief Решает квадратное уравнение ax^2 + bx + c = 0.
 * 
 * @param a Коэффициент перед x^2.
 * @param b Коэффициент перед x.
 * @param c Свободный член.
 * @param x1 Указатель для записи первого корня (или единственного решения).
 * @param x2 Указатель для записи второго корня (или совпадающего с x1 при одном решении).
 * 
 * @note Если уравнение имеет бесконечно много решений (0 = 0), выводится соответствующее сообщение.
 * @note Если решений нет, выводится сообщение "No solutions", а x1 и x2 присваивается значение NaN (Not a Number).
 * @note Если решений в поле вещественных чисел нет, выводится сообщение "No real solutions", а x1 и x2 присваивается значение NaN (Not a Number)
 * @note В случае одного корня x1 и x2 получают одинаковое значение.
 */

void solveQuadraticEquation(double const a, double const b, double const c, double *x1, double *x2) {
    if (a == 0) {
        if (b == 0) {
            if (c == 0) cout << "Infinitive solutions" << endl;
            else cout << "No solutions" << endl;
            *x1 = NAN;
            *x2 = NAN;
        } else {
            *x1 = -c / b;
            *x2 = *x1;
        }
    } else {
        double const discriminant = getDiscriminant(a, b, c);
        if (discriminant < 0) {
            cout << "No real solutions" << endl;
            *x1 = NAN;
            *x2 = NAN;
        }
        else {
            *x1 = (-b + sqrt(discriminant)) / (2.0 * a);
            *x2 = (-b - sqrt(discriminant)) / (2.0 * a);
        }
    }
}