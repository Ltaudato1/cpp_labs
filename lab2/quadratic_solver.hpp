#pragma once

enum AnswerType {
    INFINITE_ROOTS,
    TWO_ROOTS,
    ONE_ROOT,
    NO_ROOTS
};

using Roots = struct {
    vector<double> roots;
    AnswerType answerType;
};

using QuadraticEquation = struct {
    double a;
    double b;
    double c;
};

Roots& solveQuadraticEquation(QuadraticEquation& const equation);
