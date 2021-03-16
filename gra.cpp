#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "statki.h"
#include "config.h"
#include "funkcje.h"

konfiguracja ustawienia;
historia Hist;

void menu()
{
	int wybor;
	while(true)
	{
		std::cout << "Menu glowne: \n 1 -> wybierz rozmiar planszy \n 2 -> nowa gra \n 3 -> kontynuuj \n 4 -> wyswietl ranking \n 5 -> zasady gry \n 6 -> zakończ" << std::endl;
		std::cin >> wybor;
		switch(wybor)
		{
			case 1: { rozmiarPlanszy(); break; }
			case 2: { nowa(); break; }
			case 3: { kontynuuj(); break; }
			case 4: { 
						ranking Ranking; 
						Ranking.wczytaj(); 
						break; 
					}
			case 5: { zasady(); break; }
			case 6: { 
						Hist.~historia();
						ustawienia.~konfiguracja();
						return;
					 }
			default: std::cout << "nie ma takiej opcji" << std::endl;
		}
	}
}

void rozmiarPlanszy()
{
	std::cout << "ustaw szerokosc (min. 5 pol, max. 25 pol): ";
	int n; std::cin >> n;
	while(n < 5 || n > 25)
	{
		std::cout << "\nnieprawidlowa wartosc, wpisz ponownie ";
		std::cin >> n;
	}
	ustawienia.setKolumny(n);
	std::cout << "ustaw wysokosc (min. 5 pol max. 25 pol): ";
	std::cin >> n;
	while(n < 5 || n > 25)
	{
		std::cout << "\nnieprawidlowa wartosc, wpisz ponownie ";
		std::cin >> n;
	}
	ustawienia.setWiersze(n);
	ustawienia.utworzListe();
}

std::pair <int, int> wspolrzedne()
{
	std::pair <int, int> para = wpiszWsp();
	while(para.first >= ustawienia.getWiersze() || para.second >= ustawienia.getKolumny())
	{
		std::cout << "nieprawidlowe wspolrzedne, wpisz ponownie";
		para = wpiszWsp();
	}
	return para;
}

std::pair <int, int> wpiszWsp()
{
	std::string w; char X; int x,y;
	std::cin >> w;
	std::stringstream ss; ss.str(w);
	ss >> X; ss >> y;
	x = X-'A';
	std::pair <int, int> para (x,y);
	return para;
}

bool wielkosc(int a, int b, int ile)
{
	if(a > b && (a - b == ile-1))
		return true;
	else if (b > a && (b - a == ile-1))
		return true;
	return false;
}

bool poprawnosc(std::pair<int,int> w1, std::pair<int,int> w2, int ile)
{
	if(w1.first == w2.first)
		if(wielkosc(w1.second, w2.second, ile)==true)
			return true;
	if(w1.second == w2.second)
		if(wielkosc(w1.first, w2.first, ile)==true)
			return true;
	return false;
}

void gra(gracz *& g)
{
	//losowanie gracza rozpoczynającego grę
	srand(time(NULL));
	int start = rand() % 2;
	if(start == 1)
		g = g->getWrog();

	while(true)
	{
		bool dalej = g->ruch();
		if(dalej == false)
		{
			ranking Ranking;
			std::ifstream lista;
			lista.open("ranking.txt");
			if(lista.good())
			{
				std::string linia;
				while(getline(lista,linia))
				{
					std::stringstream ss; std::pair<std::string,int> wpis;
					ss.str(linia);
					ss >> wpis.first >> wpis.second;
					Ranking += wpis;
					ss.clear();
				}
			}
			lista.close();

			std::cout << "\nkoniec gry. wygral " << g->getNazwa() << std::endl;
			std::cout << "Punkty:" << std::endl;
			
			//zapis do rankingu punktow graczy
			std::pair<std::string, int> para (g->getNazwa(), g->getPunkty());
			std::cout << para.first << ": " << para.second << std::endl;
			Ranking << para;
			g = g->getWrog();
			para.first = g->getNazwa(); para.second = g->getPunkty();
			std::cout << para.first << ": " << para.second << std::endl;
			Ranking << para;

			Ranking.zapisz();
			break;
		}
		std::cout << "1 -> kontynuuj\n2 -> instant replay\n3 -> zapisz i wyjdz\n";
		int m; std::cin >> m;
		if(m == 2)
		{
			std::cout << "ile ruchow odegrac?" <<std::endl;
			int r; std::cin >> r;
			Hist.wypisz(r);
		}
		if(m == 3)
		{
			std::ofstream p1("p1.txt");
			if(p1.good())
			{
				p1 << g->getNazwa() << " " << g->getRuchy() << " " << g->getTrafione() << std::endl;
				g->zapisz(p1);
			}
			p1.close();
			g = g->getWrog();
			std::ofstream p2("p2.txt");
			if(p2.good())
			{
				p2 << g->getNazwa() << " " <<  g->getRuchy() << " " << g->getTrafione() << std::endl;
				g->zapisz(p2);
			}
			p2.close();
			std::ofstream config("config.txt");
			if(config.good())
			{
				config << ustawienia.getKolumny() << " " << ustawienia.getWiersze() << std::endl;
				config << ustawienia.getIle() << std::endl;
				for(int i = 0; i<ustawienia.getIle(); i++)
				{
					config << ustawienia.getElement(i) << " ";
				}
			}
			config.close();
			break;
		}
		g = g->getWrog();
	}
}

