#include "Gra.h"

Gra::Gra(sf::RenderWindow &window, Settings *ustawienia, ProgramState *state,
		int runda) {
	this->window = &window;
	this->state = state;
	this->runda = runda;

	srand(time( NULL));

	etap = ODLICZANIE_DO_STARTU;

	mineloCzasu = 0;

	// Utworzenie tablic na górze erkanu
	tablicaNaWynik[0] = new TablicaNaWynik(1920 / 4 * 0, 0, sf::Color(5, 5, 5));
	tablicaNaWynik[1] = new TablicaNaWynik(1920 / 4 * 1, 0,
			sf::Color(25, 25, 25));
	tablicaNaWynik[2] = new TablicaNaWynik(1920 / 4 * 2, 0, sf::Color(5, 5, 5));
	tablicaNaWynik[3] = new TablicaNaWynik(1920 / 4 * 3, 0,
			sf::Color(25, 25, 25));

	// Pobranie domyślnej mapy
	Mapa1 mapa1;
	pobierzMape(mapa1);

	tlo.setTexture(tlo_texture);

	// Utworzenie postaci graczy
	for (unsigned int i = 0; i < ustawienia->grajacy.size(); i++) {
		gracz.push_back(new Gracz(respPos[i], ustawienia->grajacy[i]));
		powiazGraczaZTablica(ustawienia->grajacy[i], tablicaNaWynik[i]);
	}

	// Stworzenie pierwszej muchy
	mucha.push_back(new Mucha(true));

	// Czcionka dla napisów gry
	font.loadFromFile("data/fonts/PORKYS.ttf");

	// Zrobienie napisu RUNDA x
	std::ostringstream ss;
	ss << "Runda ";
	ss << runda;
	std::string napis = ss.str();
	napisRunda.setString(napis);
	napisRunda.setFont(font);
	napisRunda.setCharacterSize(100);
	napisRunda.setColor(sf::Color(255, 255, 255));
	napisRunda.setOrigin(napisRunda.getGlobalBounds().width / 2,
			napisRunda.getGlobalBounds().height / 2);
	napisRunda.setPosition(2300, 240);

}

Gra::~Gra() {
	for (unsigned int i = 0; i < teren.size(); i++)
		delete teren[i];

	for (unsigned int i = 0; i < scianka.size(); i++)
		delete scianka[i];

	for (unsigned int i = 0; i < gracz.size(); i++)
		delete gracz[i];

	for (unsigned int i = 0; i < mucha.size(); i++)
		delete mucha[i];

	for (unsigned int i = 0; i < punkty.size(); i++) {
		// Dodanie punktów, który nie zdążyły dolecieć zanim Gra się
		// usunie.
		if (!punkty[i]->czyDodane)
			punkty[i]->tablicaNaWynik->pokazywany->zwiekszWynik(
					punkty[i]->wynik);
		delete punkty[i];
	}

	for (unsigned int i = 0; i < 4; i++)
		delete tablicaNaWynik[i];
}

void Gra::run() {

//	sf::Text tekst[4];
	exit = false;

//	if (tutorial) {
//		// Stworzenie obiektow potrzebnych dla tutorialu
//
//		const int tutorial_texts = 2;
//		string str[] = { "By się poruszac ruszaj lewym analogiem.",
//				"Sterowanie klasyczne." };
//		for (int i = 0; i < tutorial_texts; i++) {
//			tekst[i].setFont(font);
//			tekst[i].setCharacterSize(66);
//			tekst[i].setColor(sf::Color::Cyan);
//
//			tekst[i].setString(str[i]);
//			tekst[i].setPosition(
//					1920 / 2 - tekst[i].getGlobalBounds().width / 2, 350);
//		}
//	}
//	short wybrany_tekst = 0;

	startTimer.restart();

	// *********************   PĘTLA GŁÓWNA   ************************ //
	while (!exit) {

		// Resetowanie stopera odstępów czasowych między klatkami
		delta.restart();

		// Zablokowanie ruszania się przed startem
		if (etap != ODLICZANIE_DO_STARTU)
			for (unsigned int i = 0; i < gracz.size(); i++)
				gracz[i]->getKeys();

		while (window->pollEvent(event)) {
			// Powrót do menu - wciśnięcie ESC
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				*state = MENU;
		}

		// Wszystkie aktualizacje czynności dla poszczególnych etapów
		// znajdują się w procedurze update()
		switch (etap) {
		case ODLICZANIE_DO_STARTU: {
			if (startTimer.getElapsedTime().asSeconds() > 3) {
				etap = CIAGLE_GRAMY;
			}
		}
			break;
		case CIAGLE_GRAMY: {
		}
			break;
		case KONIEC_RUNDY: {
		}
			break;
		}

		window->clear();
		update();
		wyswietl();

		// Zapisanie minionego czasu pomiędzy poprzednią a aktualną klatką
		mineloCzasu = delta.getElapsedTime().asMilliseconds();

		// Wyjście jeśli to już nie rozgrywka
		if (*state != ROZGRYWKA)
			break;
	} // ************************************************************ //

}

