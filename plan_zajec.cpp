
#include <iostream> 
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


#include "struktury.h"
#include <list>
#include "funkcje.h"

using namespace std; 

int main()
{
	list<Prowadzacy> lista_prowadzacych;
	list<Grupa> lista_grup;
	list<Przedmiot> lista_przedmiotow;
	list<Zajecia> lista_zajec;

	if (!wczytaj_wszystko1(lista_prowadzacych, lista_grup, lista_przedmiotow, lista_zajec))
	{
		return 0;
	}

	cout << " PLAN ZAJEC" << endl;

	glowna_petla(lista_prowadzacych, lista_grup, lista_przedmiotow, lista_zajec);



	return 0;
}


