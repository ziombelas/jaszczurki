/*
 * Input, za pomocą którego porusza się gracz, może być to pad
 * o id 0-4 (nr pada), bądź klawiatura, gdzie id = 0 oznacza strzałki,
 * a id = 1 oznacza wsad.
 */

#ifndef INPUT_H_
#define INPUT_H_

#include <SFML/Graphics.hpp>

enum ktoryKlawisz {
	// Dotyczą akcji w grze
	ster_lewo,
	ster_prawo,
	ster_dol,
	ster_skok,
	ster_atak,

	// Dotyczą dołączania do gry
	ster_akceptuj,
	ster_esc,
	ster_menu_lewo,
	ster_menu_prawo,
};

class Input {
public:
	enum jakiInput {
		KLAWA, PAD
	};

	// Przyjaźń z PoleDolacz, aby mógł używać jakPoruszacSprite
	friend class PoleDolacz;

	Input(jakiInput input, int id, sf::Event & event);

	bool isPressed(ktoryKlawisz);
	void update();

	int getId();
	jakiInput getRodzajInputu();

	Input  & operator=(const Input  & stary);
private:
	jakiInput rodzajInputu;
	int id;

	/* KLAWIATURA */
	// Klawisze dołączania do gry
	// (strzałki bez zmian).
	sf::Keyboard::Key KL_akceptuj;
	sf::Keyboard::Key KL_esc;

	// Klawisze do każdej akcji w grze
	sf::Keyboard::Key KL_lewo;
	sf::Keyboard::Key KL_prawo;
	sf::Keyboard::Key KL_dol;
	sf::Keyboard::Key KL_skok;
	sf::Keyboard::Key KL_atak;

	/* PAD */
	// Suma przesunięć gałki lewo/prawo zapisana po to tak
	// aby przewijać np. w menu przy osiąganiu -650/650
	float przesuniecieGalki;

	// Tekstury jak sterować
	sf::Texture jakPoruszacPad;
	sf::Texture jakPoruszacKlawa1;
	sf::Texture jakPoruszacKlawa2;

	// Sprite pod odpowiedni z powyższych
	sf::Sprite jakPoruszacSprite;

	sf::Event * event;

};

#endif