void Gra::update() {
	// Update ścianek
	if (etap != ODLICZANIE_DO_STARTU)
		for (unsigned int i = 0; i < scianka.size(); i++)
			scianka[i]->update(mineloCzasu);

	// Update graczy
	for (unsigned int i = 0; i < gracz.size(); i++)
		gracz[i]->update(mineloCzasu);

	// Update przeciwników (much)
	if (etap != ODLICZANIE_DO_STARTU)
		for (unsigned int i = 0; i < mucha.size(); i++)
			updatePrzeciwnikow(*mucha[i]);

	if (etap != ODLICZANIE_DO_STARTU)
		for (unsigned int i = 0; i < gracz.size(); i++)
			updateKamuflaz(*gracz[i]);

	// Usunięcie znaczników podłoża u graczy
	for (unsigned int i = 0; i < gracz.size(); i++) {
		gracz[i]->maPodloze = false;
		gracz[i]->terenSpoczynku = NULL;
	}

	// Kolizje gracz - gracz
	for (unsigned int i = 0; i < gracz.size(); i++)
		for (unsigned int j = 0; j < gracz.size(); j++)
			if (j != i && gracz[i]->status == Gracz::ZYJE
					&& gracz[j]->status == Gracz::ZYJE) {
				kolizjePostacPostac(*gracz[i], *gracz[j]);
			}

	// Aktualizacja procesów związanych z terenem
	if (etap != ODLICZANIE_DO_STARTU)
		for (unsigned int i = 0; i < teren.size(); i++)
			teren[i]->update(mineloCzasu);

	// Sprawdzenie czy gracz ląduje na jakimś terenie, bądź go opuszcza
	for (unsigned int i = 0; i < gracz.size(); i++)
		for (unsigned int j = 0; j < teren.size(); j++) {
			if (gracz[i]->status == Gracz::ZYJE)
				kolizjePostacTeren(*gracz[i], *teren[j]);
		}

	// Kolizje gracz - mucha
	for (unsigned int i = 0; i < gracz.size(); i++) {
		for (unsigned int j = 0; j < mucha.size(); j++)
			if (gracz[i]->status == Gracz::ZYJE) {
				kolizjePostacMucha(*gracz[i], *mucha[j]);
			}
	}

	// Sprawdzanie czy nastąpiło zwycięstwo
	if (etap != KONIEC_RUNDY) {
		int nr_alives = 0;
		for (unsigned int i = 0; i < gracz.size(); i++) {
			if (gracz[i]->status == Gracz::ZYJE)
				nr_alives++;
		}
		if (nr_alives == 1) {
			for (unsigned int i = 0; i < gracz.size(); i++) {
				if (gracz[i]->status == Gracz::ZYJE)
					winner = gracz[i]->grajacy->getImie().get_c_str();
				etap = KONIEC_RUNDY;
				czasKonca.restart();
			}
		}
	}
	// Update lecących punktów z wynikiem
	for (unsigned int i = 0; i < punkty.size(); i++)
		punkty[i]->update(mineloCzasu);

	// Tablice na wynik
	for (unsigned int i = 0; i < 4; i++)
		tablicaNaWynik[i]->update();

	// Przesunięcie napisu pokazującego nr rundy
	if (napisRunda.getPosition().x > -3000)
		napisRunda.move(-1400 * (mineloCzasu / 1000.f), 0);

	if (czasKonca.getElapsedTime().asMilliseconds() > 5000
			&& etap == KONIEC_RUNDY)
		exit = true;
}

