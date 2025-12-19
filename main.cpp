#include "studentas.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <ctime>

using namespace std;

int main() {
    srand((unsigned)time(0));
    vector<Studentas> visiStudentai;
    string eilute;

    cout << "Pasirinkite veiksma:\n";
    cout << "1. Ivesti studentu duomenis rankiniu budu\n";
    cout << "2. Nuskaityti studentu duomenis is pasirinkto failo\n";
    cout << "3. Sugeneruoti 5 testinius failus (nuo 1 000 iki 10 000 000)\n";
    cout << "Jusu pasirinkimas: ";
    
    int veiksmas;
    if (!(cin >> veiksmas)) return 0;
    cin.ignore();

    if (veiksmas == 3) {
        vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
        for (int d : dydziai) {
            string fVardas = "studentai_" + to_string(d) + ".txt";
            generuotiFaila(fVardas, d);
        }
        cout << "\nVisi failai sukurti. Programa baigia darba.\n";
        return 0;
    }

    if (veiksmas == 2) {
        string failoVardas;
        cout << "Iveskite norimo failo pavadinima (pvz., studentai_1000.txt): ";
        getline(cin, failoVardas);

        ifstream in(failoVardas);
        if (!in) {
            cerr << "Nepavyko atidaryti failo!" << endl;
            return 1;
        }

        getline(in, eilute); // Praleidžiame antraštės eilutę
        while (getline(in, eilute)) {
            if (eilute.empty()) continue;
            stringstream ss(eilute);
            Studentas s;
            ss >> s.vardas >> s.pavarde;

            int sk;
            while (ss >> sk) s.nd.push_back(sk);

            if (!s.nd.empty()) {
                s.egz = s.nd.back();
                s.nd.pop_back();
                visiStudentai.push_back(s);
            }
        }
        in.close();
    } 
        
    else if (veiksmas == 1) {
        while (true) {
            Studentas s;
            cout << "\n--- Naujas studentas (tuscias vardas - pabaiga) ---\n";
            cout << "Vardas: ";
            getline(cin, s.vardas);
            if (s.vardas.empty()) break;

            cout << "Pavarde: ";
            getline(cin, s.pavarde);

            cout << "Ar generuoti balus atsitiktinai? (y/n): ";
            getline(cin, eilute);
            
            if (eilute == "y" || eilute == "Y") {
                for (int i = 0; i < 5; i++) s.nd.push_back(rand() % 11);
                s.egz = rand() % 11;
            } else {
                cout << "Iveskite ND (baigti - tuscia eilute):\n";
                while (true) {
                    getline(cin, eilute);
                    if (eilute.empty()) break;
                    s.nd.push_back(stoi(eilute));
                }
                cout << "Egzamino balas: ";
                getline(cin, eilute);
                s.egz = stoi(eilute);
            }
            visiStudentai.push_back(s);
        }
    }

    sort(visiStudentai.begin(), visiStudentai.end(), [](const Studentas &a, const Studentas &b) {
        if (a.vardas != b.vardas) return a.vardas < b.vardas;
        return a.pavarde < b.pavarde;
    });

    if (!visiStudentai.empty()) {
        cout << "\n" << left << setw(20) << "Vardas" << setw(20) << "Pavarde" 
             << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
        cout << string(80, '-') << endl;

        for (const auto &s : visiStudentai) {
            double vid = skaicVid(s.nd);
            double med = skaicMediana(s.nd);
            
            // Skaiciuojame galutini bala: 0.4 * ND + 0.6 * Egz
            double galVid = 0.4 * vid + 0.6 * s.egz;
            double galMed = 0.4 * med + 0.6 * s.egz;

            cout << left << setw(20) << s.vardas 
                 << setw(20) << s.pavarde 
                 << setw(20) << fixed << setprecision(2) << galVid 
                 << setw(20) << fixed << setprecision(2) << galMed << endl;
        }
    }

    return 0;
}
