#include "TextureManager.h"

std::shared_ptr<sf::Texture> TextureManager::loadAndGetTexture(const std::string& textureName, const std::string& texturePath)
{
	// Check if the texture was already loaded and inserted on texturesMap. If true, it just returns it without having to load again.
	for (const auto& texture : texturesMap)
	{
		if (texture.first == textureName)
		{
			return texture.second;
		}
	}

	// If it wasn't load previously, then it loads and inserts into the map
	std::shared_ptr<sf::Texture> newTexture{ std::make_shared<sf::Texture>() };
	if (!newTexture->loadFromFile(texturePath))
	{
		throw "ERRO AO CARREGAR TEXTURA";
	}

	texturesMap.emplace(textureName, newTexture);

	return newTexture;
}

// Singleton Pattern -> makes sures that only one instance of this class exists in the entire program
TextureManager& TextureManager::getInstance()
{
	static TextureManager* instance = new TextureManager();
	return *instance;
}