void Gra::wyswietl() {
	// Tło mapy
	window->draw(tlo);

	// NARYSOWANIE:
	//• ścianek
	for (unsigned int i = 0; i < scianka.size(); i++)
		window->draw(*scianka[i]);
	//• terenów
	for (unsigned int i = 0; i < teren.size(); i++)
		window->draw(*teren[i]);
	//• graczy
	for (unsigned int i = 0; i < gracz.size(); i++)
		window->draw(*gracz[i]);
	//• much
	for (unsigned int i = 0; i < mucha.size(); i++)
		window->draw(*mucha[i]);
	//• tablic na wynik
	for (unsigned int i = 0; i < 4; i++)
		window->draw(*tablicaNaWynik[i]);
	//• lecących punktów
	for (unsigned int i = 0; i < punkty.size(); i++)
		window->draw(*punkty[i]);

	// Odliczanie: 3 2 1 START
	if (startTimer.getElapsedTime().asMilliseconds() < 3500) {
		if (startTimer.getElapsedTime().asSeconds() > 3)
			napisStart.setString("START");
		else if (startTimer.getElapsedTime().asSeconds() > 2)
			napisStart.setString("1");
		else if (startTimer.getElapsedTime().asSeconds() > 1)
			napisStart.setString("2");
		else if (startTimer.getElapsedTime().asSeconds() > 0)
			napisStart.setString("3");

		napisStart.setFont(font);
		napisStart.setCharacterSize(172);
		napisStart.setColor(sf::Color(255, 130, 30));
		napisStart.setOrigin(napisStart.getGlobalBounds().width / 2,
				napisStart.getGlobalBounds().height / 2);
		napisStart.setPosition(1920 / 2, 1080 / 2 - 90);
		window->draw(napisStart);
	}

	// Napis RUNDA x
	window->draw(napisRunda);

	// Napis zwycięstwa: Wygrywa Xyz (wstaw Maks :D)
	if (etap == KONIEC_RUNDY) {
		wchar_t zw[30];
		wcscpy(zw, L"Gratsy ");
		wcscat(zw, winner);

		koniecText.setString(zw);
		koniecText.setFont(font);
		koniecText.setCharacterSize(106);
		koniecText.setColor(sf::Color(255, 130, 30));
		koniecText.setOrigin(koniecText.getGlobalBounds().width / 2,
				koniecText.getGlobalBounds().height);
		koniecText.setPosition(1920 / 2, 1080 / 2 - 90);
		window->draw(koniecText);
	}
	window->display();

}

void Gra::pobierzMape(Mapa & mapa) {
	// Przypisanie obiektów z mapy stworzonej na potrzeby Gry
	teren = mapa.teren;
	scianka = mapa.scianka;
	respPos = mapa.respPos;

	tlo_texture = mapa.tlo_texture;
}

void Gra::updateKamuflaz(Jaszczurka & jaszczurka) {
	// Restart timera kamuflażu gdy niekamufluje
	if (jaszczurka.faza_kamuflazu == Jaszczurka::NIEKAMUFLUJE)
		jaszczurka.czas_kamuflowania.restart();

	// Druga faza kamuflażu (kamuflaż udany)
	if (jaszczurka.czas_kamuflowania.getElapsedTime().asMilliseconds() > 1500) {
		jaszczurka.faza_kamuflazu = Jaszczurka::ZAKAMUFLOWANY;
	}

	// Wyzerowanie bool'a, będziemy zaraz sprawdzać czy może kamuflować
	jaszczurka.mozeKamuflowac = false;

	// Sprawdzenie czy postać kryje się w całości w jakimś obszarze - wówczas
	// następuje zakamuflowanie
	for (unsigned int i = 0; i < scianka.size(); i++) {
		probaKamuflazu(jaszczurka, *scianka[i]);
	}

	// Gdy kamuflować nie może (nie pokrywa się cały z żadną ścianką) to niekamufluje
	if (!jaszczurka.mozeKamuflowac) {
		jaszczurka.faza_kamuflazu = Jaszczurka::NIEKAMUFLUJE;
	}

}

void Gra::probaKamuflazu(Jaszczurka & gracz, Scianka & scianka) {
	for (int nr = 0; nr < 9; nr++)
		for (int nr2 = 0; nr2 < 9; nr2++)
			// W całości graniczy ze ścianką we właściwym kolorze
			if (kol_calkowita(gracz, nr, scianka, nr2)) {
				gracz.mozeKamuflowac = true;
				// Jeśli w tym nie momenie nie kamuflował to teraz włącza się kamuflaż
				if (gracz.faza_kamuflazu == Gracz::NIEKAMUFLUJE) {
					gracz.kamuflowany_kolor = scianka.kolor;
					gracz.faza_kamuflazu = Gracz::KAMUFLUJE;
				}
			}
}

