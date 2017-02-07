/*
 * Grajacy - osoba która dołączyła do gry i liczone będą jej punkty.
 *
 * Poza punktami cechuje ją posiadanie imienia oraz sposób poruszania
 * się (input).
 *
 * Zawiera wskaźnik do tablicy na wynik, który jest wzajemnie powiązany
 * ze wskaźnikiem do grającego (po to deklaracja TablicyNaWynik).
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
	Input & getInput();
	int getWynik();

	void zwiekszWynik(int ile);

	TablicaNaWynik *tablicaNaWynik;
private:
	Imie imie;
	int wynik;
	Input *input;
};

#endif /* GRAJACY_H_ */
