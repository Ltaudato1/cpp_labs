#include <iostream>
#include "exam.hpp"
#include "email.hpp"
#include "students.hpp"
#include "teacher.hpp"
#include "solver.hpp"
#include "parser.hpp"

int main() {
    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned int>(time(0)));

    // Создаём экзамен, считывая уравнения из файла "equations.txt"
    string filename = "equations.txt";
    Exam exam(filename);
    const std::vector<QuadraticEquation>& equations = exam.getTasks();
    if (equations.empty()) {
        std::cerr << "No equations" << std::endl;
        return 1;
    }
    
    // Создаём студентов (имя и тип)
    vector<string> names = {"Andrey", "Artyom", "Vlad"};
    std::vector<Student> students = {
        Student(names[0], GOOD),
        Student(names[1], AVERAGE),
        Student(names[2], BAD)
    };
    
    // Создаём преподавателя
    string teacherName = "Khalidov";
    Teacher teacher = Teacher(teacherName);
    
    // Моделируем рассылку заданий студентам
    // Каждый студент получает каждое уравнение, решает его и отправляет ответ преподавателю.
    for (auto student : students) {
        Email email = student.passExam(exam);
        teacher.receiveEmail(email);
    }
    
    // Преподаватель проверяет все полученные письма
    teacher.checkEmails();
    
    // Публикуем результаты зачёта
    map<string, int> results = teacher.getResults();

    for (auto [key, value] : results) {
        std::cout << key << " : " << value << std::endl;
    }
    
    return 0;
}