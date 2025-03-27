#include <iostream>
#include <sstream>
#include <string>

using std::cin;
using std::cout;
using std::getline;
using std::string;
using std::stringstream;

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

void getEquation(double *a, double *b, double *c) {
    string input;
    double tempA, tempB, tempC;

    while (true) {
        cout << "Введите коэффициенты a, b, c через пробел: ";
        getline(cin, input);

        stringstream ss(input);
        if (ss >> tempA >> tempB >> tempC) {
            if (ss.eof()) {
                *a = tempA;
                *b = tempB;
                *c = tempC;
                return;
            }
        }

        cout << "Ошибка ввода! Убедитесь, что ввели три числа через пробел.\n";
        cin.clear();
    }
}