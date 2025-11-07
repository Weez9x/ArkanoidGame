#pragma once
#include "GameObject.h"
#include "GameSettings.h"
#include <SFML/Window/Keyboard.hpp>

namespace Arkanoid
{
	class Platform : public GameObject
	{
	private:
		float speed;

	public:
		Platform(float x, float y);

		void update(float dt) override;
	};
}
