#ifndef funckje_h
#define funkcje_h

#include "struktury.h"
using namespace std;

bool wczytaj_prowadzacych(list<Prowadzacy>& lista_prowadzacych);
bool wczytaj_grupy(list<Grupa>& lista_grup);
bool wczytaj_przedmioty(list<Przedmiot>& lista_przedmiotow);
bool wczytaj_zajecia(list<Zajecia>& lista_zajec,
					 list<Prowadzacy>& lista_prowadzacych,
				     list<Grupa>& lista_grup,
				     list<Przedmiot>& lista_przedmiotow);
void pokaz_zajecia_danego_prowadzacego(list<Zajecia>& lista_zajec, Prowadzacy* wybrany);
void showlistGrupa(list<Zajecia>& lista_zajec);
void showlistPrzedmiot(list<Zajecia>& lista_zajec);
void termin_zajec(list<Zajecia>& lista_zajec);
int czy_dobry_znak();
bool wczytaj_wszystko1(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Przedmiot> &lista_przedmiotow, list <Zajecia> &lista_zajec);
Prowadzacy* wyszukaj_prowadzacego(list<Prowadzacy> &lista_prowadzacych);
void wybierz_kryterium(std::list<Zajecia>& lista_zajec);
void glowna_petla(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Przedmiot>& lista_przedmiotow, list <Zajecia>& lista_zajec);
void pokaz_zajecia_danego_prowadzacego(list<Zajecia>& lista_zajec, Prowadzacy* wybrany);
Grupa* wyszukaj_grupe(list<Grupa>& lista_grup);
void pokaz_zajecia_danej_grupy(list<Zajecia>& lista_zajec, Grupa* wybrana);
#endif