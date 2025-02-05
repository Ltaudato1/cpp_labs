#include <iostream>

void solve(double const a, double const b, double const c, double *x1, double *x2) {
    if (a == 0) {
        if (b == 0) {
            if (c == 0) std::cout << "Infinitive solutions\n";
            else std::cout << "No real solutions\n";
        } else {
            *x1 = -c / b;
            *x2 = *x1;
        }
    }
}

int main() {
    return 0;
}