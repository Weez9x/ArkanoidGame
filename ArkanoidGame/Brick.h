#pragma once
#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class Brick
	{
	private:
		sf::RectangleShape shape;
		bool destroyed = false;

	public:
		Brick(float x, float y, float width, float height);

		void draw(sf::RenderWindow& window) const;
		sf::FloatRect getBounds() const;
		bool isDestroyed() const { return destroyed; }
		void destroy() { destroyed = true; }
	};
}
