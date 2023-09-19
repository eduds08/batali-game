#include "TexturesManager.h"

std::map<std::string, sf::Texture*> TexturesManager::texturesMap{};

TexturesManager::TexturesManager()
{
}

TexturesManager::~TexturesManager()
{
	std::map<std::string, sf::Texture*>::iterator mapIterator;

	for (mapIterator = texturesMap.begin(); mapIterator != texturesMap.end(); mapIterator++)
	{
		delete mapIterator->second;
		mapIterator->second = nullptr;
		std::cout << "Textura de nome: " << mapIterator->first << " deletada!\n";
	}
}

sf::Texture& TexturesManager::loadAndGetTexture(const std::string& textureName, const std::string& texturePath)
{
	std::map<std::string, sf::Texture*>::iterator mapIterator;

	for (mapIterator = texturesMap.begin(); mapIterator != texturesMap.end(); mapIterator++)
	{
		if (mapIterator->first == textureName)
		{
			return *mapIterator->second;
		}
	}

	sf::Texture* newTexture{ new sf::Texture{} };
	if (!newTexture->loadFromFile(texturePath))
	{
		std::cout << "Erro ao carregar a textura " << textureName << " no caminho " << texturePath << '\n';
		throw "ERRO AO CARREGAR TEXTURA";
	}

	texturesMap.emplace(textureName, newTexture);

	return *newTexture;
}
