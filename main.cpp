#include "studentas.h"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <chrono>

using namespace std;

// Pagalbinė funkcija duomenų nuskaitymui testavimui
void nuskaitytiIsFailo(string failoVardas, vector<Studentas>& studentai) {
    ifstream in(failoVardas);
    if (!in) {
        cout << "Klaida: nepavyko rasti failo " << failoVardas << endl;
        return;
    }
    studentai.clear();
    string eilute;
    getline(in, eilute); // Praleidžiam antraštę
    while (getline(in, eilute)) {
        istringstream iss(eilute);
        Studentas s;
        iss >> s.vardas >> s.pavarde;
        int p;
        while (iss >> p) s.nd.push_back(p);
        s.egz = s.nd.back();
        s.nd.pop_back();
        s.galutinis = 0.4 * skaicVid(s.nd) + 0.6 * s.egz;
        studentai.push_back(s);
    }
}

int main() {
    srand((unsigned)time(0));
    vector<Studentas> visiStudentai;
    string eilute;

    while (true) {
        cout << "\n====================================================\n";
        cout << "1. Ivesti studentus ranka (RODYTI ADRESUS)\n";
        cout << "2. Generuoti failus testavimui\n";
        cout << "3. Atlikti VECTOR ir LIST spartos analize (v0.3)\n";
        cout << "4. TESTUOTI SKIRSTYMO STRATEGIJAS (v1.0)\n";
        cout << "0. Baigti darba\n";
        cout << "====================================================\n";
        cout << "Pasirinkimas: ";
        
        int veiksmas;
        if (!(cin >> veiksmas)) break;
        cin.ignore();

        if (veiksmas == 0) break;

        if (veiksmas == 1) {
            visiStudentai.clear();
            while (true) {
                Studentas s;
                cout << "Vardas (tuscia - pabaiga): ";
                getline(cin, eilute);
                if (eilute.empty()) break;
                s.vardas = eilute;
                cout << "Pavarde: ";
                getline(cin, s.pavarde);
                
                for (int i = 0; i < 5; i++) s.nd.push_back(rand() % 11);
                s.egz = rand() % 11;
                s.galutinis = 0.4 * skaicVid(s.nd) + 0.6 * s.egz;
                
                visiStudentai.push_back(s);
            }
            
            if (!visiStudentai.empty()) {
                cout << "\n--- Studentu adresai atmintyje (Vector) ---\n";
                cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << "Atminties adresas\n";
                cout << "----------------------------------------------------\n";
                for (auto &st : visiStudentai) {
                    cout << left << setw(15) << st.vardas 
                         << setw(15) << st.pavarde 
                         << &st << endl; 
                }
            }
        } 
        else if (veiksmas == 2) {
            vector<int> dydziai = {1000, 10000, 100000, 1000000};
            for (int d : dydziai) {
                generuotiFaila("studentai_" + to_string(d) + ".txt", d);
            }
            cout << "\nFailai sugeneruoti sekmingai.\n";
        }
        else if (veiksmas == 3) {
            vector<int> dydziai = {1000, 10000, 100000, 1000000};
            for (int d : dydziai) {
                string fv = "studentai_" + to_string(d) + ".txt";
                matuotiSpartaVector(fv);
                matuotiSpartaList(fv);
            }
        }
        else if (veiksmas == 4) {
            // v1.0 Strategijų testavimas
            cout << "Iveskite duomenu kieki testui (pvz. 100000): ";
            int n;
            cin >> n;
            string fv = "studentai_" + to_string(n) + ".txt";
            
            vector<Studentas> studentai;
            nuskaitytiIsFailo(fv, studentai);

            if (studentai.empty()) continue;

            cout << "\nPasirinkite strategija (1, 2, 3): ";
            int strat;
            cin >> strat;

            vector<Studentas> vargsiukai;
            auto start = chrono::high_resolution_clock::now();

            if (strat == 1) {
                vector<Studentas> kietiakai;
                strategija1(studentai, vargsiukai, kietiakai);
                cout << "Naudojama 1 strategija (Kopijavimas i du naujus).\n";
            } 
            else if (strat == 2) {
                strategija2(studentai, vargsiukai);
                cout << "Naudojama 2 strategija (Trynimas is vektoriaus).\n";
            } 
            else if (strat == 3) {
                strategija3(studentai, vargsiukai);
                cout << "Naudojama 3 strategija (stable_partition).\n";
            }

            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            cout << "Skaidymas uztruko: " << diff.count() << " s\n";
        }
    }
    return 0;
}
