#include "studentas.h"
#include <algorithm>
#include <numeric>
#include <iterator>

double skaicVid(const std::vector<int>& pazymiai) {
    if (pazymiai.empty()) return 0;
    double suma = std::accumulate(pazymiai.begin(), pazymiai.end(), 0.0);
    return suma / (double)pazymiai.size();
}

double skaicMediana(std::vector<int> pazymiai) {
    if (pazymiai.empty()) return 0;
    std::sort(pazymiai.begin(), pazymiai.end());
    int n = pazymiai.size();
    if (n % 2 == 0) return (pazymiai[n / 2 - 1] + pazymiai[n / 2]) / 2.0;
    else return pazymiai[n / 2];
}

// Skirstymo taisyklė
bool arVargsiukas(const Studentas& s) {
    return s.galutinis < 5.0;
}

void strategija1(std::vector<Studentas>& bendras, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietiakai) {
    for (const auto& s : bendras) {
        if (arVargsiukas(s)) vargsiukai.push_back(s);
        else kietiakai.push_back(s);
    }
}

void strategija2(std::vector<Studentas>& kietiakai, std::vector<Studentas>& vargsiukai) {
    auto it = kietiakai.begin();
    while (it != kietiakai.end()) {
        if (arVargsiukas(*it)) {
            vargsiukai.push_back(*it);
            it = kietiakai.erase(it); // Lėta operacija vektoriui
        } else {
            ++it;
        }
    }
}

void strategija2List(std::list<Studentas>& kietiakai, std::list<Studentas>& vargsiukai) {
    auto it = kietiakai.begin();
    while (it != kietiakai.end()) {
        if (arVargsiukas(*it)) {
            vargsiukai.push_back(*it);
            it = kietiakai.erase(it); // Labai greita operacija sąrašui
        } else {
            ++it;
        }
    }
}

void strategija3(std::vector<Studentas>& kietiakai, std::vector<Studentas>& vargsiukai) {
    auto it = std::stable_partition(kietiakai.begin(), kietiakai.end(), [](const Studentas& s) {
        return s.galutinis >= 5.0; // Kieti lieka priekyje
    });

    vargsiukai.assign(std::make_move_iterator(it), std::make_move_iterator(kietiakai.end()));
    
    kietiakai.erase(it, kietiakai.end());
}
