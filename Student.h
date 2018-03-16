//
// Created by Pawel on 2016-11-06.
//

#ifndef PO_M1_STUDENT_H
#define PO_M1_STUDENT_H

#include "Pracownik_firmy.h"

class Student : public Pracownik_firmy {
private:
    string nazwa_uczelni;
public:
    Student(int vId, string vImie, string vNazwisko, string vNazwa_uczelni);

    void wyswietl_dane();

    void zapisz_dane(ofstream &plik);

    string getNazwauczelni();
};


#endif //PO_M1_STUDENT_H
