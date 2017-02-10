/*
 * Teren czyli wszystkie płytki i windy, czyli coś co na czym jaszczurka
 * będzie sobie spoczywać. Ma wymiar x/y elementów. Może być
 * przenikalna, bądź nie i wówczas natępują kolizja od góry terenu.
 */

#ifndef TEREN_H_
#define TEREN_H_

#include "Obiekt.h"

enum RodzajTerenu {
	PLYTKA, BLOK, WINDA,
};

class Teren: public Obiekt {
public:
	// Konstruktor z częściami terenu wymagającymi innego sprite'u z lewej/prawej
	Teren(RodzajTerenu rodzaj, int dlugosc, int wysokosc, int x, int y,
			int specjalne = 0);

	// Konstruktor dla windy, należy podać prędkość i punkty A, B
	Teren(RodzajTerenu rodzaj, int dlugosc, int ax, int ay, int bx, int by,
			float vel);

	~Teren(void);

	// Aktualizacja procesów związanych z terenm
	void update(int mineloCzasu);

	// Pobranie aktualnej prędkości
	sf::Vector2f getVelocity() const;

	// Pozycja terenu w tej klatce i poprzedniej
	sf::Vector2f getPosition(unsigned int nr = 0) const;
	sf::Vector2f getPrevPosition(unsigned int nr = 0) const;

	// Prostokąt, w którym jest teren teraz, jak i klatkę temu
	sf::FloatRect getGlobalBounds(unsigned int nr = 0) const;
	sf::FloatRect getPrevGlobalBounds(unsigned int nr = 0) const;

	// Przeładowanie metody wyświetlania
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
private:
	//************* DANE DOTYCZĄCE WYGLĄDU I ANIMACJI *************
	// Tekstury terenu w dla różnych krawędzi
	sf::Texture teren_texture;
	sf::Texture teren_textureL;
	sf::Texture teren_textureP;
	sf::Texture teren_textureS;
	sf::Texture teren_textureSL;
	sf::Texture teren_textureSP;

	sf::Sprite sprite;
	sf::Sprite spriteL;
	sf::Sprite spriteP;
	sf::Sprite spriteS;
	sf::Sprite spriteSL;
	sf::Sprite spriteSP;

	//*********************** CECHY FIZYCZNE ***********************
	// Ilość kawałków w poziomie i pionie, z których składa się teren
	int dlugosc, wysokosc;

	// Czy mozna przechodzić przez niego góra/dół
	bool przenikalnosc;

	// Prędkość poruszania się (domyślnie 0)
	sf::Vector2f velocity;

	// Punkty A i B, dotyczą wind
	sf::Vector2f punktA, punktB;

	// ************************ POZOSTAŁE *************************
	// Poprzednia pozycja
	sf::Vector2f prevPosition[9];

	friend class Gra;
};

#endif /* TEREN_H_ */
