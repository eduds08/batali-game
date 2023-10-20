#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <unordered_map>

class TextureManager
{
public:
	~TextureManager() {};

	// Returns an existing texture from the texturesMap or create and save a new one in the map and then returns it
	std::shared_ptr<sf::Texture> loadAndGetTexture(const std::string& textureName, const std::string& texturePath);

	// Singleton Pattern -> makes sures that only one instance of this class exists in the entire program
	static TextureManager& getInstance();

private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> texturesMap{};

	TextureManager() {};
};
