/*
 * Ustawieniają tak naprawdę tylko pojemnik na grających, gdzie zbierane
 * są informacje o sposobie ich sterowania oraz np. punktach.
 */

#ifndef USTAWIENIA_H_
#define USTAWIENIA_H_

#include <string.h>
#include <vector>

#include "Grajacy.h"

enum ProgramState {
	MENU, ROZGRYWKA, EKRAN_WYBORU, INSTRUKCJA, PROGRAM_END
};

class Ustawienia {
public:
	Ustawienia();
	~Ustawienia();

private:
	std::vector<Grajacy*> grajacy;

	friend class EkranWyboru;
	friend class Gra;
	friend class PodsumowanieWynikow;
	friend class Program;
};

#endif
