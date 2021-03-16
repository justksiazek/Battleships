#ifndef STATKI_H
#define STATKI_H

#include <string>
#include <iostream>

struct el_statek;

struct el_maszt
{
	/** współrzędne masztu */
	int x, y;
	/** wskaźnik na kolejny element listy masztów */
	el_maszt * next;

	/** Konstruktor wieloargumentowy struktury elementu masztu */
	el_maszt(int _x, int _y, el_maszt * n) :x(_x), y(_y), next(n) {};
};

class maszt
{
protected:
	/** wskaźnik na glowe listy masztów */
	el_maszt * head; 
public:
	/** Metoda dodaje nowy maszt na początek listy masztów
	 * @param wsp współrzędne masztu
	 * @return referencja do obiektu maszt
	 */
	maszt & operator+=(std::pair<int,int> wsp);
	/** Metoda sprawdza czy istnieje lista masztów
	 * @return true jeśli istnieje wskaźnik na głowę listy masztów; false jeśli ten wskaźnik to nullptr
	 */
	bool operator!();
	/** Metoda przeszukuje listę statków w poszukiwaniu masztu o podanych współrzędnych
	 * @param wsp współrzędne szukanego masztu
	 * @return true jeżeli znaleziono maszt o podanych współrzędnych; false jeżli nie znaleziono takiego masztu
	 */
	bool szukaj(std::pair<int,int> wsp);
	/** Metoda przeszukuje listę masztów w poszukiwaniu masztu o podanych współrzędnych i usuwa go
	 * @param wsp współrzędne szukanego masztu
	 * @return true jeżeli znaleziono maszt o podanych współrzędnych i go usunięto; false jeżli nie znaleziono takiego masztu
	 */
	bool trafienie(std::pair<int,int> wsp);
	/** Metoda zapisuje maszty z listy do pliku
	 * @param plik strumień, do którego zapisujemy
	 */
	void zapisz(std::ofstream & plik);
	/** Metoda porównuje tymczasową listę masztów z istniejącymi masztami
	 * @param istniejace lista istniejących już statków
	 * @return true jeżeli znaleziono powtarzające się maszty; false jeśli maszty się nie powtarzają
	 */
	bool porownaj(el_statek *& istniejace);
	/** Metoda przepisuje tymczasową listę masztów do listy istniejącego statku
	 * @param temp wskaźnik na tymczasową listę masztów
	 */
	void przepisz(el_statek *& temp);
	/** Konstruktor bezargumentowy klasy maszt */
	maszt() : head(nullptr) {}
	/** Destruktor klasy maszt */
	~maszt();
};

struct el_statek : public maszt
{
	/** ilość masztów danego statku */
	int ile_m; 
	/** wskaźnik na kolejny element listy statków */
	el_statek * next; 

	/** Konstruktor wieloargumentowy struktury elementu statku */
	el_statek(int i, el_statek * n) :ile_m(i), next(n) {};
};

class statek
{
protected:
	/** wskaźnik na głowę listy statków */
	el_statek * head; 
public:
	/** Metoda dodaje nowy statek na początek listy statków
	 * @param ile ilość masztów statku
	 * @return referencja do obiektu statek
	 */
	statek & operator+=(int ile);
	/** Metoda sprawdza czy istnieje lista statków
	 * @return true jeśli istnieje wskaźnik na głowę listy statkóœ; false jeśli ten wskaźnik to nullptr
	 */
	bool operator!();
	/** Metoda przeszukuje listę statków w poszukiwaniu statku z masztem o podanych współrzędnych
	 * @param wsp współrzędne szukanego masztu
	 * @return true jeżeli znaleziono maszt o podanych współrzędnych; false jeżli nie znaleziono takiego masztu
	 */
	bool szukaj(std::pair<int,int> wsp);
	/** Metoda przeszukuje listę statków w poszukiwaniu masztu o podanych współrzędnych i usuwa statek, w którym znaleziono ten maszt, jeśli był on ostatnim masztem
	 * @param wsp współrzędne szukanego masztu
	 * @return true jeżeli znaleziono statek o podanych współrzędnych; false jeżli nie znaleziono takiego masztu
	 */
	bool trafienie(std::pair<int,int> wsp);
	/** Metoda zapisuje statki z listy do pliku
	 * @param plik strumień, do którego zapisujemy
	 */
	void zapisz(std::ofstream & plik);
	/** Metoda wczytuje maszty z pliku do listy
	 * @param wsp współrzędne masztu
	 */
	void wczytaj(std::pair<int,int> wsp);
	/** Metoda obsługuje wprowadzanie i kontrolę poprawności wprowadzania statków */
	void wprowadz();
	/** Konstruktor bezargumentowy klasy statek */
	statek() : head(nullptr) {}
	/** Destruktor klasy statek */
	~statek();
};

