/*
 * Rozgrywka.h
 *
todo opis klasy Rozgrywka
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
	//****************** ELEMENTY ROZGRYWKI ******************
	int runda;

	// Tworzona dynamicznie Gra
	Gra *gra;

	//****************** DOTYCZY PĘTLI PROGRAMU **************
	ProgramState *state;

	Settings *ustawienia;

	//**************** POTRZEBNE DLA DZIAŁANIA SFML *************
	sf::RenderWindow *window;
	sf::Event event;
};

#endif /* ROZGRYWKA_H_ */
