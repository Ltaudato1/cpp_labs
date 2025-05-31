#include <iostream>
#include <vector>
#include "students.hpp"
#include "solver.hpp"
#include <cstdlib>

Email Student::passExam(Exam& exam) {
    vector<QuadraticEquation> tasks = exam.getTasks();

    int chanceForRightAnswer = 0;
    
    switch (type) {
        case GOOD:
            chanceForRightAnswer = 100;
            break;
        case AVERAGE:
            chanceForRightAnswer = 50;
            break;
        default:
            break;
    }

    vector<Answer> answer;

    for (auto task: tasks) {
        int chance = rand() % 100;
        if (chance < chanceForRightAnswer) {
            Roots roots = solveQuadraticEquation(task);
            answer.push_back({task, roots});
        } else {
            vector<double> roots = {0, 0};
            answer.push_back({task, {roots, ONE_ROOT}});
        }
    }

    Email email = Email(answer, this->name);

    return email;
}