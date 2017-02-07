/* Punkty zapisane liczbowo jako napis np. "+1" lecący w stronę tablicy
 * gracza który ten punkt zdobył. Jak trafi na tablicę jest kasowany, a score
 * gracza zwiększa się o przekazaną wartość.
 */

#ifndef PUNKTY_H_
#define PUNKTY_H_

#include <sstream>

#include "TablicaNaWynik.h"

class Punkty: public sf::Drawable {
public:
	Punkty(int wynik, TablicaNaWynik * tablicaNaWynik, int x, int y);
	~Punkty();

	// Wyświetlanie napisu z punktami na ekranie
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	// Aktualizacja procesów związanych z lecącymi punktami
	void update(int mineloCzasu);
private:
	//******************** ELEMENTY PUNKTÓW **********************
	// Tablica do której leca punkty
	TablicaNaWynik *tablicaNaWynik;

	// Liczba punktów lecących punktów
	int wynik;

	// Czy te punkty są już dodane
	bool czyDodane;

	// Prędkość z jaką leci góra/dół
	double vx, vy;

	//******************* ELEMENTY GRAFICZNE *********************
	float przezroczystosc;

	sf::Font font;
	sf::Text text;

	friend class Gra;
};

#endif /* PUNKTY_H_ */
