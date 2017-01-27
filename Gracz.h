/* Postać gracza, którym można sterować za pomocą układu klawiszy
 *
 */

#ifndef GRACZ_H_
#define GRACZ_H_

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Grajacy.h"
#include "Jaszczurka.h"
#include "Imie.h"
#include "Input.h"

class Gracz: public Jaszczurka {
public:
	Gracz(sf::Vector2f startVec, Grajacy * grajacy);
	~Gracz();

	// Wyświetlanie gracza na ekranie
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// Aktualizacja procesów związanych z graczem
	void update(int mineloCzasu);

	// Pobranie informacji o wciśniętych klawiszach z inputu
	void getKeys();

private:
	//********************* FUNDAMENTALNE DANE********************
	// Którys z grających, reprezentuje jego imię, punkty i korzysta z
	// ustawień tam też przypisanych.
	Grajacy * grajacy;

	//************* DANE DOTYCZĄCE WYGLĄDU I ANIMACJI *************
	// Czcionka imiona
	sf::Font font;

	// Tekst do wyświetlenia nad graczem + 8 odniesień
	sf::Text imieSprite[9];

	friend class Gra;
	friend class TablicaNaWynik;
	friend class Punkty;
};

#endif /* GRACZ_H_ */
