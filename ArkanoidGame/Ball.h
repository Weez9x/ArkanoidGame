#pragma once
#include "GameObject.h"
#include "GameSettings.h"

namespace Arkanoid
{
	class Ball : public GameObject
	{
	private:
		sf::Vector2f velocity;
		bool isLost = false;

	public:
		Ball(float x, float y);

		void update(float dt, const sf::FloatRect& platformBounds);
		void reset();

		void reflectX() { velocity.x *= -1; }
		void reflectY() { velocity.y *= -1; }

		bool lost() const { return isLost; }
		void move(float dx, float dy) { shape.move(dx, dy); }
	};
}
