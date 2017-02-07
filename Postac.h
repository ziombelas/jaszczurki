/*
 * Każda postać w grze. W konstruktorze należy podać ilość klatek oraz tempo
 * w jakim następować ma ich animacja.
 */

#ifndef POSTAC_H_
#define POSTAC_H_

#include <cmath>

#include "Obiekt.h"

class Postac: public Obiekt {
public:
	Postac(int arg_ilosc_tekstur, float arg_klatki_na_sek);
	virtual ~Postac();

	enum Status {
		ZYJE, UMIERA, UMIERAJACY, POZAMIATANY,
	};

	// Aktualizacja procesów związanych z postacią
	void update(int mineloCzasu);

	// Ustawienie 8 dodatkowych spritów postaci o przesunięcia z
	// kombinacji dł./szer. ekranu by mogły przechodzić przez krawędzie ekranu
	void updateWszystkieOdniesienia();

	// Zarządzanie animacją postaci
	void playAnimation(int mineloCzasu);

	// Pozycja gracz w tej klatce i poprzedniej/następnej
	sf::Vector2f getPosition(unsigned int nr = 0) const;
	sf::Vector2f getPrevPosition(unsigned int nr = 0) const;
	sf::Vector2f getNextPosition() const;
	sf::Vector2f pozycjaWzgledemMonitora() const;

	// Prostokąt, w którym jest gracz teraz, jak i klatkę temu
	virtual sf::FloatRect getGlobalBounds(unsigned int nr = 0) const;
	virtual sf::FloatRect getPrevGlobalBounds(unsigned int nr = 0) const;

	// Wyświetlanie postaci na ekranie
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
protected:
	// **************************** OGÓLNE  ************************
	// Status, czyli np. czy postać żyje
	Status status;

	// Pozycja początkowa postaci
	sf::Vector2f respPos;

	//********************* STEROWANIE POSTACIĄ ********************
	// Wcisnięte klawisze - były czy nie?
	bool PRESSED[5];

	// Pomocnicze stałe jako elementy powyższej tablicy
	enum {
		lewo, prawo, dol, skok, atak
	};

	//************* DANE DOTYCZĄCE WYGLĄDU I ANIMACJI *************
	// Tekstury postaci załadowane z dysku
	const int ilosc_tekstur;

	// Ilość klatek na sekundę w animacji
	const float klatki_na_sek;

	// Tekstury postaci
	sf::Texture tekstura_postaci[50];

	// Sprite reprezentujący postać + odniesienia względem pozycji ekranu w
	// dodatkowych ośmiu
	sf::Sprite sprite[9];

	// Nr klatki w zmiennej float, rzut na jej wartość całkowitą określi klatkę
	float frame;

	//******************* DANE DOTYCZĄCE FIZYKI *******************
	// Przesunięcie - wypadkowa prędkość × czas
	float move_x, move_y;

	// Prędkość z odepchnięcia (pix/s)
	float vel_odpych_x, vel_odpych_y;

	// ************************ POZOSTAŁE *************************
	// Poprzednia pozycja
	sf::Vector2f prevPosition[9];

};

#endif /* POSTAC_H_ */
