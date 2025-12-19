# Duomen-nuskaitymo-programa
lab darbas
Testavimo rezultatai

Visi laiko matavimai pateikiami **sekundėmis (s)**.

| Įrašų kiekis | Nuskaitymas (s) | Rūšiavimas (s) | Išvedimas (s) | Bendra trukmė (s) |
| :--- | :---: | :---: | :---: | :---: |
| **1 000** | 0.0018 | 0.0001 | 0.0440 | 0.0459 |
| **10 000** | 0.0143 | 0.0014 | 0.0131 | 0.0288 |
| **100 000** | 0.1273 | 0.0092 | 0.0726 | 0.2091 |
| **1 000 000** | 1.0576 | 0.1067 | 0.7342 | 1.8985 |
| **10 000 000** | 19.0000 | 0.9321 | 6.9308 | 26.8629 |


Atlikus testavimą su duomenų kiekiais nuo 1 tūkst. iki 10 mln. įrašų, galima daryti šias išvadas:

1. **Efektyvumas ir sudėtingumas:** Programos vykdymo laikas auga tiesiškai ($O(n)$ sudėtingumas). Tai reiškia, kad programa yra gerai optimizuota darbui su dideliais duomenų kiekiais.
2. **Nuskaitymo trukmė:** Duomenų nuskaitymas iš failo yra pati lėčiausia operacija. Tai lemia disko įvesties/išvesties (I/O) sparta ir duomenų transformavimas iš tekstinio formato į programos objektus (`std::stringstream` naudojimas). Prie 10 mln. įrašų nuskaitymas užima apie 70% viso proceso laiko.
3. **Rūšiavimo sparta:** Studentų skirstymas į „vargšiukus“ ir „kietiakius“ operatyviojoje atmintyje vyksta labai sparčiai (10 mln. įrašų surūšiuoti užtruko mažiau nei 1 sekundę). Tai įrodo, kad `std::vector` ir tiesinis perėjimas per duomenis yra tinkamas sprendimas.
4. **Išvedimo laikas:** Rezultatų įrašymas į du atskirus failus yra greitesnis už nuskaitymą, nes rašant tiesioginį srautą į diską sunaudojama mažiau procesoriaus resursų nei analizuojant tekstą.
5. **Bendras vertinimas:** Programa sėkmingai apdoroja 10 milijonų įrašų per maždaug 27 sekundes, o tai atitinka šiuolaikinius spartos reikalavimus tokio tipo užduotims.


Spartos testavimas po antro karto:

--- VECTOR Analize (studentai_1000.txt) ---
Nuskaitymas: 0.0015511 s
Vector rusiavimas: 0.0001625 s
Vector irasymas:  0.0023045 s

--- LIST Analize (studentai_1000.txt) ---
Nuskaitymas: 0.0026068 s
List rusiavimas: 0.0002797 s
List irasymas:  0.0043995 s

--- VECTOR Analize (studentai_10000.txt) ---
Nuskaitymas: 0.0244796 s
Vector rusiavimas: 0.0018897 s
Vector irasymas:  0.0306666 s

--- LIST Analize (studentai_10000.txt) ---
Nuskaitymas: 0.0189401 s
List rusiavimas: 0.0023373 s
List irasymas:  0.0137395 s

--- VECTOR Analize (studentai_100000.txt) ---
Nuskaitymas: 0.138421 s
Vector rusiavimas: 0.0150951 s
Vector irasymas:  0.135042 s

--- LIST Analize (studentai_100000.txt) ---
Nuskaitymas: 0.118248 s
List rusiavimas: 0.0158043 s
List irasymas:  0.0948206 s

--- VECTOR Analize (studentai_1000000.txt) ---
Nuskaitymas: 1.09136 s
Vector rusiavimas: 0.155575 s
Vector irasymas:  0.901 s

--- LIST Analize (studentai_1000000.txt) ---
Nuskaitymas: 1.08578 s
List rusiavimas: 0.168152 s
List irasymas:  1.06113 s

DISKAS SSD
ATMINTIS 16GB
CPU AMD Ryzen 5 7530U
