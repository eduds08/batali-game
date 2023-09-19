#include "TexturesManager.h"

std::shared_ptr<sf::Texture> TexturesManager::loadAndGetTexture(const std::string& textureName, const std::string& texturePath)
{
	std::map<std::string, std::shared_ptr<sf::Texture>>::iterator mapIterator;

	for (mapIterator = texturesMap.begin(); mapIterator != texturesMap.end(); mapIterator++)
	{
		if (mapIterator->first == textureName)
		{
			return mapIterator->second;
		}
	}

	std::shared_ptr<sf::Texture> newTexture{ std::make_shared<sf::Texture>() };
	if (!newTexture->loadFromFile(texturePath))
	{
		std::cout << "Erro ao carregar a textura " << textureName << " no caminho " << texturePath << '\n';
		throw "ERRO AO CARREGAR TEXTURA";
	}

	texturesMap.emplace(textureName, newTexture);

	return newTexture;
}
