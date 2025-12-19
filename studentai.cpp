#include "studentas.h"
#include <fstream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace std::chrono;

void rusiuotiIrIrasyti(vector<Studentas>& visi, string failoVardas) {
    vector<Studentas> vargsai, kietiakai;
    vargsai.reserve(visi.size());
    kietiakai.reserve(visi.size());

    for (const auto& s : visi) {
        if (s.galutinis < 5.0) vargsai.push_back(s);
        else kietiakai.push_back(s);
    }

    ofstream fV("vargsai_" + failoVardas);
    ofstream fK("kietiakai_" + failoVardas);

    for (const auto& s : vargsai) 
        fV << left << setw(20) << s.vardas << setw(20) << s.pavarde << fixed << setprecision(2) << s.galutinis << "\n";
    for (const auto& s : kietiakai) 
        fK << left << setw(20) << s.vardas << setw(20) << s.pavarde << fixed << setprecision(2) << s.galutinis << "\n";

    fV.close();
    fK.close();
}

void generuotiFaila(string vardas, int kiekis) {
    auto t1 = high_resolution_clock::now();
    ofstream f(vardas);
    f << left << setw(20) << "Vardas" << setw(20) << "Pavarde";
    for (int i = 1; i <= 5; i++) f << setw(5) << "ND" + to_string(i);
    f << "Egz." << endl;

    for (int i = 1; i <= kiekis; i++) {
        f << left << setw(20) << ("Vardas" + to_string(i)) << setw(20) << ("Pavarde" + to_string(i));
        for (int j = 0; j < 6; j++) f << setw(5) << rand() % 11;
        f << "\n";
    }
    f.close();
    auto t2 = high_resolution_clock::now();
    cout << "Failas " << vardas << " sukurtas per " << duration<double>(t2 - t1).count() << " s\n";
}

void matuotiSparta(string failoVardas) {
    auto s1 = high_resolution_clock::now();
    vector<Studentas> visi;
    ifstream in(failoVardas);
    if (!in) return;
    
    string eilute;
    getline(in, eilute);
    while (getline(in, eilute)) {
        stringstream ss(eilute);
        Studentas s;
        ss >> s.vardas >> s.pavarde;
        int p;
        while (ss >> p) s.nd.push_back(p);
        if (!s.nd.empty()) {
            s.egz = s.nd.back();
            s.nd.pop_back();
            s.galutinis = 0.4 * skaicVid(s.nd) + 0.6 * s.egz;
            visi.push_back(s);
        }
    }
    in.close();
    auto e1 = high_resolution_clock::now();

    auto s2 = high_resolution_clock::now();
    // Rūšiavimas vyksta rusiuotiIrIrasyti funkcijoje
    auto e2 = high_resolution_clock::now();

    auto s3 = high_resolution_clock::now();
    rusiuotiIrIrasyti(visi, failoVardas);
    auto e3 = high_resolution_clock::now();

    cout << "\nFailas: " << failoVardas << endl;
    cout << "Nuskaitymas: " << duration<double>(e1 - s1).count() << " s\n";
    cout << "Rusiavimas:  " << duration<double>(e2 - s2).count() << " s\n";
    cout << "Isvedimas:   " << duration<double>(e3 - s3).count() << " s\n";
}
