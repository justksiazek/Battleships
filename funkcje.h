#ifndef FUNKCJE_H
#define FUNKCJE_H

#include "statki.h"

/** Funkcja wyświetla i obsługuje menu główne */
void menu();
/** Funkcja pozwala użytkownikowi ustawić rozmiar planszy oraz ilość i wymiary statków */
void rozmiarPlanszy();
/** Funkcja uruchamia nową grę - umożliwia stworzenie graczy i ustawienie statków na planszach */
void nowa();
/** Funkcja odczytuje z pliku informacje o graczach i ich statkach, pochodzące z uprzednio rozpoczętej, nieskończonej i zapisanej rozgrywki */
void kontynuuj();
/** Funkcja obsługuje rozgrywkę 
 * @param g wskaźnik na gracza nr 1 (umożliwia dostęp do obiektu gracza 1 i gracza 2)
*/
void gra(gracz *& g);
/** Funkcja obsługuje wpisywanie współrzędnych
 * @return typ para składający się z dwóch zmiennych typu int, symbolizujących współrzędną x oraz współrzędną y
 */
std::pair <int, int> wpiszWsp();
/** Funkcja wczytuje współrzędne i kontroluje ich poprawność - czy nie wychodzą poza planszę
 * @return typ para składający się z dwóch zmiennych typu int, symbolizujących współrzędną x oraz współrzędną y
 */
std::pair <int, int> wspolrzedne();
/** Funkcja sprawdza czy odległość między współrzędnymi jest odpowienia
 * @param a pierwsza współrzędna (x)
 * @param b druga współrzędna (y)
 * @param ile ilość masztów danego statku
 * @return true jeżeli wspłrzędne zapewniają odpowiednią ilość masztów; false jeżeli jej nie zapewniają
 */
bool wielkosc(int a, int b, int ile);
/** Funkcja sprawdza czy wprowadzone maszty dzioba i rufy znajdują się w jednej linii oraz czy długość statku jest odpowiednia
 * @param w1 współrzędne dzioba
 * @param w2 współrzędne rufy
 * @param ile liczba masztów danego statku
 * @return true jeżeli wartości są poprawne; false jeżeli są niepoprawne
 */
bool poprawnosc(std::pair<int,int> w1, std::pair<int,int> w2, int ile);
/** Funkcja wyświetla zasady i instrukje gry */
void zasady();

#endif