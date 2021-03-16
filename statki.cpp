#include <iostream>
#include <string>
#include <utility>
#include <fstream>
#include <sstream>
#include "statki.h"
#include "config.h"
#include "funkcje.h"


/*********************************************************/
/*                        MASZT                          */
/*********************************************************/

maszt::~maszt()
{
	while (head)
    {
        el_maszt * p = head->next;
        delete head;
        head = p;
    }
}

maszt & maszt::operator+=(std::pair<int,int> wsp)
{
	head = new el_maszt(wsp.first, wsp.second, head);
	return *this;
}

bool maszt::operator!()
{
	if(head == nullptr)
		return true;
	return false;
}

bool maszt::trafienie(std::pair<int,int> wsp)
{
	el_maszt * pop = head; el_maszt * akt = head;
	while(akt)
	{
		if(akt->x == wsp.first && akt->y == wsp.second)
		{
			std::cout << "trafiony!" << std::endl;
			if(head == akt)
				head = akt->next;
			else
				pop->next = akt->next;
			delete akt; 
			return true;
		}
		else
		{
			pop = akt;
			akt = akt->next;
		}
	}
	return false;
}

bool maszt::szukaj(std::pair<int,int> wsp)
{
	el_maszt * pop = head; el_maszt * akt = head;
	while(akt)
	{
		if(akt->x == wsp.first && akt->y == wsp.second)
			return true;
		else
		{
			pop = akt;
			akt = akt->next;
		}
	}
	return false;
}

bool maszt::porownaj(el_statek *& istniejace)
{
	el_maszt * temp = head;
	while(temp)
	{
		std::pair<int,int> wsp (temp->x, temp->y);
		el_statek * p = istniejace; 
		while(p)
		{
			if(p->szukaj(wsp))
				return true;
			p = p->next;
		}
		temp = temp->next;
	}
	return false;
}

void maszt::przepisz(el_statek *& temp)
{
	el_maszt * t = temp->head;
	while(t)
	{
		head = new el_maszt(t->x, t->y, head);
		t = t->next;
	}
}

void maszt::zapisz(std::ofstream & plik)
{
	el_maszt * m = head;
	while(m)
	{
		plik << m->x << " " << m->y << " ";
		m = m->next;
	}
}

/*********************************************************/
/*                       STATEK                          */
/*********************************************************/

statek::~statek()
{
	while (head)
    {
        el_statek * p = head->next;
        delete head;
        head = p;
    }
}

statek & statek::operator+=(int ile)
{
	head = new el_statek(ile, head);
	return *this;
}

bool statek::operator!()
{
	if(head == nullptr)
		return true;
	return false;
}

bool statek::trafienie(std::pair<int,int> wsp)
{
	el_statek * pop = head; el_statek * akt = head;
	while(akt)
	{
		if(akt->trafienie(wsp) == true)
		{
			if(!(*akt))
			{
				std::cout << akt->ile_m << "-masztowiec zatopiony!" << std::endl;
				if(head == akt)
					head = akt->next;
				else
					pop->next = akt->next;
				delete akt;
			}
			return true;
		}
		else
		{
			pop = akt;
			akt = akt->next;
		}
	}
	return false;
}

bool statek::szukaj(std::pair<int,int> wsp)
{
	el_statek * pop = head; el_statek * akt = head;
	while(akt)
	{
		if(akt->szukaj(wsp) == true)
			return true;
		else
		{
			pop = akt;
			akt = akt->next;
		}
	}
	return false;
}

void statek::zapisz(std::ofstream & plik)
{
	el_statek * p = head;
	while(p)
	{
		plik << p->ile_m << " ";
		p->zapisz(plik);
		plik << std::endl;
		p = p->next;
	}
}

void statek::wczytaj(std::pair<int,int> wsp)
{
	(*head) += wsp;
}

