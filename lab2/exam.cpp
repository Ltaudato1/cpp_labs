#include "exam.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "parser.hpp"

using std::string;
using std::ifstream;
using std::cerr;
using std::endl;


Exam::Exam(string& const filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Cannot open file " << filename << endl;
        return;
    }

    string line;
    double a, b, c;
    while (getline(infile, line)) {
        if (getEquation(&a, &b, &c, line)) {
            this->tasks.push_back({a, b, c});
        }
    }
}