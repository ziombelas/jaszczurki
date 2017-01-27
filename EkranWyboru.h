/*
 * Ekran w którym następują dołączenie graczy,
 * TODO pola powinny mieć charakter pojemnika
 * TODO spobony dolaczenia urzadzenia jako osobna klasa, ?
 *
 */

#ifndef EKRANWYBORU_H_
#define EKRANWYBORU_H_

#include <SFML/Graphics.hpp>

#include "Settings.h"
#include "PoleDolacz.h"

class EkranWyboru {
public:
	EkranWyboru(sf::RenderWindow &window, Settings *ustawienia,
			ProgramState & state);
	~EkranWyboru();

	// Głowna procedura z pętlą głowną
	void run();
private:
	//************** DOTYCZY PĘTLI PROGRAMU *************
	bool exit;
	ProgramState *state;

	//*************** FUNDAMENTALNE DANE ***************
	Settings *ustawienia;

	Input *input[6];
	bool zajetoscInputu[6];

	std::vector<PoleDolacz*> pole;

	//**************** DO WYŚWIETLENIA *****************
	sf::RectangleShape rectNaGracza[4];
	sf::Text tekst[4][3];

	sf::RenderWindow *window;
	sf::Event event;

	void update();
	void draw();
};

#endif /* EKRANWYBORU_H_ */
