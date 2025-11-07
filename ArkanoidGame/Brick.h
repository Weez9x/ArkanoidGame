#pragma once
#include "GameObject.h"

namespace Arkanoid
{
	class Brick : public GameObject
	{
	public:
		Brick(float x, float y, float width, float height);

		void destroy();
	};
}
