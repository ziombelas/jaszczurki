/*
 * Gra jest rozgrywającą się sceną czyli zbiorem wszystkich postaci,
 * terenów i innych obiektów i procedur, która wiążą relacjami między
 * tymi obiektami.
 */

#ifndef GRA_H_
#define GRA_H_

#include <vector>
#include <string>

#include "Gracz.h"
#include "Mucha.h"
#include "Mapa1.h"
#include "Punkty.h"
#include "Ustawienia.h"

class Gra {
public:
	enum Etap {
		ODLICZANIE_DO_STARTU, KONIEC_RUNDY, CIAGLE_GRAMY
	};

	Gra(sf::RenderWindow &window, Ustawienia *ustawienia, ProgramState *state,
			int runda);
	~Gra();

	// Uruchomienie pętli głównej wewnątrz Gra
	void run();

	void update();
	void wyswietl();
private:
	//******************* ELEMENTY GRY *********************
	// Gracze
	std::vector<Gracz*> gracz;

	// Muchy
	std::vector<Mucha*> mucha;

	// Lecące punkty z wynikiem +x
	std::vector<Punkty*> punkty;

	// Tablice na górze ekranu na których pokazywany jest wynik graczy
	TablicaNaWynik *tablicaNaWynik[4];

	wchar_t *winner;

	Etap etap;
	sf::Clock czasKonca;

	sf::Sprite tlo;

	// Czicionka do wyświetlenia odliczania do startu lubinfo o winie
	sf::Font font;

	sf::Text napisStart;
	sf::Text koniecText;

	// Napis RUNDA x, który wjeżdza zawsze na początku
	sf::Text napisRunda;

	// Stoper mierzący czas między kolejnymi klatkami gry
	sf::Clock delta;

	// Zapisane wartości z powyższego po narysowaniu
	int mineloCzasu;

	// Stoper mierzący czas od uruchomienia gry aż do startu
	sf::Clock startTimer;

	// -----------------  POBIERANE Z MAPY -----------------
	// Procedura pobrania poniższych elementów z mapy
	void pobierzMape(Mapa & mapa);

	// Tereny gry
	std::vector<Teren*> teren;

	// Ściany kamuflujące jaszczurki
	std::vector<Scianka*> scianka;

	// 4 Pozycje respawnu
	std::vector<sf::Vector2f> respPos;

	// Tło mapy
	sf::Texture tlo_texture;

	//*************** PROCEDURY DLA OBIEKTÓW GRY ****************
	// Procedura zarządzająca w całości kamuflażem
	void updateKamuflaz(Jaszczurka & jaszczurka);

	// Sprawdza czy ścianka w całości pokrywa gracza
	void probaKamuflazu(Jaszczurka & jaszczurka, Scianka & scianka);

	// Kolizje z terenem od każdej z 4 stron
	void kolizjePostacTeren(Gracz & player, Teren & teren);

	// Kolizje postaci z drugą postacią
	void kolizjePostacPostac(Gracz & p1, Gracz & p2);

	// Kolizje postaci i muchy
	void kolizjePostacMucha(Gracz & gracz, Mucha & mucha);

	// Aktualizacja much
	void updateMuch(Mucha & mucha);

	//----------- FUNKCJE POMOCNICZE KOLIZJI 2 OBIEKTÓW -----------
	bool kol_ogolnie(Obiekt &ob1, int nr, Obiekt & ob2);
	bool kol_calkowita(Obiekt &ob1, int nr, Obiekt & ob2, int nr2 = 0);
	bool kol_dol_do_gory(Obiekt & ob1, int nr, Obiekt & ob2);
	bool kol_gora_do_dolu(Obiekt & ob1, int nr, Obiekt & ob2);
	bool kol_prawa_do_lewej(Obiekt & ob1, int nr, Obiekt & ob2);
	bool kol_lewa_do_prawej(Obiekt & ob1, int nr, Obiekt & ob2);
	bool kol_os_x(Obiekt & ob1, int nr, Obiekt & ob2);
	bool kol_os_y(Obiekt & ob1, int nr, Obiekt & ob2);

	// Powiązanie tablicy na wynik z graczem
	void powiazGraczaZTablica(Grajacy *grajacy, TablicaNaWynik *tablica);

	// Wektor przesunięcia o kombinacje dł./szer. ekranu
	inline sf::Vector2f pozycjaWzgledemAllSprites(unsigned int nr = 0) {
		switch (nr) {
		case 0:
			return sf::Vector2f(0, 0);
		case 1:
			return sf::Vector2f(1920, 0);
		case 2:
			return sf::Vector2f(-1920, 0);
		case 3:
			return sf::Vector2f(0, 990);
		case 4:
			return sf::Vector2f(0, -990);
		case 5:
			return sf::Vector2f(1920, 990);
		case 6:
			return sf::Vector2f(-1920, 990);
		case 7:
			return sf::Vector2f(1920, -990);
		case 8:
			return sf::Vector2f(-1920, -990);
		}
	}

	//***************** DOTYCZY PĘTLI PROGRAMU ****************
	bool exit;
	ProgramState *state;
	int runda;

	//**************** POTRZEBNE DLA DZIAŁANIA SFML *************
	sf::RenderWindow *window;
	sf::Event event;
};

#endif /* GRA_H_ */
