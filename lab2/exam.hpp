#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "solver.hpp"

struct Answer {
    QuadraticEquation equation;
    Roots ans;
};

using std::vector;
using std::string;

class Exam {
    private:
        vector<QuadraticEquation> tasks;
    public:
        Exam(string& filename);
        const vector<QuadraticEquation>& getTasks() { return tasks; }
};