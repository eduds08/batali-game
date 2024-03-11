#include "PhysicalEntity.h"

PhysicalEntity::PhysicalEntity()
	: AnimatedEntity{}
{
}

void PhysicalEntity::updateLimits()
{
	// Limit is set to 5 tiles in each direction (top, right, bottom left) from the center of entity's shape
	int tilesAmount = 5;

	m_rightShapeLimit = getShapePosition().x + tilesAmount * TILE_SIZE_FLOAT;
	m_leftShapeLimit = getShapePosition().x - tilesAmount * TILE_SIZE_FLOAT;

	m_topShapeLimit = getShapePosition().y - tilesAmount * TILE_SIZE_FLOAT;
	m_bottomShapeLimit = getShapePosition().y + tilesAmount * TILE_SIZE_FLOAT;
}
