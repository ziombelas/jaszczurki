/*
 * Ustawieniają tak naprawdę tylko pojemnik na grających, gdzie zbierane
 * są informacje o sposobie ich sterowania oraz np. punktach.
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <string.h>
#include <vector>

#include "Grajacy.h"

enum ProgramState {
	MENU, ROZGRYWKA, EKRAN_WYBORU, PROGRAM_END
};

class Settings {
public:
	Settings();
	~Settings();

private:
	std::vector<Grajacy*> grajacy;

	friend class EkranWyboru;
	friend class Gra;
	friend class Program;
};

#endif