void Gra::kolizjePostacTeren(Gracz & gracz, Teren & teren) {
	for (int nr = 0; nr < 9; nr++) {
		// PRZYPADEK 1: KOLIZJA DO GÓRY - nogami w glebę.
		// Sprawdzane jest czy aktualna krawędź dolna postaci nie spowodowała
		// kontaktu z krawędzią górną, a proces ten nie zachodził klatkę temu.

		// Pozycja postaci mieści się miedzy brzegami w osi X
		if (kol_os_x(gracz, nr, teren)
		// i nie bylo wcisniete w dół (dla przenikalnego terenu)
				&& (teren.przenikalnosc == false || !gracz.PRESSED[Gracz::dol])) {

			//	Znajduje się dokładnie na podłożu (i nie unosi się w górę)
			if (static_cast<int>(gracz.getGlobalBounds(nr).top
					+ gracz.getGlobalBounds().height)
					== static_cast<int>(teren.getGlobalBounds().top)
			// Przed chwilą nie był poniżej
					&& static_cast<int>(gracz.getPrevGlobalBounds(nr).top
							+ gracz.getPrevGlobalBounds(nr).height)
							<= static_cast<int>(teren.getGlobalBounds().top)) {
				// Postać sukcesywnie spoczywa na terenie
				gracz.maPodloze = true;
				gracz.terenSpoczynku = &teren;
			}

			// Dolna krawędź postaci przekracza krawędź górna w tej klatce,
			// a w poprzedniej nie przekraczała
			else if (kol_dol_do_gory(gracz, nr, teren)) {
				// Postać sukcesywnie spoczywa na terenie
				gracz.maPodloze = true;
				gracz.terenSpoczynku = &teren;
				// Przesuwanie postaci w górę o tyle, aż dół postaci będzie tam gdzie góra terenu.
				do {
					gracz.sprite[0].move(0, -1);
					gracz.updateWszystkieOdniesienia();
				} while (static_cast<int>(gracz.getGlobalBounds(nr).top
						+ gracz.getGlobalBounds(nr).height)
						> static_cast<int>(teren.getGlobalBounds().top));
			}
		}

		// ******* POZOSTAŁE PRZYPADKI DLA NIEPRZENIKALNYCH TERENÓW ********
		if (!teren.przenikalnosc) {

			// PRZYPADEK 2: KOLIZJA DO LEWEJ - prawa strona postaci w ściane
			// Sprawdzane jest czy aktualna prawa krawędź spowodowała kolizje z
			// lewą terenu, a proces nie zachodził klatkę temu.
			if ((kol_os_y(gracz, nr, teren)
					&& kol_prawa_do_lewej(gracz, nr, teren))) {
				// Odbicie się ↔ prędkość odbicia staje się przeciwna wypadkowej
				gracz.vel_odpych_x = -gracz.vel_x();

				// Zaprzestanie ataku po zderzeniu
				gracz.fazaAtaku = Gracz::NIEATAKUJE;

				// Przesuwanie postaci w lewo o tyle, aż prawa krawędź postaci
				// będzie tam gdzie lewa krawędź terenu.
				do {
					gracz.sprite[0].move(-1, 0);
					gracz.updateWszystkieOdniesienia();
				} while (static_cast<int>(gracz.getGlobalBounds(nr).left
						+ gracz.getGlobalBounds(nr).width)
						> static_cast<int>(teren.getGlobalBounds().left));
			}

			// PRZYPADEK 3: KOLIZJA DO PRAWEJ - lewa strona postaci w ściane
			// Sprawdzane jest czy aktualna lewa krawędź spowodowała kolizje z
			// prawą terenu, a proces nie zachodził klatkę temu.
			if (kol_os_y(gracz, nr, teren)
					&& kol_lewa_do_prawej(gracz, nr, teren)) {
				// Odbicie się ↔ prędkość odbicia staje się przeciwna wypadkowej
				gracz.vel_odpych_x = -gracz.vel_x();

				// Zaprzestanie ataku po zderzeniu
				gracz.fazaAtaku = Gracz::NIEATAKUJE;

				// Przesuwanie postaci w prawo o tyle, aż lewa krawędź postaci
				// będzie tam gdzie prawa krawędź terenu.
				do {
					gracz.sprite[0].move(1, 0);
					gracz.updateWszystkieOdniesienia();
				} while (static_cast<int>(gracz.getGlobalBounds(nr).left)
						<= static_cast<int>(teren.getGlobalBounds().left
								+ teren.getGlobalBounds(nr).width));
			}

			// PRZYPADEK 4: KOLIZJA DO DOŁU - łbem postaci w sufit.
			// Sprawdzane jest czy aktualna krawędź górna spowodowała kolizje z
			// krawędzią dolną terenu, a proces nie zachodził klatkę temu.
			if (kol_gora_do_dolu(gracz, nr, teren)
					&& kol_os_x(gracz, nr, teren)) {
				gracz.vel_odpych_y -= gracz.vel_y();
				// Przesuwanie postaci w górę o tyle, aż dół postaci będzie tam gdzie góra terenu.
				do {
					gracz.sprite[0].move(0, 1);
					gracz.updateWszystkieOdniesienia();
				} while (static_cast<int>(gracz.getGlobalBounds(nr).top)
						< static_cast<int>(teren.getGlobalBounds().top
								+ teren.getGlobalBounds().height));
			}
		}	// if (!teren.przenikalnosc)
	}	// for dla nr 0 → 9
}

