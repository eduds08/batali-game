#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <string>
#include <memory>

class TexturesManager
{
public:
	TexturesManager() {};
	~TexturesManager() {};

	std::shared_ptr<sf::Texture> loadAndGetTexture(const std::string& textureName, const std::string& texturePath);

private:
	std::map<std::string, std::shared_ptr<sf::Texture>> texturesMap{};
};
