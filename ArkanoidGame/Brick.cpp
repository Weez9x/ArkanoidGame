#include "Brick.h"
#include "GameSettings.h"
#include <cassert>

namespace Arkanoid
{
	std::vector<sf::Texture> Brick::textures;

	void Brick::loadTextures()
	{
		if (!textures.empty()) return; // уже загружено

		const std::vector<std::string> textureNames = {
			"Blue.png",
			"green.png",
			"yellow.png",
			"orange.png",
			"red.png"
		};

		textures.resize(textureNames.size());

		for (size_t i = 0; i < textureNames.size(); ++i)
		{
			bool ok = textures[i].loadFromFile(TEXTURES_PATH + textureNames[i]);
			assert(ok && "Failed to load brick texture");
		}
	}

	Brick::Brick(float x, float y, float width, float height, int typeIndex)
		: type(typeIndex)
	{
		if (textures.empty())
			loadTextures();

		shape.setSize({ width, height });
		shape.setOrigin(width / 2.f, height / 2.f);
		shape.setPosition(x, y);

		// защита на случай, если нет текстур
		if (!textures.empty())
		{
			if (type < 0) type = 0;
			if (type >= (int)textures.size()) type = (int)textures.size() - 1;
			shape.setTexture(&textures[type]);
		}
		else
		{
			shape.setFillColor(sf::Color::White);
		}
	}

	void Brick::destroy()
	{
		active = false;
	}

	void Brick::unloadTextures()
	{
		textures.clear();
	}
}