void nowa()
{
	gracz g1;
	gracz g2;
	gracz * g = &g2;
	g1.setWrog(g);
	g = &g1;
	g2.setWrog(g);

	//utworzenie graczy
	std::cout << "Tworzenie 1 gracza..." << std::endl;
	std::cout << "wpisz nazwe gracza: "; std::string nazwa; std::cin >> nazwa;
	g1.setNazwa(nazwa); 
	std::cout << "Tworzenie 2 gracza" << std::endl;
	std::cout << "wpisz nazwe gracza: "; std::cin >> nazwa;
	g2.setNazwa(nazwa);

	//utworzenie list statkow graczy
	for(int i=0; i < ustawienia.getIle(); i++)
	{
		g1 += ustawienia.getElement(i);
		g2 += ustawienia.getElement(i);
	}

	//wprowadzanie statków
	std::cout << g1.getNazwa() << " wprowadz swoje statki" << std::endl; 
	g1.wprowadz();
	std::cout << g2.getNazwa() << " wprowadz swoje statki" << std::endl;
	g2.wprowadz();

	g1.wypelnij();
	g2.wypelnij();

	gra(g);
}

void kontynuuj()
{
	std::ifstream config("config.txt");
	if(config.good())
		ustawienia.wczytaj(config);
	config.close();

	gracz g1;
	gracz g2;
	gracz * g = &g2;
	g1.setWrog(g);
	g = &g1;
	g2.setWrog(g);

	std::ifstream p1("p1.txt");
	if(p1.good())
		g1.czytaj(p1);
	p1.close();
	
	std::ifstream p2("p2.txt");
	if(p2.good())
		g2.czytaj(p2);
	p2.close();

	g1.wypelnij();
	g2.wypelnij();

	gra(g);
}

void zasady()
{
	std::cout << "ZASADY:" << std::endl;
	std::cout << "1. Kazdy z dwoch graczy ma dwie plansze - jedna ze swoimi statkami i jedna pusta na poczatku gry, na ktorej beda zaznaczane jego strzaly" << std::endl;
	std::cout << "2. Domyslne ustawienie to plansza 10x10 i 6 statkow po kolejno: 2, 2, 3, 3, 4 i 5 masztów. Ustawienie to mozna zmienic." << std::endl;
	std::cout << "3. Statki można ustawiać tylko w poziomie lub w pionie i nie moga sie stykac - musza byc otoczone jednym polem odstepu:\n\t\t        \n\t\t ~~~    \n\t\t ~#~    \n\t\t ~#~    \n\t\t ~#~    \n\t\t ~#~~~~ \n\t\t ~~~##~ \n\t\t   ~~~~ " <<std::endl;
	std::cout << "4. Podczas jednej tury jeden z graczy wykonuje ruch. Gra trwa aż wszystkie statki jednego z graczy są zestrzelone" << std::endl;
	std::cout << "5. Wspolrzedne nalezy wpisywac w formie: A0 -> bez spacji i znakow przestankowych, litera wspolrzednej z duzej litery." << std::endl;
}