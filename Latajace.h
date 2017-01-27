/* Latające obiekty, obecnie tylko Mucha. Jedyne cechy
 * jakie są zapisane w tej klasie to minimalna i maksymalna
 * prędkość lotu.
 */

#ifndef LATAJACE_H_
#define LATAJACE_H_

#include "Postac.h"

class Latajace : public Postac{
public:
	// Konstruktor, destruktor
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
