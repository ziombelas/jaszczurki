/*
 * Rozgrywka.h
 *
 *  Created on: 18-10-2016
 *      Author: maks
 */

#ifndef ROZGRYWKA_H_
#define ROZGRYWKA_H_

#include "Gra.h"

class Rozgrywka {
public:
	Rozgrywka(sf::RenderWindow &window, Settings *ustawienia, ProgramState &state);
	~Rozgrywka();

	// Główna procedura z pętlą głowną
	void run();
private:
	//**************** FUNDAMENTALNE DANE (SFML) *************
	sf::RenderWindow *window;
	sf::Event event;

	ProgramState *state;

	Gra *gra;

	Settings *ustawienia;

	// Numer aktualnej rundy
	int runda;
};

#endif /* ROZGRYWKA_H_ */
