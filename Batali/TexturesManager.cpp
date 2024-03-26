#include "TexturesManager.h"

std::shared_ptr<sf::Texture> TexturesManager::loadAndGetTexture(const std::string& textureName, const std::string& texturePath)
{
	// Check if the texture was already loaded and inserted on texturesMap. If true, it just returns it without having to load again.
	for (const auto& texture : texturesMap)
	{
		if (texture.first == textureName)
		{
			return texture.second;
		}
	}

	std::cout << textureName << "\n";

	// If it wasn't load previously, then it loads and inserts into the map
	std::shared_ptr<sf::Texture> newTexture{ std::make_shared<sf::Texture>() };
	try
	{
		if (!newTexture->loadFromFile(texturePath))
		{
			throw "ERROR LOADING TEXTURE -- " + textureName + " -- " + texturePath + "\n";
		}
	}
	catch (char const* error)
	{
		std::cerr << error << '\n';
	}


	texturesMap.emplace(textureName, newTexture);

	return newTexture;
}

TexturesManager& TexturesManager::getInstance()
{
	static TexturesManager* instance = new TexturesManager();
	return *instance;
}
