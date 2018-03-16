#ifndef PO_M1_CZLOWIEK_H
#define PO_M1_CZLOWIEK_H

using namespace std;

class czlowiek {
private:
    string imie;
    string nazwisko;
public:
    czlowiek(string vImie, string vNazwisko);

    string getImie();

    string getNazwisko();

    virtual void wyswietl_dane()=0;

};


#endif //PO_M1_CZLOWIEK_H
