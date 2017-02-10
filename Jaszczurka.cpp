#include "Jaszczurka.h"

Jaszczurka::Jaszczurka() :
		Ladowe(11, 26, 435, -755) {
	faza_kamuflazu = NIEKAMUFLUJE;

	fazaAtaku = NIEATAKUJE;
	naladowanieAtk = 0;

	// Dotyczące kolizyjności
	tolerancja_lp = 10;
	tolerancja_top = 89;
	tolerancja_bot = 16;

	// Wczytanie tekstur poruszającej się jaszczurki
	tekstura_postaci[0].loadFromFile("data/JASZCZURKA/1.png");
	tekstura_postaci[1].loadFromFile("data/JASZCZURKA/2.png");
	tekstura_postaci[2].loadFromFile("data/JASZCZURKA/3.png");
	tekstura_postaci[3].loadFromFile("data/JASZCZURKA/4.png");
	tekstura_postaci[4].loadFromFile("data/JASZCZURKA/5.png");
	tekstura_postaci[5].loadFromFile("data/JASZCZURKA/6.png");
	tekstura_postaci[6].loadFromFile("data/JASZCZURKA/7.png");
	tekstura_postaci[7].loadFromFile("data/JASZCZURKA/8.png");
	tekstura_postaci[8].loadFromFile("data/JASZCZURKA/9.png");
	tekstura_postaci[9].loadFromFile("data/JASZCZURKA/10.png");
	tekstura_postaci[10].loadFromFile("data/JASZCZURKA/11.png");

	for (int i = 0; i < 9; i++) {
		sprite[i].setTexture(tekstura_postaci[0], true);
		sprite[i].setOrigin(40, 40);
	}
}

Jaszczurka::~Jaszczurka() {
}

