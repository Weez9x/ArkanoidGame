// GameStatePlaying.cpp
#include "GameStatePlaying.h"
#include "GameSettings.h"
#include <cassert>

namespace Arkanoid
{
	GameStatePlaying::GameStatePlaying()
		: platform(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 50.f),
		ball(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f)
	{
		buildBricks();
	}

	void GameStatePlaying::onEnter()
	{

		if (!font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"))
		{

		}
		infoText.setFont(font);
		infoText.setCharacterSize(18);
		infoText.setString("ESC - to menu");
		infoText.setFillColor(sf::Color::White);
	}

	void GameStatePlaying::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				requestToMainMenu = true;
			}
		}
	}

	void GameStatePlaying::update(float dt)
	{
		if (isGameOver) return;

		platform.update(dt);
		ball.update(dt, platform.getBounds());

		auto ballBounds = ball.getBounds();

		for (auto& brick : bricks)
		{
			if (brick.isDestroyed())
				continue;

			auto brickBounds = brick.getBounds();

			if (ballBounds.intersects(brickBounds))
			{
				brick.destroy();

				float ballLeft = ballBounds.left;
				float ballRight = ballBounds.left + ballBounds.width;
				float ballTop = ballBounds.top;
				float ballBottom = ballBounds.top + ballBounds.height;

				float brickLeft = brickBounds.left;
				float brickRight = brickBounds.left + brickBounds.width;
				float brickTop = brickBounds.top;
				float brickBottom = brickBounds.top + brickBounds.height;

				float overlapLeft = ballRight - brickLeft;
				float overlapRight = brickRight - ballLeft;
				float overlapTop = ballBottom - brickTop;
				float overlapBottom = brickBottom - ballTop;


				bool ballFromLeft = std::abs(overlapLeft) < std::abs(overlapRight);
				bool ballFromTop = std::abs(overlapTop) < std::abs(overlapBottom);

				float minOverlapX = ballFromLeft ? overlapLeft : -overlapRight;
				float minOverlapY = ballFromTop ? overlapTop : -overlapBottom;

				if (std::abs(minOverlapX) < std::abs(minOverlapY))
				{
					ball.reflectX();
					ball.move(minOverlapX, 0.f);
				}
				else
				{
					ball.reflectY();
					ball.move(0.f, minOverlapY);
				}

				break;
			}
		}

		if (ball.lost())
			isGameOver = true;
	}

	void GameStatePlaying::draw(sf::RenderWindow& window)
	{
		platform.draw(window);
		ball.draw(window);

		for (const auto& brick : bricks)
			brick.draw(window);

		// HUD
		infoText.setPosition(10.f, 10.f);
		window.draw(infoText);
	}

	void GameStatePlaying::buildBricks()
	{
		bricks.clear();
		const float xStart = 60.f;
		const float gap = 5.f;
		for (int i = 0; i < BRICK_ROWS; ++i)
		{
			for (int j = 0; j < BRICK_COLUMNS; ++j)
			{
				float x = xStart + j * (BRICK_WIDTH + gap) + BRICK_WIDTH * 0.5f;
				float y = 50.f + i * (BRICK_HEIGHT + gap) + BRICK_HEIGHT * 0.5f;
				bricks.emplace_back(x, y, BRICK_WIDTH, BRICK_HEIGHT);
			}
		}
	}
}
