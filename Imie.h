/*
 * Imię, poza nazwą gracza reprezentuje jego kolor (drużynę),
 * jak i również teksty będące np. rekacją na wygraną konretnego gracza.
 */

#ifndef IMIE_H_
#define IMIE_H_

#include <string.h>
#include <SFML/Graphics.hpp>

enum jakieImie {
	BRAK, MAKS, SZYMON, JUREK, WOJTEK, MACIEK, WERA,
};
enum jakaPlec {
	FACET, BABKA
};

class Imie {
public:
	Imie();
	~Imie();

	Imie(jakieImie jakie);

	char * get_c_str();
	jakaPlec getPlec();

	// Przełowanie operatora przypisania dla imion
	Imie & operator=(const Imie & stare);
private:
	// Imię gracza
	char imie[16];

	jakaPlec plec;
};

#endif /* IMIE_H_ */
