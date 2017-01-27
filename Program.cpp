#include "Program.h"

sf::RenderWindow window;

Program::Program(void) {
	// Utawienia graficzne
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	window.create(sf::VideoMode(1920, 1080), "Jaszczurki", sf::Style::Fullscreen,
			settings);

	state = PROGRAM_END;
	window.setFramerateLimit(60);

	// Czcionki
	font_title.loadFromFile("data/fonts/PORKYS.ttf");
	font_opis.loadFromFile("data/fonts/EncodeSansWide-Black.ttf");


	ifTutorial = false;
	state = MENU;

	ustawienia = NULL;
}

Program::~Program() {
}

void Program::run() {
	// Wczytanie obrazku z jaszczurkami
	tlo_texture.loadFromFile("data/title_bg.png");
	tlo_jaszczurki.setTexture(tlo_texture);
	tlo_jaszczurki.setPosition(0, 1080 - 300);
	tlo_jaszczurki_drugibok.setTexture(tlo_texture);
	tlo_jaszczurki_drugibok.setPosition(tlo_jaszczurki.getGlobalBounds().width,
			1080 - 300);

	// Napis tytułowy
	sf::Text title("Jaszczurki", font_title, 180);
	title.setStyle(sf::Text::Bold);
	title.setColor(sf::Color::Green);

	title.setPosition(1920 / 2 - title.getGlobalBounds().width / 2, 30);

	sf::Text opis(L"Aby rozpocząć, wcisnij enter lub A na padzie,", font_opis, 64);
	opis.setPosition(1920 / 2 - opis.getGlobalBounds().width / 2, 360);

	sf::Text tutorialtext(
			L"żeby włączyć instrukcję wciśnij T lub Y na padzie.",
			font_opis, 48);
	tutorialtext.setPosition(
			1920 / 2 - tutorialtext.getGlobalBounds().width / 2, 550);

	// *********************   PETLA GLOWNA   ************************ //
	while (state != PROGRAM_END) {
		switch (state) {
		case MENU: {
			while (window.pollEvent(event)) {

				// Wcisniecie ESC lub przycisk X
				if (event.type == sf::Event::Closed
						|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
								&& event.type == sf::Event::KeyPressed)) {
					state = PROGRAM_END;
				}

				// Wcisnięcie A na padzie albo enter
				else if (sf::Joystick::isButtonPressed(0, 0)
						|| sf::Joystick::isButtonPressed(1, 0)
						|| sf::Joystick::isButtonPressed(2, 0)
						|| sf::Joystick::isButtonPressed(3, 0)
						|| (event.type == sf::Event::KeyPressed
								&& event.key.code == sf::Keyboard::Return)) {
					ifTutorial = false;
					state = EKRAN_WYBORU;
				}
			}

			tlo_jaszczurki.move(-.33, 0);
			tlo_jaszczurki_drugibok.move(-.33, 0);

			if (tlo_jaszczurki.getPosition().x
					< -tlo_jaszczurki.getGlobalBounds().width * 2 + 1920)
				tlo_jaszczurki.setPosition(1920, 1080 - 300);

			if (tlo_jaszczurki_drugibok.getPosition().x
					< -tlo_jaszczurki.getGlobalBounds().width * 2 + 1920)
				tlo_jaszczurki_drugibok.setPosition(1920, 1080 - 300);

			window.clear();

			// Rysowanie - ekran poczatkowy
			window.draw(title);
			window.draw(opis);
			window.draw(tutorialtext);
			window.draw(tlo_jaszczurki);
			window.draw(tlo_jaszczurki_drugibok);

			window.display();
		}
			break;
		case EKRAN_WYBORU: {
			// Nowe ustawienia, bedą kasowane po rozgrywce
			ustawienia = new Settings();

			// Sworzenie ekranu wyboru
			EkranWyboru ekrWyb(window, ustawienia, state);

			// Przenisienie pętli głownej → ekrWyb
			ekrWyb.run();
		}
			break;
		case ROZGRYWKA: {
			Rozgrywka rozgrywka(window, ustawienia, state);

			// Przeniesienie pętli głownej → rozgrywka
			rozgrywka.run();

			// Po opuszczeniu rozgrywki program wraca do menu
			state = MENU;
		}
			break;
		}
	} // ************************************************************ //
}

