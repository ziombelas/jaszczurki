/*
 * Tablica na punkty. Zanim będzie w użyciu musi zostać wzajemnie powiązana
 * z którymś z grających. Tablica wyświetla imię gracza oraz posiadaną
 * przez niego liczbę punktow.
 */

#ifndef TABLICANAWYNIK_H_
#define TABLICANAWYNIK_H_

#include <SFML/Graphics.hpp>
#include <sstream>

#include "Grajacy.h"

class TablicaNaWynik: public sf::Drawable {
public:
	TablicaNaWynik(int x, int y, sf::Color kolor);
	~TablicaNaWynik();

	// Wyświetlanie tablicy z wynikiem na ekranie
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// Aktualizacja procesów związanych z tablicą
	void update();
private:
	//******************* ELEMENTY TABLICY *********************
	// W momencie gdy tablica została powiązana z graczem to
	// stanie się w u użyciu
	bool wUzyciu;

	// Grający, którego imię oraz wynik będzie wyświetlać
	Grajacy *pokazywany;

	//******************* ELEMENTY GRAFICZNE *********************
	// Tło
	sf::RectangleShape rect;

	// Czcionka
	sf::Font font;

	// Teksty do wyświetlenia na tab. wyników
	sf::Text imieNaTablice;
	sf::Text wynikNaTablice;

	// Dodatkowe przesunięcie po to, by pokazywać na ostatnią cyfrę wyniku
	// (efekt dodawania punktów jest teraz ustawiony na pierwszą cyfrę od prawej)
	int przesuniecieOdCyfr;

	friend class Gra;
	friend class Punkty;

};

#endif /* TABLICANAWYNIK_H_ */
