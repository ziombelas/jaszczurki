/* Jest to pole, które pojawia się w ekranie wyboru po tym
 * jak dołączy któryś z graczy przez wciśnięcie akceptacji.
 * Wybiera się tu imię.
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

	void update();
private:
	//************** ELEMENTY POLA DOŁĄCZ **************
	std::vector<Imie*> imie;

	unsigned int nr_imiona;

	bool gotowy;

	// Urządzenia wejścia, którym steruje gracz
	Input *input;

	//**************** ELEMENTY GRAFICZNE *****************
	sf::RectangleShape rect;

	sf::Sprite jakPoruszacSprite;

	// Czcionki na imię i strzałki do zmiany ◀ imienia ▶
	sf::Font font, fontArrows;

	sf::Text wyswietlaneImie;
	sf::Text textArrows;

	friend class EkranWyboru;
};

#endif /* POLEDOLACZ_H_ */
