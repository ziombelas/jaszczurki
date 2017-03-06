/*
 * Program, tu ma początek utworzenie okna sfml i zarządzanie
 * aktualnym etapem programu w zależności od ProgramState.
 * Klasa Program zawiera w sobie również menu (ekran tytułowy)
 * i jego obsługę.
 */

#ifndef PROGRAM_H_
#define PROGRAM_H_

#include <SFML/Graphics.hpp>
#include <string>

#include "Rozgrywka.h"
#include "EkranWyboru.h"
#include "Instrukcja.h"

using namespace std;

class Program {
public:
	Program();
	~Program();

	// Urchomienie programu
	void run();
private:
	//**************** DOTYCZY PĘTLI PROGRAMU *************
	ProgramState state;
	Ustawienia *ustawienia;

	//*************** ELEMENTY GRAFICZNE MENU ****************
	sf::Font font_title, font_opis;

	sf::Texture tlo_texture;
	sf::Sprite tlo_jaszczurki;
	sf::Sprite tlo_jaszczurki_drugibok;

	//**************** POTRZEBNE DLA DZIAŁANIA SFML *************
	sf::RenderWindow window;
	sf::Event event;

};

#endif /* GRA_H_ */
