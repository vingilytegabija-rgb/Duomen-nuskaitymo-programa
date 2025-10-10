#include "skaiciavimai.h"
#include <algorithm>

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
    if (n % 2 == 0)
        return (pazymiai[n / 2 - 1] + pazymiai[n / 2]) / 2.0;
    else
        return pazymiai[n / 2];
}
