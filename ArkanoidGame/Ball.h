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
		float speed = 350.f;

	public:
		Ball(float x, float y);
		void update(float dt, const sf::FloatRect& platformBounds);
		void reset();
		void normalizeSpeed();
		void reflectX() { velocity.x *= -1; normalizeSpeed();}
		void reflectY() { velocity.y *= -1; normalizeSpeed();}
		bool lost() const { return isLost; }
		void move(float offsetX, float offsetY);
		const sf::Vector2f& getVelocity() const { return velocity; }
		float getSpeed() const { return std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y); }
		void setVelocity(float vx, float vy) { velocity = { vx, vy }; }
	};
}
