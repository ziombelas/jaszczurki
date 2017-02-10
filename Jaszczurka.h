/*
 * Jaszczurka, od której dziedziczona jest klasa Gracz.
 * Potrafi kamuflować się i atakować, gdzie siła ataku
 * zależy od czasu jego ładowania.
 */

#ifndef JASZCZURKA_H_
#define JASZCZURKA_H_

#include <iostream>

#include "Ladowe.h"
#include "Scianka.h"

class Jaszczurka: public Ladowe {
public:
	Jaszczurka();
	virtual ~Jaszczurka();

	// Aktualizacja procesów związanych z jaszczurką
	void update(int mineloCzasu);
protected:
	//***************** DANE DOTYCZĄCE ATAKOWANIA ****************
	enum FazaAtaku {
		NIEATAKUJE, LADUJE, ATAKUJE,
	};
	FazaAtaku fazaAtaku;

	float naladowanieAtk;

	// Czas, który upłynął od rozpoczęcia ładowania ataku
	sf::Clock czasLadowaniaAtk;

	//*************** DANE DOTYCZĄCE KAMUFLOWANIA ***************
	enum FazaKamuflazu {
		NIEKAMUFLUJE, KAMUFLUJE, ZAKAMUFLOWANY
	};
	// Aktualna faza kamuflażu
	FazaKamuflazu faza_kamuflazu;

	// Kolor, na który odbywa się kamuflaż
	KolorSciany kamuflowany_kolor;

	// Czas, który upłynął od stanięcia w bezruchu
	sf::Clock czas_kamuflowania;

	// Do zaznacznenia czy znajduje się cały w ściance
	bool mozeKamuflowac;

	// Tu odbywa się zmiana koloru (transparentości) w
	// zależności od czasu kamuflowania
	void kamufluj();

	friend class Gra;
};

#endif /* JASZCZURKA_H_ */
