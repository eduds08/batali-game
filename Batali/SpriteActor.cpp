#include "SpriteActor.h"

SpriteActor::SpriteActor()
	: m_texturesManager{ TexturesManager::getInstance() }
{
}

void SpriteActor::setTexture(const std::string& textureName, const std::string& texturePath)
{
	if (textureName != "" && texturePath != "") 
	{
		m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));
	}
	else
	{
		std::cout << "Unable to load the following texture (empty string): \"" << textureName << "\" -- \"" << texturePath << "\"\n";
	}
}
