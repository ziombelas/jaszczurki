#include "Mucha.h"

Mucha::Mucha() :
		Latajace(6, 11, 45, 225) {

	tolerancja_lp = 0;
	tolerancja_top = 0;
	tolerancja_bot = 0;

	// Wczytanie 4 tekstur muchy w locie
	tekstura_postaci[0].loadFromFile("data/MUCHA/1.png");
	tekstura_postaci[1].loadFromFile("data/MUCHA/2.png");
	tekstura_postaci[2].loadFromFile("data/MUCHA/3.png");
	tekstura_postaci[3].loadFromFile("data/MUCHA/4.png");
	tekstura_postaci[4].loadFromFile("data/MUCHA/5.png");
	tekstura_postaci[5].loadFromFile("data/MUCHA/6.png");
	for (int i = 0; i < 9; i++) {
		sprite[i].setTexture(tekstura_postaci[0], true);
		sprite[i].setOrigin(20, 20);
	}

	sprite[0].setPosition(
			sf::Vector2f(std::rand() % 1710 + 100, std::rand() % 600 + 200));

	min_odlot = 8;
	max_odlot = 22;

	// Nadanie pierwszej pozycji docelowej muchy
	nadajCelLotu();

	status = ZYJE;
}

Mucha::~Mucha() {
}

void Mucha::update(int mineloCzasu) {
	move_x = vel_x * (mineloCzasu / 1000.f);
	move_y = vel_y * (mineloCzasu / 1000.f);

	playAnimation(mineloCzasu);

	// *********** UPDATE Z KLASY PODSTAWOWEJ  ***********
	Latajace::update(mineloCzasu);
}

void Mucha::nadajCelLotu() {
	/* Nadanie nowego punktu docelowego. Wylosowanie go z przedziału
	 * aktualna pozycja +/- liczba między min_odlot a max_odlot. Na tej
	 * podstawie ustalane są wartości czyWiecejX/Y
	 * informujące o zwrocie wektora odległości do celu.
	 */

	// todo losowanie w promieniu min_max dest
	bool a = std::rand() % 2;
	bool b = std::rand() % 2;

	a ? czyWiecejX = 1 : czyWiecejX = -1;
	b ? czyWiecejY = 1 : czyWiecejY = -1;
	dest = sf::Vector2f(
			(getPosition().x
					+ (std::rand() % (max_odlot - min_odlot) + min_odlot)
							* czyWiecejX),
			(getPosition().y
					+ (std::rand() % (max_odlot - min_odlot) + min_odlot)
							* czyWiecejY));
	// i prędkości
	vel_x = czyWiecejX
			* (std::rand() % (vel_lotu_max - vel_lotu_min) + vel_lotu_min);
	vel_y = czyWiecejY
			* (std::rand() % (vel_lotu_max - vel_lotu_min) + vel_lotu_min);

	// Aktualizowanie położeń przekraczających krawędź ekranu + połowe długości/szerokości
	// z prawej
	if (dest.x > 1920 + 1920 / 2) {
		dest += sf::Vector2f(-1920, 0);
	}

	// z lewej
	if (dest.x < -1920 / 2) {
		dest += sf::Vector2f(1920, 0);
	}

	// z dołu
	if (dest.y > 990 + 990 / 2) {
		dest += sf::Vector2f(0, -990);
	}

	// z góry
	if (dest.y < -990 / 2) {
		dest += sf::Vector2f(0, 990);
	}
}
