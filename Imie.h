/*
 * Imię - ciąg znaków plus informacja o płci gracza.
 */

#ifndef IMIE_H_
#define IMIE_H_

#include <string.h>
#include <SFML/Graphics.hpp>

enum jakieImie {
	BRAK,
	MAKS,
	SZYMON,
	JUREK,
	WOJTEK,
	MACIEK,
	WERA,
	STYKU,
	TOSIA,
	PIOTREK,
	SAMANTA,
	BIALY,
	KASIA,
	MATEUSZ,
	SUM,
	DANIELA,
	MIKSER,
	EDDIE,
	DOMSON,
};

enum jakaPlec {
	FACET, BABKA
};

class Imie {
public:
	Imie();
	~Imie();

	Imie(jakieImie jakie);

	char *get_c_str();
	jakaPlec getPlec();

	// Przełowanie operatora przypisania dla imion
	Imie & operator=(const Imie & stare);
private:
	// Imię gracza
	char imie[16];

	jakaPlec plec;
};

#endif /* IMIE_H_ */
