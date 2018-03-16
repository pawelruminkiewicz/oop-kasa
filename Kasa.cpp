#ifndef PO_M1_KASA_H
#define PO_M1_KASA_H

#include <iostream>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <iomanip>
#include <conio.h>

#include "Konto_pracownika.h"
#include "Programista.h"
#include "Student.h"
#include "Pracownik_firmy.h"
#include "Obiad.h"

using namespace std;

template<class T>
class kasa {
private:
    string nazwa_pliku = "dane.dat";
    vector<T *> konta;
public:
    void dodaj_konto(T *object) {
        konta.push_back(object);
    }

    void usun_konto(int vId) {
        try {
            Konto_pracownika *konto = znajdz_konto(vId);
            int i = znajdz_iterator_konta(vId);
            if (konto->getSaldo() != 0) cout << "Nie mozna usunac konta! Konto nie jest puste.\n";
            else {
                konta.erase(konta.begin() + i);
                cout << "Konto usuniete.\n";
            }
            poczekaj();
        }
        catch (int x) {
            cout << "Nie znaleziono konta!\n";
            poczekaj();
        }
    }

    Konto_pracownika *znajdz_konto(int vId) {
        int it;
        for (it = 0; it != konta.size(); it++) {
            if (konta[it]->getWlasciciel()->getId() == vId) return konta[it];
        }
        if (it == konta.size()) {
            throw -99;
        }
    }

    int znajdz_iterator_konta(int vId) {
        int it;
        for (it = 0; it != konta.size(); it++) {
            if (konta[it]->getWlasciciel()->getId() == vId) return it;
        }
        if (it == konta.size()) {
            throw -99;
        }
    }

    Konto_pracownika wprowadz_posilek() {
        try {
            int id;
            float koszt_posilku, zaplata;
            cout << "Podaj id konta: ";
            cin >> id;
            Konto_pracownika *konto = znajdz_konto(id);
            cout << "Podaj koszt posilku: ";
            cin >> koszt_posilku;
            cout << "Podaj kwote zaplacona dostawcy: ";
            cin >> zaplata;
            Obiad *obiad = new Obiad(zaplata, koszt_posilku);
            if (konto->getSaldo() > 0 && obiad->oblicz_zwrot_do_konta() > 0) {
                *konto += obiad->oblicz_zwrot_do_konta();
                cout << "Zwrocono na konto: " << obiad->oblicz_zwrot_do_konta() << "\n";
            } else cout << "Brak wystarczajacych srodkow na koncie!";
        }
        catch (int x) {
            cout << "Nie znaleziono konta!\n";
            poczekaj();
        }
    }

    void wyswietl_stan_kont() {
        cout << "Lista kont zarejestrowanych w KASIE:" << endl;
        cout << setw(4) << "Id" << setw(15) << "Imie" << setw(30) << "Nazwisko" << setw(14) << "Saldo" << endl;
        for (int it = 0; it != konta.size(); it++) {
            cout << setw(4) << konta[it]->getWlasciciel()->getId() << setw(15) << konta[it]->getWlasciciel()->getImie()
                 << setw(30) << konta[it]->getWlasciciel()->getNazwisko() << setw(14) << konta[it]->getSaldo() << endl;
        }
    }

    void wyswietl_dane_pracownikow() {
        cout << "Lita osob zatrudnionych w firmie:\n";
        for (int it = 0; it != konta.size(); it++) {
            konta[it]->getWlasciciel()->wyswietl_dane();
        }
    }

    void wyswietl_saldo() {
        cout << "Aktualne saldo kasy: ";
        float saldo_kasy = 0;
        for (int it = 0; it != konta.size(); it++) {
            saldo_kasy += konta[it]->getSaldo();
        }
        cout << saldo_kasy << endl;
    }

    void wykonaj_przelew() {
        try {
            int nadawca, odbiorca, kwota;
            Konto_pracownika *odb, *nad;
            cout << "Wykonywanie przelewu.\nId konta nadawcy: ";
            cin >> nadawca;
            cout << "Id konta odbiorcy: ";
            cin >> odbiorca;

            nad = znajdz_konto(nadawca);
            odb = znajdz_konto(odbiorca);
            if (Student *s = dynamic_cast<Student *>( odb->getWlasciciel())) {
                cout << "Blad: odbiorca jest studentem. Oni nigdy nie oddaja!";
            } else {
                cout << "Wprowadz kwote: ";
                cin >> kwota;
                if (nad->getSaldo() > kwota) {
                    *nad -= kwota;
                    *odb += (kwota);
                    cout << "Przelew wykonano.";
                } else {
                    cout << "Nadawca przelewu nie wystarczajacej liczby srodkow na koncie!\n";
                }
            }
        }
        catch (int x) {
            cout << "Nie znaleziono konta!\n";
            poczekaj();
        }
    }

    void wyplac() {
        try {
            int id;
            cout << "Wyplata pieniedzy z konta.\nPodaj id konta: ";
            cin >> id;
            if (znajdz_konto(id)->getSaldo() > 0) {
                cout << "Wyplaciles z konta: " << znajdz_konto(id)->getSaldo() << ". Twoje konto jest juz puste.\n";
                *znajdz_konto(id) -= znajdz_konto(id)->getSaldo();
            } else {
                cout << "Twoje konto jest puste!\n";
            }
            poczekaj();
        }
        catch (int x) {
            cout << "Nie znaleziono konta!\n";
            poczekaj();
        }

    }

    void odczytaj_z_pliku() {
        ifstream plik;
        string stanowisko, imie, nazwisko, uczelnia, znane_jezyki;
        int id;
        float saldo;
        try {
            plik.open(nazwa_pliku);
            if (plik.good()) {
                while (!plik.eof()) {
                    plik >> stanowisko >> id >> imie >> nazwisko;
                    if (plik.eof()) break;
                    if (stanowisko == "+Programista") {
                        plik >> znane_jezyki;
                        plik >> saldo;
                        Programista *programista = new Programista(id, imie, nazwisko, znane_jezyki);
                        Konto_pracownika *konto = new Konto_pracownika(programista, saldo);
                        dodaj_konto(konto);
                    } else if (stanowisko == "+Student") {
                        plik >> uczelnia;
                        plik >> saldo;
                        Student *student = new Student(id, imie, nazwisko, uczelnia);
                        Konto_pracownika *konto = new Konto_pracownika(student, saldo);
                        dodaj_konto(konto);
                    }
                }
                plik.close();

            } else {
                throw string("bladpliku");
            }
        }
        catch (string x) {
            cout
                    << "Plik bazy danych nie istnieje. Jezeli jest to pierwsze uruchomienie zostanie stworzony nowy plik danych. "
                    << "Jezeli nie jest to pierwsze uruchomienie, zamknij program i umiesc w katalogu programu plik z baza danych.";
            return;
        }
    }

    void zapisz_do_pliku() {
        ofstream plik;
        plik.open(nazwa_pliku);
        for (int it = 0; it != konta.size(); it++) {
            konta[it]->zapisz_dane(plik);
        }
    }

    void poczekaj() {
        sleep(2);
    }

    void poczekaj_na_klawisz() {
        cout << "\n--------------Aby przejsc dalej wcisnij ESC aby wyjsc wcisnij [w]!--------------\n";
        char a = getch();
        while (a != '\x1B' || a != 'W') {
            if (a == 'W' || a == 'w') exit(0);
            if (a == '\x1B') return;
            a = getch();
        };
    }
};

#endif