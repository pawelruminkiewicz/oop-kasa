#ifndef PO_M1_OBIAD_H
#define PO_M1_OBIAD_H


class Obiad {
private:
    float koszt_obiadu;
    float zaplata_dla_dostawcy;
public:
    Obiad(float koszt, float zaplata);

    float oblicz_zwrot_do_konta();

};


#endif //PO_M1_OBIAD_H
