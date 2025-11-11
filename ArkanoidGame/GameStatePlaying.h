#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Platform.h"
#include "Ball.h"
#include "Brick.h"
#include "GameState.h"

namespace Arkanoid
{
	class GameStatePlaying : public GameState
	{
	private:
		Platform platform;
		Ball ball;
		std::vector<std::unique_ptr<GameObject>> bricks;
		sf::Font font;
		sf::Text infoText;

		bool isGameOver = false;
		bool requestToMainMenu = false;
		bool isWin = false;


		void buildBricks();

	public:
		GameStatePlaying();
		~GameStatePlaying() override = default;

		void onEnter() override;
		void handleEvent(const sf::Event& event) override;
		void update(float dt) override;
		void draw(sf::RenderWindow& window) override;

		bool gameOver() const { return isGameOver; }
		bool shouldGoToMainMenu() const { return requestToMainMenu; }
		bool gameWin() const { return isWin; }
	};
}
