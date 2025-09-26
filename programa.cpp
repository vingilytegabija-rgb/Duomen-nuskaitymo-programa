#include <iostream>
#include <vector>
#include <string>
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
int main(){
    Studentas s;
    cout<<"Įveskite studento vardą:";
    cin>>s.vardas;
    cout<<"Įveskite studento pavardę:";
    cin>>s.pavarde;

    cout<<"Įveskite namų darbų rezultatus(teigiami skaičiai rašomi be kablelių (formatas 4 5 2 0), baigiama su nuliu):";
    int paz;
    while(true){
        cin>>paz;
        if(paz==0) break;
        s.nd.push_back(paz);
    }
cout<<"Įveskite egzamino rezultatą:";
cin>>s.egz;

s.nd.push_back(s.egz);
double galutinis = skaicVid(s.nd);

cout<< endl;
cout<< left<< setw(12) <<"Vardas"
     << setw(12) <<"Pavardė"
     << setw(20) <<"Galutinis(Vid.)"<<endl;
cout << "---------------------------------------------" << endl;

cout<<left<<setw(12)<<s.vardas
    <<setw(12)<<s.pavarde
    <<setw(20) <<fixed<<setprecision(2)<<galutinis<<endl;
return 0;
}

