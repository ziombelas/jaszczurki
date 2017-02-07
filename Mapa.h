/*
 * Mapa to wirtualna klasa zawierająca wektory dynamicznie
 * tworzonych elementów mapy : scianek, terenów oraz informacje
 * o początkowych pozycjach respawnu oraz tło
 */

#ifndef MAPA_H_
#define MAPA_H_

#include "Teren.h"
#include "Scianka.h"

class Mapa {
public:
	Mapa();
	virtual ~Mapa();
protected:
	// ********************* ELEMENTY MAPY ******************
	std::vector<Scianka*> scianka;
	std::vector<Teren*> teren;
	std::vector<sf::Vector2f> respPos;

	// ********************* ELEMENTY GRAFICZNE ******************
	sf::Texture tlo_texture;

private:
	friend class Gra;
};

#endif /* MAPA_H_ */
