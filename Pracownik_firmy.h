#ifndef PO_M1_PRACOWNIK_FIRMY_H
#define PO_M1_PRACOWNIK_FIRMY_H

#include "czlowiek.h"

using namespace std;

class Pracownik_firmy : public czlowiek {
private:
    int id;
public:
    Pracownik_firmy(int vId, string vImie, string vNazwisko);

    void wyswietl_dane();

    void zapisz_dane(ofstream &plik);

    int getId();

    virtual ~Pracownik_firmy();
};


#endif //PO_M1_PRACOWNIK_FIRMY_H
