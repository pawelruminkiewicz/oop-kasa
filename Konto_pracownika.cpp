#include <iostream>
#include <fstream>

#include "Konto_pracownika.h"
#include "Student.h"
#include "Programista.h"

using namespace std;

Konto_pracownika::Konto_pracownika(Pracownik_firmy *vWlasciciel_konta, float vSaldo) {
    saldo = vSaldo;
    wlasciciel_konta = vWlasciciel_konta;
}

float Konto_pracownika::getSaldo() {
    return saldo;
}

void Konto_pracownika::zapisz_dane(ofstream &plik) {
    if (Student *s = dynamic_cast<Student *>( wlasciciel_konta )) {
        s->zapisz_dane(plik);
    } else if (Programista *p = dynamic_cast<Programista *>( wlasciciel_konta)) {
        p->zapisz_dane(plik);
    }
    plik << this->getSaldo() << endl;
}

Konto_pracownika &Konto_pracownika::operator+=(float kwota) {
    saldo += kwota;
}

Konto_pracownika &Konto_pracownika::operator-=(float kwota) {
    saldo -= kwota;
}

Pracownik_firmy *Konto_pracownika::getWlasciciel() {
    return wlasciciel_konta;
}