/*
 * Instrukcja do gry, każda linijka zapisana jest w kolejnych elementach
 * tablicy sf::Text o nazwie linia. Poza tekstem znajdują się ilustracje
 * do instrukcji.
 */

#ifndef INSTRUKCJA_H_
#define INSTRUKCJA_H_

#include "Ustawienia.h"

class Instrukcja {
public:
	Instrukcja(sf::RenderWindow &window);
	~Instrukcja();

	// Uruchomienie pętli głównej wewnątrz Instrukcji
	void run();
private:
	//******************* ELEMENTY INSTRUKCJI ******************
	// Czcionka
	sf::Font font;

	// Pola tekstowe zapisywane linijce
	sf::Text linia[21];

	// Ilustracje z gry
	sf::Sprite ilustracja[10];

	void wyswietl();

	//****************** DOTYCZY PĘTLI PROGRAMU *****************
	bool exit;

	//**************** POTRZEBNE DLA DZIAŁANIA SFML *************
	sf::RenderWindow *window;
	sf::Event event;
};

#endif /* INSTRUKCJA_H_ */
