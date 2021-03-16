#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <iostream>
#include "statki.h"

struct el_ranking
{
	/** nazwa gracza */
	std::string nazwa; 
	/** ilość punktów gracza */
	int punkty; 
	/** wskaźnik na kolejny element listy rankingu */
	el_ranking * next; 

	/** Konstruktor wieloargumentowy struktury elementu rankingu */
	el_ranking(std::string n, int p, el_ranking * ptr) : nazwa(n), punkty(p), next(ptr) {}
};

class ranking
{
	/** wkaźnik na głowę listy rankingowej */
	el_ranking * head; 
public:
	/** Metoda dodaje wpis rankingu na koniec jednokierunkowej listy rankingowej
	 * @param wpis nazwa gracza oraz ilość jego punktów
	 * @return referencja do obiektu ranking
	 */
	ranking & operator+=(std::pair<std::string,int> wpis);
	/** Metoda dodaje wpis rankingu w posortowanej kolejności
	 * @param wpis nazwa gracza oraz ilość jego punktów
	 * @return referencja do obiektu ranking
	 */
	ranking & operator<<(std::pair<std::string,int> wpis);
	/** Metoda wyświetla ranking, odczytując go z pliku */
	void wczytaj();
	/** Metoda zapisuje ranking do pliku */
	void zapisz();
	/** Konstruktor bezargumentowy klasy ranking */
	ranking() : head(nullptr) {}
	/** Destruktor klasy ranking */
	~ranking();
};

struct el_historia
{
	/** nazwa gracza, który wykonał ruch */
	std::string nazwa; 
	/** współrzędne wprowadzone przez gracza */
	int x, y; 
	/** informacja, czy gracz trafił w tym ruchu */
	bool trafienie; 
	/** wskaźnik na kolejny element listy historii */
	el_historia * next; 

	/** Konstruktor wieloargumentowy struktury elementu historii */
	el_historia(std::string _n, int _x, int _y, bool _t, el_historia * n) : nazwa(_n), x(_x), y(_y), trafienie(_t), next(n) {};
};

class historia
{
	/** wskaźnik na głowę listy historii */
	el_historia * head; 
public:
	/** Metoda dodaje element na początek listy historii
	 * @param nazwa nazwa gracza, który wykonał ruch
	 * @param wsp współrzędne ruchu wykonanego przez gracza
	 * @param traf informacja czy gracz trafił w maszt podczas wykonywania ruchu
	 */
	void zapisz(std::string nazwa, std::pair<int,int> wsp, bool traf);
	/** Metoda wypisuje uprzednie ruchy graczy
	 * @param i ilość ruchów do wyświetlenia
	 */
	void wypisz(int i);
	/** Konstruktor bezargumentowy klasy historia */
	historia() : head(nullptr) {}
	/** Destruktor klasy historia */
	~historia();
};

class konfiguracja
{
	/** ilość wierszy planszy */
	int wiersze = 10; 
	/** ilość kolumn planszy */
	int kolumny = 10; 
	/** tabela z ilościami masztów kolejnych statków */
	int * tab; 
	/** ilość statków w rozgrywce */
	int ileStatkow = 6; 
public:
	/** Metoda zwraca ilość wierszy */
	int getWiersze() { return wiersze; }
	/** Metoda zwraca ilość kolumn */
	int getKolumny() { return kolumny; }
	/** Metoda pozwala na ustawienie liczby wierszy */
	void setWiersze(int n) { wiersze = n; }
	/** Metoda pozwala na ustawienie liczby kolumn */
	void setKolumny(int n) { kolumny = n; }
	/** Metoda zwraca wartość elementu spod danego indeksu tablicy */
	int getElement(int i) { return tab[i]; }
	/** Metoda zwraca informację o ilości statków */
	int getIle() { return ileStatkow; }
	/** Metoda wczytuje z pliku infomacje o konfiguracji
	 * @param plik strumień, z którego czytamy
	 */
	void wczytaj(std::ifstream & plik);
	/** Metoda tworzy jednowymiarową tablicę przechowującą ilości masztów kolejnych statków * */
	void utworzListe();
	/** Konstruktor bezargumentowy klasy konfiguracja * */
	konfiguracja();
	/** Destruktor klasy konfiguracja * */
	~konfiguracja();
};

extern konfiguracja ustawienia; /** Globalna zmienna przechowująca ustawienia */
extern historia Hist; /** Globalna zmienna przechowywująca historię rozgrywki */

#endif