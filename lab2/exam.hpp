#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "quadratic_solver.hpp"

using std::pair;

using Answer = struct {
    QuadraticEquation equation;
    Roots roots;
};

using std::vector;
using std::string;

class Exam {
    private:
        vector<QuadraticEquation> tasks;
    public:
        Exam(string& const filename);
        const vector<QuadraticEquation>& getTasks() { return tasks; }
};