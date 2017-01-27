

#ifndef TABLICANAWYNIK_H_
#define TABLICANAWYNIK_H_

#include <SFML/Graphics.hpp>
#include <sstream>

#include "Grajacy.h"

class TablicaNaWynik : public sf::RectangleShape {
public:
	TablicaNaWynik(int x, int y, sf::Color kolor);
	~TablicaNaWynik();

	// Wyświetlanie tablicy z wynikiem na ekranie
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// Aktualizacja
	void update();
private:
	// Rectangle, którego będziemy używać
	sf::RectangleShape rect;

	// Jeśli jest powiązana z którymś z graczy
	// jeśli nie jest, to będzie wyświetlona pusta
	bool wUzyciu;

	// Gracz, którego imię i wynik będzie pokazywać
	Grajacy * pokazywany;

	// Czcionka
	sf::Font font;

	// Teksty do wyświetlenia na tab. wyników
	sf::Text imieNaTablice;
	sf::Text wynikNaTablice;

	// Dodatkowe przesunięcie uwzględniane by pokazywać na ostatnią cyfrę wyniku
	int przesuniecieOdCyfr;

	friend class Gra;
	friend class Punkty;

};

#endif /* TABLICANAWYNIK_H_ */
