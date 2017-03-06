#include "Ustawienia.h"

Ustawienia::Ustawienia() {
}

Ustawienia::~Ustawienia() {
	for (int unsigned i = 0; i < grajacy.size(); i++)
		delete grajacy[i];
}
