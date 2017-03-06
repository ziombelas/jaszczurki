/*
 * Rozgrywka.cpp
 *
 *  Created on: 18-10-2016
 *      Author: maks
 */

#include "Rozgrywka.h"

Rozgrywka::Rozgrywka(sf::RenderWindow & window, Ustawienia *ustawienia,
		ProgramState & state) {
	this->window = &window;
	this->ustawienia = ustawienia;
	this->state = &state;

	gra = NULL;
	podsumowanie = NULL;

	// Licznik rund zaczyna od 1
	runda = 1;
}

Rozgrywka::~Rozgrywka() {
}

void Rozgrywka::run() {
	while (runda <= 5) {
		gra = new Gra(*window, ustawienia, state, runda);

		// Przeniesienie pętli głownej → game
		(*gra).run();

		// Skasowanie zakończonej gry
		delete gra;

		runda++;

		// Wyjście, jeśli rozgrywka została zakończona
		if (*state != ROZGRYWKA)
			break;
	}

	// Pokazanie ekranu podsumowanie, jeżeli rozgrywka przebiegła do końca
	if (*state == ROZGRYWKA) {
		podsumowanie = new PodsumowanieWynikow(*window, ustawienia, state);

		// Przeniesienie pętli głownej → podsumowanie
		podsumowanie->run();

		delete podsumowanie;
	}
}
