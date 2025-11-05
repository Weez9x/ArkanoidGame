#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"

namespace Arkanoid
{
	class Ball
	{
	private:
		sf::CircleShape shape;
		sf::Vector2f velocity;
		bool isLost = false;

	public:
		Ball(float x, float y);

		void update(float dt, const sf::FloatRect& platformBounds);
		void draw(sf::RenderWindow& window) const;
		void reset();
		bool lost() const { return isLost; }
		sf::FloatRect getBounds() const;

		void reflectX() { velocity.x *= -1; }
		void reflectY() { velocity.y *= -1; }

		sf::Vector2f getPosition() const { return shape.getPosition(); }
		void move(float dx, float dy) { shape.move(dx, dy); }
	};
}
