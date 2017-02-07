/*
 * Postać gracza, czyli Jaszczurka, którą można sterować.
 *
 * Klasa pochodna Jaszczurki zawierająca dodatkowow skaźnik do osoby
 * grającej tą jaszczurką oraz takie cechy jak np. imię.
 */

#ifndef GRACZ_H_
#define GRACZ_H_

#include <SFML/Graphics.hpp>
#include <cmath>

#include "Grajacy.h"
#include "Jaszczurka.h"

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
	//********************* ELEMENTY GRACZA ********************
	// Którys z grających, ten obiekt reprezentuje jego imię,
	// punkty i jego ustawienia poruszania.
	Grajacy *grajacy;

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
