/*
 * Scianka odnosi się do jednokolorowej sciany kamuflujacej. By ją stworzyć
 * należy podać położenie początkowe, wielkość i kolor (spośród zadeklarowanych
 * w typie wyliczeniowym KolorSciany).
 */

#ifndef SCIANKA_H_
#define SCIANKA_H_

#include "Obiekt.h"

enum KolorSciany {
	SCIANA_MORSKI, SCIANA_ZOLC, SCIANA_FIOLET,
};

class Scianka: public Obiekt {
public:
	Scianka(KolorSciany kolor, int x, int y, int w, int h);
	~Scianka(void);

	KolorSciany kolor;

	// Aktualizacja procesów związanych ze ścianką
	void update(int mineloCzasu);

	// Ustawienie 8 dodatkowych spritów postaci o przesunięcia z
	// kombinacji dł./szer. ekranu by mogły przechodzić przez krawędzie ekranu
	void updateWszystkieOdniesienia();

	// Przeładowanie dostępu do prostokąta z obiektem
	sf::FloatRect getGlobalBounds(unsigned int nr = 0) const;
	sf::FloatRect getPrevGlobalBounds(unsigned int nr = 0) const;

	// Przeładowanie metod dostępu do pozycji obiektu
	sf::Vector2f getPosition(unsigned int nr = 0) const;
	sf::Vector2f getPrevPosition(unsigned int nr = 0) const;

	// Wyświetlanie ścianki na ekranie
	void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
	//************* DANE DOTYCZĄCE WYGLĄDU I ANIMACJI *************
	// Głowny prostokąt będący ścianką + 8 odniesień do pozostałych pozycji
	sf::RectangleShape rect[9];

	//******************* DANE DOTYCZĄCE FIZYKI *******************
	// Predkość ruchu w pix/s
	float predkosc_na_sek;

	friend class Gra;

};

#endif /* SCIANKA_H_ */
