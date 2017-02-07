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
	case STYKU: {
		strcpy(imie, "Styku");
		plec = FACET;
	}
		break;
	case TOSIA: {
		strcpy(imie, "Tosia");
		plec = BABKA;
	}
		break;
	case PIOTREK: {
		strcpy(imie, "Piotrek");
		plec = FACET;
	}
		break;
	case SAMANTA: {
		strcpy(imie, "Samanta");
		plec = BABKA;
	}
		break;
	case BIALY: {
		strcpy(imie, "Bialy");
		plec = FACET;
	}
		break;
	case KASIA: {
		strcpy(imie, "Kasia");
		plec = BABKA;
	}
		break;
	case MATEUSZ: {
		strcpy(imie, "Mateusz");
		plec = FACET;
	}
		break;
	case SUM: {
		strcpy(imie, "Sum");
		plec = FACET;
	}
		break;
	case DANIELA: {
		strcpy(imie, "Daniela");
		plec = BABKA;
	}
		break;
	case MIKSER: {
		strcpy(imie, "Mikser");
		plec = FACET;
	}
		break;
	case EDDIE: {
		strcpy(imie, "Eddie");
		plec = FACET;
	}
		break;
	case DOMSON: {
		strcpy(imie, "Domson");
		plec = FACET;
	}
		break;
	}
}

char *Imie::get_c_str() {
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
