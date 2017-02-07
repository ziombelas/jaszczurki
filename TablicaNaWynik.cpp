#include "TablicaNaWynik.h"

TablicaNaWynik::TablicaNaWynik(int x, int y, sf::Color kolor) {
	rect.setSize(sf::Vector2f(1920 / 4, 90));
	rect.setPosition(x, y);
	rect.setFillColor(kolor);

	wUzyciu = false;

	font.loadFromFile("data/fonts/EncodeSansWide-Black.ttf");

	przesuniecieOdCyfr = 0;
	pokazywany = NULL;
}

TablicaNaWynik::~TablicaNaWynik() {
}

void TablicaNaWynik::draw(sf::RenderTarget &target,
		sf::RenderStates states) const {
	// Narysowanie tła czyli czarnego prostokątu
	target.draw(rect);

	if (wUzyciu) {
		target.draw(imieNaTablice);
		target.draw(wynikNaTablice);
	}

}

void TablicaNaWynik::update() {
	if (wUzyciu) {
		// Wyświetlenie imienia
		imieNaTablice.setString(pokazywany->getImie().get_c_str());
		imieNaTablice.setFont(font);
		imieNaTablice.setCharacterSize(52);
		imieNaTablice.setColor(sf::Color(215, 225, 0));
		imieNaTablice.setOrigin(0, imieNaTablice.getGlobalBounds().height / 2);
		imieNaTablice.setPosition(rect.getGlobalBounds().left + 30,
				rect.getGlobalBounds().top + 90 / 2 - 8);

		// Wyświetlenie wyniku
		std::ostringstream ss;
		ss << pokazywany->getWynik();
		std::string str = ss.str();

		wynikNaTablice.setString(str);
		wynikNaTablice.setFont(font);
		wynikNaTablice.setCharacterSize(52);
		wynikNaTablice.setColor(sf::Color(215, 225, 0));
		wynikNaTablice.setOrigin(0,
				wynikNaTablice.getGlobalBounds().height / 2);
		wynikNaTablice.setPosition(
				rect.getGlobalBounds().left + rect.getGlobalBounds().width - 85,
				rect.getGlobalBounds().top + 90 / 2 - 8);

		if (pokazywany->getWynik() < 10)
			przesuniecieOdCyfr = 0;
		else if (pokazywany->getWynik() >= 10) {
			// Sprawdzenie ile pikseli zajemuje pierwsza cyfra, żeby ustalić przesunięcie
			sf::Text jednaCyfra;

			std::ostringstream ss;
			ss << pokazywany->getWynik() / 10;
			std::string str = ss.str();

			jednaCyfra.setString(str);
			jednaCyfra.setFont(font);
			jednaCyfra.setCharacterSize(52);

			przesuniecieOdCyfr = jednaCyfra.getGlobalBounds().width;
		}
	}
}
