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

    cout<<"Pasirinkti duomenų įkelimo būdą:\n";
    cout<<"1. Įvesti studentų duomenis rankiniu būdu\n";
    cout<<"2. Nuskaityti studentų duomenis iš pasirinkto failo\n:";
    cout<<"Jūsų pasirinkimas:";
    int veiksmas;
    cin>>veiksmas;
    cin.ignore();

    if(veiksmas == 2){
        string failoVardas;
        cout<<"Įveskite norimo failo pavadinimą:";
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
    }
    else{
        cin.ignore();
    while(true) {
        Studentas s;
        cout<<"\n---Naujas studentas ---\n";
        cout<<"Įveskite studento vardą (tuščia eilutė reiškia studentų sąrašo pabaigą):";
        getline(cin, eilute);
        if (eilute.empty()) break;
        s.vardas = eilute;

        cout<<"Įveskite studento pavardę:";
        getline(cin, s.pavarde);

        int pasirinkimas;
        cout<<"Pasirinkti balų įvedimo būdą:";
        cout<<" 1. Įvesti balus rankiniu būdu,";
        cout<<" 2. Sugeneruoti balus atsitiktinai.";
        cout<<" Jūsų pasirinkimas:";
        getline(cin, eilute);
        stringstream ss(eilute);
        ss>>pasirinkimas;

        if (pasirinkimas == 1){
            cout<<"Įveskite namų darbų rezultatus(po kiekvieno paspausti enter, tuščias enter signalizuoja pabaigą):";
            while(true){
                getline(cin, eilute);
                if(eilute.empty()) break;
                s.nd.push_back(stoi(eilute));
       }
cout<<"Įveskite egzamino rezultatą:";
getline(cin, eilute);
s.egz = stoi(eilute);
        }
        else if (pasirinkimas == 2){
            cout<<"Įveskite namų darbų kiekį:";
            getline(cin, eilute);
            int ndKiek = stoi(eilute);
            for (int i = 0; i<ndKiek; i++)
                s.nd.push_back(rand()%11);
            s.egz =rand()%11;
        }
        else{
            cout << "Netinkamas pasirinkimas. Studentas nebus įtrauktas";
            continue;
        }
visiStudentai.push_back(s);
    }
}
cout<< "\nRezultatai:\n";
cout<< left<< setw(12) <<"Vardas"
     << setw(12) <<"Pavardė"
     << setw(20) <<"Galutinis(Vid.)"
     << setw(20) <<"Galutinis(Med.)"<<endl;
cout << string(70, '-')<<endl;

for (const Studentas &s : visiStudentai) {
    vector<int> viskas = s.nd;
    viskas.push_back(s.egz);
    cout<<left<<setw(12)<<s.vardas
    <<setw(12)<<s.pavarde
    <<setw(20) <<fixed<<setprecision(2)<<skaicVid(viskas)
    <<setw(20) <<fixed<<setprecision(2) <<skaicMediana(viskas)
    <<endl;
}
return 0;
}

