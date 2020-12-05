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
int czy_dobry_znak();
bool wczytaj_wszystko1(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Przedmiot> &lista_przedmiotow, list <Zajecia> &lista_zajec);
Prowadzacy* wyszukaj_prowadzacego(list<Prowadzacy> &lista_prowadzacych);
void wybierz_kryterium(list<Zajecia>& lista_zajec, list <Przedmiot>& lista_przedmiotow);
void glowna_petla(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Przedmiot>& lista_przedmiotow, list <Zajecia>& lista_zajec);
Grupa* wyszukaj_grupe(list<Grupa>& lista_grup);
void pokaz_zajecia_danej_grupy(list<Zajecia>& lista_zajec, Grupa* wybrana);
Przedmiot* wyszukaj_przedmiot(list<Przedmiot>& lista_przedmiotow);
void pokaz_plan_przedmiotu(list<Zajecia>& lista_zajec, Przedmiot* wybrany);
void wybierz_dzien(list<Zajecia>& lista_zajec, bool tymczasowy);
list<Zajecia*> zajecia_danego_dnia(list<Zajecia*> lista_zajec, string nazwa_dnia);
void wybierz_przedmiot(list<Przedmiot>& lista_przedmiotow,list<Zajecia> lista_zajec);
void wybierz_sale(list<Zajecia>& lista_zajec, list<Przedmiot>& lista_pzedmiotow, bool tymczasowy);
pair<list<Prowadzacy>, list<Zajecia>>& usun_prowadzacego(list<Prowadzacy>& lista_prowadzacych, list<Zajecia>& lista_zajec, int tym);
pair<list<Przedmiot>, list<Zajecia>>& usun_przedmiot(list<Przedmiot>& lista_przedmiotow, list<Zajecia>& lista_zajec, int tym);
void wybierz_modifikacje(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Przedmiot>& lista_przedmiotow, list <Zajecia>& lista_zajec, int tym);
void usun_zajecie(list<Zajecia>& lista_zajec);
int dodaj_zajecie(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Przedmiot>& lista_przedmiotow, list <Zajecia>& lista_zajec, double tym);
void zmien_termin_zajec(list<Zajecia>& lista_zajec, float tym);
void zmien_miejsce_zajec(list<Zajecia>& lista_zajec, double tym);
bool zapisz_prowadzacych(list <Prowadzacy>& lista_prowadzacych, int tym);

bool zapisz_wszystko(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Zajecia>& lista_zajec,list <Przedmiot> lista_przedmiotow,int tym);
bool zapisz_zajecia(list <Zajecia>& lista_zajec, list<Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list<Przedmiot>& lista_przedmiotow, float tym);
bool zapisz_grupy(list <Grupa>& lista_grup, int tym);
#endif