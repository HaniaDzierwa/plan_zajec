#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <list>


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
bool wczytaj_zajecia(list<Zajecia>& lista_zajec, list<Prowadzacy>& lista_prowadzacych, list<Grupa>& lista_grup,
	list<Przedmiot>& lista_przedmiotow)
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
// pokaz plan dla danego nauczyciela 
list <Zajecia*> zajecia_danego_dnia(list<Zajecia*> lista_zajec_prowadzacego, string nazwa_dnia)   // funkcja bedzie zwracac liste wskaznikow zajec 
{

	list <Zajecia*> zajecia_danego_dnia;
	for (auto it = lista_zajec_prowadzacego.begin(); it != lista_zajec_prowadzacego.end(); it++)
	{

		if ((*it)->dzien == nazwa_dnia)
		{
			zajecia_danego_dnia.push_back(*it);   //*it wycigamy caly obiekt, operator wyluskania
		}

	}
	zajecia_danego_dnia.sort([](Zajecia* pierwszy, Zajecia* drugi) {
		return pierwszy->godzina <= drugi->godzina; // okresla sposob porownania

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
			cout << "godz: "<< zajecia->godzina <<  " " << przedmiot->nazwa << " " << przedmiot->rodzaj << " " 
				<< "nr.sali: " << przedmiot->miejsce << " " << "grupa: "<< zajecia->grupa->nazwa  << "\n";
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

Grupa* wyszukaj_grupe( list<Grupa>& lista_grup)
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
	int wybor = czy_dobry_znak()-1 ;
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

void showlistGrupa(list<Zajecia>& lista_zajec)
{
	//dla poszczegolnych przedmiotow
	for (Zajecia tymczasowe : lista_zajec)
	{

		cout << tymczasowe.grupa->nazwa << " " << tymczasowe.dzien << " " << tymczasowe.godzina
			<< " " << tymczasowe.przedmiot->miejsce << " "
			<< tymczasowe.prowadzacy->nazwisko << " " << tymczasowe.prowadzacy->imie << endl;
	}
}
void showlistPrzedmiot(list<Zajecia>& lista_zajec)
{
	for (Zajecia tymczasowe : lista_zajec)
	{
		cout << tymczasowe.przedmiot->nazwa << " " << tymczasowe.przedmiot->rodzaj << " "
			<< tymczasowe.dzien << " " << tymczasowe.godzina << " " << tymczasowe.przedmiot->miejsce << " "
			<< tymczasowe.prowadzacy->nazwisko << " " << tymczasowe.prowadzacy->imie << " "
			<< tymczasowe.grupa->nazwa << endl;

	}
}

void termin_zajec(list<Zajecia>& lista_zajec)
{
	for (Zajecia przedmiot : lista_zajec)
	{
		cout << przedmiot.dzien << " " << przedmiot.godzina << " " << przedmiot.przedmiot->nazwa << endl;

	}
}

int czy_dobry_znak() // tutaj ma byc ampersant aby zostala przekazna wartosc z maina ?
{
	int zm_wybor;
	while (!(cin >> zm_wybor))
	{
		cout << "To nie jest poprawny znak\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return zm_wybor;
}

void wybierz_kryterium(list<Zajecia>& lista_zajec)
{
	int wybor = 0;
	do
	{
		cout << "Wybierz kryterium\n";
		cout << "1. Termin zajec \n";
		cout << "2. Zajecia w danym dniu\n";
		cout << "3. Zajec w danych salach\n";
		cout << "4. Powrot do menu\n";
		cout << "Wprowadz odpowiednia liczbe\n";

		wybor = czy_dobry_znak();
		switch (wybor)
		{
		case 1:
			termin_zajec(lista_zajec);
			break;

		case 2:
			break;
		case 4:
			cout << "Powrot do menu ";
			break;


		default:
			cout << "Nieodpowiedni numer";
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
		case 3: showlistPrzedmiot(lista_zajec);
			break;
		case 4:
			wybierz_kryterium(lista_zajec);
			break;
		case 5:// jak to zrobic aby po dadaniu nowego prowadzacego pojawily sie dostpene dla niego funkcje ???
			cout << " ";
			break;

		case 6:
			cout << "Koniec programu";
			return;
		default:
			cout << "Nieodpowiedni numer";
			break;
		}
	}

}