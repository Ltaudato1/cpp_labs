#include <iostream>
#include <vector>
#include "students.hpp"
#include <cstdlib>

Email& Student::passExam(Exam& const exam) {
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
            answer.push_back({task, solveQuadraticEquation(task)});
        } else {
            vector<double> roots = {0, 0};
            answer.push_back({task, {roots, ONE_ROOT}});
        }
    }

    Email email = Email(answer, this->name);

    return email;

}