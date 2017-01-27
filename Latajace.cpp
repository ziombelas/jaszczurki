/*
 * Latajace.cpp
 *
 *  Created on: 24-09-2016
 *      Author: maks
 */

#include "Latajace.h"

Latajace::Latajace(int arg_ilosc_tekstur, float arg_klatki_na_sek, float arg_vel_lotu_min,
		float arg_vel_lotu_max) :
		Postac(arg_ilosc_tekstur, arg_klatki_na_sek), vel_lotu_min(arg_vel_lotu_min), vel_lotu_max(
				arg_vel_lotu_max) {

}

Latajace::~Latajace() {
}

void Latajace::update(int mineloCzasu) {
	// *********** UPDATE Z KLASY PODSTAWOWEJ  ***********
	Postac::update(mineloCzasu);
}

