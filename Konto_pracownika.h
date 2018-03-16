#ifndef PO_M1_KONTO_PRACOWNIKA_H
#define PO_M1_KONTO_PRACOWNIKA_H

#include "Pracownik_firmy.h"

using namespace std;

class Konto_pracownika {
private:
    float saldo;
    Pracownik_firmy *wlasciciel_konta;
public:
    Konto_pracownika(Pracownik_firmy *vWlasciciel_konta, float vSaldo);

    void zapisz_dane(ofstream &plik);

    float getSaldo();

    Konto_pracownika &operator+=(float kwota);

    Konto_pracownika &operator-=(float kwota);

    Pracownik_firmy *getWlasciciel();
};


#endif //PO_M1_KONTO_PRACOWNIKA_H
