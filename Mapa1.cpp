#include "Mapa1.h"

Mapa1::Mapa1() {
	// ********************* ELEMENTY GRAFICZNE ******************
	tlo_texture.loadFromFile("data/bg.png");

	//*************************** TERENY *************************
	teren.push_back(new Teren(BLOK, 8, 4, 0, 380, -1));

	teren.push_back(new Teren(BLOK, 8, 4, 1920 - 40 * 8, 380, 1));

	// Najwyzsze plytki
	teren.push_back(new Teren(PLYTKA, 10, 1, 500, 390 + 10));
	teren.push_back(new Teren(PLYTKA, 10, 1, 1920 - 500 - 20 * 10, 390 + 10));

	teren.push_back(new Teren(PLYTKA, 10, 1, 1920 / 2 - 5 * 20 - 10, 560 + 10));

	teren.push_back(new Teren(PLYTKA, 10, 1, 680, 475 + 10));
	teren.push_back(
			new Teren(PLYTKA, 10, 1, 1920 - 680 - 10 * 20 - 10, 475 + 10));

	// Teren wysoko
	teren.push_back(new Teren(BLOK, 8, 2, 1920 / 2 - 40 * 8 / 2, 220));

	teren.push_back(new Teren(BLOK, 20, 2, 1920 - 800, 1000, 1));

	teren.push_back(new Teren(BLOK, 20, 2, 0, 1000, -1));

	// Dolne długie płytki
	teren.push_back(new Teren(PLYTKA, 18, 1, 160, 730));
	teren.push_back(new Teren(PLYTKA, 18, 1, 1920 - 160 - 18 * 20, 730));

	// Długa pozioma linia
	teren.push_back(
			new Teren(PLYTKA, 30, 1, 1920 / 2 - 15 * 20, 645 + 10 + 10));

	// Dolny teren
	teren.push_back(new Teren(BLOK, 13, 2, 1920 / 2 - 13 * 40 / 2, 760));

	teren.push_back(
			new Teren(WINDA, 7, 300, 895, 1920 - 300 - 7 * 20, 895, 120));

	//******************* ŚCIANKI KAMUFLUJĄCE **********************
	scianka.push_back(
			new Scianka(SCIANA_MORSKI, 1920 / 3 * 0, 90, 1920 / 3, 1590));
	scianka.push_back(
			new Scianka(SCIANA_ZOLC, 1920 / 3 * 1, 90, 1920 / 3, 1590));
	scianka.push_back(
			new Scianka(SCIANA_FIOLET, 1920 / 3 * 2, 90, 1920 / 3, 1590));

	//******************** POZYCJE RESPAWNU ***********************
	respPos.push_back(sf::Vector2f(500 + 10 * 20 / 2, 230));
	respPos.push_back(sf::Vector2f(1920 - 500 - 20 * 10 + 10 * 20 / 2, 230));
	respPos.push_back(sf::Vector2f(200 + 20 * 20 / 2, 480));
	respPos.push_back(sf::Vector2f(1920 - 200 - 20 * 20 + 20 * 20 / 2, 480));
}

Mapa1::~Mapa1() {
}

