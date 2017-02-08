/*
 * Imię - ciąg znaków plus informacja o płci gracza.
 */

#ifndef IMIE_H_
#define IMIE_H_

#include <string.h>
#include <SFML/Graphics.hpp>

enum jakaPlec {
	FACET, BABKA
};

class Imie {
public:
	Imie();
	~Imie();

	Imie(const wchar_t *imie, jakaPlec plec);

	wchar_t *get_c_str();
	jakaPlec getPlec();

	// Przełowanie operatora przypisania dla imion
	Imie & operator=(const Imie & stare);
private:
	// Imię gracza
	wchar_t imie[16];

	jakaPlec plec;
};

#endif /* IMIE_H_ */
