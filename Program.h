/*
 * Program gdzie ma początek utworzenie okna sfml i zarządzanie
 * aktualnym etapem programu w zależności od ProgramState.
 * Program zawiera w sobie również ekran tytułowy i jego obsługę.
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

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
	//***************** ELEMENTY PROGRAMU *****************
//	bool ifTutorial;

	//**************** DOTYCZY PĘTLI PROGRAMU *************
	ProgramState state;
	Settings *ustawienia;

	//**************** ELEMENTY GRAFICZNE *****************
	sf::Font font_title, font_opis;

	sf::Texture tlo_texture;
	sf::Sprite tlo_jaszczurki;
	sf::Sprite tlo_jaszczurki_drugibok;

	//**************** POTRZEBNE DLA DZIAŁANIA SFML *************
	sf::Event event;


};

#endif /* GRA_H_ */
