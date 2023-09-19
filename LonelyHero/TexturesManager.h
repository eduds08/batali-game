#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <map>
#include <string>

class TexturesManager
{
public:
	TexturesManager();
	~TexturesManager();

	static sf::Texture& loadAndGetTexture(const std::string& textureName, const std::string& texturePath);

private:
	static std::map<std::string, sf::Texture*> texturesMap;
};
