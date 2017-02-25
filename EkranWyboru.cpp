#include "EkranWyboru.h"

EkranWyboru::EkranWyboru(sf::RenderWindow & window, Settings *ustawienia,
		ProgramState & state) {

	// Inicjalizacja ekranu wyboru - dostarczenia adresów okna, ustawień, stanu gry
	this->window = &window;
	this->ustawienia = ustawienia;
	this->state = &state;

	// Inicjalizacja obiektów do wyświetlania
	for (int i = 0; i < 4; i++) {
		rectNaGracza[i].setFillColor(sf::Color(77, 77, 77, 255));
		rectNaGracza[i].setSize(sf::Vector2f(350, 800));
		rectNaGracza[i].setPosition(200 + i * 400, 100);
	}

	// Wyzerowanie booli informujących o zajętości inputów
	for (int i = 0; i < 6; i++) {
		zajetoscInputu[i] = false;
	}

	// Utworzenie wszystkich inputów
	input[0] = new Input(Input::KLAWA, 0, event);
	input[1] = new Input(Input::KLAWA, 1, event);
	input[2] = new Input(Input::PAD, 0, event);
	input[3] = new Input(Input::PAD, 1, event);
	input[4] = new Input(Input::PAD, 2, event);
	input[5] = new Input(Input::PAD, 3, event);

	fontWPolu.loadFromFile("data/fonts/EncodeSansWide-Black.ttf");

	// Utworzenie tekstów zachęcających do dołączenia
	for (int n = 0; n < 4; n++) {
		tekst[n][0].setString(L"Aby dołączyć wciśnij");
		tekst[n][1].setString(L"Enter, H, bądź");
		tekst[n][2].setString(L"A na padzie");
		for (int i = 0; i < 3; i++) {
			tekst[n][i].setFont(fontWPolu);
			tekst[n][i].setCharacterSize(28);
			tekst[n][i].setColor(sf::Color::White);
			tekst[n][i].setPosition(
					200 + 400 * n + 350 / 2
							- tekst[n][i].getGlobalBounds().width / 2,
					190 + i * 60);
		}
	}

	exit = false;
}

EkranWyboru::~EkranWyboru(void) {
	// Skasowanie każdego z dostępnych inputów utworzonych na rzecz ekranu wyboru
	for (int i = 0; i < 6; i++)
		delete input[i];

	// Usunięcie wszystkich pól wyboru gdzie ktoś dołączył
	for (unsigned int i = 0; i < pole.size(); i++)
		delete pole[i];

}

void EkranWyboru::run() {
	// *********************   PĘTLA GŁÓWNA   ************************ //
	while (!exit) {
		while (window->pollEvent(event)) {

			// Wcisnięcie ESC lub zamknięcie okna
			if (event.type == sf::Event::Closed
					|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
							&& event.type == sf::Event::KeyPressed)) {
				*state = MENU;
				exit = true;
			}

			// Dołączanie do gry za pomocą klawiatury lub pada
			if (pole.size() < 4)
				for (int i = 0; i < 6; i++)
					if (!zajetoscInputu[i])
						if (input[i]->isPressed(ster_akceptuj)) {
							pole.push_back(
									new PoleDolacz(200 + pole.size() * 400, 100,
											input[i]));
							zajetoscInputu[i] = true;
						}

			// Akceptacja gotowości
			for (int unsigned i = 0; i < pole.size(); i++) {
				if (pole[i]->input->isPressed(ster_akceptuj))
					// Gdy imię jest wybrane można dołączać
					if (pole[i]->wybranoImie())
						pole[i]->gotowy = true;
			}

			// Przesuwanie w lewo/prawo klawiatura aby zmienic imie (klawa)
			for (int unsigned i = 0; i < pole.size(); i++)
				if (pole[i]->input->getRodzajInputu() == Input::KLAWA) {
					if (pole[i]->input->isPressed(ster_menu_lewo)
							&& event.type == sf::Event::KeyPressed)
						pole[i]->poprzednieImie();
					else if (pole[i]->input->isPressed(ster_menu_prawo)
							&& event.type == sf::Event::KeyPressed)
						pole[i]->nastepneImie();
				}

		}
		// Przesuwanie w lewo/prawo klawiatura aby zmienic imie (pady)
		for (unsigned int i = 0; i < pole.size(); i++)
			if (pole[i]->input->getRodzajInputu() == Input::PAD) {
				if (pole[i]->input->isPressed(ster_menu_lewo))
					pole[i]->poprzednieImie();
				else if (pole[i]->input->isPressed(ster_menu_prawo))
					pole[i]->nastepneImie();
			}

		for (int i = 0; i < 6; i++)
			input[i]->update();

		window->clear();
		update();
		wyswietl();
	} // ************************************************************ //
}

void EkranWyboru::update() {
	for (unsigned int i = 0; i < pole.size(); i++)
		pole[i]->update();

	int ile_gotowych = 0;
	int ile_ogolem = pole.size();

	// Liczenie ile jest gotowych graczy
	for (unsigned int i = 0; i < pole.size(); i++) {
		if (pole[i]->gotowy)
			ile_gotowych++;
	}

	// Jeśli przynajmniej 2 osoby dołączyły i nie ma żadnych niegotowych osób...
	if (ile_gotowych >= 2 && ile_gotowych == ile_ogolem) {
		// ... To zaczynamy grę!
		for (unsigned int i = 0; i < pole.size(); i++) {
			ustawienia->grajacy.push_back(
					new Grajacy(*pole[i]->input,
							*(pole[i]->imie[pole[i]->nr_imiona])));
		}
		// START!
		*state = ROZGRYWKA;
		exit = true;
	}
}

void EkranWyboru::wyswietl() {
	// Narysowanie wolnych pól dla graczy
	for (int i = 0; i < 4; i++)
		window->draw(rectNaGracza[i]);

	for (int n = 0; n < 4; n++)
		for (int i = 0; i < 3; i++) {
			window->draw(tekst[n][i]);
		}

	// Wyświetlenie pól graczy, którzy dołączyli ↔ zasłonięcie powyższych
	for (unsigned int i = 0; i < pole.size(); i++)
		window->draw(*pole[i]);

	window->display();
}