void Gra::kolizjePostacPostac(Gracz & p1, Gracz & p2) {
	for (int nr = 0; nr < 9; nr++) {
		// PRZYPADEK 1: KOLIZJA DO GÓRY - nogami na głowę.
		// Sprawdzane jest czy aktualna krawędź dolna postaci nie spowodowała
		// kontaktu z krawędzią górną, a proces ten nie zachodził klatkę temu.

		// Pozycja postaci mieści się miedzy brzegami w osi X
		if (kol_os_x(p1, nr, p2)) {
			//	Znajduje się dokładnie na podłożu (i nie unosi się w górę)
			if (static_cast<int>(p1.getGlobalBounds(nr).top
					+ p1.getGlobalBounds().height)
					== static_cast<int>(p2.getGlobalBounds().top)) {
				p1.maPodloze = true;
				if (p2.vel_y() < p2.min_vel_grawitacja) {
					float temp = p2.vel_y();
					p2.vel_odpych_y -= p2.vel_y() * .45;
					p1.vel_odpych_y += temp * 1;
				} else
					p1.vel_odpych_y = -p2.vel_y();
			}
			// Dolna krawędź postaci przekracza krawędź górna w tej klatce,
			// a w poprzedniej nie przekraczała
			else if (kol_dol_do_gory(p1, nr, p2)) {
				p1.maPodloze = true;
				if (p2.vel_y() < p2.min_vel_grawitacja) {
					float temp = p2.vel_y();
					p2.vel_odpych_y -= p2.vel_y() * .45;
					p1.vel_odpych_y += temp * 1;
				} else
					p1.vel_odpych_y = -p2.vel_y();

				// Przesuwanie postaci w górę o tyle, aż dół postaci będzie tam gdzie góra drugiej
				do {
					p1.sprite[0].move(0, -1);
					if (p2.vel_y() < p2.min_vel_grawitacja)
						p2.sprite[0].move(0, 1);
					p1.updateWszystkieOdniesienia();
					p2.updateWszystkieOdniesienia();
				} while (static_cast<int>(p1.getGlobalBounds(nr).top
						+ p1.getGlobalBounds(nr).height)
						> static_cast<int>(p2.getGlobalBounds().top));
			}
			// W poprzedniej klatce drugi był idealnie na pierwszym, teraz natomiast
			// nastąpiła kolizja
			else if (static_cast<int>(p1.getPrevGlobalBounds(nr).top
					+ p1.getPrevGlobalBounds().height)
					== static_cast<int>(p2.getPrevGlobalBounds().top)
					&& kol_ogolnie(p1, nr, p2)) {
				if (p2.vel_y() < p2.min_vel_grawitacja) {
					float temp = p2.vel_y();
					p2.vel_odpych_y -= p2.vel_y() * .45;
					p1.vel_odpych_y += temp * 1;
				} else
					p1.vel_odpych_y = -p2.vel_y();

				// Przesuwanie postaci w górę o tyle, aż dół postaci będzie tam gdzie góra terenu.
				do {
					p1.sprite[0].move(0, -1);
					if (p2.vel_y() < p2.min_vel_grawitacja)
						p2.sprite[0].move(0, 1);
					p1.updateWszystkieOdniesienia();
					p2.updateWszystkieOdniesienia();
				} while (static_cast<int>(p1.getGlobalBounds(nr).top
						+ p1.getGlobalBounds(nr).height)
						> static_cast<int>(p2.getGlobalBounds().top));
			}
		}

		// PRZYPADEK 2: KOLIZJA DO LEWEJ - prawa strona postaci w lewą krawędź 2giej
		// Sprawdzane jest czy aktualna prawa krawędź  postaci spowodowała kolizje z
		// lewą drugiej, a proces nie zachodził klatkę temu.
		//
		// To jedno sprawdzenie wystarcza by ustalić czy następiło zderzenie między
		// dowolnymi dwoma graczami.
		if ((kol_os_y(p1, nr, p2) && kol_prawa_do_lewej(p1, nr, p2))) {
			float temp = p1.vel_x();
			if (p2.vel_x() <= 0 && p1.vel_x() >= 0) {
				p1.vel_odpych_x = p2.vel_x();
				p2.vel_odpych_x = temp;

				// Zderzenie czołowe, obie atakują
				if (p1.fazaAtaku == Gracz::ATAKUJE
						&& p2.fazaAtaku == Gracz::ATAKUJE && p1.zwrot == 1
						&& p2.zwrot == -1) {
					p1.fazaAtaku = Gracz::NIEATAKUJE;
					p2.fazaAtaku = Gracz::NIEATAKUJE;

					// Pierwszy ma więcej mocy
					if (p1.naladowanieAtk > p2.naladowanieAtk) {
						p2.status = Gracz::UMIERA;
						// Przyznanie punktów 1szemu
						punkty.push_back(
								new Punkty(7, p1.grajacy->tablicaNaWynik,
										p2.pozycjaWzgledemMonitora().x,
										p2.pozycjaWzgledemMonitora().y));
						p1.grajacy->upolowalJaszczurke();
					}
					// Drugi ma więcej mocy
					else if (p2.naladowanieAtk > p1.naladowanieAtk) {
						p1.status = Gracz::UMIERA;
						// Przyznanie punktów 2giemu
						punkty.push_back(
								new Punkty(7, p2.grajacy->tablicaNaWynik,
										p1.pozycjaWzgledemMonitora().x,
										p1.pozycjaWzgledemMonitora().y));
						p2.grajacy->upolowalJaszczurke();
					}
				}

				// Pierwsza bezbronna, druga atakuje
				if ((p1.fazaAtaku != Gracz::ATAKUJE || p1.zwrot == -1)
						&& p2.fazaAtaku == Gracz::ATAKUJE && p2.zwrot == -1) {
					p1.fazaAtaku = Gracz::NIEATAKUJE;
					p2.fazaAtaku = Gracz::NIEATAKUJE;
					p1.status = Gracz::UMIERA;

					// Przyznanie punktów atakującemu (2gi)
					punkty.push_back(
							new Punkty(7, p2.grajacy->tablicaNaWynik,
									p1.pozycjaWzgledemMonitora().x,
									p1.pozycjaWzgledemMonitora().y));
					p2.grajacy->upolowalJaszczurke();
				}

				// Pierwsza atakuje, druga bezbronna
				if (p1.fazaAtaku == Gracz::ATAKUJE && p1.zwrot == 1
						&& (p2.fazaAtaku != Gracz::ATAKUJE || p2.zwrot == 1)) {
					p1.fazaAtaku = Gracz::NIEATAKUJE;
					p2.fazaAtaku = Gracz::NIEATAKUJE;
					p2.status = Gracz::UMIERA;

					// Przyznanie punktów atakującemu (1wszy)
					punkty.push_back(
							new Punkty(7, p1.grajacy->tablicaNaWynik,
									p2.pozycjaWzgledemMonitora().x,
									p2.pozycjaWzgledemMonitora().y));
					p1.grajacy->upolowalJaszczurke();

				}

				// Dla dużego odpychu 20% prędkości powyżej 300 idzie na wyrzut w górę
				if (p2.vel_odpych_x > 300) {
					float iks = sqrt(
							(p2.vel_odpych_x - 300) * (p2.vel_odpych_x - 300)
									/ 0.68);
					p2.vel_odpych_y -= iks * 0.2;
					p2.vel_odpych_x += iks * 0.2;
				}
				if (p1.vel_odpych_x < -300) {
					float iks = sqrt(
							(p1.vel_odpych_x + 300) * (p1.vel_odpych_x + 300)
									/ 0.68);
					p1.vel_odpych_y -= iks * 0.2;
					p1.vel_odpych_x -= iks * 0.2;
				}
			}
			// Przesuwanie postaci w lewo o tyle, aż prawa krawędź postaci
			// będzie tam gdzie lewa krawędź p2.
			do {
				p1.sprite[0].move(-1, 0);
				p2.sprite[0].move(1, 0);
				p1.updateWszystkieOdniesienia();
				p2.updateWszystkieOdniesienia();
			} while (static_cast<int>(p1.getGlobalBounds(nr).left
					+ p1.getGlobalBounds(nr).width)
					> static_cast<int>(p2.getGlobalBounds().left));
		}
	} // for dla nr 0 → 9
}

