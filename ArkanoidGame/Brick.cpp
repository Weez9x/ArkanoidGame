#include "Brick.h"

namespace Arkanoid
{
	Brick::Brick(float x, float y, float width, float height)
	{
		shape.setSize({ width, height });
		shape.setOrigin(width / 2.f, height / 2.f);
		shape.setPosition(x, y);
		shape.setFillColor(sf::Color::Red);
	}

	void Brick::draw(sf::RenderWindow& window) const
	{
		if (!destroyed)
			window.draw(shape);
	}

	sf::FloatRect Brick::getBounds() const
	{
		return shape.getGlobalBounds();
	}
}
