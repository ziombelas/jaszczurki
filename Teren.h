/* Klasa dla wszystkich obiektów kontrolujących teren. Zbudowana
 * z poziomych zestawów płytek np. 8na1 albo 20na4. Może być
 * przenikalna, bądź nie i wówczas natępują kolizja od góry.
 *
 */

#ifndef TEREN_H_
#define TEREN_H_

#include "Obiekt.h"

class Game;

enum RodzajTerenu {
	PLYTKA, BLOK, WINDA,
};

class Teren: public Obiekt {
public:
	~Teren(void);

	// Konstruktor z częściami terenu wymagającymi innego sprite'u z lewej/prawej
	Teren(RodzajTerenu rodzaj, int dlugosc, int wysokosc, int x, int y,
			int specjalne = 0);

	// Konstruktor dla windy, należy podać prędkość i punkty A, B
	Teren(RodzajTerenu rodzaj, int dlugosc, int ax, int ay,
			int bx, int by, float vel);

	// Aktualizacja procesów związanych z terenm
	void update(int mineloCzasu);

	sf::Vector2f getPosition(unsigned int nr = 0) const;
	sf::Vector2f getPrevPosition(unsigned int nr = 0) const;

	// Przeładowanie obszaru, który jest terenem
	sf::FloatRect getGlobalBounds(unsigned int nr = 0) const;
	sf::FloatRect getPrevGlobalBounds(unsigned int nr = 0) const;

	// Przeładowanie metody wyświetlania
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	//************* DANE DOTYCZĄCE WYGLĄDU I ANIMACJI *************

	// Tekstury postaci załadowane z dysku
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
	// Ilość poziomych kawałków, z których składa się teren
	int dlugosc, wysokosc;

	// Czy mozna przechodzić przez niego góra/dół
	bool przenikalnosc;

	// Prędkość poruszania się (domyślnie 0)
	sf::Vector2f velocity;

	// Punkty A i B, dotyczą wind
	sf::Vector2f punktA, punktB;

	//******************* DANE DOTYCZĄCE FIZYKI *******************
	// Poprzednia pozycja
	sf::Vector2f prevPosition;

	friend class Gra;
};

#endif /* TEREN_H_ */
