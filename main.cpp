#include <iostream>
#include <unistd.h>

#include "Konto_pracownika.h"
#include "Pracownik_firmy.h"
#include "Kasa.cpp"

using namespace std;

kasa<Konto_pracownika> *Kasa = new kasa<Konto_pracownika>();

void dodaj_nowe_konto() {
    cout << "Kim bedzie wlasciciel konta ?(wybierz liczbe)\n"
         << "1. Student\n"
         << "2. Programista\n";
    int typ_pracownika;
    cin >> typ_pracownika;
    if (typ_pracownika < 1 || typ_pracownika > 2) {
        cout << "Wybrano zly typ pracownika. Powrot do menu glownego.\n";
        Kasa->poczekaj();
        return;
    }
    string imie, nazwisko, uczelnia;
    int id;
    float saldoPocz;
    cout << "Imie: ";
    cin >> imie;
    cout << "Nazwisko: ";
    cin >> nazwisko;
    cout << "Identyfikator: ";
    cin >> id;
    cout << "Saldo poczatkowe: ";
    cin >> saldoPocz;
    Konto_pracownika *konto;
    Programista *programista;
    Student *student;
    switch (typ_pracownika) {
        case 1: {
            cout << "Wprowadz nazwe uczelni(uzyj podkreslnikow zamiast spacji): ";
            cin >> uczelnia;
            student = new Student(id, imie, nazwisko, uczelnia);
            konto = new Konto_pracownika(student, saldoPocz);
            Kasa->dodaj_konto(konto);
            break;
        }
        case 2: {
            string znane_jezyki;
            cout << "Wprowadz znane jezyki programowania(po przecinku, bez spacji): ";
            cin >> znane_jezyki;
            programista = new Programista(id, imie, nazwisko, znane_jezyki);
            konto = new Konto_pracownika(programista, saldoPocz);
            Kasa->dodaj_konto(konto);
            break;
        }
    }
    cout << "Konto dodane pomyslnie";
    Kasa->poczekaj();
}

void usun_konto() {
    int id;
    Kasa->wyswietl_stan_kont();
    cout << "Id konta do usuniecia: ";
    cin >> id;
    Kasa->usun_konto(id);
}

int main() {
    Kasa->odczytaj_z_pliku();
    int wybor;
    do {
        try {
            system("CLS");
            cout << "--------------------------------------------------------------------------------"
                 << "                            KASA FIRMOWA 1.0                                    "
                 << "--------------------------------------------------------------------------------"
                 << endl;
            cout << "1. Wyswietl saldo kasy\n"
                 << "2. Wyswietl saldo wszystkich kont\n"
                 << "3. Dodaj konto\n"
                 << "4. Usun konto\n"
                 << "5. Edytuj saldo konta\n"
                 << "6. Wykonaj przelew\n"
                 << "7. Wprowadz posilek\n"
                 << "8. Wyplac z kasy\n"
                 << "9. Wyswietl wszystkich pracownikow\n"
                 << "10. Wyjscie\n";
            cin >> wybor;
            if (cin.fail() || wybor > 10 || wybor < 1) throw -98;
            cout << "--------------------------------------------------------------------------------";
            switch (wybor) {
                case 1 : {
                    Kasa->wyswietl_saldo();
                    Kasa->poczekaj_na_klawisz();
                    break;
                }
                case 2 : {
                    Kasa->wyswietl_stan_kont();
                    Kasa->poczekaj_na_klawisz();
                    break;
                }
                case 3 : {
                    dodaj_nowe_konto();
                    Kasa->zapisz_do_pliku();
                    break;
                }
                case 4 : {
                    usun_konto();
                    Kasa->zapisz_do_pliku();
                    break;
                }
                case 5 : {
                    try {
                        int idKonta;
                        float kwota;
                        cout << "Wpisz id konta, ktorego saldo chcesz zmienic: ";
                        cin >> idKonta;
                        Konto_pracownika *konto = Kasa->znajdz_konto(idKonta);
                        cout << "Wpisz kwote: ";
                        cin >> kwota;
                        if (konto->getSaldo() + kwota > 0)
                            *konto += kwota;
                        else cout << "Blad: ujemna kwota jest niemozliwa!\n";
                        Kasa->zapisz_do_pliku();
                        Kasa->poczekaj();
                    }
                    catch (int x) {
                        cout << "Nie znaleziono konta!\n";
                        Kasa->poczekaj();
                    }
                    break;
                }
                case 6 : {
                    Kasa->wykonaj_przelew();
                    Kasa->zapisz_do_pliku();
                    break;
                }
                case 7 : {
                    Kasa->wprowadz_posilek();
                    break;
                }
                case 8 : {
                    Kasa->wyplac();
                    Kasa->zapisz_do_pliku();
                    break;
                }
                case 9 : {
                    Kasa->wyswietl_dane_pracownikow();
                    Kasa->poczekaj_na_klawisz();
                    break;
                }
                case 10 :
                    break;

            }
        }
        catch (int x) {
            cout << "Niepoprawna pozycja menu!\n";
            Kasa->poczekaj();
            cin.clear();
            cin.ignore();
            continue;
        }

    } while (wybor != 10);
    return 0;
}