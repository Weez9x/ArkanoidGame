#include "GameStatePlaying.h"
#include "GameSettings.h"
#include "CrackedBrick.h"
#include <cstdlib>
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
        if (isGameOver || isWin)
            return;

        //обновляем движение платформы и шара
        platform.update(dt);
        ball.update(dt, platform.getBounds());

        //прогноз следующего положения шара
        sf::FloatRect nextPos = ball.getBounds();
        sf::Vector2f velocity = ball.getVelocity();
        nextPos.left += velocity.x * dt;
        nextPos.top += velocity.y * dt;

        //проверка коллизий с кирпичами
        for (auto& brick : bricks)
        {
            if (!brick->isActive())
                continue;

            sf::FloatRect brickBounds = brick->getBounds();

            if (nextPos.intersects(brickBounds))
            {
                // Разрушаем блок (CrackedBrick сам решит, ломаться или трескаться)
                brick->destroy();

                //расчёт сторон пересечения
                sf::FloatRect ballBounds = ball.getBounds();
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

                bool fromLeft = std::abs(overlapLeft) < std::abs(overlapRight);
                bool fromTop = std::abs(overlapTop) < std::abs(overlapBottom);
                float minOverlapX = fromLeft ? overlapLeft : -overlapRight;
                float minOverlapY = fromTop ? overlapTop : -overlapBottom;

                //определяем направление отражения
                if (std::abs(minOverlapX) < std::abs(minOverlapY))
                {
                    ball.reflectX();
                    ball.move(minOverlapX * 0.5f, 0.f);
                }
                else
                {
                    ball.reflectY();
                    ball.move(0.f, minOverlapY * 0.5f);
                }
                break;
            }
        }

        sf::FloatRect ballBounds = ball.getBounds();
        sf::FloatRect platformBounds = platform.getBounds();

        if (ballBounds.intersects(platformBounds))
        {
            float platformCenter = platformBounds.left + platformBounds.width / 2.f;
            float ballCenter = ballBounds.left + ballBounds.width / 2.f;
            float hitFactor = (ballCenter - platformCenter) / (platformBounds.width / 2.f);

            // плавный контроль угла отскока
            const float MAX_ANGLE = 75.f * 3.14159265f / 180.f;
            float angle = hitFactor * MAX_ANGLE;

            float speed = ball.getSpeed();
            ball.setVelocity(
                speed * std::sin(angle),
                -speed * std::cos(angle)
            );

            // чуть сдвигаем вверх, чтобы не застрял
            ball.move(0.f, -2.f);
        }

        //проверка победы
        bool allDestroyed = true;
        for (const auto& brick : bricks)
        {
            if (brick->isActive())
            {
                allDestroyed = false;
                break;
            }
        }
        if (allDestroyed)
            isWin = true;

        //проверка проигрыша
        if (ball.lost())
            isGameOver = true;
    }


	void GameStatePlaying::draw(sf::RenderWindow& window)
	{
		platform.draw(window);
		ball.draw(window);

		for (const auto& brick : bricks)
			brick->draw(window);

		// HUD
		infoText.setPosition(10.f, 10.f);
		window.draw(infoText);
	}

	void GameStatePlaying::buildBricks()
	{
		bricks.clear();
		const float gap = 5.f;
		float totalWidth = BRICK_COLUMNS * BRICK_WIDTH + (BRICK_COLUMNS - 1) * gap;
		float startX = (SCREEN_WIDTH - totalWidth) / 2.f + BRICK_WIDTH / 2.f;
		float startY = 80.f;

		for (int i = 0; i < BRICK_ROWS; ++i)
		{
			for (int j = 0; j < BRICK_COLUMNS; ++j)
			{
				float x = startX + j * (BRICK_WIDTH + gap);
				float y = startY + i * (BRICK_HEIGHT + gap);
				int typeIndex = i % 5;

				// каждый 3-й блок будет "CrackedBrick"
				if ((i + j) % 4 == 0)
				{
					bricks.emplace_back(std::make_unique<CrackedBrick>(x, y, BRICK_WIDTH, BRICK_HEIGHT, typeIndex));
				}
				else
				{
					bricks.emplace_back(std::make_unique<Brick>(x, y, BRICK_WIDTH, BRICK_HEIGHT, typeIndex));
				}
			}
		}
	}

}
