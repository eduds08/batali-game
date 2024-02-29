#include "DrawableEntity.h"

DrawableEntity::DrawableEntity()
	: m_texturesManager{ TextureManager::getInstance() }
{
}

void DrawableEntity::setTexture(const std::string& textureName, const std::string& texturePath)
{
	if (textureName != "" && texturePath != "") 
	{
		m_sprite.setTexture(*m_texturesManager.loadAndGetTexture(textureName, texturePath));
	}
}
