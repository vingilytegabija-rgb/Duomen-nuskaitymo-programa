#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include "studentas.h"
#include "skaiciavimai.h"
using namespace std;

int main() {
    srand((unsigned)time(0));
    vector<Studentas> visiStudentai;

    cout << "Pasirinkti duomenų įkelimo būdą:\n";
    cout << "1. Rankinis įvedimas\n";
    cout << "2. Nuskaitymas iš failo\n";
    cout << "3. Sugeneruoti failus\n";
    cout << "Pasirinkimas: ";
    int veiksmas;
    cin >> veiksmas;

    if (veiksmas == 3) {
        vector<int> kiekiai = {1000, 10000, 100000};
        for (int k : kiekiai)
            sugeneruotiFaila(k, 5);
        return 0;
    }

}
