/*
 * PodsumowanieWynikow.cpp
 *
 *  Created on: 16 lut 2017
 *      Author: maks
 */

#include "PodsumowanieWynikow.h"

PodsumowanieWynikow::PodsumowanieWynikow(sf::RenderWindow &window,
		Ustawienia *ustawienia, ProgramState *state) {

	this->window = &window;
	this->ustawienia = ustawienia;
	this->state = state;

	// Czcionki
	font_title.loadFromFile("data/fonts/PORKYS.ttf");
	font.loadFromFile("data/fonts/EncodeSansWide-Black.ttf");

	jaszczurkaUpolowana_texture.loadFromFile(
			"data/podsumowanie/upolowaneJaszczurki.png");
	muchaUpolowana_texture.loadFromFile("data/podsumowanie/upolowaneMuchy.png");

	exit = false;
}

PodsumowanieWynikow::~PodsumowanieWynikow() {
}

void PodsumowanieWynikow::run() {
	// Napis tytułowy
	title.setString("Podsumowanie gry");
	title.setFont(font_title);
	title.setCharacterSize(102);
	title.setStyle(sf::Text::Bold);
	title.setColor(sf::Color::Green);
	title.setPosition(1920 / 2 - title.getGlobalBounds().width / 2, 30);

	for (unsigned int i = 0; i < ustawienia->grajacy.size(); i++) {
		// Ustawienie imion
		imie[i].setString(ustawienia->grajacy[i]->getImie().get_c_str());
		imie[i].setFont(font);
		imie[i].setColor(sf::Color(255, 255, 255));
		imie[i].setCharacterSize(80);
		imie[i].setPosition(50, i * 155 + 300);

		// Prostokąty z punktami każdego z graczy
		rectPunkty[i].setPosition(450, i * 155 + 300 + 10);
		rectPunkty[i].setSize(
				sf::Vector2f(ustawienia->grajacy[i]->getWynik() * 9, 120));
		if (ustawienia->grajacy[i]->getImie().getPlec() == FACET)
			rectPunkty[i].setFillColor(sf::Color(210, 140, 0));
		else
			rectPunkty[i].setFillColor(sf::Color(210, 40, 140));

		// Punkty dosłownie, upolowane muchy i jaszczurki
		std::ostringstream s1, s2, s3;
		s1 << ustawienia->grajacy[i]->getWynik();
		s2 << ustawienia->grajacy[i]->getUpolowaneMuchy();
		s3 << ustawienia->grajacy[i]->getUpolowaneJaszczurki();

		wynikPunkty[i].setString(s1.str().c_str());
		wynikJaszczurki[i].setString(s3.str().c_str());
		wynikMuchy[i].setString(s2.str().c_str());
		wynikPunkty[i].setFont(font);
		wynikJaszczurki[i].setFont(font);
		wynikMuchy[i].setFont(font);
		wynikPunkty[i].setCharacterSize(80);
		wynikJaszczurki[i].setCharacterSize(80);
		wynikMuchy[i].setCharacterSize(80);
		wynikPunkty[i].setPosition(1310, i * 155 + 300);
		wynikJaszczurki[i].setPosition(1580, i * 155 + 300);
		wynikMuchy[i].setPosition(1780, i * 155 + 300);
	}

	// Ilustracje przedstawiające upolowane jaszczurki i muchy
	jaszczurkaUpolowana.setTexture(jaszczurkaUpolowana_texture);
	muchaUpolowana.setTexture(muchaUpolowana_texture);
	jaszczurkaUpolowana.setPosition(1580, 260);
	muchaUpolowana.setPosition(1790, 260);

	// *********************   PĘTLA GŁÓWNA   ************************ //
	while (!exit) {
		while (window->pollEvent(event)) {

			// Wcisnięcie ESC / alt + f4 / B u któregoś z grających
			for (int unsigned i = 0; i < ustawienia->grajacy.size(); i++) {
				if (ustawienia->grajacy[i]->getInput().isPressed(ster_esc)) {
					*state = MENU;
					exit = true;
				}
			}
			window->clear();
			wyswietl();
		} // ************************************************************ //
	}
}

void PodsumowanieWynikow::wyswietl() {
	window->draw(title);
	window->draw(jaszczurkaUpolowana);
	window->draw(muchaUpolowana);

	for (int i = 0; i < 4; i++) {
		window->draw(rectPunkty[i]);
		window->draw(imie[i]);
		window->draw(wynikPunkty[i]);
		window->draw(wynikMuchy[i]);
		window->draw(wynikJaszczurki[i]);
	}

	window->display();
}

