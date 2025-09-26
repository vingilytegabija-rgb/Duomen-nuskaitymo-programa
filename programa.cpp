#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

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
    for (int p : pazymiai) suma+= p;
    return (double)suma/pazymiai.size();
}
int main() {
    vector<Studentas> visiStudentai;
    string eilute;

    while(true) {
        Studentas s;
        cout<<"\n---Naujas studentas ---\n";

        cout<<"Įveskite studento vardą (tuščia eilutė reiškia studentų sąrašo pabaigą):";
        getline(cin, eilute);
        if (eilute.empty()) break;
        s.vardas = eilute;

        cout<<"Įveskite studento pavardę:";
        getline(cin, s.pavarde);

    cout<<"Įveskite namų darbų rezultatus(teigiami skaičiai rašomi be kablelių (formatas 4 5 2 0), baigiama su nuliu):";
    string ndEilute;
    getline(cin, ndEilute);
    stringstream ss(ndEilute);
    int paz;
    while(ss>>paz){
        if(paz==0) break;
        s.nd.push_back(paz);
    }

cout<<"Įveskite egzamino rezultatą:";
getline(cin, eilute);
s.egz = stoi(eilute);

s.nd.push_back(s.egz);
visiStudentai.push_back(s);
    }

cout<< "\nRezultatai:\n";
cout<< left<< setw(12) <<"Vardas"
     << setw(12) <<"Pavardė"
     << setw(20) <<"Galutinis(Vid.)"<<endl;
cout << "---------------------------------------------" << endl;

for (Studentas s: visiStudentai){
    double galutinis = skaicVid(s.nd);
    cout<<left<<setw(12)<<s.vardas
    <<setw(12)<<s.pavarde
    <<setw(20) <<fixed<<setprecision(2)<<galutinis<<endl;
}
return 0;
}