void statek::wprowadz()
{
	el_statek * p = head;
	while(p)
	{
		el_statek * temp = new el_statek(p->ile_m, nullptr);
		std::cout << "statek " << p->ile_m << "-masztowy" << std::endl;
		std::cout << "Podaj wspolrzedne dzioba statku: ";
		std::pair <int, int> dziob = wspolrzedne();
		if(p->ile_m > 1)
		{
			std::cout << "Podaj wspolrzedne rufy statku: ";
			std::pair <int, int> rufa = wspolrzedne();
			
			while(poprawnosc(dziob, rufa, p->ile_m) == false)
			{
				//sprawdzenie czy statek ma odpowiedni rozmiar i czy znajduje sie w jedenj linii
				std::cout << "niepoprawne wspolrzedne, ktora chcesz poprawic?\n 1 -> dziob\n 2 -> rufa\n";
				int ktora; std::cin >> ktora;
				if(ktora == 1)
				{
					std::cout << "Podaj wspolrzedne dzioba statku: ";
					dziob = wspolrzedne();
				}
				else
				{
					std::cout << "Podaj wspolrzedne rufy statku: ";
					rufa = wspolrzedne();
				}
			}
			(*temp) += rufa;
			
			if(p->ile_m > 2)
			{
				//wypełnianie przestrzeni między dziobem i rufą
				if(dziob.first == rufa.first)
				{
					std::cout <<dziob.first <<"=="<< rufa.first<<std::endl;
					if(dziob.second > rufa.second)
					{
						std::cout <<dziob.second <<">"<< rufa.second<<std::endl;
						for(int i=1; i < p->ile_m-1; i++)
						{
							std::pair<int,int> wsp (dziob.first,rufa.second+i);
							std::cout << "dodaje" << wsp.first << wsp.second<<std::endl;
							(*temp) += wsp;
						}
					}		
					else
					{
						std::cout <<dziob.second <<"<"<< rufa.second<<std::endl;
						for(int i=1; i < p->ile_m-1; i++)
						{
							std::pair<int,int> wsp (dziob.first,dziob.second+i);
							std::cout << "dodaje" << wsp.first << wsp.second<<std::endl;
							(*temp) += wsp;
						}
					}
				}
				if(dziob.second == rufa.second)
				{
					std::cout <<dziob.second <<"=="<< rufa.second<<std::endl;
					if(dziob.first > rufa.first)
					{
						std::cout <<dziob.first <<">"<< rufa.first<<std::endl;
						for(int i=1; i < p->ile_m-1; i++)
						{
							std::pair<int,int> wsp (rufa.first+i,rufa.second);
							std::cout << "dodaje" << wsp.first << wsp.second<<std::endl;
							(*temp) += wsp;
						}
					}
					else
					{
						std::cout <<dziob.first <<"<"<< rufa.first<<std::endl;
						for(int i=1; i < p->ile_m-1; i++)
						{
							std::pair<int,int> wsp (dziob.first+i,rufa.second);
							std::cout << "dodaje" << wsp.first << wsp.second<<std::endl;
							(*temp) += wsp;
						}
					}
				}
			}
		}
		(*temp) += dziob;

		if(temp->porownaj(head) == false)
		{
			p->przepisz(temp);
			p = p->next;
		}
		else
			std::cout << "niepoprawnie wprowadzony statek, sproboj ponownie" << std::endl;

		delete temp;
	}
}

/*********************************************************/
/*                       PLANSZA                         */
/*********************************************************/

plansza::plansza()
{
	tGracz = new char *[ustawienia.getWiersze()];
	tWrog = new char *[ustawienia.getWiersze()];
	for (int i=0; i<ustawienia.getWiersze(); i++)
	{
		tGracz[i] = new char [ustawienia.getKolumny()];
		tWrog[i] = new char [ustawienia.getKolumny()];
		for(int j=0; j<ustawienia.getKolumny(); j++)
		{
			tGracz[i][j] = '~';
			tWrog[i][j] = '~';
		}
	}
}

plansza::~plansza()
{
	for (int w = 0; w < ustawienia.getWiersze(); w++)
	{
		delete[] tGracz[w];
		delete[] tWrog[w];
	}
	delete[] tGracz;
	delete[] tWrog;
}

