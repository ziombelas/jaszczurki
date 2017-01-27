/* Grajacy - osoba która dołączyła do gry i liczone będą jej punkty.
 * Poza punktami cechuje ją imię oraz sposób poruszania się (input)
 */

#ifndef GRAJACY_H_
#define GRAJACY_H_

#include "Input.h"
#include "Imie.h"

class TablicaNaWynik;

class Grajacy {
public:
	Grajacy(Input input, Imie imie);
	~Grajacy();

	Imie & getImie();
	int getWynik();

	void zwiekszWynik(int ile);
private:
	Imie imie;
	int wynik;
	Input * input;

	TablicaNaWynik * tablicaNaWynik;

	friend class Gracz;
	friend class Gra;
};

#endif /* GRAJACY_H_ */
