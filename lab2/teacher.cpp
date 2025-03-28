#include <iostream>
#include "teacher.hpp"
#include "solver.hpp"

void Teacher::checkEmails() {
    while (!solutions.empty()) {
        Email email = solutions.front();
        solutions.pop();

        string author = email.getAuthor();
        vector<Answer> solutions = email.getCompletedTasks();

        results[author] = 0;

        for (auto solution: solutions) {
            auto rightAnswer = solveQuadraticEquation(solution.equation);
            if ((solution.ans.roots == rightAnswer.roots || rightAnswer.answerType == NO_ROOTS || rightAnswer.answerType == INFINITE_ROOTS)
             && solution.ans.answerType == rightAnswer.answerType) {
                results[author]++;
            }
        }
    }
}