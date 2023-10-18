#include "DrawableEntity.h"

DrawableEntity::DrawableEntity()
	: m_texturesManager{ &TextureManager::getInstance() }
{
}
