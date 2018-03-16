#include <iostream>
#include <fstream>

#include "Pracownik_firmy.h"

using namespace std;

Pracownik_firmy::Pracownik_firmy(int vId, string vImie, string vNazwisko) : czlowiek(vImie, vNazwisko) {
    id = vId;
}

void Pracownik_firmy::wyswietl_dane() {
    cout << "---------------------------\n"
         << "+Id: " << this->getId() << "\n"
         << "+Imie: " << this->getImie() << "\n"
         << "+Nazwisko: " << this->getNazwisko() << "\n";
}

void Pracownik_firmy::zapisz_dane(ofstream &plik) {
    plik << this->getId() << endl;
    plik << this->getImie() << endl;
    plik << this->getNazwisko() << endl;
}

int Pracownik_firmy::getId() {
    return id;
}

Pracownik_firmy::~Pracownik_firmy() {

}