#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono> 

using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
};

double skaicVid(const vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0;
    int suma = 0;
    for (int p : pazymiai) suma += p;
    return (double)suma / pazymiai.size();
}

double skaicMediana(vector<int> pazymiai) {
    if (pazymiai.empty()) return 0;
    sort(pazymiai.begin(), pazymiai.end());
    int n = pazymiai.size();
    if (n % 2 == 0) {
        return (pazymiai[n / 2 - 1] + pazymiai[n / 2]) / 2.0;
    } else {
        return pazymiai[n / 2];
    }
}

void generuotiFaila(string vardas, int kiekis) {
    auto t1 = chrono::high_resolution_clock::now();
    ofstream f(vardas);
    
    // Antraštė
    f << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 1; i <= 15; i++) f << setw(5) << "ND" + to_string(i);
    f << "Egzaminas" << endl;

    for (int i = 1; i <= kiekis; i++) {
        f << left << setw(20) << ("Vardas" + to_string(i))
          << setw(20) << ("Pavarde" + to_string(i));
        
        for (int j = 0; j < 16; j++) {
            f << setw(5) << rand() % 11;
        }
        f << endl;
    }
    f.close();
    
    auto t2 = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = t2 - t1;
    cout << "Failas " << vardas << " sugeneruotas per " << diff.count() << " s.\n";
}

int main() {
    srand((unsigned)time(0));
    vector<Studentas> visiStudentai;
    string eilute;

    cout << "Pasirinkti veiksma:\n";
    cout << "1. Ivesti studentu duomenis rankiniu budu\n";
    cout << "2. Nuskaityti studentu duomenis is pasirinkto failo\n";
    cout << "3. Sugeneruoti 5 testinius failus (nuo 1k iki 10mln)\n";
    cout << "Jusu pasirinkimas: ";
    int veiksmas;
    cin >> veiksmas;
    cin.ignore();

    if (veiksmas == 3) {
        vector<int> dydziai = {1000, 10000, 100000, 1000000, 10000000};
        for (int d : dydziai) {
            string fVardas = "studentai_" + to_string(d) + ".txt";
            generuotiFaila(fVardas, d);
        }
        cout << "\nVisi failai sukurti sekmingai.\n";
        return 0; // Baigiame darbą po generavimo
    }

    if (veiksmas == 2) {
        string failoVardas;
        cout << "Iveskite norimo failo pavadinima: ";
        getline(cin, failoVardas);

        ifstream in(failoVardas);
        if (!in) {
            cerr << "Nepavyko atidaryti failo: " << failoVardas << endl;
            return 1;
        }

        getline(in, eilute); // Praleidžiame antraštę
        while (getline(in, eilute)) {
            if (eilute.empty()) continue;
            stringstream ss(eilute);
            Studentas s;
            ss >> s.vardas >> s.pavarde;

            int sk;
            vector<int> paz;
            while (ss >> sk) paz.push_back(sk);

            if (paz.empty()) continue;

            s.egz = paz.back();
            paz.pop_back();
            s.nd = paz;
            visiStudentai.push_back(s);
        }
        in.close();
    } else {
        while (true) {
            Studentas s;
            cout << "\n--- Naujas studentas ---\n";
            cout << "Iveskite studento varda (tuscia eilute - pabaiga): ";
            getline(cin, eilute);
            if (eilute.empty()) break;
            s.vardas = eilute;

            cout << "Iveskite studento pavarde: ";
            getline(cin, s.pavarde);

            cout << "1. Rankinis ivedimas, 2. Atsitiktinis generavimas: ";
            getline(cin, eilute);
            int pasirinkimas = stoi(eilute);

            if (pasirinkimas == 1) {
                cout << "Iveskite ND rezultatus (tuscias enter - pabaiga):\n";
                while (true) {
                    getline(cin, eilute);
                    if (eilute.empty()) break;
                    s.nd.push_back(stoi(eilute));
                }
                cout << "Iveskite egzamino rezultata: ";
                getline(cin, eilute);
                s.egz = stoi(eilute);
            } else {
                cout << "Kiek ND sugeneruoti? ";
                getline(cin, eilute);
                int ndKiek = stoi(eilute);
                for (int i = 0; i < ndKiek; i++) s.nd.push_back(rand() % 11);
                s.egz = rand() % 11;
            }
            visiStudentai.push_back(s);
        }
    }

    // Rūšiavimas
    sort(visiStudentai.begin(), visiStudentai.end(), [](const Studentas &a, const Studentas &b) {
        if (a.vardas != b.vardas) return a.vardas < b.vardas;
        return a.pavarde < b.pavarde;
    });

    // Rezultatų išvedimas
    cout << "\nRezultatai:\n";
    cout << left << setw(20) << "Vardas" << setw(20) << "Pavarde"
         << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(80, '-') << endl;

    for (const Studentas &s : visiStudentai) {
        vector<int> viskas = s.nd;
        viskas.push_back(s.egz);
        cout << left << setw(20) << s.vardas << setw(20) << s.pavarde
             << setw(20) << fixed << setprecision(2) << (skaicVid(s.nd) * 0.4 + s.egz * 0.6)
             << setw(20) << fixed << setprecision(2) << (skaicMediana(s.nd) * 0.4 + s.egz * 0.6)
             << endl;
    }

    return 0;
}

