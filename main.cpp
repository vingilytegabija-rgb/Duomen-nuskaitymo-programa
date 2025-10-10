#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>    
#include "studentas.h"
#include "skaiciavimai.h"

using namespace std;

int main() {
    srand((unsigned)time(0));
    vector<Studentas> visiStudentai;
    string eilute;

    cout << "Pasirinkti duomenų įkelimo būdą:\n";
    cout << "1. Rankinis įvedimas\n";
    cout << "2. Nuskaitymas iš failo\n";
    cout << "3. Sugeneruoti failus\n";
    cout << "Pasirinkimas: ";
    int veiksmas;
    cin >> veiksmas;
    cin.ignore();


    if (veiksmas == 3) {
        vector<int> kiekiai = {1000, 10000, 100000};
        int ndKiek = 5;

        for (int k : kiekiai) {
            auto start = chrono::high_resolution_clock::now();

            sugeneruotiFaila(k, ndKiek); // studentas.cpp funkcija

            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << "Failo generavimas (" << k << " studentų) uztruko: "
                 << duration.count() << " ms\n";
        }
        return 0;
    }


    if (veiksmas == 2) {
        string failoVardas;
        cout << "Iveskite failo pavadinima: ";
        cin.ignore();
        getline(cin, failoVardas);

        auto startRead = chrono::high_resolution_clock::now();

        ifstream in(failoVardas);
        if (!in) { cerr << "Nepavyko atidaryti failo.\n"; return 1; }

        getline(in, eilute); // ignoruojam header
        while (getline(in, eilute)) {
            if (eilute.empty()) continue;
            stringstream ss(eilute);
            Studentas s;
            ss >> s.vardas >> s.pavarde;
            vector<int> paz;
            int sk;
            while (ss >> sk) paz.push_back(sk);
            s.egz = paz.back(); paz.pop_back();
            s.nd = paz;
            visiStudentai.push_back(s);
        }
        in.close();

        auto endRead = chrono::high_resolution_clock::now();
        auto durationRead = chrono::duration_cast<chrono::milliseconds>(endRead - startRead);
        cout << "Duomenu nuskaitymas uztruko: " << durationRead.count() << " ms\n";
    }

    auto startSort = chrono::high_resolution_clock::now();

    vector<Studentas> vargsiukai;
    vector<Studentas> galvociai;
    for (const Studentas& s : visiStudentai) {
        double galutinisVid = 0.4 * skaicVid(s.nd) + 0.6 * s.egz;
        if (galutinisVid < 5.0) vargsiukai.push_back(s);
        else galvociai.push_back(s);
    }

    auto endSort = chrono::high_resolution_clock::now();
    auto durationSort = chrono::duration_cast<chrono::milliseconds>(endSort - startSort);
    cout << "Studentu rusiuojimas uztruko: " << durationSort.count() << " ms\n";

    auto startWrite = chrono::high_resolution_clock::now();

    auto spausdintiIFaila = [](const vector<Studentas>& grupe, const string& failoVardas) {
        ofstream out(failoVardas);
        if (!out) { cerr << "Nepavyko sukurti failo: " << failoVardas << endl; return; }

        out << "Vardas Pavarde Galutinis(Vid.) Galutinis(Med.)\n";
        for (const Studentas& s : grupe) {
            double ndVid = skaicVid(s.nd);
            double ndMed = skaicMediana(s.nd);
            double galutinisVid = 0.4*ndVid + 0.6*s.egz;
            double galutinisMed = 0.4*ndMed + 0.6*s.egz;
            out << s.vardas << " " << s.pavarde << " "
                << galutinisVid << " " << galutinisMed << "\n";
        }
    };

    spausdintiIFaila(vargsiukai, "vargsiukai.txt");
    spausdintiIFaila(galvociai, "galvociai.txt");

    auto endWrite = chrono::high_resolution_clock::now();
    auto durationWrite = chrono::duration_cast<chrono::milliseconds>(endWrite - startWrite);
    cout << "Isvedimas i failus uztruko: " << durationWrite.count() << " ms\n";

    return 0;
}
    }

}
