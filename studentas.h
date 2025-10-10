#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
using namespace std;

struct Studentas {
    string vardas;
    string pavarde;
    vector<int> nd;
    int egz;
};

Studentas generuotiStudenta(int id, int ndKiek);
void sugeneruotiFaila(int studentuKiekis, int ndKiek);

#endif
