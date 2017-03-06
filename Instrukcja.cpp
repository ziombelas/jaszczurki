#include "Instrukcja.h"

Instrukcja::Instrukcja(sf::RenderWindow & window) {

	this->window = &window;

	font.loadFromFile("data/fonts/EncodeSansWide-Black.ttf");

	exit = false;
}

Instrukcja::~Instrukcja() {
}

void Instrukcja::run() {

	for (int i = 0; i < 21; i++) {
		linia[i].setFont(font);
		linia[i].setCharacterSize(28);
		linia[i].setPosition(20, i * 45 + 30);
		linia[i].setColor(sf::Color::White);
	}

	sf::Texture ilu1, ilu2, ilu3, ilu4, ilu5, ilu6, ilu7, ilu8;

	ilu1.loadFromFile("data/instrukcja/1.png");
	ilustracja[0].setTexture(ilu1);
	ilustracja[0].setPosition(1500, 10);

	ilu2.loadFromFile("data/instrukcja/2.png");
	ilustracja[1].setTexture(ilu2);
	ilustracja[1].setPosition(1370, 220);

	ilu3.loadFromFile("data/instrukcja/3.png");
	ilustracja[2].setTexture(ilu3);
	ilustracja[2].setPosition(1650, 220);

	ilu4.loadFromFile("data/instrukcja/4.png");
	ilustracja[3].setTexture(ilu4);
	ilustracja[3].setPosition(1400, 360);

	ilu5.loadFromFile("data/instrukcja/5.png");
	ilustracja[4].setTexture(ilu5);
	ilustracja[4].setPosition(1650, 360);

	ilu6.loadFromFile("data/instrukcja/6.png");
	ilustracja[5].setTexture(ilu6);
	ilustracja[5].setPosition(1440, 540);

	ilu7.loadFromFile("data/instrukcja/7.png");
	ilustracja[6].setTexture(ilu7);
	ilustracja[6].setPosition(1480, 700);

	ilu8.loadFromFile("data/instrukcja/8.png");
	ilustracja[7].setTexture(ilu8);
	ilustracja[7].setPosition(1520, 860);

	linia[0].setString(
			L"Sterujesz jaszczurką. Celem gry jest wyeliminowanie pozostałych jaszczurek łapiąc");
	linia[1].setString(
			L"przy tym muchy. Poruszanie odbywa się w lewo/prawo oraz przy użycu przycisku");
	linia[2].setString(
			L"skoku. Ponadto wciskając przycisk w dół możesz spadać z niebieskich płytek.");

	linia[3].setString(L"");

	linia[4].setString(
			L"Kiedy zatrzymasz jaszczurkę tak, by pokryta była w całości tłem jednego koloru to");
	linia[5].setString(
			L"rozpocznie się kamuflaż. Aby zakończył się sukcesem jaszczurka musi pozostać tak");
	linia[6].setString(
			L"przez chwilę w bezruchu i wówczas stanie się niewidzialna na tak długo, aż opuści");
	linia[7].setString(L"tło, za którym się zakamuflowała, bądź wykona atak.");

	linia[8].setString(L"");
	linia[9].setString(L"");

	linia[10].setString(
			L"Aby zaatakować naciśnij przycisk ataku. Zanim puścisz przycisk ataku najlepiej");
	linia[11].setString(
			L"przytrzymuj go przez chwilę. Czym dłużej będziesz trzymał przycisk ataku tym");
	linia[12].setString(
			L"mocniej twoja jaszczurka zaatakuje. Czym mocniej naładowany jest atak tym bardziej ");
	linia[13].setString(
			L"czerwony odcień przybierze jaszczurka. Gdy puścisz przycisk jaszczurka");
	linia[14].setString(
			L"wystrzeli naprzód. Warto dodać, że można przygotowywać atak pozostając");
	linia[15].setString(
			L"ciągle w kamuflażu - jaszczurka ujawni się dopiero gdy puścisz atak.");

	linia[16].setString(L"");

	linia[17].setString(
			L"Jeśli jaszczurka zostanie zaatakowana umiera do końca rundy, a sterujący");
	linia[18].setString(
			L"atakującą jaszczurką otrzymuje 7 punktów. Można też polować na muchy za 2 pkt.");
	linia[19].setString(L"");
	linia[20].setString(L"Gra kończy się po 5 rundach, gl hf.");

	// *********************   PĘTLA GŁÓWNA   ************************ //
	while (!exit) {
		while (window->pollEvent(event)) {

			// Wcisnięcie ESC lub  alt + f4 lub B na dowolnym padzie
			if (event.type == sf::Event::Closed
					|| (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
							&& event.type == sf::Event::KeyPressed)
					|| (sf::Joystick::isButtonPressed(0, 1)
							|| sf::Joystick::isButtonPressed(1, 1)
							|| sf::Joystick::isButtonPressed(2, 1)
							|| sf::Joystick::isButtonPressed(3, 1))) {

				exit = true;
			}

		}
		window->clear();
		wyswietl();
	} // ************************************************************ //

}

void Instrukcja::wyswietl() {
	// Wyświetlenie tekstu
	for (int i = 0; i < 21; i++)
		window->draw(linia[i]);

	// Wyświetlenie ilustracji do instrukcji
	for (int i = 0; i < 8; i++) {
		window->draw(ilustracja[i]);
	}

	window->display();
}
