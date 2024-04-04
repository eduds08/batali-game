#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>

#include "LoopingAnimation.h"
#include "PlayedOnceAnimation.h"

class TexturesManager
{
public:
	// Returns an existing texture from the texturesMap or create and save a new one in the map and then returns it
	std::shared_ptr<sf::Texture> loadAndGetTexture(const std::string& textureName, const std::string& texturePath);

	bool loadTexture(const std::string& textureName, const std::string& texturePath);

	// Singleton Pattern -> makes sures that only one instance of this class exists in the entire program
	static TexturesManager& getInstance();

	std::unique_ptr<AbstractAnimation> createNewAnimation(const std::string& name, sf::Vector2i frameSize, bool isLooping, const std::string& playerName);

private:
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> texturesMap{};

	TexturesManager() {};
	~TexturesManager() {};
};
