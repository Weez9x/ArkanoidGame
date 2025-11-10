#include "Ball.h"

namespace Arkanoid
{
	Ball::Ball(float x, float y)
	{
		shape.setSize({ BALL_RADIUS * 2, BALL_RADIUS * 2 });
		//shape.setFillColor(sf::Color::White);
		shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
		shape.setPosition(x, y);
		setTexture(TEXTURES_PATH + "ball.png");
		velocity = { BALL_SPEED, -BALL_SPEED };
	}

	void Ball::update(float dt, const sf::FloatRect& platformBounds)
	{
		if (!active) return;

		auto pos = shape.getPosition();
		pos += velocity * dt;
		shape.setPosition(pos);

		// От стен
		if (pos.x - BALL_RADIUS <= 0.f || pos.x + BALL_RADIUS >= SCREEN_WIDTH)
			reflectX();
		if (pos.y - BALL_RADIUS <= 0.f)
			reflectY();

		// Потеря шара
		if (pos.y > SCREEN_HEIGHT)
			isLost = true;

		// От платформы
		if (shape.getGlobalBounds().intersects(platformBounds))
		{
			reflectY();

			// изменяем направление X в зависимости от точки удара по платформе
			float platformCenter = platformBounds.left + platformBounds.width / 2.f;
			float hitPos = (pos.x - platformCenter) / (PLATFORM_WIDTH / 2.f);
			velocity.x = BALL_SPEED * hitPos;
		}
	}

	void Ball::reset()
	{
		isLost = false;
		active = true;
		shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
		velocity = { BALL_SPEED, -BALL_SPEED };
	}
}
