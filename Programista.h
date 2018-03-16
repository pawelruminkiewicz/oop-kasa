#ifndef PO_M1_PROGRAMISTA_H
#define PO_M1_PROGRAMISTA_H

#include "Pracownik_firmy.h"

class Programista : public Pracownik_firmy {
private:
    string znane_jezyki_programowania;
    int ilosc_znanych_jezykow;
public:
    Programista(int vId, string vImie, string vNazwisko, string vJezyki);

    void wyswietl_dane();

    void zapisz_dane(ofstream &plik);

    string getJezyki();
};


#endif //PO_M1_PROGRAMISTA_H
