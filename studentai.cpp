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

    // Matuojame tik įrašymą į failus
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

    cout << konteineris << " rusiavimas uztruko: " << duration<double>(e2 - s2).count() << " s\n";
    cout << konteineris << " irasymas uztruko:  " << duration<double>(e3 - s3).count() << " s\n";
}
