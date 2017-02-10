#include "Teren.h"

Teren::Teren(RodzajTerenu rodzaj, int dlugosc, int wysokosc, int x, int y,
		int specjalne) {
	velocity = sf::Vector2f(0, 0);

	this->dlugosc = dlugosc;
	this->wysokosc = wysokosc;

	switch (rodzaj) {
	case PLYTKA: {
		teren_texture.loadFromFile("data/tereny/plytka1.png");
		teren_textureL.loadFromFile("data/tereny/plytka1L.png");
		teren_textureP.loadFromFile("data/tereny/plytka1P.png");
		przenikalnosc = true;
		tolerancja_lp = 14;
		tolerancja_top = 0;
		tolerancja_bot = 0;
	}
		break;
	case BLOK: {
		teren_texture.loadFromFile("data/tereny/teren1.png");
		teren_textureL.loadFromFile("data/tereny/teren1L.png");
		teren_textureP.loadFromFile("data/tereny/teren1P.png");
		teren_textureS.loadFromFile("data/tereny/teren1S.png");
		teren_textureSL.loadFromFile("data/tereny/teren1SL.png");
		teren_textureSP.loadFromFile("data/tereny/teren1SP.png");
		przenikalnosc = false;
		tolerancja_lp = 4;
		tolerancja_top = 5;
		tolerancja_bot = 3;
	}
		break;
	case WINDA: {
		teren_texture.loadFromFile("data/tereny/plytka2.png");
		teren_textureL.loadFromFile("data/tereny/plytka2L.png");
		teren_textureP.loadFromFile("data/tereny/plytka2P.png");
		przenikalnosc = true;
		tolerancja_lp = 14;
		tolerancja_top = 0;
		tolerancja_bot = 0;
	}
		break;
	}

	switch (specjalne) {
	case -1: {
		sprite.setTexture(teren_texture, true);
		spriteL.setTexture(teren_texture, true);
		spriteP.setTexture(teren_textureP, true);
		spriteS.setTexture(teren_textureS, true);
		spriteSL.setTexture(teren_textureS, true);
		spriteSP.setTexture(teren_textureSP, true);
	}
		break;
	case 1: {
		sprite.setTexture(teren_texture, true);
		spriteL.setTexture(teren_textureL, true);
		spriteP.setTexture(teren_texture, true);
		spriteS.setTexture(teren_textureS, true);
		spriteSL.setTexture(teren_textureSL, true);
		spriteSP.setTexture(teren_textureS, true);
	}
		break;
	case 0: {
		sprite.setTexture(teren_texture, true);
		spriteL.setTexture(teren_textureL, true);
		spriteP.setTexture(teren_textureP, true);
		spriteS.setTexture(teren_textureS, true);
		spriteSL.setTexture(teren_textureSL, true);
		spriteSP.setTexture(teren_textureSP, true);
	}
		break;
	}

	spriteL.setPosition(x, y);

	spriteSL.setPosition(x, y + sprite.getGlobalBounds().height);
	spriteS.setPosition(x + (spriteL.getGlobalBounds().width),
			y + sprite.getGlobalBounds().height);
	spriteSP.setPosition(x + (dlugosc - 1) * (sprite.getGlobalBounds().width),
			y + sprite.getGlobalBounds().height);

}

Teren::Teren(RodzajTerenu rodzaj, int dlugosc, int ax, int ay, int bx, int by,
		float vel) {
	this->dlugosc = dlugosc;

	this->velocity = sf::Vector2f(vel, 0);
	this->punktA = sf::Vector2f(ax, ay);
	this->punktB = sf::Vector2f(bx, by);

	wysokosc = 1;

	switch (rodzaj) {
	case PLYTKA: {
		teren_texture.loadFromFile("data/tereny/plytka1.png");
		teren_textureL.loadFromFile("data/tereny/plytka1L.png");
		teren_textureP.loadFromFile("data/tereny/plytka1P.png");
		przenikalnosc = true;
		tolerancja_lp = 14;
		tolerancja_top = 0;
		tolerancja_bot = 0;
	}
		break;
	case BLOK: {
		teren_texture.loadFromFile("data/tereny/teren1.png");
		teren_textureL.loadFromFile("data/tereny/teren1L.png");
		teren_textureP.loadFromFile("data/tereny/teren1P.png");
		teren_textureS.loadFromFile("data/tereny/teren1S.png");
		teren_textureSL.loadFromFile("data/tereny/teren1SL.png");
		teren_textureSP.loadFromFile("data/tereny/teren1SP.png");
		przenikalnosc = false;
		tolerancja_lp = 4;
		tolerancja_top = 5;
		tolerancja_bot = 3;
	}
		break;
	case WINDA: {
		teren_texture.loadFromFile("data/tereny/plytka2.png");
		teren_textureL.loadFromFile("data/tereny/plytka2L.png");
		teren_textureP.loadFromFile("data/tereny/plytka2P.png");
		przenikalnosc = true;
		tolerancja_lp = 14;
		tolerancja_top = 0;
		tolerancja_bot = 0;
	}
		break;
	}

	sprite.setTexture(teren_texture, true);
	spriteL.setTexture(teren_textureL, true);
	spriteP.setTexture(teren_textureP, true);
	spriteS.setTexture(teren_textureS, true);
	spriteSL.setTexture(teren_textureSL, true);
	spriteSP.setTexture(teren_textureSP, true);

	// Winda pojawia się początkowo w punkcie A
	int x = ax;
	int y = ay;

	spriteL.setPosition(x, y);
	spriteSL.setPosition(x, y + sprite.getGlobalBounds().height);
	spriteS.setPosition(x + (spriteL.getGlobalBounds().width),
			y + sprite.getGlobalBounds().height);
	spriteSP.setPosition(x + (dlugosc - 1) * (sprite.getGlobalBounds().width),
			y + sprite.getGlobalBounds().height);
}

