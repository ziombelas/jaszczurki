#include "Grajacy.h"

Grajacy::Grajacy(Input input, Imie imie) {
	this->input = new Input(input);
	this->imie = imie;
	wynik = 0;
	tablicaNaWynik = NULL;
}

Grajacy::~Grajacy() {
	delete input;
}

Imie & Grajacy::getImie() {
	return imie;
}

int Grajacy::getWynik() {
	return wynik;
}

void Grajacy::zwiekszWynik(int ile)
{
	wynik += ile;
}
