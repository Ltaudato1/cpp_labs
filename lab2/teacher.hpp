#pragma once

#include <queue>
#include <map>
#include "email.hpp"
#include "solver.hpp"

using std::queue;
using std::map;

/**
 * @brief Класс, моделирующий преподавателя.
 */
class Teacher {
private:
    queue<Email> solutions; ///< Очередь писем с решениями
    map<std::string, int> results; ///< Результаты (имя → баллы)
    string name; ///< Имя преподавателя
public:
    /**
     * @brief Конструктор.
     * @param name Имя преподавателя.
     */
    Teacher(string& name): name(name) {}
    
    /**
     * @brief Принимает письмо от студента.
     * @param email Письмо с решениями.
     */
    void receiveEmail(Email& email) { solutions.push(email); }
    
    /**
     * @brief Проверяет все письма и подсчитывает баллы.
     */
    void checkEmails();
    
    /**
     * @brief Возвращает результаты экзамена.
     * @return Словарь: имя студента → количество верных ответов.
     */
    map<string, int>& getResults() { return results; }
};