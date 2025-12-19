#include "studentas.h"
#include <fstream>
#include <iomanip>
#include <chrono>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace std::chrono;

template <typename T>
void rusiuotiIrIrasyti(T& visi, string failoVardas, string konteineris) {
    T vargsai, kietiakai;
    
    auto s2 = high_resolution_clock::now();
    for (const auto& s : visi) {
        if (s.galutinis < 5.0) vargsai.push_back(s);
        else kietiakai.push_back(s);
    }
    auto e2 = high_resolution_clock::now();

    auto s3 = high_resolution_clock::now();
    ofstream fV(konteineris + "_vargsai_" + failoVardas);
    ofstream fK(konteineris + "_kietiakai_" + failoVardas);

    for (const auto& s : vargsai) 
        fV << left << setw(20) << s.vardas << setw(20) << s.pavarde << fixed << setprecision(2) << s.galutinis << "\n";
    for (const auto& s : kietiakai) 
        fK << left << setw(20) << s.vardas << setw(20) << s.pavarde << fixed << setprecision(2) << s.galutinis << "\n";

    fV.close();
    fK.close();
    auto e3 = high_resolution_clock::now();

    cout << konteineris << " rusiavimas: " << duration<double>(e2 - s2).count() << " s\n";
    cout << konteineris << " irasymas:  " << duration<double>(e3 - s3).count() << " s\n";
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

void matuotiSpartaVector(string failoVardas) {
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

    cout << "\n--- VECTOR Analize (" << failoVardas << ") ---\n";
    cout << "Nuskaitymas: " << duration<double>(e1 - s1).count() << " s\n";
    
    rusiuotiIrIrasyti(visi, failoVardas, "Vector");
}
void matuotiSpartaList(string failoVardas) {
    auto s1 = high_resolution_clock::now();
    list<Studentas> visi;
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

    cout << "\n--- LIST Analize (" << failoVardas << ") ---\n";
    cout << "Nuskaitymas: " << duration<double>(e1 - s1).count() << " s\n";
    
    rusiuotiIrIrasyti(visi, failoVardas, "List");
}
