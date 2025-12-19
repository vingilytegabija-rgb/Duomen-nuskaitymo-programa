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
std::vector spartos analizė:
Įrašų kiekis,Nuskaitymas (s),Rūšiavimas (s),Išvedimas (s),Bendra trukmė (s)
1 000,0.0016,0.0002,0.0023,0.0041
10 000,0.0245,0.0019,0.0307,0.0571
100 000,0.1384,0.0151,0.1350,0.2885
1 000 000,1.0914,0.1556,0.9010,2.1480


std::list spartos analizė:
Įrašų kiekis,Nuskaitymas (s),Rūšiavimas (s),Išvedimas (s),Bendra trukmė (s)
1 000,0.0026,0.0003,0.0044,0.0073
10 000,0.0189,0.0023,0.0137,0.0349
100 000,0.1182,0.0158,0.0948,0.2288
1 000 000,1.0858,0.1682,1.0611,2.3151
