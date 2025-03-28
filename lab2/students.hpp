#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "exam.hpp"
#include "email.hpp"

using std::vector;
using std::string;

enum StudentType {
    GOOD,
    AVERAGE,
    BAD
};

class Student {
    private:
        string name;
        StudentType type;
    public:
        Student(string& const name, StudentType const type): name(name), type(type) {}

        Email& passExam(Exam& const exam);
};