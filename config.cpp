#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "config.h"
#include "statki.h"

/*********************************************************/
/*                       RANKING                         */
/*********************************************************/

ranking::~ranking()
{
	while (head)
    {
        el_ranking * p = head->next;
        delete head;
        head = p;
    }
}

ranking & ranking::operator+=(std::pair<std::string,int> wpis)
{
	if(!head)
		head = new el_ranking(wpis.first, wpis.second, nullptr);
	else
	{
		el_ranking * p = head;
		while(p->next)
			p = p->next;
		p->next = new el_ranking(wpis.first, wpis.second, nullptr);
	}
	return *this;
}

ranking & ranking::operator<<(std::pair<std::string,int> wpis)
{
	if(!head)
    {
		//lista pusta
        head = new el_ranking(wpis.first, wpis.second, head);
        return *this;
    }
    if(head->punkty <= wpis.second)
	{
		//uzyskano wiecej punktow niz najwyzszy wynik
		head = new el_ranking(wpis.first, wpis.second, head);
		return *this;
	}
	el_ranking * p = head;
	while(p->next)
	{
		if(p->punkty >= wpis.second && p->next->punkty <= wpis.second)
		{
			//jezeli mamy mniej lub tyle samo punktow co ta pozycja
			//i jednoczesnie wiecej lub tyle samo niż nastepna pozycja
			el_ranking * t = new el_ranking(wpis.first, wpis.second, p->next);
			p->next = t;
			return *this;
		}
		p = p->next;
	}
	//uzyskano mniej punktow niz najgorszy wynik
	p->next = new el_ranking(wpis.first, wpis.second, nullptr);
	return *this;
}

void ranking::wczytaj()
{
	std::ifstream rankingi;
	rankingi.open("ranking.txt");
	if(rankingi.good())
	{
		std::cout << std::setw(3) << "poz." << std::setw(3) << "|" << std::setw(10) << "nazwa" << std::setw(3) << "|" << std::setw(10) << "punkty" << std::endl;
		std::cout << std::setfill('-') << std::setw(7) << "+" << std::setw(13) << "+" << std::setw(10) << "-" << std::endl;
		std::string linia; int i=1;
		while(getline(rankingi, linia))
		{
			std::stringstream ss; std::string nazwa; int punkty;
			ss.str(linia); ss >> nazwa >> punkty;
			std::cout << std::setfill(' ') << std::setw(3) << i << "." << std::setw(3) << "|" << std::setw(10) << nazwa << std::setw(3) << "|" << std::setw(10) << punkty << std::endl;
			i++;

		}
	}
	rankingi.close();
}

void ranking::zapisz()
{
	std::ofstream rankingi;
	rankingi.open("ranking.txt");
	if(rankingi.good())
	{
		el_ranking * p = head;
		int i = 0;
		while (p && i<10)
		{
			rankingi << p->nazwa << " " << p->punkty << std::endl;
			p = p->next;
			i++;
		}
	}
	rankingi.close();
}

/*********************************************************/
/*                      HISTORIA                         */
/*********************************************************/

historia::~historia()
{
	while (head)
    {
        el_historia * p = head->next;
        delete head;
        head = p;
    }
}

void historia::zapisz(std::string nazwa, std::pair<int,int> wsp, bool traf)
{
	head = new el_historia (nazwa, wsp.first, wsp.second, traf, head);
}

void historia::wypisz(int i)
{
	el_historia * p = head;
	while(p && i>0)
	{
		char X = p->x+'A';
		std::cout << std::setw(11) << "gracz: " << p->nazwa << std::endl;
		std::cout << std::setw(11) << "strzal: " << X << p->y << std::endl;
		std::cout << std::setw(11) << "trafienie: "; 
		if(p->trafienie)
			std::cout << "TAK" << std::endl;
		else
			std::cout << "NIE" << std::endl;
		std::cout << std::endl;
		p = p->next;
		i--;
	}
}

/*********************************************************/
/*                     KONFIGURACJA                      */
/*********************************************************/

konfiguracja::konfiguracja()
{
	tab = new int [ileStatkow];
	tab[0] = 2;
	tab[1] = 2;
	tab[2] = 3;
	tab[3] = 3;
	tab[4] = 4;
	tab[5] = 5;
}

konfiguracja::~konfiguracja()
{
	std::cout << tab[0];
	delete[] tab;
}

void konfiguracja::utworzListe()
{
	delete[] tab;
	std::cout << "ile statkow chcesz w rozgrywce? ";
	std::cin >> ileStatkow;
	tab = new int [ileStatkow];
	std::cout << "ile masztow ma miec kazdy ze statkow?" << std::endl;
	int ileMasztow;
	for (int i = 0; i < ileStatkow; i++)
	{
		std::cout << i+1 << ". -> ";
		std::cin >> ileMasztow;
		while(ileMasztow > wiersze || ileMasztow > kolumny)
		{
			std::cout << "za duzo, sprobuj ponownie: ";
			std::cin >> ileMasztow;
		}
		tab[i] = ileMasztow;
	}
}

void konfiguracja::wczytaj(std::ifstream & plik)
{
	std::string linia; std::stringstream ss;
	getline(plik, linia); ss.str(linia);
	ss >> kolumny >> wiersze;
	ss.clear();

	getline(plik, linia); ss.str(linia);
	ss >> ileStatkow;
	ss.clear();

	getline(plik, linia); ss.str(linia);
	for (int i=0; i<ileStatkow; i++)
		ss >> tab[i];
}