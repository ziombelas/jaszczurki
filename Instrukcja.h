/*
 * Instrukcja.h
 *
 *  Created on: 14 lut 2017
 *      Author: maks
 */

#ifndef INSTRUKCJA_H_
#define INSTRUKCJA_H_

#include "Settings.h"

class Instrukcja {
public:
	Instrukcja(sf::RenderWindow &window);
	~Instrukcja();

	// Uruchomienie pętli głównej wewnątrz Instrukcji
	void run();
private:
	//****************** ELEMENTY INSTRUKCJI ******************
	// Czcionka
	sf::Font font;

	// Pola tekstowe zapisywane linijce
	sf::Text linia[21];

	// Ilustracje z gry
	sf::Sprite ilustracja[10];

	void wyswietl();

	//*************** DOTYCZY PĘTLI PROGRAMU **************
	bool exit;

	//**************** POTRZEBNE DLA DZIAŁANIA SFML *************
	sf::RenderWindow *window;
	sf::Event event;
};

#endif /* INSTRUKCJA_H_ */
