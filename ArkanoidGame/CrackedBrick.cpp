#include "CrackedBrick.h"
#include "GameSettings.h"
#include <iostream>

namespace Arkanoid
{
	CrackedBrick::CrackedBrick(float x, float y, float width, float height, int typeIndex)
		: Brick(x, y, width, height, typeIndex)
	{
		// Загружаем треснутую текстуру, если есть
		static const std::vector<std::string> crackedNames =
		{
			"Blue broken.png",
			"green broken.png",
			"yellow broken.png",
			"orange broken.png",
			"red broken.png"
		};

		if (typeIndex >= 0 && typeIndex < (int)crackedNames.size())
		{
			if (!crackedTexture.loadFromFile(TEXTURES_PATH + crackedNames[typeIndex]))
			{
				std::cerr << "Ошибка загрузки " << crackedNames[typeIndex] << std::endl;
			}
		}
	}

	void CrackedBrick::destroy()
	{
		hitsRemaining--;

		if (hitsRemaining == 1 && !cracked)
		{
			// Меняем на треснутую текстуру
			if (crackedTexture.getSize().x > 0)
				shape.setTexture(&crackedTexture);
			cracked = true;
		}
		else if (hitsRemaining <= 0)
		{
			active = false;
		}
	}
}
