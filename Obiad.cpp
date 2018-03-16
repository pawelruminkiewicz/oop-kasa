#include <iostream>

#include "Obiad.h"

using namespace std;

Obiad::Obiad(float zaplata, float koszt) {
    koszt_obiadu = koszt;
    zaplata_dla_dostawcy = zaplata;
}

float Obiad::oblicz_zwrot_do_konta() {
    return zaplata_dla_dostawcy - koszt_obiadu;
}