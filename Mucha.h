/*
 * Mucha, która lata sobie tu i tam... Jej docelowe miejsca lotu
 * to losowe zmienne z przedziału min/max_odlot, a prędkości z
 * jakimi sobie popierdziela są także losowe z przedziału stałych
 * vel_lotu_min/max wrzuconych w konstruktor klasy Latajace.
 *
 * Gdy mucha osiągnie swój docelowy punkt (dest) to
 * następuje losowanie wyżej wymienonych wartośći
 * (nowy dest w odleglości min/max_odlot, predkość
 * z przedziału vel_lotu_min/max i na tej podstawie ustala się
 * zmienne czyWiecejX/Y, żeby wiedzieć w jaką stronę ma się
 * kierować na dest.
 */

#ifndef MUCHA_H_
#define MUCHA_H_

#include "Latajace.h"

class Mucha: public Latajace {
public:
	Mucha(bool firstOne = false);
	~Mucha();

	// Aktualizacja procesów związanych z muchą
	void update(int mineloCzasu);
private:
	// Nadanie nowej pozycji docelowej (dest)
	void nadajCelLotu();

	// Minimalna i maksymalna wartość na ile może odfrunąć (pix)
	int min_odlot;
	int max_odlot;

	// Czy musi przekroczyć dodatnio (+1) czy ujemnie (-1) wartość w x/y
	int czyWiecejX, czyWiecejY;

	// Punkt docelowy lotu
	sf::Vector2f dest;

	// Aktulana prędkość (pix/s)
	float vel_x, vel_y;

	friend class Gra;
};

#endif /* MUCHA_H_ */
