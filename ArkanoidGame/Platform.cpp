// Platform.cpp
#include "Platform.h"

namespace Arkanoid
{
	Platform::Platform(float x, float y)
		: speed(PLATFORM_SPEED)
	{
		shape.setSize({ PLATFORM_WIDTH, PLATFORM_HEIGHT });
		shape.setFillColor(sf::Color::Blue);
		shape.setOrigin(PLATFORM_WIDTH / 2.f, PLATFORM_HEIGHT / 2.f);
		shape.setPosition(x, y);
	}

	void Platform::update(float dt)
	{
		float moveDir = 0.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			moveDir = -1.f;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			moveDir = 1.f;

		sf::Vector2f pos = shape.getPosition();
		pos.x += moveDir * speed * dt;

		if (pos.x - PLATFORM_WIDTH / 2 < 0)
			pos.x = PLATFORM_WIDTH / 2;
		if (pos.x + PLATFORM_WIDTH / 2 > SCREEN_WIDTH)
			pos.x = SCREEN_WIDTH - PLATFORM_WIDTH / 2;

		shape.setPosition(pos);
	}

	void Platform::draw(sf::RenderWindow& window) const
	{
		window.draw(shape);
	}

	sf::FloatRect Platform::getBounds() const
	{
		return shape.getGlobalBounds();
	}

	void Platform::reset()
	{
		shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 50.f);
	}
}
