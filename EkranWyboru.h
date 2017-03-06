/*
 * Ekran w którym gracze mogą przyłączać się do gry, reprezentując
 * jedno z 6 możliwych inputów jako 2 układy klawiatury i 4ry id padów.
 * Gdy gracze są gotowi wartośc na wskaźniku stanu programu zostaje
 * ustawiona na początek rozgrywki.
  */

#ifndef EKRANWYBORU_H_
#define EKRANWYBORU_H_

#include <SFML/Graphics.hpp>

#include "PoleDolacz.h"
#include "Ustawienia.h"

class EkranWyboru {
public:
	EkranWyboru(sf::RenderWindow & window, Ustawienia *ustawienia,
			ProgramState & state);
	~EkranWyboru();

	// Uruchomienie pętli głównej wewnątrz EkranuWyboru
	void run();
private:
	//************** ELEMENTY EKRANU WYBORU **************
	Ustawienia *ustawienia;

	Input *input[6];
	bool zajetoscInputu[6];

	std::vector<PoleDolacz*> pole;

	void update();
	void wyswietl();

	//*************** DOTYCZY PĘTLI PROGRAMU **************
	bool exit;
	ProgramState *state;

	//**************** ELEMENTY GRAFICZNE *****************
	// Czcionka do tekstu dołączenia
	sf::Font fontWPolu;

	sf::RectangleShape rectNaGracza[4];
	sf::Text tekst[4][3];

	//**************** POTRZEBNE DLA DZIAŁANIA SFML *************
	sf::RenderWindow *window;
	sf::Event event;
};

#endif /* EKRANWYBORU_H_ */
