#ifndef struktury_h 
#define struktury_h

#include <vector> 
#include <string>
using namespace std;

struct Prowadzacy
{
    long id;
    string nazwisko;
    string imie;
};

struct Grupa
{
    long id;
    string nazwa;
};

struct Przedmiot
{
    long id;
    string nazwa;
    string rodzaj; 
    int miejsce;
   
};

struct Zajecia
{ 
    Prowadzacy *prowadzacy;
    Grupa * grupa;
    Przedmiot *przedmiot;
    string dzien;
    int godzina;
};



#endif