void Gra::kolizjePostacMucha(Gracz & gracz, Mucha & mucha) {
	for (int nr = 0; nr < 9; nr++) {
		// Sprawdzenie ogólnej kolizji wystarcza by ustalić czy następiło zderzenie
		// między graczm a przeciwnikiem
		if (kol_ogolnie(gracz, nr, mucha)) {
			if (gracz.fazaAtaku == Gracz::ATAKUJE) {

				// Przyznanie punktów
				punkty.push_back(
						new Punkty(2, gracz.grajacy->tablicaNaWynik,
								mucha.pozycjaWzgledemMonitora().x,
								mucha.pozycjaWzgledemMonitora().y));

				gracz.grajacy->upolowalMuche();

				// Skasowanie i zdjęcie starej muchy
				delete &mucha;
				Gra::mucha.erase(Gra::mucha.begin());

				// Wstawienie nowej muchy
				Gra::mucha.push_back(new Mucha());

				// Wyjście z pętli tudzież całej procedury
				break;
			}
		}
	} // for dla nr 0 → 9
}

void Gra::updatePrzeciwnikow(Mucha & mucha) {
// Sprawdzenie czy udało się osiągnać już pozycję wylosowaną jako dest
	if ((mucha.getPosition().x > mucha.dest.x && mucha.czyWiecejX == 1
			&& mucha.getPosition().y > mucha.dest.y && mucha.czyWiecejY == 1)
			|| (mucha.getPosition().x < mucha.dest.x && mucha.czyWiecejX == -1
					&& mucha.getPosition().y > mucha.dest.y
					&& mucha.czyWiecejY == 1)
			|| (mucha.getPosition().x < mucha.dest.x && mucha.czyWiecejX == -1
					&& mucha.getPosition().y < mucha.dest.y
					&& mucha.czyWiecejY == -1)
			|| (mucha.getPosition().x > mucha.dest.x && mucha.czyWiecejX == 1
					&& mucha.getPosition().y < mucha.dest.y
					&& mucha.czyWiecejY == -1)) {

		bool bezkolizijnosc;
		int proby = 0;
		do {
			bezkolizijnosc = true;

			// Losowanie nowej pozycji
			mucha.nadajCelLotu();
			// sprawdzenie dla 10 odcinków między akt. pozycją a celem
			sf::Vector2f wektorPrzesuniecia = mucha.dest - mucha.getPosition();
			for (int z = 1; z < 5; z++) {
				sf::Vector2f odcinekProbny = wektorPrzesuniecia * (z / 5.f);

				for (int nr = 0; nr < 9; nr++) {
					// Jeżeli zawadza to terenom na mapie - zaznacza kolizijność
					for (unsigned int i = 0; i < teren.size(); i++)
						if (mucha.dest.x + odcinekProbny.x
								+ pozycjaWzgledemAllSprites(nr).x
								+ mucha.getGlobalBounds().width / 2
								> (*teren[i]).getGlobalBounds().left
								&& mucha.dest.x + odcinekProbny.x
										+ pozycjaWzgledemAllSprites(nr).x
										- mucha.getGlobalBounds().width / 2
										< (*teren[i]).getGlobalBounds().left
												+ (*teren[i]).getGlobalBounds().width
								&& mucha.dest.y + odcinekProbny.y
										+ +pozycjaWzgledemAllSprites(nr).y
										+ mucha.getGlobalBounds().height / 2
										> (*teren[i]).getGlobalBounds().top
								&& mucha.dest.y + odcinekProbny.y
										+ pozycjaWzgledemAllSprites(nr).y
										- mucha.getGlobalBounds().height / 2
										< (*teren[i]).getGlobalBounds().top
												+ (*teren[i]).getGlobalBounds().height)
							bezkolizijnosc = false;
					// Jeżeli znajduje się w pobliżu postaci - zaznacza kolizijność
					for (unsigned int i = 0; i < gracz.size(); i++)
						if (mucha.dest.x + odcinekProbny.x
								+ pozycjaWzgledemAllSprites(nr).x
								+ mucha.getGlobalBounds().width * 3
								> (*gracz[i]).getGlobalBounds().left
								&& mucha.dest.x + odcinekProbny.x
										+ pozycjaWzgledemAllSprites(nr).x
										- mucha.getGlobalBounds().width * 3
										< (*gracz[i]).getGlobalBounds().left
												+ (*gracz[i]).getGlobalBounds().width
								&& mucha.dest.y + odcinekProbny.y
										+ pozycjaWzgledemAllSprites(nr).y
										+ mucha.getGlobalBounds().height * 3
										> (*gracz[i]).getGlobalBounds().top
								&& mucha.dest.y + odcinekProbny.y
										+ pozycjaWzgledemAllSprites(nr).y
										- mucha.getGlobalBounds().height * 3
										< (*gracz[i]).getGlobalBounds().top
												+ (*gracz[i]).getGlobalBounds().height)
							bezkolizijnosc = false;
				}
			}
			// Jeśli nie daje się uniknąć kolizji z terenem to niech zostanie ten dest
			proby++;
			if (proby > 15)
				break;
			// TODO zrobić tak, żeby przy przekraczaniu krawędzi ekranu skrypt działał
			// teź opracować algorytm żeby nie lagowało a mogło zrobić troche więcej prób
			// np. niepowatrzanie sprawdzania dla terenóœ które i tak eni bd kolidowały
		} while (!bezkolizijnosc);
	}
	mucha.update(mineloCzasu);
}

