/* Obiekt czyli klasa abstrakcyjna, stworzona dla wszystkich obiektów
 * silnika gry, stworzona po to by np. móc rozpatrywać kolizje między
 * dwoma obiektami.
 */

#ifndef OBIEKT_H_
#define OBIEKT_H_

#include <SFML/Graphics.hpp>

class Obiekt: public sf::Drawable {
public:
	Obiekt();
	virtual ~Obiekt();

	// Przeładowanie dostępu do prostokąta wyznaczającego krawędzie
	virtual sf::FloatRect getGlobalBounds(unsigned int nr = 0) const = 0;
	virtual sf::FloatRect getPrevGlobalBounds(unsigned int nr = 0) const = 0;

	// Przeładowanie dostępu do pozycji
	virtual sf::Vector2f getPosition(unsigned int nr = 0) const = 0;
	virtual sf::Vector2f getPrevPosition(unsigned int nr = 0) const = 0;

	// Przeładowanie metody wyświetlania
	virtual void draw(sf::RenderTarget &target,
			sf::RenderStates states) const = 0;

	// Tolerancja ma informować ile pikseli od brzegu prostokątu z obiektem
	// nie będzie powodować kolizji.
	int tolerancja_lp; // lewo/prawo
	int tolerancja_top;
	int tolerancja_bot;
};

#endif /* OBIEKT_H_ */
