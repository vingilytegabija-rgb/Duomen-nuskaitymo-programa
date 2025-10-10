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

Studentas generuotiStudenta(int i, int ndKiek){
Studentas s;
s.vardas ="Vardas" + to_string(id);
s.pavarde = "Pavarde" + to_string(id);
for (int i = 0; i< ndKiek; i++)
    s.nd.push_back(rand()%11);
s.egz = rand() % 11;
return s;
}

void sugeneruotiFaila(int studentuKiekies, int ndKiek) {
string failoVardas = "studentai_" + to_string(studentuKiekis) + ".txt";
pfstream out(failoVardas);
if(!out) {
cerr << "Nepavyko sukurti failo:"<<failoVardas <<endl;
return;
}
cout<<"Vardas Pavarde ND1 ND2 ND3 ... Egzaminas" <<endl;
for (int i = 1; i<=studentuKiekis; i++) {
Studentas s = sugeneruotiStudenta(i, ndKiek);
out <<s.vardas<<""<<s.pavarde<<"";
for (int balas :s.nd) out<<balas<<"";
out <<s.egz<<endl;
}
out.close();
cout<<"Failas"<<failoVardas<<"sukurtas su"<<studentuKiekis<< " įrašų.\n";
}
    
int main() {
    srand((unsigned)time(0));
    vector<Studentas> visiStudentai;
    string eilute;

    cout<< "Pasirinkti duomenų įkelimo būdą:\n";
    cout<< "1. Įvesti studentų duomenis rankiniu būdu\n";
    cout<< "2. Nuskaityti studentų duomenis iš pasirinkto failo\n:";
    cout<< "3. Sugeneruoti studentų sąrašų failus\n";
    cout<< "Jūsų pasirinkimas:";
    int veiksmas;
    cin >> veiksmas;
    cin.ignore();

    if (veiksmas==3){
        vector<int> kiekiai={1000, 10000, 100000, 1000000, 10000000};
        int ndKiek= 5;
        for (int k : kiekiai) {
            sugeneruotiFaila(k, ndKiek);
        }

    if(veiksmas == 2) {
        string failoVardas;
        cout << "Įveskite norimo failo pavadinimą:";
        getline(cin, failoVardas);

        ifstream in(failoVardas);
        if (!in) {
            cerr << "Nepavyko atidaryti failo:" << failoVardas << endl;
            return 1;
        }

    getline(in, eilute);
        while(getline(in,eilute)) {
            if (eilute.empty()) continue;

            stringstream ss(eilute);
            Studentas s;
            ss >> s.vardas >> s.pavarde;
            vector<int> paz;
            int sk;
            while (ss >> sk) paz.push_back(sk);

            if(paz.empty()) continue;

            s.egz = paz.back();
            paz.pop_back();
            s.nd = paz;

            visiStudentai.push_back(s);
        }
        in.close();
    }
    else {
    while(true) {
        Studentas s;
        cout << "\n---Naujas studentas ---\n";
        cout << "Įveskite studento vardą (tuščia eilutė reiškia studentų sąrašo pabaigą):";
        getline(cin, eilute);
        if (eilute.empty()) break;
        s.vardas = eilute;

        cout << "Įveskite studento pavardę:";
        getline(cin, s.pavarde);
        
        cout << "Pasirinkti balų įvedimo būdą:\n";
        cout << "1. Įvesti balus rankiniu būdu\n";
        cout << "2. Sugeneruoti balus atsitiktinai\n";
        cout << "Jūsų pasirinkimas:";
        getline(cin, eilute);

        int pasirinkimas;
        stringstream ss(eilute);
        ss >> pasirinkimas;

        if (pasirinkimas == 1) {
            cout << "Įveskite namų darbų rezultatus(po kiekvieno paspausti enter, tuščias enter signalizuoja pabaigą):";
            while(true) {
                getline(cin, eilute);
                if(eilute.empty()) break;
                s.nd.push_back(stoi(eilute));
       }
cout << "Įveskite egzamino rezultatą:";
getline(cin, eilute);
s.egz = stoi(eilute);
        }
        else if (pasirinkimas == 2) {
            cout << "Įveskite namų darbų kiekį:";
            getline(cin, eilute);
            int ndKiek = stoi(eilute);
            for (int i = 0; i<ndKiek; i++)
                s.nd.push_back(rand()%11);
            s.egz =rand()%11;
        }
        else {
            cout << "Netinkamas pasirinkimas. Studentas nebus įtrauktas";
            continue;
        }
visiStudentai.push_back(s);
    }
}
 sort(visiStudentai.begin(), visiStudentai.end(), [](const Studentas &a, const Studentas &b) {
     if (a.vardas == b.vardas)
        return a.pavarde < b.pavarde;  
     return a.vardas < b.vardas;
      });

vector<Studentas> vargsiukai;
vecotr<Studentas> galvociai;
    for (const Studentas& s: visiStudentai) {
        double ndVid =skaicVid(s.nd);
        double galutinisVid = 0.4*ndVid + 0.6*s.egz;
        if (galutinisVid< 5.0)
            vargsiukai.push_back(s);
        else
            galvociai.push_back(s);
    }
    auto spausdinti = [](const vector<Studentas>& grupe, const string& pavadinimas) {
        cout << "\n=== " << pavadinimas << " ===\n";
cout << left<< setw(15) << "Vardas"
     << setw(15) << "Pavardė"
     << setw(20) << "Galutinis(Vid.)"
     << setw(20) << "Galutinis(Med.)" << endl;
cout << string(70, '-') << endl;

for (const Studentas &s : visiStudentai) {
    double ndVid =skaicVid(s.nd);
    double ndMed = skaicMediana(s.nd);

    double galutinisVid = 0.4 * ndVid + 0.6 * s.egz;
    double galutinisMed = 0.4 * ndMed + 0.6 * s.egz;
    
    cout << left << setw(15) << s.vardas
    << setw(15) << s.pavarde
    << setw(20) << fixed << setprecision(2) << galutinisVid
    << setw(20) << fixed << setprecision(2) << galutinisMed
    << endl;
}
    }
    spausdinti(vargsiukai, "Vargsiukai (galutinis vid. <5.0)");
    spaudinti(galvociai, "Galvociai (galutinis vis >= 5.0)");
return 0;
}

