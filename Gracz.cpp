#include "Gracz.h"

Gracz::Gracz(sf::Vector2f startVec, Grajacy *grajacy) {
	this->respPos = startVec;
	this->grajacy = grajacy;

	font.loadFromFile("data/fonts/EncodeSansWide-Black.ttf");

	sprite[0].setPosition(respPos);
	if (respPos.x < 1920 / 2)
		zwrot = 1;
	else
		zwrot = -1;

	prevPosition[0] = sprite[0].getPosition();
	updateWszystkieOdniesienia();

	vel_grawitacja = min_vel_grawitacja;

	for (int i = 0; i < 9; i++) {
		imieSprite[i].setString(grajacy->getImie().get_c_str());
		imieSprite[i].setFont(font);
		imieSprite[i].setCharacterSize(32);

		imieSprite[i].setOrigin(imieSprite[i].getGlobalBounds().width / 2, 50);
		if (grajacy->getImie().getPlec() == FACET)
			imieSprite[i].setColor(sf::Color(255, 40, 30));
		else if (grajacy->getImie().getPlec() == BABKA)
			imieSprite[i].setColor(sf::Color(255, 40, 150));

	}

}

Gracz::~Gracz() {
}

void Gracz::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	// Wyświetlenia imienia
	switch (status) {
	case ZYJE: {
		for (int i = 0; i < 9; i++) {
			if (faza_kamuflazu != ZAKAMUFLOWANY)
				target.draw(imieSprite[i]);
		}
	}
		break;
	case UMIERA: {
	}
		break;
	case UMIERAJACY: {
		target.draw(imieSprite[0]);
		target.draw(imieSprite[1]);
		target.draw(imieSprite[2]);
	}
		break;
	case POZAMIATANY: {
	}
		break;
	}

	// Wywołanie wyświetlenia z klasy podstawowej
	Postac::draw(target, states);

}

void Gracz::update(int mineloCzasu) {
	/* Aktualizacje wszystkich procesów związanych z graczem.
	 * Poza tym co wykonuje zwykła jaszczurka dochodzi jedynie
	 * aktualizacja pozycji imienia gracza.
	 */

	Jaszczurka::update(mineloCzasu);

	for (int i = 0; i < 9; i++) {
		imieSprite[i].setPosition(sprite[i].getPosition());
	}

}

void Gracz::getKeys() {
	PRESSED[lewo] = (grajacy->getInput().isPressed(ster_lewo));
	PRESSED[prawo] = (grajacy->getInput().isPressed(ster_prawo));
	PRESSED[dol] = (grajacy->getInput().isPressed(ster_dol));
	PRESSED[skok] = (grajacy->getInput().isPressed(ster_skok));
	PRESSED[atak] = (grajacy->getInput().isPressed(ster_atak));
}
