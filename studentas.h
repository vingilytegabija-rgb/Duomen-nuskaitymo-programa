#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egz;
    double galutinis;
};

double skaicVid(const std::vector<int>& pazymiai);
double skaicMediana(std::vector<int> pazymiai);
void generuotiFaila(std::string vardas, int kiekis);
bool arVargsiukas(const Studentas& s); // Reikalinga skirstymui

void matuotiSpartaVector(std::string failoVardas);
void matuotiSpartaList(std::string failoVardas);


void strategija1(std::vector<Studentas>& bendras, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietiakai);

void strategija2(std::vector<Studentas>& kietiakai, std::vector<Studentas>& vargsiukai);
void strategija2List(std::list<Studentas>& kietiakai, std::list<Studentas>& vargsiukai);

void strategija3(std::vector<Studentas>& kietiakai, std::vector<Studentas>& vargsiukai);

#endif
