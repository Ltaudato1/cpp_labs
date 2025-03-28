#include <iostream>
#include "teacher.hpp"

void Teacher::checkEmails() {
    while (!solutions.empty()) {
        Email email = solutions.front();
        solutions.pop();

        string author = email.getAuthor();
        vector<Answer> solutions = email.getCompletedTasks();

        results[author] = 0;

        for (auto solution: solutions) {
            auto rightAnswer = solveQuadraticEquation(solution.equation);
            results[author] += ((solution.ans.roots == rightAnswer.roots) && (solution.ans.answerType == solution.ans.answerType));
        }
    }
}