bool Gra::kol_ogolnie(Obiekt &ob1, int nr, Obiekt & ob2) {
	// Zwykła kolizja, gdzie prostokąty przedstawiające 2 obiekty
	// mają niepusty zbiór wspólnych punktów.
	if (static_cast<int>(ob1.getGlobalBounds(nr).left
			+ ob1.getGlobalBounds().width)
			>= static_cast<int>(ob2.getGlobalBounds().left)
			&& static_cast<int>(ob1.getGlobalBounds(nr).left)
					<= static_cast<int>(ob2.getGlobalBounds().left
							+ ob2.getGlobalBounds().width)
			&& static_cast<int>(ob1.getGlobalBounds(nr).top
					+ ob1.getGlobalBounds().height)
					>= static_cast<int>(ob2.getGlobalBounds().top)
			&& static_cast<int>(ob1.getGlobalBounds(nr).top)
					<= static_cast<int>(ob2.getGlobalBounds().top
							+ ob2.getGlobalBounds().height))
		return true;
	return false;
}

bool Gra::kol_calkowita(Obiekt &ob1, int nr, Obiekt & ob2, int nr2) {
	// Obszary obu obiektów pokrywają się całkowicie
	if (static_cast<int>(ob1.getGlobalBounds(nr).left)
			>= static_cast<int>(ob2.getGlobalBounds(nr2).left)
			&& static_cast<int>(ob1.getGlobalBounds(nr).left
					+ ob1.getGlobalBounds(nr).width)
					< static_cast<int>(ob2.getGlobalBounds(nr2).left
							+ ob2.getGlobalBounds(nr2).width)
			&& static_cast<int>(ob1.getGlobalBounds(nr).top)
					>= static_cast<int>(ob2.getGlobalBounds(nr2).top)
			&& static_cast<int>(ob1.getGlobalBounds(nr).top
					+ ob1.getGlobalBounds(nr).height)
					< static_cast<int>(ob2.getGlobalBounds(nr2).top
							+ ob2.getGlobalBounds(nr2).height))
		return true;
	return false;
}