Teren::~Teren(void) {
}

void Teren::update(int mineloCzasu) {
	// Zapisanie poprzedniej pozycji
	for (int i = 0; i < 9; i++)
		prevPosition[i] = getPosition(i);

	if (velocity != sf::Vector2f(0, 0)) {
		spriteL.move(velocity.x * (mineloCzasu / 1000.f), 0);
		if (spriteL.getPosition().x >= punktB.x
				&& spriteL.getPosition().y >= punktB.y) {
			spriteL.setPosition(punktB);
			velocity = -velocity;
		}
		if (spriteL.getPosition().x <= punktA.x
				&& spriteL.getPosition().y >= punktA.y) {
			spriteL.setPosition(punktA);
			velocity = -velocity;
		}

	}
}

sf::Vector2f Teren::getVelocity() const {
	return velocity;
}

sf::Vector2f Teren::getPrevPosition(unsigned int nr) const {
	return prevPosition[nr];
}

sf::Vector2f Teren::getPosition(unsigned int nr) const {
	return spriteL.getPosition();
}

sf::FloatRect Teren::getGlobalBounds(unsigned int nr) const {
	return sf::FloatRect(spriteL.getGlobalBounds().left + tolerancja_lp,
			spriteL.getGlobalBounds().top + tolerancja_top,
			(sprite.getGlobalBounds().width) * (dlugosc) - 2 * tolerancja_lp,
			sprite.getGlobalBounds().height * wysokosc - tolerancja_bot
					- tolerancja_top);
}

sf::FloatRect Teren::getPrevGlobalBounds(unsigned int nr) const {
	return sf::FloatRect(spriteL.getGlobalBounds().left + tolerancja_lp,
			spriteL.getGlobalBounds().top + tolerancja_top,
			(sprite.getGlobalBounds().width) * (dlugosc) - 2 * tolerancja_lp,
			sprite.getGlobalBounds().height * wysokosc - tolerancja_bot
					- tolerancja_top);
}

void Teren::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	// Utworzenie tymczasowego sprite2 - będzie na nim następowało przypisanie
	sf::Sprite sprite2;
	int x = spriteL.getPosition().x;
	int y = spriteL.getPosition().y;

	// Wyświetlenie lewej płytki
	target.draw(spriteL);

	// Wyświetlenie prawej płytki
	sprite2 = spriteP;
	sprite2.setPosition(x + (dlugosc - 1) * (sprite.getGlobalBounds().width),
			y);
	target.draw(sprite2);

	sprite2 = sprite;
	for (int lev = 0; lev < wysokosc; lev++) {
		// Dla płytek na wierzchu
		if (lev == 0) {
			for (int i = 0; i < dlugosc - 2; i++) {
				sprite2.setPosition(
						x + (i + 1) * (sprite.getGlobalBounds().width), y);
				target.draw(sprite2);
			}
		} else {
			// Dla płytek poniżej
			x = spriteS.getPosition().x;
			y = spriteS.getPosition().y;

			sprite2 = spriteSL;
			sprite2.setPosition(spriteSL.getPosition().x,
					y + (lev - 1) * (sprite.getGlobalBounds().height));
			target.draw(sprite2);

			sprite2 = spriteS;
			for (int i = 0; i < dlugosc - 2; i++) {
				sprite2.setPosition(x + i * (sprite.getGlobalBounds().width),
						y + (lev - 1) * (sprite.getGlobalBounds().height));
				target.draw(sprite2);
			}
			sprite2 = spriteSP;
			sprite2.setPosition(spriteSP.getPosition().x,
					y + (lev - 1) * (sprite.getGlobalBounds().height));

			target.draw(sprite2);
		}
	}

	//sprite.setPosition(x, y);
	//target.draw(sprite);
}
