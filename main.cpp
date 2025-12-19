#include "studentas.h"
#include <iostream>
#include <vector>
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
        cout << "1. Ivesti studentu duomenis rankiniu budu\n";
        cout << "2. Nuskaityti studentu duomenis is pasirinkto failo\n";
        cout << "3. Sugeneruoti 5 testinius failus\n";
        cout << "4. Atlikti sugeneruotu failu SPARTOS ANALIZE\n";
        cout << "0. Baigti darba\n";
        cout << "====================================================\n";
        cout << "Pasirinkimas: ";
        
        int veiksmas;
        if (!(cin >> veiksmas)) break;
        cin.ignore();

        if (veiksmas == 0) break;

        if (veiksmas == 1) {
            while (true) {
                Studentas s;
                cout << "Vardas (tuscia - pabaiga): ";
                getline(cin, eilute);
                if (eilute.empty()) break;
                s.vardas = eilute;
                cout << "Pavarde: ";
                getline(cin, s.pavarde);
                cout << "1. Rankinis, 2. Atsitiktinis: ";
                getline(cin, eilute);
                if (eilute == "2") {
                    for (int i = 0; i < 5; i++) s.nd.push_back(rand() % 11);
                    s.egz = rand() % 11;
                } else {
                    cout << "Iveskite ND (tuscia - pabaiga): ";
                    while (true) {
                        getline(cin, eilute);
                        if (eilute.empty()) break;
                        s.nd.push_back(stoi(eilute));
                    }
                    cout << "Egzaminas: ";
                    getline(cin, eilute);
                    s.egz = stoi(eilute);
                }
                s.galutinis = 0.4 * skaicVid(s.nd) + 0.6 * s.egz;
                visiStudentai.push_back(s);
            }
            if (!visiStudentai.empty()) rusiuotiIrIrasyti(visiStudentai, "is_rankinio_ivedimo.txt");
        } 
        else if (veiksmas == 2) {
            string fv;
            cout << "Failo pavadinimas: ";
            getline(cin, fv);
            ifstream in(fv);
            if (in) {
                getline(in, eilute);
                while (getline(in, eilute)) {
                    stringstream ss(eilute);
                    Studentas s;
                    ss >> s.vardas >> s.pavarde;
                    int sk;
                    while (ss >> sk) s.nd.push_back(sk);
                    if (!s.nd.empty()) {
                        s.egz = s.nd.back();
                        s.nd.pop_back();
                        s.galutinis = 0.4 * skaicVid(s.nd) + 0.6 * s.egz;
                        visiStudentai.push_back(s);
                    }
                }
                in.close();
                rusiuotiIrIrasyti(visiStudentai, fv);
            }
        }
        else if (veiksmas == 3) {
            vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
            for (int d : dydziai) generuotiFaila("studentai_" + to_string(d) + ".txt", d);
        }
        else if (veiksmas == 4) {
            vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
            for (int d : dydziai) matuotiSparta("studentai_" + to_string(d) + ".txt");
        }
    }
    return 0;
}
