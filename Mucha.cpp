#include "Mucha.h"

Mucha::Mucha(bool firstOne) :
		Latajace(6, 11, 45, 225) {

	// Ustalenie stałych minimalnych i maksymalnych wartości odfrunięcia
	min_odlot = 8;
	max_odlot = 22;

	// Dotyczące kolizyjności
	tolerancja_lp = 0;
	tolerancja_top = 0;
	tolerancja_bot = 0;

	// Wczytanie tekstur muchy (animacja ruchu skrzydeł)
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

	if (!firstOne)
		sprite[0].setPosition(
				sf::Vector2f(std::rand() % 1710 + 100,
						std::rand() % 600 + 200));
	else
		sprite[0].setPosition(sf::Vector2f(1920 / 2, 600));

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

	// *********** UPDATE Z KLASY PODSTAWOWEJ ************
	Latajace::update(mineloCzasu);
}

void Mucha::nadajCelLotu() {
	/* Nadanie nowego punktu docelowego. Wylosowanie go z przedziału
	 * aktualna pozycja +/- liczba między min_odlot a max_odlot. Na tej
	 * podstawie ustalane są wartości czyWiecejX/Y informujące o zwrocie
	 * wektora odległości do celu.
	 */

	// Wylosowanie kątu pod jakim będzie lecieć
	float kat = std::rand() % 360;

	// Wylosowanie punktu docelowego
	dest = sf::Vector2f(
			getPosition().x
					+ (std::rand() % (max_odlot - min_odlot) + min_odlot)
							* cos(kat * M_PI / 180.0),
			getPosition().y
					+ (std::rand() % (max_odlot - min_odlot) + min_odlot)
							* sin(kat * M_PI / 180.0));

	// Wylosowanie prędkości lotu
	float vel = std::rand() % (vel_lotu_max - vel_lotu_min) + vel_lotu_min;

	// Nadanie prędkości
	vel_x = vel * cos(kat * M_PI / 180.0);
	vel_y = vel * sin(kat * M_PI / 180.0);

	// todo poprawiony CzyWiecejXY czyli spojrzenie matematyczne na to
	// i ewentualnie wyrzucenie lub zastapienie czymm prostszym.
	// Ostatecznie na siłe bo jest problem tylko z 0, 90, 180, 270 stopni.
	if (kat >= 0 && kat < 90) {
		czyWiecejX = 1;
		czyWiecejY = 1;
	} else if (kat >= 90 && kat < 180) {
		czyWiecejX = -1;
		czyWiecejY = 1;
	} else if (kat >= 180 && kat < 270) {
		czyWiecejX = -1;
		czyWiecejY = -1;
	} else if (kat >= 270 && kat < 360) {
		czyWiecejX = 1;
		czyWiecejY = -1;
	}

	// Aktualizowanie położeń przekraczających krawędź ekranu +
	// połowe długości/szerokości:
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
