#include "StaticTexture.h"

StaticTexture::StaticTexture()
{
}

StaticTexture::~StaticTexture()
{
	if (m_texture)
	{
		delete m_texture;
		m_texture = nullptr;
	}
}

void StaticTexture::setTexture(const std::string& name, const std::string& path)
{
	m_texture = m_texturesManager.loadAndGetTexture(name, path).get();
	m_name = name;
}
