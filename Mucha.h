/* Mucha która lata sobie tu i tam... Jej odloty to losowe
 * zmienne z przedziału min/max_odlot a prędkości z jakimi
 * sobie popierdziela są także losowe na podstawie stałych
 * z klasy Latajace dostarczonych w konstruktorze Muchy.
 *
 * Gdy mucha osiągnie swój docelowy punkt (dest) to
 * następuje losowanie wyżej wymienonych wartośći
 * (nowy dest w odleglości min/max_odlot, predkość
 * z przedziału vel_lotu_min/max i na tej podstawie ustala się
 * zmienne czyWiecejX/Y żeby wiedzieć w jaką stronę ma się
 * kierować na dest.
 */

#ifndef MUCHA_H_
#define MUCHA_H_

#include "Latajace.h"
#include <cstdlib>

class Mucha: public Latajace {
public:
	// Konstruktor, destruktor
	Mucha();
	~Mucha();

	// Aktualizacja procesów związanych z muchą
	void update(int mineloCzasu);
private:
	// Nadanie nowej pozycji docelowej (dest)
	void nadajCelLotu();

	// Minimalna i maksymalna wartośc na ile może odfrunąć
	int min_odlot;
	int max_odlot;

	// Czy musi przekroczyć dodatnio (+1/) czy ujemnie (-1) wartość w x/y
	int czyWiecejX, czyWiecejY;

	// Punkt docelowy lotu
	sf::Vector2f dest;

	// Aktulana prędkość (pix/s)
	float vel_x, vel_y;

	friend class Gra;
};

#endif /* MUCHA_H_ */
