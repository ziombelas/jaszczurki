/* Jest to pole, które pojawia się w ekranie wyboru po tym
 * jak dołączy któryś z graczy. Wybiera się imię, kolor i czcionkę.
 */

#ifndef POLEDOLACZ_H_
#define POLEDOLACZ_H_

#include "Input.h"
#include "Imie.h"

class PoleDolacz: public sf::Drawable {
public:
	PoleDolacz(int x, int y, Input *input);
	~PoleDolacz();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const;

	void poprzednieImie();
	void nastepneImie();

	bool wybranoImie();
	bool wybranoKolor();

private:
	//**************** ELEMENTY POLA DOLACZANIA *****************
	sf::RectangleShape rect;

	sf::Sprite jakPoruszacSprite;

	// Czcionki na imię i strzałki do zmiany ◀ imienia ▶
	sf::Font font, fontArrows;

	sf::Text wyswietlaneImie;
	sf::Text textArrows;

	//************** DOTYCZY WYBORU IMIENIA**************
	std::vector<Imie*> imie;

	int nr_imiona, nr_koloru;

	bool gotowy;

	// Urządzenia wejścia, którym steruje gracz
	Input *input;

	void update();

	friend class EkranWyboru;
};

#endif /* POLEDOLACZ_H_ */
