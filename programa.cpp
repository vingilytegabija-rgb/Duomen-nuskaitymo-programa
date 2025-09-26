#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>

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

double skaicMediana(vector<int> pazymiai) {
    if (pazymiai.empty()) return 0;
    sort(pazymiai.begin(), pazymiai.end());
    int n = pazymiai.size();
    if (n%2 == 0) {
        return (pazymiai[n/2-1] +pazymiai[n/2]) / 2.0;
    } else {
        return pazymiai[n/2];
    }
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

    cout<<"Įveskite namų darbų rezultatus(po kiekvieno paspausti enter, tuščias enter signalizuoja pabaigą):";
    while(true){
        getline(cin, eilute);
        if(eilute.empty()) break;
        s.nd.push_back(stoi(eilute));
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
     << setw(20) <<"Galutinis(Vid.)"
     << setw(20) <<"Galutinis(Med.)"<<endl;
cout << "---------------------------------------------" << endl;

for (Studentas s: visiStudentai){
    double galutinisVid = skaicVid(s.nd);
    double galutinisMed = skaicMediana(s.nd);
    cout<<left<<setw(12)<<s.vardas
    <<setw(12)<<s.pavarde
    <<setw(20) <<fixed<<setprecision(2)<<galutinisVid
    <<setw(20) <<fixed<<setprecision(2) <<galutinisMed
    <<endl;
}
return 0;
}

