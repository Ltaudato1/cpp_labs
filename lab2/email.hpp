#pragma once

#include "exam.hpp"

/**
 * @brief Класс для передачи решений студента преподавателю.
 */
class Email {
    private:
        vector<Answer> completedTasks; ///< Список решенных задач
        string author; ///< Имя отправителя
    public:
        /**
         * @brief Конструктор.
         * @param completedTasks Решенные задания.
         * @param author Имя студента.
         */
        Email(vector<Answer>& completedTasks, string& author): completedTasks(completedTasks), author(author) {}
        
        /**
         * @brief Возвращает имя отправителя.
         * @return Ссылка на строку с именем.
         */
        string& getAuthor() { return author; }

        /**
         * @brief Возвращает список решенных задач.
         * @return Ссылка на вектор Answer.
         */
        vector<Answer>& getCompletedTasks() { return completedTasks; }
};