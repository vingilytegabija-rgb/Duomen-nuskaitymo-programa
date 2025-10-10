#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "studentas.h"
#include "skaiciavimai.h"

using namespace std;

int main() {
    using chrono::high_resolution_clock;
    using chrono::duration_cast;
    using chrono::milliseconds;
    auto visoPradzia = high_resolution_clock::now();
    srand((unsigned)time(0));
    vector<Studentas> visiStudentai;
    string eilute;
    int irasuKiekis = 0;

    cout << "Pasirinkti duomenų įkelimo būdą:\n";
    cout << "1. Rankinis įvedimas\n";
    cout << "2. Nuskaitymas iš failo\n";
    cout << "3. Sugeneruoti failus\n";
    cout << "Pasirinkimas: ";
    int veiksmas;
    cin >> veiksmas;
    cin.ignore();


    if (veiksmas == 3) {
        vector<int> kiekiai = {1000, 10000, 100000};
        int ndKiek = 5;

        for (int k : kiekiai) {
            auto start = chrono::high_resolution_clock::now();

            sugeneruotiFaila(k, ndKiek); 

            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            cout << "Failo generavimas (" << k << " studentų) uztruko: "
                 << duration.count() << " ms\n";
        }
        return 0;
    }



    if (veiksmas == 2) {
        string failoVardas;
        cout << "Iveskite failo pavadinima: ";
        cin.ignore();
        getline(cin, failoVardas);

        auto startRead = chrono::high_resolution_clock::now();

        cout << "Dabartinis darbinis katalogas: " << filesystem::current_path() << endl;
        cout << "Bandome atidaryti failą: " << failoVardas << endl;
        cout << "Pilnas kelias: " << (filesystem::current_path() / failoVardas) << endl;

        ifstream in(failoVardas);
        if (!in) {
            cerr << "Nepavyko atidaryti failo: " << failoVardas << endl;
            cerr << "Pilnas bandytas kelias: " << (filesystem::current_path() / failoVardas) << endl;
            return 1;
        }

        getline(in, eilute); 
        while (getline(in, eilute)) {
            if (eilute.empty()) continue;
            stringstream ss(eilute);
            Studentas s;
            ss >> s.vardas >> s.pavarde;
            vector<int> paz;
            int sk;
            while (ss >> sk) paz.push_back(sk);
            s.egz = paz.back(); paz.pop_back();
            s.nd = paz;
            visiStudentai.push_back(s);
        }
        in.close();
        irasuKiekis = visiStudentai.size();

        auto endRead = chrono::high_resolution_clock::now();
        auto durationRead = chrono::duration_cast<chrono::milliseconds>(endRead - startRead);
        cout << "Failo su " << irasuKiekis << " irasais nuskaitymo laikas: " << std::fixed << std::setprecision(6) << (durationRead.count() / 1000.0) << " s" << endl;
    }


    auto startSort = high_resolution_clock::now();
    sort(visiStudentai.begin(), visiStudentai.end(), [](const Studentas &a, const Studentas &b) {
        if (a.vardas == b.vardas)
            return a.pavarde < b.pavarde;
        return a.vardas < b.vardas;
    });
    auto endSort = high_resolution_clock::now();
    auto sortTime = duration_cast<milliseconds>(endSort - startSort);
    cout << "Irasu rusiavimas didejimo tvarka laikas, su sort funkcija: " << sortTime.count()/1000.0 << " s" << endl;

    auto startSplit = high_resolution_clock::now();
    vector<Studentas> vargsiukai;
    vector<Studentas> galvociai;
    for (const Studentas& s : visiStudentai) {
        double galutinisVid = 0.4 * skaicVid(s.nd) + 0.6 * s.egz;
        if (galutinisVid < 5.0) vargsiukai.push_back(s);
        else galvociai.push_back(s);
    }
    auto endSplit = high_resolution_clock::now();
    auto splitTime = duration_cast<milliseconds>(endSplit - startSplit);
    cout << "Irasu dalijimo i dvi grupes laikas: " << splitTime.count()/1000.0 << " s" << endl;
    cout << "Vargsiuku: " << vargsiukai.size() << ", Galvociu: " << galvociai.size() << endl;


    auto startWrite = chrono::high_resolution_clock::now();

    auto spausdintiIFaila = [](const vector<Studentas>& grupe, const string& failoVardas) {
        ofstream out(failoVardas);
        if (!out) { cerr << "Nepavyko sukurti failo: " << failoVardas << endl; return; }

        out << "Vardas Pavarde Galutinis(Vid.) Galutinis(Med.)\n";
        for (const Studentas& s : grupe) {
            double ndVid = skaicVid(s.nd);
            double ndMed = skaicMediana(s.nd);
            double galutinisVid = 0.4*ndVid + 0.6*s.egz;
            double galutinisMed = 0.4*ndMed + 0.6*s.egz;
            out << s.vardas << " " << s.pavarde << " "
                << galutinisVid << " " << galutinisMed << "\n";
        }
    };

    spausdintiIFaila(vargsiukai, "vargsiukai.txt");
    spausdintiIFaila(galvociai, "galvociai.txt");

    auto endWrite = chrono::high_resolution_clock::now();
    auto durationWrite = chrono::duration_cast<chrono::milliseconds>(endWrite - startWrite);

    cout << "Isvedimas i failus (" << vargsiukai.size() + galvociai.size() << " irasai) uztruko: " << std::fixed << std::setprecision(6) << (durationWrite.count() / 1000.0) << " s" << endl;
    cout << "I vargsiukai.txt irasyta: " << vargsiukai.size() << ", i galvociai.txt irasyta: " << galvociai.size() << endl;

    auto visoPabaiga = high_resolution_clock::now();
    auto visoLaikas = duration_cast<milliseconds>(visoPabaiga - visoPradzia);
    cout << "\nViso testo laikas: " << visoLaikas.count()/1000.0 << " s" << endl;

    cout << "\nPress any key to continue . . ." << endl;
    cin.get();

    return 0;
}
