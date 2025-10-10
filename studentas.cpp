#include "studentas.h"
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <iostream>
using namespace std;

Studentas generuotiStudenta(int id, int ndKiek) {
    Studentas s;
    s.vardas = "Vardas" + to_string(id);
    s.pavarde = "Pavarde" + to_string(id);
    for (int i = 0; i < ndKiek; i++)
        s.nd.push_back(rand() % 11);
    s.egz = rand() % 11;
    return s;
}

void sugeneruotiFaila(int studentuKiekis, int ndKiek) {
    string failoVardas = "studentai_" + to_string(studentuKiekis) + ".txt";
    ofstream out(failoVardas);
    if (!out) {
        cerr << "Nepavyko sukurti failo: " << failoVardas << endl;
        return;
    }

    out << "Vardas Pavarde ";
    for (int i = 1; i <= ndKiek; i++) out << "ND" << i << " ";
    out << "Egzaminas\n";

    for (int i = 1; i <= studentuKiekis; i++) {
        Studentas s = generuotiStudenta(i, ndKiek);
        out << s.vardas << " " << s.pavarde << " ";
        for (int balas : s.nd) out << balas << " ";
        out << s.egz << endl;
    }

    out.close();
    cout << "Failas " << failoVardas << " sukurtas su " << studentuKiekis << " įrašų.\n";
}