void plansza::wyswietl()
{
	//wyswietlanie naglowkow
	std::cout << "TWOJE MORZE";
	if(2*ustawienia.getKolumny() > 10)
		for(int i = 0; i< 2*ustawienia.getKolumny()-10; i++)
			std::cout << " ";
	std::cout << "\t\t\tMORZE WROGA" << std::endl;

	for(int i=0; i<ustawienia.getWiersze(); i++)
	{
		if(i==0)
		{
			//wyswietlanie numerow kolumn pierwszej planszy
			std::cout << "  ";
			for(int k=0; k<ustawienia.getKolumny(); k++)
				std::cout << k << " ";
			std::cout << "\t\t\t" << "  ";
			
			//wyswietlanie numerow kolumn drugiej planszy
			for(int k=0; k<ustawienia.getKolumny(); k++)
				std::cout << k << " ";
			std::cout << std::endl;
		}
		for(int j=0; j<ustawienia.getKolumny(); j++)
		{
			if(j==0)
			{
				//wyswietlanie indeksu wiersza
				char c = 'A'+i;
				std::cout << c << " ";
			}
			std::cout << tGracz[i][j] << " ";
		}
		std::cout << "\t\t\t";
		for(int j=0; j<ustawienia.getKolumny(); j++)
		{
			if(j==0)
			{
				//wyswietlanie indeksu wiersza
				char c = 'A'+i;
				std::cout << c << " ";
			}
			std::cout << tWrog[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void plansza::strzal(std::pair<int,int> wsp, char c, char kto)
{
	if(kto == 'w')
	{
		if(tWrog[wsp.first][wsp.second] == 'X') //jesli bylo kiedys trafienie to nie moze sie zmienic
			c = 'X';
		tWrog[wsp.first][wsp.second] = c;
	}
	else
	{
		if(tGracz[wsp.first][wsp.second] == 'X') //jesli bylo kiedys trafienie to nie moze sie zmienic
			c = 'X';
		tGracz[wsp.first][wsp.second] = c;	
	}
}

/*********************************************************/
/*                       PUNKTY                          */
/*********************************************************/

punkty::punkty()
{
	int pole = ustawienia.getKolumny()*ustawienia.getWiersze();
	int maszty = 0;
	for (int i=0; i<ustawienia.getIle(); i++)
		maszty += ustawienia.getElement(i);
	maszty *= 100;
	trudnosc = maszty/pole;
	ruchy = 0;
	trafione = 0;
}

punkty & punkty::operator++()
{
	trafione++;
	return *this;
}

punkty & punkty::operator--()
{
	ruchy++;
	return *this;
}

double punkty::getCelnosc()
{
	if(trafione == 0 || ruchy == 0)
		return 0;
	trafione *= 100;
	return trafione/ruchy;
}

/*********************************************************/
/*                        GRACZ                          */
/*********************************************************/

void gracz::wypelnij()
{
	for(int i=0; i<ustawienia.getWiersze(); i++)
	{
		for(int j=0; j<ustawienia.getKolumny(); j++)
		{
			std::pair <int, int> wsp (i,j);
			if(wrog->wrog->szukaj(wsp))
				strzal(wsp, '#', 'g');
		}
	}
}

bool gracz::ruch()
{
	std::cout << "\nruch " << nazwa << std::endl;
	(*wrog->wrog).operator--();
	wyswietl();
	
	std::pair <int, int> wsp;
	std::cout << "wprowadz wspolrzedne: ";
	wsp = wspolrzedne();

	if(wrog->trafienie(wsp))
	{
		//trafiony
		(*wrog->wrog).operator++();
		strzal(wsp, 'X', 'w');
		wrog->strzal(wsp, 'X', 'g');
		Hist.zapisz(nazwa, wsp, true);
		if(!(*wrog))
			return false;
	}
	else
	{
		//nietrafiony
		std::cout << "pudlo!" << std::endl;
		strzal(wsp, '*', 'w');
		wrog->strzal(wsp, '*', 'g');
		Hist.zapisz(nazwa, wsp, false);
	}
	return true;
}

void gracz::czytaj(std::ifstream & plik)
{
	std::string linia; std::stringstream ss;
	getline(plik, linia);
	ss.str(linia); int r,t;
	ss >> nazwa >> r >> t;
	(*wrog->wrog).setRuchy(r);
	(*wrog->wrog).setTrafione(t);
	while(getline(plik,linia))
	{
		int ile; std::pair<int,int> wsp;
		ss.clear(); ss.str(linia);
		ss >> ile;
		(*wrog->wrog) += ile;
		while(ile>0)
		{
			ss >> wsp.first >> wsp.second;
			wrog->wrog->wczytaj(wsp);
			ile--;
		}
		ss.clear();
	}	
}