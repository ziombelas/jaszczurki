#include "Grajacy.h"

Grajacy::Grajacy(Input input, Imie imie) {
	this->input = new Input(input);
	this->imie = imie;
	wynik = 0;
	upolowaneMuchy = 0;
	upolowaneJaszczurki = 0;
	tablicaNaWynik = NULL;
}

Grajacy::~Grajacy() {
	delete input;
}

Imie & Grajacy::getImie() {
	return imie;
}

Input & Grajacy::getInput() {
	return *input;
}

int Grajacy::getWynik() {
	return wynik;
}

int Grajacy::getUpolowaneMuchy() {
	return upolowaneMuchy;
}

int Grajacy::getUpolowaneJaszczurki() {
	return upolowaneJaszczurki;
}

void Grajacy::zwiekszWynik(int ile) {
	wynik += ile;
}

void Grajacy::upolowalMuche() {
	upolowaneMuchy++;
}

void Grajacy::upolowalJaszczurke() {
	upolowaneJaszczurki++;
}
