#include "ShapeActor.h"

ShapeActor::ShapeActor()
	: AnimatedActor{}
{
}

void ShapeActor::updateLimits()
{
	// Limit is set to TILES_PHYSICAL_ACTOR_LIMIT tiles in each direction (top, right, bottom left) from the center of actor's shape

	m_shapeLimits[0] = getShapePosition().y - TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// TOP
	m_shapeLimits[1] = getShapePosition().x + TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// RIGHT
	m_shapeLimits[2] = getShapePosition().y + TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// BOTTOM
	m_shapeLimits[3] = getShapePosition().x - TILES_PHYSICAL_ACTOR_LIMIT * TILE_SIZE_FLOAT;	// LEFT
}