class plansza
{
	/** plansza gracza */
	char ** tGracz; 
	/** pierwotnie pusta plansza wypełnianiana strzałami gracza */
	char ** tWrog; 
public:
	/** Metoda wyświetla plansze gracza i jego przeciwnika */
	void wyswietl();
	/** Metoda zaznacza na planszy strzał gracza
	 * @param wsp współrzędne strzału
	 * @param c symbol wstawiany do planszy
	 * @param kto symbol wskazujący na planszę, do której wstawiamy strzał
	 */
	void strzal(std::pair<int,int> wsp, char c, char kto);
	/** Konstruktor bezargumentowy klasy plansza */
	plansza();
	/** Destruktor klasy plansza */
	~plansza();
};

class punkty
{
	/** współczynnik trudności gry obliczany z rownania: 100 * ( ilość_masztów / powierzchnia_planszy ) */
	double trudnosc; 
	/** ilość trafień gracza */
	int trafione;
	/** ilość wykonanych ruchów */
	int ruchy; 
public:
	/** Metoda dodaje jeden do licznika trafionych statków (ponieważ każde trafienie zwiększa współczynnik celności) */
	punkty & operator++();
	/** Metoda dodaje jeden do licznika wykonanych ruchów (ponieważ każdy ruch zmniejsza współczynnik celności) */
	punkty & operator--();
	/** Metoda oblicza i zwraca punkty */
	double getPunkty() { return (trudnosc+getCelnosc())*10; }
	/** Metoda oblicza i zwraca współczynnik celności */
	double getCelnosc();
	/** Metoda zwraca liczbę ruchów gracza */
	int getRuchy() { return ruchy; }
	/** Metoda zwraca liczbę trafień gracza */
	int getTrafione() { return trafione; }
	/** Metoda ustawia ilość ruchów gracza */
	void setRuchy(int n) { ruchy = n; }
	/** Metoda ustawia ilość trafień gracza */
	void setTrafione(int n) { trafione = n; }
	/** Konstruktor bezargumentowy klasy punkty */
	punkty();
};

class gracz : public statek, public plansza, public punkty
{
	/** nazwa gracza */
	std::string nazwa; 
	/** wskaźnik na przeciwnika */
	gracz * wrog; 
public:
	/** Metoda zwraca nazwę gracza */
	std::string getNazwa() { return nazwa; }
	/** Metoda ustawia nazwę gracza */
	void setNazwa(std::string n) { nazwa = n; }
	/** Metoda ustawia wskaźnik na przeciwnika */
	void setWrog(gracz *& g) { wrog = g; }
	/** Metoda zwraca wskaźnik na przeciwnika */
	gracz * getWrog() { return wrog; }
	/** Metoda wczytuje z pliku informacje o graczu oraz ustawieniu statków 
	 * @param plik strumień, z którego czytamy
	 */
	void czytaj(std::ifstream & plik);
	/** Metoda obsługuje ruch w grze - pobiera współrzędne, sprawdza czy było trafienie, zaznacza na planszy strzał, zlicza punkty oraz sprawdza czy rozgrywka się zakończyła
	 * @return true jeżeli gramy dalej; false jeżeli któryś z graczy nie ma już statków
	 */
	bool ruch();
	/** Metoda obsługuje wypełnianie planszy statkami */
	void wypelnij();
	/** Konstruktor bezargumentowy klasy gracz */
	gracz() : wrog(nullptr) {}
};

#endif