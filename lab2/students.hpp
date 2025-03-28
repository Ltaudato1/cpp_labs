#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "exam.hpp"
#include "email.hpp"

/**
 * @brief Тип студента (влияет на вероятность правильного ответа).
 */
enum StudentType {
    GOOD,    ///< Всегда верный ответ
    AVERAGE, ///< 50% верных ответов
    BAD      ///< Всегда неверный ответ
};

/**
 * @brief Класс, моделирующий студента.
 */
class Student {
private:
    std::string name; ///< Имя студента
    StudentType type; ///< Тип студента
public:
    /**
     * @brief Конструктор.
     * @param name Имя студента.
     * @param type Тип студента (GOOD, AVERAGE, BAD).
     */
    Student(string& name, StudentType type): name(name), type(type) {}
    
    /**
     * @brief Решает уравнения из экзамена и возвращает ответы.
     * @param exam Экзамен с заданиями.
     * @return Email с решениями студента.
     */
    Email passExam(Exam& exam);
};