#include "Scianka.h"

Scianka::Scianka(KolorSciany kolor, int x, int y, int w, int h) {
	this->kolor = kolor;

	rect[0].setPosition(x, y);

	for (int i = 0; i < 9; i++)
		rect[i].setSize(sf::Vector2f(w, h));

	switch (kolor) {
	case SCIANA_MORSKI: {
		for (int i = 0; i < 9; i++)
			rect[i].setFillColor(sf::Color(0, 95, 120, 157));
	}
		break;
	case SCIANA_ZOLC: {
		for (int i = 0; i < 9; i++)
			rect[i].setFillColor(sf::Color(87, 72, 14, 157));

	}
		break;
	case SCIANA_FIOLET: {
		for (int i = 0; i < 9; i++)
			rect[i].setFillColor(sf::Color(50, 65, 145, 157));
	}
		break;
	}

	predkosc_na_sek = 22;
	updateWszystkieOdniesienia();
}

Scianka::~Scianka(void) {
}

void Scianka::update(int mineloCzasu) {
	// Poruszanie się
	rect[0].move(predkosc_na_sek * (mineloCzasu / 1000.f), 0);

	// Ustawienie wszystkich odniesień na nowe pozycje
	updateWszystkieOdniesienia();
}

sf::FloatRect Scianka::getGlobalBounds(unsigned int nr) const {
	return rect[nr].getGlobalBounds();
}

sf::FloatRect Scianka::getPrevGlobalBounds(unsigned int nr) const {
	return rect[nr].getGlobalBounds();
}

sf::Vector2f Scianka::getPosition(unsigned int nr) const {
	return sf::Vector2f(rect[nr].getGlobalBounds().left,
			rect[nr].getGlobalBounds().top);
}

sf::Vector2f Scianka::getPrevPosition(unsigned int nr) const {
	return sf::Vector2f(rect[nr].getGlobalBounds().left,
			rect[nr].getGlobalBounds().top);
}

void Scianka::updateWszystkieOdniesienia() {
	 /* Na potrzeby przechodzenia przez ściany, za każdym razem gdy
	 * określana jest pozycja ściany dorysowywane jest dodatkowe 8
	 * prostokątów. Obiekt rect[0] jest tym podstawowym i na podstawie jego
	 * pozycji ustawiene są pozostałe.
	 *
	 * Najpierw odbywa się wracanie rect[0] na główną, widoczną oś, w
	 * sytuacjach gdy przekraczane jest już półtora długości/szerokości.
	 *
	 * Kolejnym krokiem, który odbywa się za każdym razem gdy wywoływana jest
	 * ta procedura jest ustawienie pozostałych ośmiu odniesień o kombinacje
	 * długości/szerokości ekranu.
	 */

	// Aktualizowanie położeń przekraczających krawędź ekranu + połowe długości/szerokości
	// z prawej
	if (rect[0].getPosition().x > 1920 + 1920 / 2) {
		rect[0].move(-1920, 0);
	}

	// z lewej
	if (rect[0].getPosition().x < -1920 / 2) {
		rect[0].move(1920, 0);
	}

	// z dołu
	if (rect[0].getPosition().y > 1080) {
		rect[0].move(0, -990);
	}

	// z góry
	if (rect[0].getPosition().y < -1080 / 2) {
		rect[0].move(0, 990);
	}

	rect[1].setPosition(rect[0].getPosition() + sf::Vector2f(1920, 0));
	rect[2].setPosition(rect[0].getPosition() + sf::Vector2f(-1920, 0));
	rect[3].setPosition(rect[0].getPosition() + sf::Vector2f(0, 1590));
	rect[4].setPosition(rect[0].getPosition() + sf::Vector2f(0, -1590));
	rect[5].setPosition(rect[0].getPosition() + sf::Vector2f(1920, 1590));
	rect[6].setPosition(rect[0].getPosition() + sf::Vector2f(-1920, 1590));
	rect[7].setPosition(rect[0].getPosition() + sf::Vector2f(1920, -1590));
	rect[8].setPosition(rect[0].getPosition() + sf::Vector2f(-1920, -1590));

}
void Scianka::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	for (int i = 0; i < 9; i++) {
		target.draw(rect[i]);
	}
}
