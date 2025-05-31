#include <iostream>
#include <math.h>
#include <vector>
#include "solver.hpp"

using std::vector;

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
 * @brief Решает квадратное уравнение и возвращает корни.
 * @param equation Уравнение для решения.
 * @return Структура Roots:
 * - При D < 0: roots = {NaN, NaN}, answerType = NO_ROOTS.
 * - При D = 0: roots = {x, x}, answerType = ONE_ROOT.
 * - При D > 0: roots = {x1, x2}, answerType = TWO_ROOTS.
 * - Если a = 0 и b = 0: проверяется c (INFINITE_ROOTS или NO_ROOTS).
 */

Roots solveQuadraticEquation(QuadraticEquation& equation) {
    Roots answer;

    double const a = equation.a;
    double const b = equation.b;
    double const c = equation.c;
    if (a == 0) {
        if (b == 0) {
            if (c == 0) answer.answerType = INFINITE_ROOTS;
            else answer.answerType = NO_ROOTS;
            answer.roots.push_back(NAN);
            answer.roots.push_back(NAN);
        } else {
            answer.answerType = ONE_ROOT;
            answer.roots.push_back(-c / b);
            answer.roots.push_back(-c / b);
        }
    } else {
        double const discriminant = getDiscriminant(a, b, c);
        if (discriminant < 0) {
            answer.answerType = NO_ROOTS;
            answer.roots.push_back(NAN);
            answer.roots.push_back(NAN);
        }
        else {
            answer.answerType = TWO_ROOTS;
            answer.roots.push_back((-b + sqrt(discriminant)) / (2.0 * a));
            answer.roots.push_back((-b - sqrt(discriminant)) / (2.0 * a));
        }
    }

    return answer;
}