/* Latające obiekty, obecnie tylko Mucha. Klasa ta nie jest obecnie rozbudowana,
 * jedyne cechy jakie posiada to pobrane z konstruktora stałe dotyczące minimalnej
 * i maksymalnej prędkości lotu (poza danymi w dotyczącymi konstruktora Postaci).
 */

#ifndef LATAJACE_H_
#define LATAJACE_H_

#include "Postac.h"

class Latajace : public Postac{
public:
	Latajace(int arg_ilosc_tekstur, float arg_klatki_na_sek, float arg_vel_lotu_min,
			float arg_vel_lotu_max);
	virtual ~Latajace();

	// Aktualizacja procesów związanych z postacią
	void update(int mineloCzasu);
protected:
	//******************* DANE DOTYCZĄCE FIZYKI *******************
	// Zakres osiąganych prędkości (pix/s)
	const int vel_lotu_min;
	const int vel_lotu_max;
};

#endif /* LATAJACE_H_ */
