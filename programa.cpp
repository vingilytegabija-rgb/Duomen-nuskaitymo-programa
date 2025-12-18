#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include<ctime>
#include<fstream>

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
    srand((unsigned)time(0));
    vector<Studentas> visiStudentai;
    string eilute;

    cout<<"Pasirinkti duomenu ikelimo buda:\n";
    cout<<"1. Ivesti studentu duomenis rankiniu budu\n";
    cout<<"2. Nuskaityti studentu duomenis is pasirinkto failo\n:";
    cout<<"Jusu pasirinkimas:";
    int veiksmas;
    cin>>veiksmas;
    cin.ignore();

    if(veiksmas == 2){
        string failoVardas;
        cout<<"Iveskite norimo failo pavadinima:";
        getline(cin, failoVardas);

        ifstream in(failoVardas);
        if(!in){
            cerr <<"Nepavyko atidaryti failo:"<<failoVardas<<endl;
            return 1;
        }

    getline(in, eilute);
        while(getline(in,eilute)){
            if (eilute.empty()) continue;
            stringstream ss(eilute);
            Studentas s;
            ss>>s.vardas>>s.pavarde;

            vector<int> paz;
            int sk;
            while (ss>>sk) paz.push_back(sk);

            if(paz.empty()) continue;

            s.egz = paz.back();
            paz.pop_back();
            s.nd = paz;

            visiStudentai.push_back(s);
        }
        in.close();
    } else{
    while(true) {
        Studentas s;
        cout<<"\n---Naujas studentas ---\n";
        cout<<"Iveskite studento varda (tuscia eilute reiskia studentu saraso pabaiga):";
        getline(cin, eilute);
        if (eilute.empty()) break;
        s.vardas = eilute;

        cout<<"Iveskite studento pavarde:";
        getline(cin, s.pavarde);

        int pasirinkimas;
        cout<<"Pasirinkti balu ivedimo buda:";
        cout<<" 1. Ivesti balus rankiniu budu,";
        cout<<" 2. Sugeneruoti balus atsitiktinai.";
        cout<<" Jusu pasirinkimas:";
        getline(cin, eilute);
        stringstream ss(eilute);
        ss>>pasirinkimas;

        if (pasirinkimas == 1){
            cout<<"Iveskite namu darbu rezultatus(po kiekvieno paspausti enter, tuscias enter signalizuoja pabaiga):";
            while(true){
                getline(cin, eilute);
                if(eilute.empty()) break;
                s.nd.push_back(stoi(eilute));
       }
cout<<"Iveskite egzamino rezultata:";
getline(cin, eilute);
s.egz = stoi(eilute);
        }
        else if (pasirinkimas == 2){
            cout<<"Iveskite namu darbu kieki:";
            getline(cin, eilute);
            int ndKiek = stoi(eilute);
            for (int i = 0; i<ndKiek; i++)
                s.nd.push_back(rand()%11);
            s.egz =rand()%11;
        }
        else{
            cout << "Netinkamas pasirinkimas. Studentas nebus itrauktas";
            continue;
        }
visiStudentai.push_back(s);
    }
}
    sort(visiStudentai.begin(), visiStudentai.end(), [](const Studentas &a, const Studentas &b) {
        if (a.vardas != b.vardas) return a.vardas < b.vardas;
        return a.pavarde < b.pavarde;
    });

cout<< "\nRezultatai:\n";
cout<< left<< setw(30) <<"Vardas"
     << setw(30) <<"Pavarde"
     << setw(25) <<"Galutinis(Vid.)"
     << setw(25) <<"Galutinis(Med.)"<<endl;
cout << string(110, '-')<<endl;

for (const Studentas &s : visiStudentai) {
    vector<int> viskas = s.nd;
    viskas.push_back(s.egz);
    cout<<left<<setw(30)<<s.vardas
    <<setw(30)<<s.pavarde
    <<setw(25) <<fixed<<setprecision(2)<<skaicVid(viskas)
    <<setw(25) <<fixed<<setprecision(2) <<skaicMediana(viskas)
    <<endl;
}
return 0;
}  
    spausdinti(vargsiukai, "Vargsiukai (galutinis vid. <5.0)", "vargsiukai.txt");
    spaudinti(galvociai, "Galvociai (galutinis vis >= 5.0)", "galvociai.txt");
return 0;
}

