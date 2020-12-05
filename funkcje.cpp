#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <utility>

#include "funkcje.h"
#include "struktury.h"

using namespace std;

bool wczytaj_wszystko1(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Przedmiot>& lista_przedmiotow, list <Zajecia>& lista_zajec)
{
	return
		wczytaj_prowadzacych(lista_prowadzacych) &&
		wczytaj_grupy(lista_grup) &&
		wczytaj_przedmioty(lista_przedmiotow) &&
		wczytaj_zajecia(lista_zajec, lista_prowadzacych, lista_grup, lista_przedmiotow);

}
bool wczytaj_prowadzacych(list <Prowadzacy>& lista_prowadzacych)
{
	fstream plik("prowadzacy.txt", ios::in);

	if (plik.good())
	{
		string linia;

		while (getline(plik, linia))
		{
			stringstream ss(linia);
			Prowadzacy tworzony;
			ss >> tworzony.id;
			ss >> tworzony.nazwisko;
			ss >> tworzony.imie;
			lista_prowadzacych.push_back(tworzony);

		}

		plik.close();
	}
	else
	{
		cout << " Nie udalo sie wczytac prowadzacych";
		return false;
	}

	return true;
}
bool wczytaj_grupy(list <Grupa>& lista_grup)
{
	fstream plik("grupy.txt", ios::in);

	if (plik.good())
	{
		string linia;

		while (getline(plik, linia))
		{
			stringstream ss(linia);
			Grupa tworzony;
			ss >> tworzony.id;
			ss >> tworzony.nazwa;

			lista_grup.push_back(tworzony);

		}

		plik.close();
	}
	else
	{
		cout << " Nie udalo sie wczytac grup";
		return false;
	}
	return true;
}
bool wczytaj_przedmioty(list <Przedmiot>& lista_przedmiotow)
{
	fstream plik("przedmioty.txt", ios::in);

	if (plik.good())
	{
		string linia;

		while (getline(plik, linia))
		{
			stringstream ss(linia);
			Przedmiot tworzony;
			ss >> tworzony.id;
			ss >> tworzony.nazwa;
			ss >> tworzony.rodzaj;
			ss >> tworzony.miejsce;

			lista_przedmiotow.push_back(tworzony);

		}

		plik.close();
	}
	else
	{
		cout << " Nie udalo sie wczytac przedmiotow";

		return false;
	}
	return true;
}
bool wczytaj_zajecia(list<Zajecia>& lista_zajec, list<Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list<Przedmiot>& lista_przedmiotow)
{
	fstream plik("zajecia.txt", ios::in);

	if (plik.good())
	{
		string linia;

		while (getline(plik, linia))
		{
			stringstream ss(linia);
			Zajecia tworzony;
			int tymczasowy_id;

			ss >> tymczasowy_id;
			for (auto it = lista_prowadzacych.begin(); it != lista_prowadzacych.end(); it++)
			{
				if (tymczasowy_id == it->id)
					tworzony.prowadzacy = &(*it);
			}
			ss >> tymczasowy_id;
			for (auto it = lista_grup.begin(); it != lista_grup.end(); it++)
			{
				if (tymczasowy_id == it->id)
					tworzony.grupa = &(*it); // informacje idzie do danej komorki ( jej wartosc, nie adres)
			}
			ss >> tymczasowy_id;
			for (auto it = lista_przedmiotow.begin(); it != lista_przedmiotow.end(); it++)
			{
				if (tymczasowy_id == it->id)
					tworzony.przedmiot = &(*it); // &* to przeciazny ten operator:  ->*
			}

			ss >> tworzony.dzien;
			ss >> tworzony.godzina;



			lista_zajec.push_back(tworzony);

		}

		plik.close();
	}
	else
	{
		cout << " Nie udalo sie wczytac zajec";
		return false;
	}
	return true;
}
Prowadzacy* wyszukaj_prowadzacego(list<Prowadzacy>& lista_prowadzacych)
{

	if (lista_prowadzacych.empty())
	{
		cout << " Nie ma zadnych Prowadzacych w systemie";
		return nullptr;
	}
	list<Prowadzacy>::iterator it = lista_prowadzacych.begin();   //moze uzyc slowa kluczowego auto
	for (unsigned i = 0; i < lista_prowadzacych.size(); i++)   // size to ilosc elementow w liscie 5 jednostek ,sizeof wielkosc struktury listy bajty
	{
		cout << i + 1 << "." << it->nazwisko << " " << it->imie << endl;
		it++;
	}
	cout << "Ktorego prowadzacego chcesz zobaczyc plan ";
	int wybor = czy_dobry_znak() - 1;

	if (0 <= wybor && wybor < lista_prowadzacych.size())
	{
		it = lista_prowadzacych.begin();
		advance(it, wybor); // przesuwamy iterator i tyle miejsce o ile nam podal uzytkownik w zmiennej wybor, dlatego potem gdy zwracamy iteraotr to zwracamy danego prowadzacego
		return &(*it);
	}

	return nullptr;
}
list <Zajecia*> zajecia_danego_dnia(list<Zajecia*>lista_zajec, string nazwa_dnia)   // funkcja bedzie zwracac liste wskaznikow zajec w danym dniu
{

	list <Zajecia*> zajecia_danego_dnia;
	for (auto it = lista_zajec.begin(); it != lista_zajec.end(); it++)
	{

		if ((*it)->dzien == nazwa_dnia)
		{
			zajecia_danego_dnia.push_back(*it);   //*it wycigamy caly obiekt, operator wyluskania
		}

	}
	zajecia_danego_dnia.sort([](Zajecia* pierwszy, Zajecia* drugi)
		{
			return pierwszy->godzina < drugi->godzina; // okresla sposob porownania
		}
	);
	return zajecia_danego_dnia;
}
void pokaz_zajecia_danego_prowadzacego(list<Zajecia>& lista_zajec, Prowadzacy* wybrany)
{
	// dla prowadzacego  
	list <Zajecia*>	lista_zajec_prowadzacego; // lista wskaznikow na zajecia
	//list <Zajecia>::iterator it = lista_zajec.begin();// iterator po liscie zajec 
	for (auto it = lista_zajec.begin(); it != lista_zajec.end(); it++)  // przegladam liste zajec i kazdy element daje do zmiennej tymczasowe typu zajecia 
	{

		if (wybrany->id == it->prowadzacy->id)
		{
			lista_zajec_prowadzacego.push_back(&(*it)); // splaszczam iterator do obiektu( do pojedynczego zajecia na liscie zajec, a potem pobieram jego adres 

		}
	}

	list<Zajecia*> zajecia_pon = zajecia_danego_dnia(lista_zajec_prowadzacego, "pon");   // zajecia dnaego dnia to funkcja ktora zwraca zajecia z danego dnia i posortowane welug godzin
	cout << "Poniedzialek\n";
	if (zajecia_pon.empty())
	{
		cout << "Prowadzacy nie ma zajec w poniedzialek\n";

	}
	else
	{

		for (Zajecia* zajecia : zajecia_pon) // wyswietlaj zajecia z listy zajecia pon dopoki sa tam zajecia
		{
			Przedmiot* przedmiot = zajecia->przedmiot;  //  aby mie dokladne specyfikacje odnosie przedmiotu potrzrbuje liste wskaznikow przedmiotow 
			cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
				<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: " << zajecia->grupa->nazwa << "\n";
		}
	}
	list <Zajecia*> zajecia_wt = zajecia_danego_dnia(lista_zajec_prowadzacego, "wt");
	cout << "Wtorek\n";
	if (zajecia_wt.empty())
	{
		cout << "Prowadzacy nie ma zajec we wtorek\n";
	}
	else
	{

		for (Zajecia* zajecia : zajecia_wt)
		{
			Przedmiot* przedmiot = zajecia->przedmiot;

			cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
				<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: " << zajecia->grupa->nazwa << "\n";
		}
	}
	list <Zajecia*>  zajecia_sr = zajecia_danego_dnia(lista_zajec_prowadzacego, "sr");
	cout << "Sroda\n";
	if (zajecia_sr.empty())
	{
		cout << "Prowadzacy nie ma zajec w srode\n";
	}
	else
	{

		for (Zajecia* zajecia : zajecia_sr)
		{
			Przedmiot* przedmiot = zajecia->przedmiot;

			cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
				<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: " << zajecia->grupa->nazwa << "\n";
		}
	}
	list <Zajecia*> zajecia_czw = zajecia_danego_dnia(lista_zajec_prowadzacego, "czw");
	cout << "Czwartek\n";
	if (zajecia_czw.empty())
	{
		cout << "Prowadzacy nie ma zajec w czwartek\n";
	}
	else
	{
		for (Zajecia* zajecia : zajecia_czw)
		{
			Przedmiot* przedmiot = zajecia->przedmiot;
			cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
				<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: " << zajecia->grupa->nazwa << "\n";
		}
	}
	list <Zajecia*> zajecia_pt = zajecia_danego_dnia(lista_zajec_prowadzacego, "pt");
	cout << "Piatek\n";
	if (zajecia_pt.empty())
	{
		cout << "Prowadzacy nie ma zajec w piatek\n";
	}
	else
	{
		for (Zajecia* zajecia : zajecia_pt)
		{
			Przedmiot* przedmiot = zajecia->przedmiot;
			cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
				<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: " << zajecia->grupa->nazwa << "\n";

		}
	}

}
Grupa* wyszukaj_grupe(list<Grupa>& lista_grup)
{
	if (lista_grup.empty())
	{
		cout << "Nie ma zadnych grup w systemie";
		return nullptr;
	}

	auto  it = lista_grup.begin();
	for (unsigned i = 0; i < lista_grup.size(); i++)
	{
		cout << i + 1 << "." << it->nazwa << endl;
		it++;
	}

	cout << "Ktorej grupy chcesz zobaczyc plan ";
	int wybor = czy_dobry_znak() - 1;
	if (0 <= wybor && wybor < lista_grup.size())
	{
		it = lista_grup.begin();
		advance(it, wybor);
		return &(*it);
	}



	return nullptr;
}
void pokaz_zajecia_danej_grupy(list<Zajecia>& lista_zajec, Grupa* wybrana)
{
	list<Zajecia*> zajecia_grupy;
	for (auto it = lista_zajec.begin(); it != lista_zajec.end(); it++)
	{
		if (wybrana->id == it->grupa->id)
		{
			zajecia_grupy.push_back(&(*it));
		}

	}

	list<Zajecia*> zajecia_pon = zajecia_danego_dnia(zajecia_grupy, "pon");
	cout << "Poniedzialek\n";
	if (zajecia_pon.empty())
	{
		cout << "Grupa nie ma zajec w poniedzialek\n";

	}
	else
	{
		for (Zajecia* zajecia : zajecia_pon) // wyswietlaj zajecia z listy zajecia pon dopoki sa tam zajecia
		{
			Przedmiot* przedmiot = zajecia->przedmiot;  //  aby mie dokladne specyfikacje odnosie przedmiotu potrzrbuje liste wskaznikow przedmiotow 
			cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
				<< "nr.sali: " << przedmiot->miejsce << " " << "prowadzacy: " << zajecia->prowadzacy->nazwisko << " " << zajecia->prowadzacy->imie << "\n";
		}
	}

	list <Zajecia*> zajecia_wt = zajecia_danego_dnia(zajecia_grupy, "wt");
	cout << "Wtorek\n";
	if (zajecia_wt.empty())
	{
		cout << "Grupa nie ma zajec we wtorek\n";
	}
	else
	{

		for (Zajecia* zajecia : zajecia_wt)
		{
			Przedmiot* przedmiot = zajecia->przedmiot;

			cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
				<< "nr.sali: " << przedmiot->miejsce << " " << "prowadzacy: " << zajecia->prowadzacy->nazwisko << " " << zajecia->prowadzacy->imie << "\n";
		}
	}
	list <Zajecia*>  zajecia_sr = zajecia_danego_dnia(zajecia_grupy, "sr");
	cout << "Sroda\n";
	if (zajecia_sr.empty())
	{
		cout << "Grupa nie ma zajec w srode\n";
	}
	else
	{

		for (Zajecia* zajecia : zajecia_sr)
		{
			Przedmiot* przedmiot = zajecia->przedmiot;

			cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
				<< "nr.sali: " << przedmiot->miejsce << " " << "prowadzacy: " << zajecia->prowadzacy->nazwisko << " " << zajecia->prowadzacy->imie << "\n";
		}
	}
	list <Zajecia*> zajecia_czw = zajecia_danego_dnia(zajecia_grupy, "czw");
	cout << "Czwartek\n";
	if (zajecia_czw.empty())
	{
		cout << "Grupa nie ma zajec w czwartek\n";
	}
	else
	{
		for (Zajecia* zajecia : zajecia_czw)
		{
			Przedmiot* przedmiot = zajecia->przedmiot;
			cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
				<< "nr.sali: " << przedmiot->miejsce << " " << "prowadzacy: " << zajecia->prowadzacy->nazwisko << " " << zajecia->prowadzacy->imie << "\n";
		}
	}
	list <Zajecia*> zajecia_pt = zajecia_danego_dnia(zajecia_grupy, "pt");
	cout << "Piatek\n";
	if (zajecia_pt.empty())
	{
		cout << "Grupa nie ma zajec w piatek\n";
	}
	else
	{
		for (Zajecia* zajecia : zajecia_pt)
		{
			Przedmiot* przedmiot = zajecia->przedmiot;
			cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
				<< "nr.sali: " << przedmiot->miejsce << " " << "prowadzacy: " << zajecia->prowadzacy->nazwisko << " " << zajecia->prowadzacy->imie << "\n";

		}
	}
}
Przedmiot* wyszukaj_przedmiot(list<Przedmiot>& lista_przedmiotow)
{
	if (lista_przedmiotow.empty())
	{
		cout << " Nie ma przedmiotow w systemie";
		return nullptr;
	}

	auto it = lista_przedmiotow.begin();
	for (unsigned i = 0; i < lista_przedmiotow.size(); i++)
	{
		cout << i + 1 << "." << it->nazwa << " " << it->rodzaj << "\n";
		it++;
	}
	cout << "Wybierz przedmiot";
	int wybor = czy_dobry_znak() - 1;
	if (0 <= wybor && wybor < lista_przedmiotow.size())
	{
		it = lista_przedmiotow.begin();
		advance(it, wybor);
		return &(*it);
	}


	return nullptr;
}
void pokaz_plan_przedmiotu(list<Zajecia>& lista_zajec, Przedmiot* wybrany)
{
	// bede przegladac liste zajec tam gdzie bedzie przedmiot to go dam do nowej listy ktora potem wyswietle
	list<Zajecia*> przedmioty;
	for (auto it = lista_zajec.begin(); it != lista_zajec.end(); it++)
	{
		if (wybrany->id == it->przedmiot->id)
		{
			przedmioty.push_back(&(*it));

		}
	}
	for (Zajecia* zajecia : przedmioty)
	{
		cout << zajecia->dzien << " " << " godzina:" << zajecia->godzina << " sala:" << zajecia->przedmiot->miejsce << " " << " grupa:"
			<< zajecia->grupa->nazwa << " " << " prowadzacy:" << zajecia->prowadzacy->nazwisko << " " << zajecia->prowadzacy->imie << "\n";
	}
}
void wybierz_dzien(list<Zajecia>& lista_zajec, bool tymczasowy)
{
	list <Zajecia*>	danego_dnia;

	for (auto it = lista_zajec.begin(); it != lista_zajec.end(); it++)
	{
		danego_dnia.push_back(&(*it));
	}

	int wybor;
	cout << "1. Poniedzialek\n";
	cout << "2. Wtorek\n";
	cout << "3. Sroda\n";
	cout << "4. Czwartek\n";
	cout << "5. Piatek\n";


	wybor = czy_dobry_znak();
	switch (wybor)
	{
	case 1:
	{
		list<Zajecia*> zajecia_pon = zajecia_danego_dnia(danego_dnia, "pon");   // zajecia dnaego dnia to funkcja ktora zwraca zajecia z danego dnia i posortowane welug godzin
		cout << "Poniedzialek\n";
		if (zajecia_pon.empty())
		{
			cout << "Prowadzacy nie ma zajec w poniedzialek\n";
		}
		else
		{
			for (Zajecia* zajecia : zajecia_pon) // wyswietlaj zajecia z listy zajecia pon dopoki sa tam zajecia
			{
				Przedmiot* przedmiot = zajecia->przedmiot;  //  aby mie dokladne specyfikacje odnosie przedmiotu potrzrbuje liste wskaznikow przedmiotow 
				cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
					<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: " << zajecia->grupa->nazwa << "\n";
			}
		}
		break;
	}
	case 2:
	{
		cout << "Wtorek\n";
		list<Zajecia*> zajecia_wt = zajecia_danego_dnia(danego_dnia, "wt");

		if (zajecia_wt.empty())
		{
			cout << "Prowadzacy nie ma zajec we wtorek\n";
		}
		else
		{
			for (Zajecia* zajecia : zajecia_wt)
			{
				Przedmiot* przedmiot = zajecia->przedmiot;
				cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
					<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: " << zajecia->grupa->nazwa << "\n";
			}
		}
		break;
	}
	case 3:
	{
		cout << "Sroda\n";
		list<Zajecia*> zajecia_sr = zajecia_danego_dnia(danego_dnia, "sr");

		if (zajecia_sr.empty())
		{
			cout << "Prowadzacy nie ma zajec w srode\n";
		}
		else
		{
			for (Zajecia* zajecia : zajecia_sr)
			{
				Przedmiot* przedmiot = zajecia->przedmiot;
				cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
					<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: " << zajecia->grupa->nazwa << "\n";
			}
		}
		break;
	}
	case 4:
	{
		cout << "Czwartek\n";
		list<Zajecia*> zajecia_czw = zajecia_danego_dnia(danego_dnia, "czw");

		if (zajecia_czw.empty())
		{
			cout << "Prowadzacy nie ma zajec we wtorek\n";
		}
		else
		{
			for (Zajecia* zajecia : zajecia_czw)
			{
				Przedmiot* przedmiot = zajecia->przedmiot;
				cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
					<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: " << zajecia->grupa->nazwa << "\n";
			}
		}
		break;
	}
	case 5: cout << "Piatek\n";

		list<Zajecia*> zajecia_pt = zajecia_danego_dnia(danego_dnia, "pt");

		if (zajecia_pt.empty())
		{
			cout << "Prowadzacy nie ma zajec we wtorek\n";

		}
		else
		{

			for (Zajecia* zajecia : zajecia_pt)
			{
				Przedmiot* przedmiot = zajecia->przedmiot;
				cout << "godz: " << zajecia->godzina << " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " "
					<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: " << zajecia->grupa->nazwa << "\n";
			}
		}
		break;
	}
}
void wybierz_przedmiot(list<Przedmiot>& lista_przedmiotow, list<Zajecia> lista_zajec)
{
	if (lista_przedmiotow.empty())
	{
		cout << "W systemie nie ma ¿adnych przedmiotow";
	}

	auto it = lista_przedmiotow.begin();
	for (unsigned i = 0; i < lista_przedmiotow.size(); i++)
	{
		cout << i + 1 << "." << it->nazwa << " " << it->rodzaj << "\n";
		it++;
	}

	cout << "Ktorego przedmiotu chcesz zobaczyc plan ";
	int wybor = czy_dobry_znak() - 1;
	if (0 <= wybor && wybor < lista_przedmiotow.size())
	{
		for (auto it = lista_zajec.begin(); it != lista_zajec.end(); it++)
		{
			if (wybor + 1 == it->przedmiot->id)
			{
				cout << "godz." << (&(*it))->godzina << " sala " << (&(*it))->przedmiot->miejsce << " " <<
					"prowadzacy " << (&(*it))->prowadzacy->nazwisko << " " << (&(*it))->prowadzacy->imie << "\n";
			}

		}
	}



}
void wybierz_sale(list<Zajecia>& lista_zajec, list<Przedmiot>& lista_pzedmiotow, bool tymczasowy)
{
	int wybor;
	cout << "Wybierz sale\n";
	cout << "sala 1\n";
	cout << "sala 2\n";
	cout << "sala 3\n";
	cout << "sala 4\n";
	cout << "Wpisz odpowiednia liczbe ";

	wybor = czy_dobry_znak();
	switch (wybor)
	{
	case 1:
	{

		for (auto it = lista_zajec.begin(); it != lista_zajec.end(); it++)
		{
			if (wybor == it->przedmiot->miejsce)
				cout << (&(*it))->przedmiot->nazwa << " " << (&(*it))->przedmiot->rodzaj << "\n";
		}
		break;
	}
	case 2:
		for (auto it = lista_zajec.begin(); it != lista_zajec.end(); it++)
		{
			if (wybor == it->przedmiot->miejsce)
				cout << (&(*it))->przedmiot->nazwa << " " << (&(*it))->przedmiot->rodzaj << "\n";
		}
		break;
	case 3:
		for (auto it = lista_zajec.begin(); it != lista_zajec.end(); it++)
		{
			if (wybor == it->przedmiot->miejsce)
				cout << (&(*it))->przedmiot->nazwa << " " << (&(*it))->przedmiot->rodzaj << "\n";
		}
		break;
	case 4:
		for (auto it = lista_zajec.begin(); it != lista_zajec.end(); it++)
		{
			if (wybor == it->przedmiot->miejsce)
				cout << (&(*it))->przedmiot->nazwa << " " << (&(*it))->przedmiot->rodzaj << "\n";
		}
		break;
	default:
		cout << "Nieodpowiedni numer";
		break;
	}
}
int czy_dobry_znak()
{
	int zm_wybor;
	while (!(cin >> zm_wybor))
	{
		cout << "To nie jest poprawny znak ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return zm_wybor;
}
void wybierz_kryterium(list<Zajecia>& lista_zajec, list<Przedmiot>& lista_przedmiotow)
{
	int wybor = 0;
	do
	{
		cout << "Wybierz kryterium\n";
		cout << "1. Termin zajec \n";
		cout << "2. Zajecia w danym dniu\n";
		cout << "3. Zajec w danych salach\n";
		cout << "4. Powrot do menu\n";
		cout << "Wprowadz odpowiednia liczbe ";

		wybor = czy_dobry_znak();
		switch (wybor)
		{
		case 1:wybierz_przedmiot(lista_przedmiotow, lista_zajec);

			break;

		case 2:
			wybierz_dzien(lista_zajec, true);
			break;
		case 3:
			wybierz_sale(lista_zajec, lista_przedmiotow, true);
			break;
		case 4:
			cout << "Powrot do menu";
			break;
		default:
			cout << "Nieodpowiedni numer\n";
			break;
		}
	} while (wybor != 4);
}
void glowna_petla(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Przedmiot>& lista_przedmiotow, list <Zajecia>& lista_zajec)
{
	while (true)
	{
		cout << "Wybierz jedna z ponizszych opcji: \n";
		cout << "1. Rozklad zajec -profesorowie\n";
		cout << "2. Rozklad zajec - grupy\n";
		cout << "3. Rozklad zajec - przedmioty\n";
		cout << "4. Wyswietlanie wedlug roznych kryteriow\n";
		cout << "5. Modyfikacja planu\n";
		cout << "6. Koniec\n";
		cout << "Wprowadz odpowiednia liczbe ";

		switch (czy_dobry_znak())
		{
		case 1:
		{
			Prowadzacy* wybrany = wyszukaj_prowadzacego(lista_prowadzacych); // wybor prowadzacego
			if (wybrany == nullptr)
			{
				cout << "Nie istnieje taki prowadzacy\n";
				continue;
			}
			cout << endl;
			pokaz_zajecia_danego_prowadzacego(lista_zajec, wybrany);
			break;

		}
		case 2:
		{
			Grupa* wybrana = wyszukaj_grupe(lista_grup);
			if (wybrana == nullptr)
			{
				cout << "Nie istnieje taka grupa\n";
				continue;
			}
			pokaz_zajecia_danej_grupy(lista_zajec, wybrana);
		}
		break;
		case 3:
		{	Przedmiot* wybrany = wyszukaj_przedmiot(lista_przedmiotow);
		if (wybrany == nullptr)
		{
			cout << "Nie istnieje taki przedmiot\n";
			continue;
		}
		pokaz_plan_przedmiotu(lista_zajec, wybrany);
		break;
		}
		case 4:
			wybierz_kryterium(lista_zajec, lista_przedmiotow);
			break;
		case 5:
			wybierz_modifikacje(lista_prowadzacych, lista_grup, lista_przedmiotow, lista_zajec, 1);

			break;

		case 6:
			cout << "Koniec programu";
			return;
		default:
			cout << "Nieodpowiedni numer";
			break;
		}
		cout << endl;
	}
}
int dodaj_zajecie(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Przedmiot>& lista_przedmiotow, list <Zajecia>& lista_zajec, double tym)
{
	cout << "Wybierz prowadzacego\n";
	auto it_prowadzacego = lista_prowadzacych.begin();
	for (unsigned i = 0; i < lista_prowadzacych.size(); i++)
	{
		cout << i + 1 << ". " << (&(*it_prowadzacego))->nazwisko << " " << (&(*it_prowadzacego))->imie << "\n";
		it_prowadzacego++;
	}
	int prowadzacy;
	prowadzacy = czy_dobry_znak();
	if (prowadzacy > lista_prowadzacych.size())
	{
		cout << "Nie ma takiego prowadzacego";
		return 1;
	}
	cout << " Wybierz grupe\n";
	auto it_grupy = lista_grup.begin();
	for (unsigned i = 0; i < lista_grup.size(); i++)
	{
		cout << i + 1 << ". " << (&(*it_grupy))->nazwa << "\n";
		it_grupy++;
	}


	int grupa;
	grupa = czy_dobry_znak();

	if (grupa > lista_grup.size())
	{
		cout << "Nie ma takiej grupy";
		return 1;
	}
	cout << " Wybierz przedmiot\n";
	auto it_przedmiotu = lista_przedmiotow.begin();
	for (unsigned i = 0; i < lista_przedmiotow.size(); i++)
	{
		cout << i + 1 << ". " << (&(*it_przedmiotu))->nazwa << "  " << (&(*it_przedmiotu))->rodzaj << "\n";
		it_przedmiotu++;
	}



	int przedmiot;
	przedmiot = czy_dobry_znak();
	if (przedmiot > lista_przedmiotow.size())
	{
		cout << "Nie ma takiego przedmiotu";
		return 1;
	}

	cout << "Wybierz dzien ( np: pon,wt,sr,czw,pt) \n";
	string dzien;
	while (!(cin >> dzien))
	{
		cout << "To nie jest poprawny znak ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}


	if (dzien != "pon" || dzien != "wt" || dzien != "sr" || dzien != "czw" || dzien != "pt")
	{
		cout << "Nie ma takiego dnia";
		return 1;
	}


	cout << " Wpisz godzine rozpoczecia zajec, zajecia trwaja dwie godziny (np: 8 - zajecia rozpoczynaja sie o 8.00) \n";

	int godzina;
	godzina = czy_dobry_znak();

	Zajecia nowe;


	for (auto it = lista_prowadzacych.begin(); it != lista_prowadzacych.end(); it++)
	{
		if (prowadzacy == it->id)
			nowe.prowadzacy = &(*it);
	}

	for (auto it = lista_grup.begin(); it != lista_grup.end(); it++)
	{
		if (grupa == it->id)
			nowe.grupa = &(*it);
	}

	for (auto it = lista_przedmiotow.begin(); it != lista_przedmiotow.end(); it++)
	{
		if (przedmiot == it->id)
			nowe.przedmiot = &(*it);
	}

	nowe.dzien = dzien;
	nowe.godzina = godzina;

	bool czy_jest_zajecie;
	czy_jest_zajecie = false;


	for (Zajecia zajecia : lista_zajec)
	{
		if ((zajecia.prowadzacy == nowe.prowadzacy && zajecia.grupa == nowe.grupa && zajecia.przedmiot == nowe.przedmiot && zajecia.dzien == nowe.dzien && zajecia.godzina == nowe.godzina) ||
			(zajecia.przedmiot->miejsce == nowe.przedmiot->miejsce && zajecia.dzien == nowe.dzien && zajecia.godzina == nowe.godzina) ||
			(zajecia.godzina == nowe.godzina || zajecia.godzina == nowe.godzina + 1))
		{

			czy_jest_zajecie = true;
			break;
		}
		else
		{
			czy_jest_zajecie = false;
			break;
		}
	}

	if (czy_jest_zajecie == false)
	{
		lista_zajec.push_back(nowe);
		cout << " Udalo sie utworzyc zajecie lub konsultacje";
	}
	else
	{
		cout << "Nie udalo sie utowrzyc zajec lub konsultacje";
	}
}
void zmien_termin_zajec(list<Zajecia>& lista_zajec, float tym)
{

	auto it = lista_zajec.begin();
	for (unsigned i = 0; i < lista_zajec.size(); i++)
	{
		cout << i + 1 << ". " << (&(*it))->dzien << " " << (&(*it))->godzina << " "
			<< (&(*it))->przedmiot->nazwa << " " << (&(*it))->przedmiot->rodzaj << " " << "\n";
		it++;
	}
	list<Zajecia> zajecia_tym;
	copy(lista_zajec.begin(), lista_zajec.end(), back_inserter(zajecia_tym));
	auto tym_it = zajecia_tym.begin();
	cout << "Wybierz zajecie ktorego termin chcesz zmienic ";
	int wybor;
	wybor = czy_dobry_znak();

	if (0 < wybor && wybor < lista_zajec.size())
	{

		it = zajecia_tym.begin();
		advance(tym_it, wybor - 1);
		cout << "Podaj na jaki dzien chcesz przeniesc zajecia(pon,wt,sr,czw,pt) ";
		string nowy_dzien;

		while (!(cin >> nowy_dzien))
		{
			cout << "To nie jest poprawny znak ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		if (nowy_dzien == "pon" || nowy_dzien == "wt" || nowy_dzien == "sr" || nowy_dzien == "czw" || nowy_dzien == "pt")
		{
			tym_it->dzien = nowy_dzien;
			bool znaleziony;
			znaleziony = true;

			for (it = lista_zajec.begin(); it != lista_zajec.end(); it++)
			{
				if ((it->przedmiot->miejsce == tym_it->przedmiot->miejsce) && (it->dzien == tym_it->dzien) && (it->godzina == tym_it->godzina))
				{
					znaleziony = true;
					break;
				}
				else
				{
					znaleziony = false;
					break;
				}
			}

			if (znaleziony == true)
			{
				cout << "Sala jest zajeta\n";
			}
			else
			{
				it->dzien = nowy_dzien;
				cout << "Udalo sie zmienic dzien zajec\n";
			}


		}
		else
			cout << "Bledny zapis";
	}
}
void zmien_miejsce_zajec(list<Zajecia>& lista_zajec, double tym)
{
	auto wypisz_it = lista_zajec.begin();
	for (unsigned i = 0; i < lista_zajec.size(); i++)
	{
		cout << i + 1 << ". " << (&(*wypisz_it))->dzien << " " << (&(*wypisz_it))->godzina << " "
			<< (&(*wypisz_it))->przedmiot->nazwa << " " << (&(*wypisz_it))->przedmiot->rodzaj << " " << "\n";
		wypisz_it++;
	}

	cout << "Wybierz zajecie ktorego miejsce chcesz zmienic ";
	int wybor;
	wybor = czy_dobry_znak();
	if (0 < wybor && wybor < lista_zajec.size())
	{
		auto wybrane_zajecia_it = lista_zajec.begin();
		advance(wybrane_zajecia_it, wybor - 1);

		cout << "Podaj do ktorej sali chcesz przeniesc zajecia(1,2,3,4) ";
		int nowa_sala;
		nowa_sala = czy_dobry_znak();

		if (0 < nowa_sala && nowa_sala < 5)
		{

			bool znaleziony;
			znaleziony = true;

			auto it = lista_zajec.begin();
			for (; it != lista_zajec.end(); it++)
			{

				if ((nowa_sala == wybrane_zajecia_it->przedmiot->miejsce) && (it->dzien == wybrane_zajecia_it->dzien) && (it->godzina == wybrane_zajecia_it->godzina))
				{
					znaleziony = true;
					break;
				}
				else
				{
					znaleziony = false;
					break;
				}

			}

			if (znaleziony == true)
			{
				cout << "Sala jest zajeta\n";
			}
			else
			{
				it->przedmiot->miejsce = nowa_sala;
				cout << "Udalo sie przeniesc zajecia\n";
			}

		}
		else
			cout << "Bledny zapis";
	}
}
void usun_zajecie(list<Zajecia>& lista_zajec)
{
	auto it = lista_zajec.begin();
	for (unsigned i = 0; i < lista_zajec.size(); i++)
	{
		cout << i + 1 << ". " << (&(*it))->dzien << " " << (&(*it))->godzina << " "
			<< (&(*it))->przedmiot->nazwa << " " << (&(*it))->przedmiot->rodzaj << " " << "\n";
		it++;
	}

	cout << "Wybierz zajecie ktore chcesz usunac";
	int wybor;
	wybor = czy_dobry_znak();


	if (0 < wybor && wybor < lista_zajec.size())
	{
		auto it = lista_zajec.begin();
		advance(it, wybor - 1);
		lista_zajec.erase(it);

	}


}
void wybierz_modifikacje(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Przedmiot>& lista_przedmiotow, list <Zajecia>& lista_zajec, int tym)
{
	cout << "Wybierz modyfikacje \n";
	cout << "1. Usun prowadzaecgo\n";
	cout << "2. Usun przedmiot\n";
	cout << "3. Usun zajecie\n";
	cout << "4. Dodaj zajecie lub konsultacje \n";
	cout << "5. Zmien termin zajecia\n";
	cout << "6. Zmien miejsce zajecia\n";


	int wybor;
	wybor = czy_dobry_znak();
	switch (wybor)
	{
	case 1: usun_prowadzacego(lista_prowadzacych, lista_zajec, 1);
		break;
	case 2: usun_przedmiot(lista_przedmiotow, lista_zajec, 1);
		break;
	case 3: usun_zajecie(lista_zajec);
		break;
	case 4: dodaj_zajecie(lista_prowadzacych, lista_grup, lista_przedmiotow, lista_zajec, 1);
		break;
	case 5: zmien_termin_zajec(lista_zajec, 1);
		break;
	case 6: zmien_miejsce_zajec(lista_zajec, 1);
		break;
	default:
		cout << "Nieodpowiednia liczba";
		break;

	}

}
pair<list<Przedmiot>, list<Zajecia>>& usun_przedmiot(list<Przedmiot>& lista_przedmiotow, list<Zajecia>& lista_zajec, int tym)
{
	if (lista_przedmiotow.empty()) {
		cout << "Nie ma zadnych prowadzacych w systemie";
	}

	auto  it = lista_przedmiotow.begin();
	for (unsigned i = 0; i < lista_przedmiotow.size(); i++)
	{
		cout << i + 1 << ". " << it->nazwa << " " << it->rodzaj << "\n";
		it++;
	}

	int wybor;
	wybor = czy_dobry_znak();

	if (0 < wybor && wybor < lista_przedmiotow.size())
	{

		auto it = lista_przedmiotow.begin();
		advance(it, wybor - 1);
		bool znaleziony;
		znaleziony = true;
		while (znaleziony)
		{
			znaleziony = false;
			for (auto a = lista_zajec.begin(); a != lista_zajec.end(); a++)
			{
				if (it->id == a->przedmiot->id)
				{
					lista_zajec.erase(a);
					znaleziony = true;
					break;
				}
			}
		}
		lista_przedmiotow.erase(it);
	}

	auto para = make_pair(lista_przedmiotow, lista_zajec);
	return para;
}
pair<list<Prowadzacy>, list<Zajecia>>& usun_prowadzacego(list<Prowadzacy>& lista_prowadzacych, list<Zajecia>& lista_zajec, int tym)
{
	if (lista_prowadzacych.empty()) {
		cout << "Nie ma zadnych prowadzacych w systemie";
	}

	auto  it = lista_prowadzacych.begin();
	for (unsigned i = 0; i < lista_prowadzacych.size(); i++)
	{
		cout << i + 1 << ". " << it->nazwisko << " " << it->imie << "\n";
		it++;
	}

	int wybor;
	wybor = czy_dobry_znak();

	if (0 < wybor && wybor < lista_prowadzacych.size())
	{

		auto it = lista_prowadzacych.begin();
		advance(it, wybor - 1);
		bool znaleziony;
		znaleziony = true;
		while (znaleziony)
		{
			znaleziony = false;
			for (auto a = lista_zajec.begin(); a != lista_zajec.end(); a++)
			{
				if (it->id == a->prowadzacy->id)
				{
					lista_zajec.erase(a);
					znaleziony = true;
					break;
				}
			}
		}
		lista_prowadzacych.erase(it);
	}

	auto para = make_pair(lista_prowadzacych, lista_zajec);
	return para;
}
bool zapisz_prowadzacych(list <Prowadzacy>& lista_prowadzacych, int tym)
{
	fstream plik("nowi_prowadzacy.txt", ios::out);

	if (plik.good())
	{
		for (Prowadzacy prowadzacy : lista_prowadzacych)
		{
			string do_zapisu;
			do_zapisu = to_string(prowadzacy.id);
			do_zapisu += ".";
			do_zapisu += prowadzacy.nazwisko;
			do_zapisu += " ";
			do_zapisu += prowadzacy.imie;

			plik << do_zapisu << endl;
		}
		plik.close();
	}
	else
	{
		cout << " Nie udalo sie zapisac nowych prowadzacych";
		return false;
	}

	return true;
}
bool zapisz_grupy(list <Grupa>& lista_grup, int tym) // grupy jeszcze sie nie zapisuja, mozliwe ze 
//dlatego ze zajecia sie nie zapisuja i dlatego ogolnie jest falsz i program wogle nie zapsiuje nowych prowadzacych tylko sa z poprzedniej kompliacji 
{
	fstream plik("nowe_grupy.txt", ios::out);

	if (plik.good())
	{
		for (Grupa grupa : lista_grup)
		{
			string do_zapisu;
			do_zapisu = to_string(grupa.id);
			do_zapisu += ".";
			do_zapisu += grupa.nazwa;

			plik << do_zapisu << endl;
		}
		plik.close();
	}
	else
	{
		cout << " Nie udalo sie zapisac nowych grup";
		return false;
	}

	return true;
}
bool zapisz_zajecia(list <Zajecia>& lista_zajec, list<Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list<Przedmiot>& lista_przedmiotow, float tym)
{
	fstream plik("nowe_zajecia.txt", ios::out);

	if (plik.good())
	{
		for (Zajecia zajecia : lista_zajec)
		{
			string do_zapisu;
			do_zapisu = to_string (zajecia.prowadzacy->id);
			do_zapisu += " ";
			do_zapisu += to_string(zajecia.grupa->id);
			do_zapisu += " ";
			do_zapisu += to_string(zajecia.przedmiot->id);
			do_zapisu += " ";
			do_zapisu += zajecia.dzien;
			do_zapisu += " ";
			do_zapisu += to_string(zajecia.godzina);

			plik << do_zapisu << endl;
		}
		plik.close();
	}
	else
	{
		cout << " Nie udalo sie zapisac nowych grup";
		return false;
	}
	return true;
}
bool zapisz_wszystko(list <Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup, list <Zajecia>& lista_zajec, list<Przedmiot> lista_przedmiotow,int tym)
{
	return
	zapisz_prowadzacych(lista_prowadzacych, 1) &&
	zapisz_grupy(lista_grup, 1) &&
	zapisz_zajecia(lista_zajec, lista_prowadzacych, lista_grup, lista_przedmiotow, 1);
}