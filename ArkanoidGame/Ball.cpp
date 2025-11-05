#include "Ball.h"
#include <cmath>

namespace Arkanoid
{
	Ball::Ball(float x, float y)
	{
		shape.setRadius(BALL_RADIUS);
		shape.setFillColor(sf::Color::White);
		shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
		shape.setPosition(x, y);
		velocity = { BALL_SPEED, -BALL_SPEED };
	}

	void Ball::update(float dt, const sf::FloatRect& platformBounds)
	{
		sf::Vector2f pos = shape.getPosition();
		pos += velocity * dt;
		shape.setPosition(pos);

		// Wall collisions
		if (pos.x - BALL_RADIUS <= 0 || pos.x + BALL_RADIUS >= SCREEN_WIDTH)
			velocity.x *= -1;
		if (pos.y - BALL_RADIUS <= 0)
			velocity.y *= -1;

		// Ball lost
		if (pos.y > SCREEN_HEIGHT)
			isLost = true;

		// Platform collision
		if (shape.getGlobalBounds().intersects(platformBounds))
		{
			velocity.y = -std::abs(velocity.y);
		}
	}

	void Ball::draw(sf::RenderWindow& window) const
	{
		window.draw(shape);
	}

	sf::FloatRect Ball::getBounds() const
	{
		return shape.getGlobalBounds();
	}

	void Ball::reset()
	{
		shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		velocity = { BALL_SPEED, -BALL_SPEED };
		isLost = false;
	}
}
