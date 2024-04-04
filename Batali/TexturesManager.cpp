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

bool TexturesManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	bool isTextureLoaded = false;

	for (const auto& texture : texturesMap)
	{
		if (texture.first == textureName)
		{
			isTextureLoaded = true;
			break;
		}
	}

	if (!isTextureLoaded)
	{
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
			return false;
		}


		texturesMap.emplace(textureName, newTexture);

		return true;
	}

	return false;
}

TexturesManager& TexturesManager::getInstance()
{
	static TexturesManager* instance = new TexturesManager();
	return *instance;
}

std::unique_ptr<AbstractAnimation> TexturesManager::createNewAnimation(const std::string& name, sf::Vector2i frameSize, bool isLooping, const std::string& playerName)
{
	std::unique_ptr<AbstractAnimation> newAnimation = nullptr;

	if (isLooping)
	{
		newAnimation = std::make_unique<LoopingAnimation>(name, frameSize, loadAndGetTexture(playerName + name, "./assets/" + playerName + "/" + name + ".png"));
	}
	else
	{
		newAnimation = std::make_unique<PlayedOnceAnimation>(name, frameSize, loadAndGetTexture(playerName + name, "./assets/" + playerName + "/" + name + ".png"));
	}

	return newAnimation;
}
