#include <iostream>
#include <fstream>

#include "czlowiek.h"

czlowiek::czlowiek(string vImie, string vNazwisko) {
    imie = vImie;
    nazwisko = vNazwisko;
}

string czlowiek::getImie() {
    return imie;
}

string czlowiek::getNazwisko() {
    return nazwisko;
}