void Jaszczurka::update(int mineloCzasu) {
	/* Update dla jaszczurki przebiega następująco:
	 * wyzerowanie kamuflażu (jeśli następiła czynność, która go przerywa),
	 * nadanie koloru w zależności od fazy kamuflażu i ataku,
	 * fizyka : atakowanie, poruszanie, skakanie;
	 * wywołanie update z klasy Ladowe.
	 */

	// Zaprzestanie kamuflowania przy jakimkolwiek ruchu
	if (faza_kamuflazu == KAMUFLUJE && getPosition(0) != getPrevPosition(0)) {
		faza_kamuflazu = NIEKAMUFLUJE;
	}

	// Zapresztanie kamuflowania gdy atakuje lub ładuje atak
	if (fazaAtaku != NIEATAKUJE && faza_kamuflazu == KAMUFLUJE) {
		faza_kamuflazu = NIEKAMUFLUJE;
	}

	// Przerwanie kamuflażu podczas atakowania
	if (fazaAtaku == ATAKUJE && faza_kamuflazu == ZAKAMUFLOWANY) {
		faza_kamuflazu = NIEKAMUFLUJE;
	}

	switch (faza_kamuflazu) {
	case NIEKAMUFLUJE: {
		// Nadanie barwy graczowi z uwzględnieniem ładowania ataku
		int zmianakoloru = (naladowanieAtk - 400);
		if (zmianakoloru < 0)
			zmianakoloru = 0;
		for (int i = 0; i < 9; i++)
			sprite[i].setColor(
					sf::Color(255, 255 - zmianakoloru * 0.07,
							255 - zmianakoloru * 0.05, 255));
	}
		break;
	case KAMUFLUJE: {
		kamufluj();
	}
		break;
	case ZAKAMUFLOWANY: {
		kamufluj();
	}
		break;
	}

	// Zapisanie poprzedniej pozycji
	for (int i = 0; i < 9; i++)
		prevPosition[i] = getPosition(i);

	// Zresetowanie przesunięcia
	move_x = 0;
	move_y = 0;

	switch (status) {
	case ZYJE: {
		//======================== JASZCZURKA ZYJE ======================
		//********************** ATAKOWANIE **********************
		switch (fazaAtaku) {
		// ------ KIEDY JESZCZE NIE ATAKUJE ------
		case NIEATAKUJE: {
			// Wyzerowanie wartości dot. ataku
			vel_atak = 0;
			naladowanieAtk = 0;
			lotnosc = false;
			// Wcisnięcie kl. ataku → rozpoczęcie ładowania ataku
			if (PRESSED[atak]) {
				fazaAtaku = LADUJE;
				czasLadowaniaAtk.restart();
			}
		}
			break;
			// ---------- GDY ŁADUJE ATAK ----------
		case LADUJE: {
			if (PRESSED[atak]) {
				naladowanieAtk =
						(czasLadowaniaAtk.getElapsedTime().asMilliseconds()
								+ 300);
				if (naladowanieAtk > 3900)
					naladowanieAtk = 3900;
			} else
			// Puszczenie klawisza atakuj podczas ładowania - start ataku
			{
				fazaAtaku = ATAKUJE;
				if (naladowanieAtk > 1000)
					lotnosc = true;
			}
		}
			break;
			// ------------ GDY ATAKUJE -----------
		case ATAKUJE: {
			// i nadanie nowej
			vel_atak = zwrot * naladowanieAtk * 2.655;

			// Zwalnianie podczas ataku
			naladowanieAtk -= mineloCzasu * (naladowanieAtk * 1.19 + 3400)
					/ 1000.f;

			// Usunięcie lotności
			if (naladowanieAtk < 660)
				lotnosc = false;

			// Koniec ataku
			if (naladowanieAtk < 0) {
				fazaAtaku = NIEATAKUJE;
			}

		}
			break;
		} //switch (fazaAtaku)

		//******************* RUCH LEWO/PRAWO *******************
		// Poruszanie się gdy wciśnięto w lewo/prawo
		if (PRESSED[lewo] && !PRESSED[prawo] && fazaAtaku == NIEATAKUJE) {
			vel_ruch = -vel_ruch_const;
			zwrot = -1;
		} else if (PRESSED[prawo] && !PRESSED[lewo]
				&& fazaAtaku == NIEATAKUJE) {
			vel_ruch = vel_ruch_const;
			zwrot = 1;
		} else {
			vel_ruch = 0;
		}

		if (zwrot == -1)
			for (int i = 0; i < 9; i++)
				sprite[i].setScale(-1.8, 1.8);
		else if (zwrot == 1)
			for (int i = 0; i < 9; i++)
				sprite[i].setScale(1.8, 1.8);

		//*********************** SKAKANIE ***********************
		// Początek skoku
		if (maPodloze && PRESSED[skok] && fazaAtaku != LADUJE) {
			skacze = true;
			lotnosc = false;
		}

		if (skacze)
			vel_skok = vel_skok_const;

		// Przerwanie skakania poprzez puszczenie klawisza lub
		// gdy prędkość wypadkowa (z grawitacją) staje się ujemna
		if (skacze && (!PRESSED[skok] || vel_y() >= 0)) {
			skacze = false;
			vel_skok = 0;
			vel_grawitacja = min_vel_grawitacja;
		}

		// Animacja, gdy porusza się lewo/prawo
		if (vel_ruch != 0)
			playAnimation(mineloCzasu);

	}
		break;
		//================== NASTĘPUJE ŚMIERĆ JASZCZURKI ===============
		// Wywołanie następuje tylko raz, następnie następuje przełączenie na stan UMIERA
	case UMIERA: {
		sf::Vector2f vect(getPosition(0).x, getPosition(0).y);
		if (vect.x > 1920)
			vect += sf::Vector2f(-1920, 0);
		if (vect.x < 0)
			vect += sf::Vector2f(1920, 0);
		if (vect.y > 990)
			vect += sf::Vector2f(0, -990);
		if (vect.y < 0)
			vect += sf::Vector2f(0, 990);

		sprite[0].setPosition(vect);

		status = UMIERAJACY;
	}
		break;
		//======================= JASZCZURKA NIE ŻYJE ===================
	case UMIERAJACY: {
		// Sprzątnięcie postaci która spadła poniżej dolnej krawędzi ekranu
		if (getGlobalBounds().top
				> 1080 + tolerancja_bot + tolerancja_lp * 2 + tolerancja_top)
			status = POZAMIATANY;

		// Wyzerowanie wartości charakterystycznych dla żywej jaszczurki
		maPodloze = false;
		lotnosc = false;
		vel_atak = 0;
		naladowanieAtk = 0;

		faza_kamuflazu = NIEKAMUFLUJE;
		for (int i = 0; i < 9; i++) {
			sprite[i].setOrigin(40, 65);

			if (sprite[i].getRotation() < 180)
				sprite[i].rotate(475 * (mineloCzasu / 1000.f));
			else
				sprite[i].setRotation(180);
		}

	}
		break;
	case POZAMIATANY: {
		// nic się nie dzieje
	}
		break;
	} //switch status

	// ******************* HAMOWANIE ODPYCHU *****************
	// Odpych poziomy dodatni
	if (vel_odpych_x > 0) {
		if (vel_x() > 0)
			vel_odpych_x -= mineloCzasu * (vel_x() + 1600) * 3.1 / 1000.f;
		else if (vel_x() < 0)
			vel_odpych_x -= mineloCzasu * (-vel_x() + 1600) * 3.1 / 1000.f;
		else
			vel_odpych_x -= mineloCzasu * (1600) * 3.1 / 1000.f;
		if (vel_odpych_x < 0)
			vel_odpych_x = 0;
	}	// Odpych poziomy ujemny
	else if (vel_odpych_x < 0) {
		if (vel_x() > 0)
			vel_odpych_x += mineloCzasu * (vel_x() + 1600) * 3.1 / 1000.f;
		else if (vel_x() < 0)
			vel_odpych_x += mineloCzasu * (-vel_x() + 1600) * 3.1 / 1000.f;
		else
			vel_odpych_x += mineloCzasu * (1600) * 3.1 / 1000.f;
		if (vel_odpych_x > 0)
			vel_odpych_x = 0;
	}
	// Odpych pionowy dodatni
	if (vel_odpych_y > 0) {
		vel_odpych_y -= mineloCzasu * (4200) * 3.1 / 1000.f;
		if (vel_odpych_y < 0)
			vel_odpych_y = 0;
	}	// Odpych pionowy ujemny
	else if (vel_odpych_y < 0) {
		vel_odpych_y += mineloCzasu * (4200) * 3.1 / 1000.f;
		if (vel_odpych_y > 0)
			vel_odpych_y = 0;
	}

	move_x = vel_x() * (mineloCzasu / 1000.f);

	// *********** UPDATE Z KLASY PODSTAWOWEJ ***********
	Ladowe::update(mineloCzasu);

}

