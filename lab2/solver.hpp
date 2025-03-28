#pragma once

#include <vector>

enum AnswerType {
    INFINITE_ROOTS,
    TWO_ROOTS,
    ONE_ROOT,
    NO_ROOTS
};

struct Roots {
    std::vector<double> roots;
    AnswerType answerType;
};

struct QuadraticEquation {
    double a;
    double b;
    double c;
};

Roots solveQuadraticEquation(QuadraticEquation& equation);
