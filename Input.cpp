/*
 * Input, za pomocą którego porusza się gracz, może być to pad
 * o id 0-4 (nr pada), bądź klawiatura, gdzie id = 0 oznacza strzałki,
 * a id = 1 oznacza wsad.
 */

#include "Input.h"

//Input::Input() {
//	event = NULL;
////	KL_atak = NULL;
//}

int Input::getId() {
	return id;
}
Input::jakiInput Input::getRodzajInputu() {
	return rodzajInputu;
}

Input::Input(jakiInput jaki, int id, sf::Event & event) {
	this->event = &event;

	rodzajInputu = jaki;
	this->id = id;

	jakPoruszacPad.loadFromFile("data/xbox.png");
	jakPoruszacKlawa1.loadFromFile("data/klawa1.png");
	jakPoruszacKlawa2.loadFromFile("data/klawa2.png");

	switch (jaki) {
	case KLAWA: {
		if (id == 0) {
			KL_lewo = sf::Keyboard::Left;
			KL_prawo = sf::Keyboard::Right;
			KL_dol = sf::Keyboard::Down;
			KL_skok = sf::Keyboard::Up;
			KL_atak = sf::Keyboard::RControl;
			KL_akceptuj = sf::Keyboard::Return;
			KL_esc = sf::Keyboard::Escape;

			jakPoruszacSprite.setTexture(jakPoruszacKlawa1);
		} else if (id == 1) {
			KL_lewo = sf::Keyboard::A;
			KL_prawo = sf::Keyboard::D;
			KL_dol = sf::Keyboard::S;
			KL_skok = sf::Keyboard::W;
			KL_atak = sf::Keyboard::H;
			KL_akceptuj = sf::Keyboard::H;
			KL_esc = sf::Keyboard::Escape;

			jakPoruszacSprite.setTexture(jakPoruszacKlawa2);
		}
	}
		break;
	case PAD: {
		// Każdy pad ma to samo sterowanie wieć nie muszę
		// przypisywać klawiszy odpowiedzialnych za poszczególne funkcje
		// tylko używa ich stałych nazw przycisw isPressed

		przesuniecieGalki = 0;
		jakPoruszacSprite.setTexture(jakPoruszacPad);
	}
		break;
	}

}

bool Input::isPressed(ktoryKlawisz jaki) {
	// DOTYCZY STEROWANIA KLAWIATURĄ
	if (rodzajInputu == KLAWA) {
		switch (jaki) {
		case ster_lewo: {
			if (sf::Keyboard::isKeyPressed(KL_lewo))
				return true;
		}
			break;
		case ster_prawo: {
			if (sf::Keyboard::isKeyPressed(KL_prawo))
				return true;
		}
			break;
		case ster_dol: {
			if (sf::Keyboard::isKeyPressed(KL_dol))
				return true;
		}
			break;
		case ster_skok: {
			if (sf::Keyboard::isKeyPressed(KL_skok))
				return true;
		}
			break;
		case ster_atak: {
			if (sf::Keyboard::isKeyPressed(KL_atak))
				return true;
		}
			break;
		case ster_akceptuj: {
			if ((sf::Keyboard::isKeyPressed(KL_akceptuj)
					|| sf::Keyboard::isKeyPressed(KL_atak)))
				return true;
		}
			break;
		case ster_esc: {
			if (sf::Keyboard::isKeyPressed(KL_esc)
					|| event->type == sf::Event::Closed)
				return true;
		}
			break;
		case ster_menu_lewo: {
			if (sf::Keyboard::isKeyPressed(KL_lewo))
				return true;
		}
			break;
		case ster_menu_prawo: {
			if (sf::Keyboard::isKeyPressed(KL_prawo))
				return true;
		}
			break;
		}
		// DOTYCZY STEROWANIA PADEM
	} else if (rodzajInputu == PAD) {
		switch (jaki) {
		case ster_lewo: {
			if (sf::Joystick::getAxisPosition(id, sf::Joystick::X) < -50)
				return true;
		}
			break;
		case ster_prawo: {
			if (sf::Joystick::getAxisPosition(id, sf::Joystick::X) > 50)
				return true;
		}
			break;
		case ster_dol: {
			if (sf::Joystick::getAxisPosition(id, sf::Joystick::Y) > 50)
				return true;
		}
			break;
		case ster_skok: {
			if (sf::Joystick::isButtonPressed(id, 0))
				return true;
		}
			break;
		case ster_atak: {
			if (sf::Joystick::isButtonPressed(id, 2))
				return true;
		}
			break;
		case ster_akceptuj: {
			if (sf::Joystick::isButtonPressed(id, 0))
				return true;
		}
			break;
		case ster_esc: {
			if (sf::Joystick::isButtonPressed(id, 5))
				return true;
		}
			break;
		case ster_menu_lewo: {
			if (przesuniecieGalki <= -650) {
				przesuniecieGalki = 0;
				return true;
			}
		}
			break;
		case ster_menu_prawo: {
			if (przesuniecieGalki >= 650) {
				przesuniecieGalki = 0;
				return true;
			}
		}
			break;
		}
	}

	return false;
}

void Input::update() {
	// Aktualizacja sumy przesunię gałki w osi x
	if (sf::Joystick::getAxisPosition(id, sf::Joystick::X) > 27
			|| sf::Joystick::getAxisPosition(id, sf::Joystick::X) < -27)
		przesuniecieGalki += sf::Joystick::getAxisPosition(id, sf::Joystick::X);

	// Resetowanie, jeżeli gałka wróciła do środka
	if (sf::Joystick::getAxisPosition(id, sf::Joystick::X) <= 27
			&& sf::Joystick::getAxisPosition(id, sf::Joystick::X) >= -27)
		przesuniecieGalki = 0;
}

Input & Input::operator=(const Input & stary) {
	id = stary.id;
	rodzajInputu = stary.rodzajInputu;

	KL_akceptuj = stary.KL_akceptuj;
	KL_esc = stary.KL_esc;
	KL_lewo= stary.KL_lewo;
	KL_prawo= stary.KL_prawo;
	KL_dol = stary.KL_dol;
	KL_skok = stary.KL_skok;
	KL_atak = stary.KL_atak;

	przesuniecieGalki = stary.przesuniecieGalki;
	event = stary.event;

	return *this;
}
