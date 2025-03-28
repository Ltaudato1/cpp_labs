#pragma once

#include "exam.hpp"

class Email {
    private:
        vector<Answer> completedTasks;
        string author;
    public:
        Email(vector<Answer>& completedTasks, string& author): completedTasks(completedTasks), author(author) {}
        string& getAuthor() { return author; }
        vector<Answer>& getCompletedTasks() { return completedTasks; }
};