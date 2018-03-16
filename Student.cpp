#include <iostream>
#include <fstream>

#include "Student.h"
#include "Pracownik_firmy.h"

using namespace std;

Student::Student(int vId, string vImie, string vNazwisko, string vNazwa_uczelni) : Pracownik_firmy(vId, vImie,
                                                                                                   vNazwisko) {
    nazwa_uczelni = vNazwa_uczelni;
}

void Student::wyswietl_dane() {
    Pracownik_firmy::wyswietl_dane();
    cout << "+Uczelnia: " << this->nazwa_uczelni;
    cout << "\n---------------------------";
}

void Student::zapisz_dane(ofstream &plik) {
    plik << "+Student" << endl;
    Pracownik_firmy::zapisz_dane(plik);
    plik << this->getNazwauczelni() << endl;
}

string Student::getNazwauczelni() {
    return nazwa_uczelni;
}
