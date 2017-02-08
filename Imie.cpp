#include "Imie.h"

Imie::Imie() {
//	plec = FACET;
}

Imie::~Imie() {
}

Imie::Imie(const wchar_t *imie, jakaPlec plec) {
	this->plec = plec;
	wcscpy(this->imie, imie);
}

wchar_t *Imie::get_c_str() {
	return imie;
}

jakaPlec Imie::getPlec() {
	return plec;
}

Imie & Imie::operator=(const Imie & stare) {
	// Skopiowanie imienia
	wcscpy(imie, stare.imie);
	// Skopiowanie płci
	plec = stare.plec;

	return *this;
}