void Jaszczurka::kamufluj() {
	/* Ustalenie jaki jest kolor jaszczurki (dokładnie to jaką wartość ma
	 * transparentność) na podstawie tego jak długi jest czas zakamuflowania.
	 * Używane są do tego dwie zmienne, ponieważ mocniejsze przejście
	 * następuję gdy osiągnięty jest czas potrzebny do zakamuflowania.
	 */

	int kamuflaz_zmienna1, kamuflaz_zmienna2;
	kamuflaz_zmienna1 = ((czas_kamuflowania.getElapsedTime().asMilliseconds())
			/ 10);

	if (kamuflaz_zmienna1 < 0)
		kamuflaz_zmienna1 = 0;

	kamuflaz_zmienna2 = ((czas_kamuflowania.getElapsedTime().asMilliseconds()
			- 1800) / 3.1);

	if (kamuflaz_zmienna2 < 0)
		kamuflaz_zmienna2 = 0;

	if (kamuflaz_zmienna1 + kamuflaz_zmienna2 > 255) {
		kamuflaz_zmienna1 = 0;
		kamuflaz_zmienna2 = 255;
	}

	for (int i = 0; i < 9; i++)
		// Zmiana koloru transparentności ↔ efekt zanikania
		sprite[i].setColor(
				sf::Color(255, 255, 255,
						255 - kamuflaz_zmienna2 - kamuflaz_zmienna1));
}

