#include "PoleDolacz.h"

PoleDolacz::PoleDolacz(int x, int y, Input *input) {
	this->input = input;

	rect.setSize(sf::Vector2f(350, 800));
	rect.setPosition(x, y);

//	setSize(sf::Vector2f(350, 800));
//	setPosition(x, y);

	gotowy = false;

	input->jakPoruszacSprite.setPosition(x + 25, 100);

	fontArrows.loadFromFile("data/fonts/TakaoPGothic.ttf");
	font.loadFromFile("data/fonts/EncodeSansWide-Black.ttf");

	imie.push_back(new Imie(L"imie", FACET));
	imie.push_back(new Imie(L"Maks", FACET));
	imie.push_back(new Imie(L"Szymon", FACET));
	imie.push_back(new Imie(L"Jurek", FACET));
	imie.push_back(new Imie(L"Wojtek", FACET));
	imie.push_back(new Imie(L"Maciek", FACET));
	imie.push_back(new Imie(L"Wera", BABKA));
	imie.push_back(new Imie(L"Styku", FACET));
	imie.push_back(new Imie(L"Tosia", BABKA));
	imie.push_back(new Imie(L"Piotrek", FACET));
	imie.push_back(new Imie(L"Samanta", BABKA));
	imie.push_back(new Imie(L"Biały", FACET));
	imie.push_back(new Imie(L"Kasia", BABKA));
	imie.push_back(new Imie(L"Mateusz", FACET));
	imie.push_back(new Imie(L"Sum", FACET));
	imie.push_back(new Imie(L"Daniela", BABKA));
	imie.push_back(new Imie(L"Mikser", FACET));
	imie.push_back(new Imie(L"Eddie", FACET));
	imie.push_back(new Imie(L"Domson", FACET));

	nr_imiona = 0;

	textArrows.setString(L"◀                 ▶");
	textArrows.setFont(fontArrows);
	textArrows.setCharacterSize(58);
	textArrows.setColor(sf::Color::Black);

	textArrows.setPosition(x + 350 / 2 - textArrows.getGlobalBounds().width / 2,
			y + 500 - 5);
}

PoleDolacz::~PoleDolacz() {
	for (unsigned int i = 0; i < imie.size(); i++)
		delete imie[i];
}

void PoleDolacz::poprzednieImie() {
	gotowy = false;
	nr_imiona--;

	// Przewijanie na koniec listy, gdy wróci się na imię[0] (tekst powitalny)
	if (nr_imiona <= 0)
		nr_imiona = imie.size() - 1;
}

void PoleDolacz::nastepneImie() {
	gotowy = false;
	nr_imiona++;

	// Cofanie na początek listy po przekroczeniu ostatniego imienia
	if (nr_imiona >= imie.size())
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
	target.draw(rect);
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
		rect.setFillColor(sf::Color(225, 235, 255, 255));
	else
		rect.setFillColor(sf::Color(160, 160, 170, 255));

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
			rect.getPosition().x + 350 / 2
					- wyswietlaneImie.getGlobalBounds().width / 2,
			rect.getPosition().y + 500);

}
