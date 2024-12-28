#include <iostream>
#include <cmath>
#include <iomanip>

int main() {
    std::cout << std::fixed << std::setprecision(43);

    int n = 100;
    double x[n] = {};
    x[0] = 1.0;
    x[1] = 1.0 / 3.0;
    std::cout << x[0] << std::endl << x[1] << std::endl;

    for (int i = 2; i < n; i++) {
        x[i] = (13.0 / 3.0) * x[i - 1] - (4.0 / 3.0) * x[i - 2]; //bledy moga sie kumulowac z iloscia zaglebien obliczen
        std::cout << x[i] << std::endl;
    }

    //Zalezy ile liczb wezmiemy... taki mozemy miec blad...
    std::cout << "TEST" << std::endl << x[11] << std::endl;
    //Powinno byc to samo co 1/(3^n) ...
    std::cout << (1 / pow(3, 11));
    return 0;
}
