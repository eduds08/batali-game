#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <unordered_map>

class TextureManager
{
public:
	TextureManager() {};
	~TextureManager() {};

	std::shared_ptr<sf::Texture> loadAndGetTexture(const std::string& textureName, const std::string& texturePath);

private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> texturesMap{};
};
