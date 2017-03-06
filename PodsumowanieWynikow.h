/*
 * Ekran podsumowania wyników każdego z graczy pokazywany
 * na koniec odegranej rozgrywki.
 */

#ifndef PODSUMOWANIEWYNIKOW_H_
#define PODSUMOWANIEWYNIKOW_H_

#include <sstream>
#include "Ustawienia.h"

class PodsumowanieWynikow {
public:
	PodsumowanieWynikow(sf::RenderWindow &window, Ustawienia *ustawienia,
			ProgramState *state);
	~PodsumowanieWynikow();

	// Uruchomienie pętli głównej wewnątrz Podsumowania
	void run();
private:
	//************** ELEMENTY EKRANU WYBORU **************
	void wyswietl();

	//*************** DOTYCZY PĘTLI PROGRAMU **************
	bool exit;
	Ustawienia *ustawienia;
	ProgramState *state;

	//**************** ELEMENTY GRAFICZNE *****************
	// Imiona graczy
	sf::Text imie[4];

	// Prostokąty z punktami
	sf::RectangleShape rectPunkty[4];

	// Liczba punktów, upolowanych much i jaszczurek
	sf::Text wynikPunkty[4], wynikMuchy[4], wynikJaszczurki[4];

	// Tekstury dla powyższych
	sf::Texture jaszczurkaUpolowana_texture, muchaUpolowana_texture;

	// Ilustracje powyższych tekstur
	sf::Sprite jaszczurkaUpolowana, muchaUpolowana;

	// Tytuł
	sf::Text title;

	// Czcionka tytułowa
	sf::Font font_title;

	// Czcionka na imion graczy
	sf::Font font;

	//**************** POTRZEBNE DLA DZIAŁANIA SFML *************
	sf::RenderWindow *window;
	sf::Event event;
};

#endif /* PODSUMOWANIEWYNIKOW_H_ */
