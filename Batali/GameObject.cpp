#include "GameObject.h"

int GameObject::s_idCounter{ 1 };

GameObject::GameObject()
	: m_id{ s_idCounter }
{
	++s_idCounter;
}
