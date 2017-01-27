#include "Imie.h"

Imie::Imie() {
	plec = FACET;
}

Imie::~Imie() {
}

Imie::Imie(jakieImie jakie) {
	switch (jakie) {
	case BRAK: {
		strcpy(imie, "imie");
		plec = FACET;
	}
		break;
	case MAKS: {
		strcpy(imie, "Maks");
		plec = FACET;
	}
		break;
	case SZYMON: {
		strcpy(imie, "Szymon");
		plec = FACET;
	}
		break;
	case JUREK: {
		strcpy(imie, "Jurek");
		plec = FACET;
	}
		break;
	case WOJTEK: {
		strcpy(imie, "Wojtek");
		plec = FACET;
	}
		break;
	case MACIEK: {
		strcpy(imie, "Maciek");
		plec = FACET;
	}
		break;
	case WERA: {
		strcpy(imie, "Wera");
		plec = BABKA;
	}
		break;
	}
}

char * Imie::get_c_str() {
	return imie;
}

jakaPlec Imie::getPlec() {
	return plec;
}

Imie & Imie::operator=(const Imie & stare) {
	// Skopiowanie imienia
	strcpy(imie, stare.imie);
	// Skopiowanie płci
	plec = stare.plec;

	return *this;
}
