#include "Punkty.h"

Punkty::Punkty(int wynik, TablicaNaWynik * tablicaNaWynik, int x, int y) {
	this->tablicaNaWynik = tablicaNaWynik;
	this->wynik = wynik;
//	wynik = 0;
	font.loadFromFile("data/fonts/EncodeSansWide-Black.ttf");

	// Utworzenie napisu +x, gdzie x to liczba punktów
	std::ostringstream ss;
	ss << "+";
	ss << wynik;
	std::string napis = ss.str();
	text.setString(napis);
	text.setFont(font);
	text.setCharacterSize(52);
	przezroczystosc = 0;
	text.setOrigin(text.getGlobalBounds().width / 2,
			text.getGlobalBounds().height / 2);
	text.setPosition(x, y);

	// Ustalenie prędkości lotu w zal. w którą stronę ma iść wynik
	vx = (tablicaNaWynik->rect.getGlobalBounds().left
			+ tablicaNaWynik->rect.getGlobalBounds().width - 85
			+ tablicaNaWynik->przesuniecieOdCyfr - text.getPosition().x) * 0.9;

	vy = -(text.getPosition().y
			- (tablicaNaWynik->rect.getGlobalBounds().top
					+ tablicaNaWynik->rect.getGlobalBounds().height / 2)) * 0.9;

	if (vy > 2000 || vy < -2000) {
		vy = 0;
		vx =0;
	}
	czyDodane = false;
}

Punkty::~Punkty() {
}

void Punkty::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(text);
}

void Punkty::update(int mineloCzasu) {
	if (vy > 2000 || vy < -2000) {
		vy = 0;
	}

	// Dolatywanie do tablicy
	if (vx > 0
			&& text.getPosition().x
					> tablicaNaWynik->rect.getGlobalBounds().left
							+ tablicaNaWynik->rect.getGlobalBounds().width - 85
							+ tablicaNaWynik->przesuniecieOdCyfr) {
		vx = 0;
		text.setPosition(
				tablicaNaWynik->rect.getGlobalBounds().left
						+ tablicaNaWynik->rect.getGlobalBounds().width - 85
						+ tablicaNaWynik->przesuniecieOdCyfr,
				text.getPosition().y);
	}

	if (vx < 0
			&& text.getPosition().x
					< tablicaNaWynik->rect.getGlobalBounds().left
							+ tablicaNaWynik->rect.getGlobalBounds().width - 85
							+ tablicaNaWynik->przesuniecieOdCyfr) {
		vx = 0;
		text.setPosition(
				tablicaNaWynik->rect.getGlobalBounds().left
						+ tablicaNaWynik->rect.getGlobalBounds().width - 85
						+ tablicaNaWynik->przesuniecieOdCyfr,
				text.getPosition().y);
	}

	// Doleciał w osi x, napis zaczyna znikać
	if (vx == 0)
		przezroczystosc -= vy * 4.2 * (mineloCzasu / 1000.f);

	if (!czyDodane
			&& text.getPosition().y
					< tablicaNaWynik->rect.getGlobalBounds().top
							+ tablicaNaWynik->rect.getGlobalBounds().height
									/ 2) {
		czyDodane = true;
		tablicaNaWynik->pokazywany->zwiekszWynik(wynik);
	}

	if (przezroczystosc >= 255)
		przezroczystosc = 255;

	text.setColor(sf::Color(215, 225, 0, 255 - przezroczystosc));

	text.move(vx * (mineloCzasu / 1000.f), vy * (mineloCzasu / 1000.f));
}
