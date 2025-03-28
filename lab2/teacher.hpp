#pragma once

#include <queue>
#include <map>
#include "email.hpp"
#include "solver.hpp"

using std::queue;
using std::map;

class Teacher {
    private:
        queue<Email> solutions;
        map<string, int> results;
        string name;
    public:
        Teacher(string& name): name(name) {}
        void receiveEmail(Email& email) { solutions.push(email); }
        map<string, int>& getResults() { return results; }
        void checkEmails();
};