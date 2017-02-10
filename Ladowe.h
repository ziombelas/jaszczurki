/*
 * Lądowe postacie, w tym momencie tylko Jaszczurka.
 * W konstruktorze należy podać stałe odpowiadające za prędkość poruszania
 * się i skoku (poza informacjami dla konstruktora Postaci).
 */

#ifndef LADOWE_H_
#define LADOWE_H_

#include "Postac.h"
#include "Teren.h"

class Ladowe: public Postac {
public:
	Ladowe(int arg_ilosc_tekstur, float arg_klatki_na_sek,
			float arg_vel_ruch_const, float arg_vel_skok_const);
	virtual ~Ladowe();

	// Aktualizacja procesów związanych z postacią
	void update(int mineloCzasu);
protected:
	//******************* DANE DOTYCZĄCE FIZYKI *******************
	// Stałe dla poruszania się (pix/s)
	const float vel_ruch_const;

	// Aktualna prędkość ruchu (pix/s)
	float vel_ruch;

	// Prędkość ataku (pix/s)
	float vel_atak;

	// Przyśpieszenie spadania (pix/s^2)
	double acc_grawitacja;

	// Prędkość spadania (pix/s)
	float vel_grawitacja;

	// Minimalna i maksymalna prędkość spadku
	float min_vel_grawitacja, max_vel_grawitacja;

	// Zwrot postaci, -1(←), bądź +1(→)
	int zwrot;

	// Czy spoczywa na gruncie
	bool maPodloze;

	// Teren, na którym aktualnie spoczywa
	Teren *terenSpoczynku;

	// Czy uzyskał lotność, która pozwala nie spadać
	bool lotnosc;

	// Wypadkowe dla poruszania się (pix/s)
	float vel_x() {
		return vel_ruch + vel_atak + vel_odpych_x;
	}
	float vel_y() {
		return vel_grawitacja + vel_skok + vel_odpych_y;
	}

	//-------- DOTYCZY SAMEGO SKAKANIA ------
	// Stała prędkość skoku, z którą wybija się w górę
	const float vel_skok_const;

	// Czy teraz skacze?
	bool skacze;

	// Aktualna prędkość skoku jaką posiada
	float vel_skok;

};

#endif /* LADOWE_H_ */
