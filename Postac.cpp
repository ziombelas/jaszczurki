#include "Postac.h"

Postac::Postac(int arg_ilosc_tekstur, float arg_klatki_na_sek) :
		ilosc_tekstur(arg_ilosc_tekstur), klatki_na_sek(arg_klatki_na_sek) {

	frame = 0;

	vel_odpych_x = 0;
	vel_odpych_y = 0;

	PRESSED[lewo] = false;
	PRESSED[prawo] = false;
	PRESSED[dol] = false;
	PRESSED[skok] = false;
	PRESSED[atak] = false;

	move_x = 0;
	move_y = 0;

	status = ZYJE;
}

Postac::~Postac(void) {
}

void Postac::update(int mineloCzasu) {
	// ************** PROCESY KOŃCOWE UPDATE **************
	// Przesunięcie spritu na nową pozycję
	sprite[0].setPosition(getNextPosition());

	// Ustawienie wszystkich odniesień na nowe pozycje
	updateWszystkieOdniesienia();
}

void Postac::updateWszystkieOdniesienia() {
	/* Na potrzeby przechodzenia przez ściany, za każdym razem gdy
	 * określana jest pozycja gracza dorysowywane jest dodatkowe 8
	 * spritów. Obiekt sprite[0] jest tym podstawowym i na podstawie jego
	 * pozycji ustawiene są pozostałe.
	 *
	 * Najpierw odbywa się wracanie sprite[0] na główną, widoczną oś, w
	 * sytuacjach gdy przekraczane jest już półtora długości/szerokości.
	 *
	 * Kolejnym krokiem, który odbywa się za każdym razem gdy wywoała jest
	 * ta procedura jest ustawienie pozostałych ośmiu odniesień o kombinacje
	 * długości/szerokości ekranu.
	 */

	// Aktualizowanie położeń przekraczających krawędź ekranu + połowe długości/szerokości
	// z prawej
	if (sprite[0].getPosition().x > 1920 + 1920 / 2) {
		sprite[0].move(-1920, 0);
		prevPosition[0] += sf::Vector2f(-1920, 0);
	}

	// z lewej
	if (sprite[0].getPosition().x < -1920 / 2) {
		sprite[0].move(1920, 0);
		prevPosition[0] += sf::Vector2f(1920, 0);
	}

	// z dołu
	if (sprite[0].getPosition().y > 1080 + 1080 / 2) {
		sprite[0].move(0, -990);
		prevPosition[0] += sf::Vector2f(0, -990);
	}

	// z góry
	if (sprite[0].getPosition().y < -1080 / 2) {
		sprite[0].move(0, 990);
		prevPosition[0] += sf::Vector2f(0, 990);
	}

	sprite[1].setPosition(sprite[0].getPosition() + sf::Vector2f(1920, 0));
	sprite[2].setPosition(sprite[0].getPosition() + sf::Vector2f(-1920, 0));
	sprite[3].setPosition(sprite[0].getPosition() + sf::Vector2f(0, 990));
	sprite[4].setPosition(sprite[0].getPosition() + sf::Vector2f(0, -990));
	sprite[5].setPosition(sprite[0].getPosition() + sf::Vector2f(1920, 990));
	sprite[6].setPosition(sprite[0].getPosition() + sf::Vector2f(-1920, 990));
	sprite[7].setPosition(sprite[0].getPosition() + sf::Vector2f(1920, -990));
	sprite[8].setPosition(sprite[0].getPosition() + sf::Vector2f(-1920, -990));

	prevPosition[1] = getPrevPosition(0) + sf::Vector2f(1920, 0);
	prevPosition[2] = getPrevPosition(0) + sf::Vector2f(-1920, 0);
	prevPosition[3] = getPrevPosition(0) + sf::Vector2f(0, 990);
	prevPosition[4] = getPrevPosition(0) + sf::Vector2f(0, -990);
	prevPosition[5] = getPrevPosition(0) + sf::Vector2f(1920, 990);
	prevPosition[6] = getPrevPosition(0) + sf::Vector2f(-1920, 990);
	prevPosition[7] = getPrevPosition(0) + sf::Vector2f(1920, -990);
	prevPosition[8] = getPrevPosition(0) + sf::Vector2f(-1920, -990);
}

void Postac::playAnimation(int mineloCzasu) {
	// W przypadku ruchu następuje przesunięcie klatki na podstawie
	// ilości upłyniętego czasu
	frame += klatki_na_sek * (mineloCzasu / 1000.f);
	if (frame >= ilosc_tekstur)
		frame = 0;
	for (int i = 0; i < 9; i++)
		sprite[i].setTexture(tekstura_postaci[int(frame)], true);
}

sf::Vector2f Postac::getPosition(unsigned int nr) const {
	return sprite[nr].getPosition();
}

sf::Vector2f Postac::getPrevPosition(unsigned int nr) const {
	return prevPosition[nr];
}

sf::Vector2f Postac::getNextPosition() const {
	return sf::Vector2f(sprite[0].getPosition().x + move_x,
			sprite[0].getPosition().y + move_y);
}

sf::FloatRect Postac::getGlobalBounds(unsigned int nr) const {
	return sf::FloatRect(sprite[nr].getGlobalBounds().left + tolerancja_lp,
			sprite[nr].getGlobalBounds().top + tolerancja_top,
			sprite[nr].getGlobalBounds().width - 2 * tolerancja_lp,
			sprite[nr].getGlobalBounds().height - tolerancja_bot
					- tolerancja_top);
}

sf::FloatRect Postac::getPrevGlobalBounds(unsigned int nr) const {
	sf::Vector2f roznica = getPosition(0) - getPrevPosition(0);

	return sf::FloatRect(
			sprite[nr].getGlobalBounds().left + tolerancja_lp - roznica.x,
			sprite[nr].getGlobalBounds().top + tolerancja_top - roznica.y,
			sprite[nr].getGlobalBounds().width - 2 * tolerancja_lp,
			sprite[nr].getGlobalBounds().height - tolerancja_bot
					- tolerancja_top);
}

void Postac::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	switch (status) {
	case ZYJE: {
		for (int i = 0; i < 9; i++) {
			target.draw(sprite[i]);
		}
	}
		break;
	case UMIERA: {

	}
		break;
	case UMIERAJACY: {
		// Jeśli umiera rysowane są jedynie klatki ze zmiennym odniesiem w osi x
		// by unikać rysowania spritów na górze gdy ciało spada i przechodzi przez
		// dolną krawędź ekranu
		target.draw(sprite[0]);
		target.draw(sprite[1]);
		target.draw(sprite[2]);
	}
		break;
	case POZAMIATANY: {
	}
		break;
	}
}

sf::Vector2f Postac::pozycjaWzgledemMonitora() const {
	sf::Vector2f vect(getPosition(0).x, getPosition(0).y);
	if (vect.x >= 1920)
		vect += sf::Vector2f(-1920, 0);
	if (vect.x <= 0)
		vect += sf::Vector2f(1920, 0);
	if (vect.y >= 1080)
		vect += sf::Vector2f(0, -990);
	if (vect.y <= 90)
		vect += sf::Vector2f(0, 990);
	return vect;
}
