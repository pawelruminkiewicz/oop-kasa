#include <iostream>
#include <fstream>

#include "Programista.h"

using namespace std;

Programista::Programista(int vId, string vImie, string vNazwisko, string vJezyki) : Pracownik_firmy(vId, vImie,
                                                                                                    vNazwisko) {
    znane_jezyki_programowania = vJezyki;
}

void Programista::wyswietl_dane() {
    Pracownik_firmy::wyswietl_dane();
    cout << "+Znane jezyki: ";
    cout << znane_jezyki_programowania << endl;
    cout << "\n---------------------------";
}

void Programista::zapisz_dane(ofstream &plik) {
    plik << "+Programista" << endl;
    Pracownik_firmy::zapisz_dane(plik);
    plik << this->getJezyki() << endl;
}

string Programista::getJezyki() {
    return znane_jezyki_programowania;
}