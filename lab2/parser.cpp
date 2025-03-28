#include <iostream>
#include <sstream>
#include <string>


/**
 * @brief Функция запрашивает у пользователя коэффициенты a, b и c для квадратного уравнения.
 * 
 * @param a Указатель на переменную для хранения коэффициента a.
 * @param b Указатель на переменную для хранения коэффициента b.
 * @param c Указатель на переменную для хранения коэффициента c.
 * 
 * @note Функция гарантирует, что a, b и c будут корректными числами (double).
 * @note Если ввод некорректен, пользователь будет запрашиваться повторно.
 */

bool getEquation(double *a, double *b, double *c, std::string& const input) {
    double tempA, tempB, tempC;

    std::stringstream ss(input);
    if (ss >> tempA >> tempB >> tempC && ss.eof()) {
        *a = tempA;
        *b = tempB;
        *c = tempC;
        return true;
    } else {
        std::cerr << "Invalid format for string" << std::endl;
        return false;
    }
}