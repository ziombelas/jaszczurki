/*
 * Rozgrywka to zbiór odbywających się po kolei gier (gdy rozpoczyna się
 * kolejna runda obiekt klasy Gra jest usuwany i tworzony na nowo). Pod
 * koniec rozgrywki, czyli po zakończeniu wszystkich rund tworzone i
 * uruchamiane jest PodsumowanieWynikow.
 */

#ifndef ROZGRYWKA_H_
#define ROZGRYWKA_H_

#include "Gra.h"
#include "PodsumowanieWynikow.h"

class Rozgrywka {
public:
	Rozgrywka(sf::RenderWindow &window, Ustawienia *ustawienia,
			ProgramState &state);
	~Rozgrywka();

	// Uruchomienie pętli głównej wewnątrz Rozgrywki
	void run();
private:
	//****************** ELEMENTY ROZGRYWKI ******************
	int runda;

	// Tworzona dynamicznie Gra
	Gra *gra;

	// Tworzone dynamicznie PodsumowanieWynikow
	PodsumowanieWynikow *podsumowanie;

	//****************** DOTYCZY PĘTLI PROGRAMU **************
	ProgramState *state;
	Ustawienia *ustawienia;

	//**************** POTRZEBNE DLA DZIAŁANIA SFML *************
	sf::RenderWindow *window;
	sf::Event event;
};

#endif /* ROZGRYWKA_H_ */
