#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "solver.hpp"

struct Answer {
    QuadraticEquation equation;
    Roots ans;
};

using std::vector;
using std::string;

/**
 * @brief Класс для загрузки уравнений из файла.
 */
class Exam {
private:
    vector<QuadraticEquation> tasks; ///< Список уравнений
public:
    /**
     * @brief Конструктор, загружающий уравнения из файла.
     * @param filename Имя файла с уравнениями (формат: a b c на каждой строке).
     */
    Exam(std::string& filename);
    
    /**
     * @brief Возвращает список уравнений.
     * @return Константная ссылка на вектор QuadraticEquation.
     */
    const vector<QuadraticEquation>& getTasks() { return tasks; }
};