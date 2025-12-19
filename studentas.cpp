#include "studentas.h"
#include <fstream>
#include <iomanip>
#include <chrono>

void generuotiFaila(std::string vardas, int kiekis) {
    std::ofstream f(vardas);
    // Sugeneruojame antraštę
    f << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde";
    for (int i = 1; i <= 5; i++) f << std::setw(5) << "ND" + std::to_string(i);
    f << "Egz." << std::endl;

    for (int i = 1; i <= kiekis; i++) {
        f << std::left << std::setw(20) << ("Vardas" + std::to_string(i))
          << std::setw(20) << ("Pavarde" + std::to_string(i));
        for (int j = 0; j < 6; j++) f << std::setw(5) << rand() % 11;
        f << "\n";
    }
    f.close();
    std::cout << "Failas " << vardas << " sukurtas.\n";
}
    }
