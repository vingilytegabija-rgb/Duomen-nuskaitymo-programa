#ifndef STUDENTAS_H
#d#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <vector>
#include <string>

struct Studentas {
    std::string vardas;
    std::string pavarde;
    std::vector<int> nd;
    int egz;
};

double skaicVid(const std::vector<int>& pazymiai);
double skaicMediana(std::vector<int> pazymiai);

void generuotiFaila(std::string vardas, int kiekis);

#endif
