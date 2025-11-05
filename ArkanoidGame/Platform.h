// Platform.h
#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"

namespace Arkanoid
{
	class Platform
	{
	private:
		sf::RectangleShape shape;
		float speed;

	public:
		Platform(float x, float y);

		void update(float dt);
		void draw(sf::RenderWindow& window) const;
		sf::FloatRect getBounds() const;
		void reset();
	};
}
