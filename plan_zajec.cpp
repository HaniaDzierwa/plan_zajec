
#include <iostream> 
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <tuple>


#include "struktury.h"
#include <list>
#include "funkcje.h"


using namespace std; 

int main(int liczba_argumentow, char** tablica_argumentow)
{
	tuple<string, string, string, string> nazwy_plikow;

	if (liczba_argumentow == 5)
	{
		nazwy_plikow=make_tuple(tablica_argumentow[1], tablica_argumentow[2], tablica_argumentow[3], tablica_argumentow[4]);
	}
	else
	{
		cout << "Nie udalo sie";
		return 0;
	
	}

	list<Prowadzacy> lista_prowadzacych;
	list<Grupa> lista_grup;
	list<Przedmiot> lista_przedmiotow;
	list<Zajecia> lista_zajec;

	if (!wczytaj_wszystko(lista_prowadzacych, lista_grup, lista_przedmiotow, lista_zajec,nazwy_plikow))
	{
		return 0;
	}

	cout << " PLAN ZAJEC" << endl;

	glowna_petla(lista_prowadzacych, lista_grup, lista_przedmiotow, lista_zajec);



	if (!zapisz_wszystko(lista_prowadzacych, lista_grup, lista_zajec,lista_przedmiotow,nazwy_plikow))
	{	

		return 0;
	}
	return 0;
}


