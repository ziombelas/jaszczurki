#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Rozgrywka.h"
#include "EkranWyboru.h"

using namespace std;

class Program {
public:
	Program();
	~Program();

	// Urchomienie programu
	void run();
private:
	//**************** FUNDAMENTALNE DANE ****************
	sf::Event event;
	ProgramState state;
	Settings *ustawienia;

	//**************** ELEMENTY GRAFICZNE *****************
	sf::Font font_title, font_opis;

	sf::Texture tlo_texture;
	sf::Sprite tlo_jaszczurki;
	sf::Sprite tlo_jaszczurki_drugibok;

	bool ifTutorial;
};

