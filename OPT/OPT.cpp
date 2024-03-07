#include <iostream>
#include <fstream>
using namespace std;

const int kolumny = 20;
int strony[kolumny];
int liczbaRamek;
int liczbaZastapien = 0;
bool czyJuzJest = false;
int najpozniejsza = 0;

int main() {
    ifstream plik("dane2.txt"); // Otwiera plik do odczytu
    for (int i = 0; i < kolumny; i++) plik >> strony[i];
    plik >> liczbaRamek; // Wczytanie 2 linii z pliku do zmiennej
    plik.close();   // Zamyka plik

    int ramki[liczbaRamek];
    int kiedyWystapi[liczbaRamek];
    for (int i = 0; i < liczbaRamek; i++) ramki[i] = strony[i]; // Wypelnienie pustych ramek
    for (int i = 0; i < liczbaRamek; i++) cout << ramki[i] << " "; // Wyswietlanie aktualnych zawartosci ramek
    cout << "Ramki po 3 wejsciach "  << endl;

    for (int i = liczbaRamek; i < kolumny; i++) { // Glowna petla po stronach
        for(int l = 0; l < liczbaRamek; l++) kiedyWystapi[l] = 0; // Inicjalizacja tablicy kiedyWystapi
        for (int j = 0; j < liczbaRamek; j++) {
            if(ramki[j] == strony[i]) czyJuzJest = true; // Sprawdzenie czy dana strona juz jest w ktorejs z ramek
        }
        if(!czyJuzJest){ // Zmiana ramek
            for(int a = i+1; a < kolumny; a++){
                for(int j = 0; j < liczbaRamek; j++){
                    if(ramki[j] == strony[a] && kiedyWystapi[j] == 0) kiedyWystapi[j] = a-i;
                }
            }
            for (int l = 1; l < liczbaRamek; l++) { // Proces decyzyjny, ktora strona wystapi najwczesniej
                if (kiedyWystapi[l] > kiedyWystapi[najpozniejsza]) najpozniejsza = l;
            }
            for(int l = 0; l < liczbaRamek; l++){ // Jesli jakas strona juz nie wystapi to ja zastepujemy
                if(kiedyWystapi[l] == 0) najpozniejsza = l;
            }
            ramki[najpozniejsza] = strony[i]; // Zastepowanie ramek
            liczbaZastapien++; // Zapis zastapienia strony
        }
        najpozniejsza = 0;
        czyJuzJest = false;
        for (int k = 0; k < liczbaRamek; k++) cout << ramki[k] << " "; // Wyswietlanie aktualnych zawartosci ramek
            cout << "Ramki po "<< i+1 <<" wejsciach " << endl;
    }
    cout << "Liczba zastapionych stron "<< liczbaZastapien << endl; // // Wyswietlanie liczby zastapionych stron
    ofstream plikk; // Przesyla raport programu do pliku
    plikk.open("wynikOPT.txt");
    plikk << "Ilosc zastapionych stron dla metody OPT: " << liczbaZastapien<< endl;
    plikk.close();
    return 0;
}
