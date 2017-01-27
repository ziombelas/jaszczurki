#include "PoleDolacz.h"

PoleDolacz::PoleDolacz(int x, int y, Input * input) {
	this->input = input;

	this->x = x;
	this->y = y;
	bok.setSize(sf::Vector2f(350, 800));
	bok.setPosition(x, y);

	gotowy = false;

	input->jakPoruszacSprite.setPosition(x + 25, 100);

	fontArrows.loadFromFile("data/fonts/TakaoPGothic.ttf");
	font.loadFromFile("data/fonts/EncodeSansWide-Black.ttf");

	imie[0] = new Imie(BRAK);
	imie[1] = new Imie(MAKS);
	imie[2] = new Imie(SZYMON);
	imie[3] = new Imie(JUREK);
	imie[4] = new Imie(WOJTEK);
	imie[5] = new Imie(MACIEK);
	imie[6] = new Imie(WERA);

	nr_imiona = 0;

	textArrows.setString(L"◀                 ▶");
	textArrows.setFont(fontArrows);
	textArrows.setCharacterSize(58);
	textArrows.setColor(sf::Color::Black);

	textArrows.setPosition(x + 350 / 2 - textArrows.getGlobalBounds().width / 2,
			y + 500 - 5);
}

PoleDolacz::~PoleDolacz() {
	for (int i = 0; i < iloscImion; i++)
		delete imie[i];
}

void PoleDolacz::poprzednieImie() {
	gotowy = false;
	nr_imiona--;

	// Przewijanie na koniec listy, gdy wróci się na imię[0] (tekst powitalny)
	if (nr_imiona <= 0)
		nr_imiona = iloscImion - 1;
}

void PoleDolacz::nastepneImie() {
	gotowy = false;
	nr_imiona++;

	// Cofanie na początek listy po przekroczeniu ostatniego imienia
	if (nr_imiona >= iloscImion)
		nr_imiona = 1;
}

bool PoleDolacz::wybranoImie() {
	if (nr_imiona != 0)
		return true;
	return false;
}

bool PoleDolacz::wybranoKolor() {
	if (nr_koloru != 0)
		return true;
	return false;
}

void PoleDolacz::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(bok);
	target.draw(input->jakPoruszacSprite);
	//target.draw(imieSprite);

	// Wyświetlenie imienia
//	target.draw(*imie[nr_imiona]);

	// Narysowanie strzałek do wybierania
	target.draw(textArrows);
	target.draw(wyswietlaneImie);

}

void PoleDolacz::update() {
	if (gotowy)
		bok.setFillColor(sf::Color(225, 235, 255, 255));
	else
		bok.setFillColor(sf::Color(160, 160, 170, 255));

//
//	imieSprite.setString(imie[nr_imiona]);
//	if (wybranoImie == false)
//		imieSprite.setString("Wybierz imie X / B");
//	imieSprite.setFont(font);
//	imieSprite.setCharacterSize(56);
//	imieSprite.setColor(sf::Color::Red);
//	imieSprite.setPosition(x + 350 / 2 - imieSprite.getGlobalBounds().width / 2,
//	y + 500);

//imieSprite.setString(imie[nr_imiona]);

	wyswietlaneImie.setString(imie[nr_imiona]->get_c_str());
	wyswietlaneImie.setFont(font);
	wyswietlaneImie.setCharacterSize(56);
	if (imie[nr_imiona]->getPlec() == FACET)
		wyswietlaneImie.setColor(sf::Color(255, 0, 30));
	else if (imie[nr_imiona]->getPlec() == BABKA)
		wyswietlaneImie.setColor(sf::Color(255, 0, 150));

	wyswietlaneImie.setPosition(
			x + 350 / 2 - wyswietlaneImie.getGlobalBounds().width / 2, y + 500);

}