bool Gra::kol_dol_do_gory(Obiekt & ob1, int nr, Obiekt & ob2) {
	// Przekroczenie dołem obiektu 1. góry obiektu 2.
	if (static_cast<int>(ob1.getGlobalBounds(nr).top
			+ ob1.getGlobalBounds().height)
			> static_cast<int>(ob2.getGlobalBounds().top)
	// Nieprzekroczenie jej klatkę temu
			&& static_cast<int>(ob1.getPrevGlobalBounds(nr).top
					+ ob1.getPrevGlobalBounds().height)
					< static_cast<int>(ob2.getPrevGlobalBounds().top))
		return true;
	return false;
}

bool Gra::kol_gora_do_dolu(Obiekt & ob1, int nr, Obiekt & ob2) {
	// Przekroczenie górą obiektu 1. dołu obiektu 2.
	if (ob1.getGlobalBounds(nr).top
			< ob2.getGlobalBounds().top + ob2.getGlobalBounds().height
	// Nieprzekroczenie jej klatkę temu
			&& ob1.getPrevGlobalBounds(nr).top
					>= ob2.getPrevGlobalBounds().top
							+ ob2.getPrevGlobalBounds().height)
		return true;
	return false;
}

bool Gra::kol_prawa_do_lewej(Obiekt & ob1, int nr, Obiekt & ob2) {
	// Przekroczenie prawą krawędzią obiektu 1. lewej krawędzi obiektu 2.
	if (static_cast<int>(ob1.getGlobalBounds(nr).left
			+ ob1.getGlobalBounds().width)
			> static_cast<int>(ob2.getGlobalBounds().left)
	// Nieprzekroczenie jej klatkę temu
			&& static_cast<int>(ob1.getPrevGlobalBounds(nr).left
					+ ob1.getPrevGlobalBounds().width)
					<= static_cast<int>(ob2.getPrevGlobalBounds().left))
		return true;
	return false;
}

bool Gra::kol_lewa_do_prawej(Obiekt & ob1, int nr, Obiekt & ob2) {
	// Przekroczenie lewą krawędzią obiektu 1. prawej krawędzi obiektu 2.
	if (static_cast<int>(ob1.getGlobalBounds(nr).left)
			< static_cast<int>(ob2.getGlobalBounds().left
					+ ob2.getGlobalBounds().width)
	// Nieprzekroczenie jej klatkę temu
			&& static_cast<int>(ob1.getPrevGlobalBounds(nr).left)
					>= static_cast<int>(ob2.getPrevGlobalBounds().left
							+ ob2.getPrevGlobalBounds().width))
		return true;
	return false;
}

bool Gra::kol_os_x(Obiekt & ob1, int nr, Obiekt & ob2) {
	// Przekroczenie prawej krawędzi
	if (static_cast<int>(ob1.getGlobalBounds(nr).left)
			< static_cast<int>(ob2.getGlobalBounds().left
					+ ob2.getGlobalBounds().width) &&
	// Przekroczenie lewej krawędzi
			static_cast<int>(ob1.getGlobalBounds(nr).left
					+ ob1.getGlobalBounds().width)
					> static_cast<int>(ob2.getGlobalBounds().left))
		return true;
	return false;
}

bool Gra::kol_os_y(Obiekt & ob1, int nr, Obiekt & ob2) {
	// Przekroczenie krawędzi dolnej
	if (static_cast<int>(ob1.getGlobalBounds(nr).top)
			< static_cast<int>(ob2.getGlobalBounds().top
					+ ob2.getGlobalBounds().height) &&
	// Przekroczenie krawędzi górnej
			static_cast<int>(ob1.getGlobalBounds(nr).top
					+ ob1.getGlobalBounds().height)
					> static_cast<int>(ob2.getGlobalBounds().top))
		return true;
	return false;
}

void Gra::powiazGraczaZTablica(Grajacy * grajacy, TablicaNaWynik * tablica) {
	grajacy->tablicaNaWynik = tablica;
	tablica->pokazywany = grajacy;
	tablica->wUzyciu = true;
}
