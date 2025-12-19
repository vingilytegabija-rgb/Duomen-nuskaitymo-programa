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

using namespace std;

int main() {
    srand((unsigned)time(0));
    vector<Studentas> visiStudentai;
    string eilute;

    while (true) {
        cout << "\n====================================================\n";
        cout << "1. Ivesti studentus ranka (RODYTI ADRESUS)\n";
        cout << "2. Generuoti failus testavimui\n";
        cout << "3. Atlikti VECTOR ir LIST spartos analize\n";
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
                
                // Atsitiktinis ND generavimas greitam testui
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
                         << &st << endl; // ISVEDAMAS ADRESAS
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
    }
    return 0;
}
