/*
 * Mapa.h
 *
 *  Created on: 11-10-2016
 *      Author: maks
 */

#ifndef MAPA_H_
#define MAPA_H_

#include "Teren.h"
#include "Scianka.h"

class Mapa {
public:
	Mapa();
	~Mapa();
protected:
	std::vector<Scianka*> scianka;
	std::vector<Teren*> teren;
	std::vector<sf::Vector2f> respPos;

	sf::Texture tlo_texture;

private:
	friend class Gra;
};

#endif /* MAPA_H_ */
