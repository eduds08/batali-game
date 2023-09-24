#include "TextureManager.h"

TextureManager* TextureManager::instance = nullptr;

std::shared_ptr<sf::Texture> TextureManager::loadAndGetTexture(const std::string& textureName, const std::string& texturePath)
{
	for (const auto& texture : texturesMap)
	{
		if (texture.first == textureName)
		{
			return texture.second;
		}
	}

	std::shared_ptr<sf::Texture> newTexture{ std::make_shared<sf::Texture>() };
	if (!newTexture->loadFromFile(texturePath))
	{
		throw "ERRO AO CARREGAR TEXTURA";
	}

	texturesMap.emplace(textureName, newTexture);

	return newTexture;
}

TextureManager* TextureManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureManager();
	}
	return instance;
}
