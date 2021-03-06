#include "Ladowe.h"

Ladowe::Ladowe(int arg_ilosc_tekstur, float arg_klatki_na_sek,
		float arg_vel_ruch_const, float arg_vel_skok_const) :
		Postac(arg_ilosc_tekstur, arg_klatki_na_sek), vel_ruch_const(
				arg_vel_ruch_const), vel_skok_const(arg_vel_skok_const) {
	skacze = false;

	acc_grawitacja = 1940;
	min_vel_grawitacja = 0;
	max_vel_grawitacja = 2500;

	vel_grawitacja = 0;
	vel_atak = 0;
	vel_ruch = 0;
	vel_skok = 0;

	maPodloze = false;
	terenSpoczynku = NULL;

	lotnosc = false;
}

Ladowe::~Ladowe() {
}

void Ladowe::update(int mineloCzasu) {
	//********************** SPADEK W DÓŁ **********************
	if (maPodloze)
		vel_grawitacja = min_vel_grawitacja;
	else {
		// Przyrost prędkości spadku
		if (!lotnosc)
			vel_grawitacja += acc_grawitacja * (mineloCzasu / 1000.0);
		if (vel_grawitacja > max_vel_grawitacja)
			vel_grawitacja = max_vel_grawitacja;
	}

	// Uwzględnienie wartości przyśpiesznia tylko gdy nie spada
	if (maPodloze) {
		move_y += (vel_y() - vel_grawitacja) * (mineloCzasu / 1000.0);
	} else {
		if (!lotnosc)
			move_y += vel_y() * (mineloCzasu / 1000.0);
		else
			move_y += (vel_y() - vel_grawitacja) * (mineloCzasu / 1000.0);
	}

	//*************** PORUSZANIE SIĘ RAZEM Z TERENEM ***************
	if (terenSpoczynku) {
		if (move_x == 0)
			move_x += terenSpoczynku->getVelocity().x * (mineloCzasu / 1000.0);
		move_y += terenSpoczynku->getVelocity().y * (mineloCzasu / 1000.0);
	}

	// *********** UPDATE Z KLASY PODSTAWOWEJ ***********
	Postac::update(mineloCzasu);

}
