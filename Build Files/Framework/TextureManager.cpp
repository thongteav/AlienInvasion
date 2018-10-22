// COMP710 GP 2D Framework 2018

// This include:
#include "TextureManager.h"

// Local includes:
#include "Texture.h"
#include "LogManager.h"

// Library includes:
#include <SDL.h>
#include <string>

TextureManager::TextureManager()
	: m_pRenderer(0)
{

}

TextureManager::~TextureManager()
{
	std::map<std::string, Texture*>::iterator iter;
	iter = m_pLoadedTextures.begin();

	while (iter != m_pLoadedTextures.end())
	{
		delete iter->second;
		iter->second = 0;
		++iter;
	}

	m_pLoadedTextures.clear();
}

bool
TextureManager::Initialise(SDL_Renderer* pRenderer)
{
	m_pRenderer = pRenderer;

	return (true);
}

Texture*
TextureManager::GetTexture(const char* pcFilename)
{
	Texture* pTexture = 0;

	if (m_pLoadedTextures.find(pcFilename) == m_pLoadedTextures.end())
	{
		// Not already loaded... so load...
		pTexture = new Texture();
		if (!pTexture->Initialise(pcFilename, m_pRenderer))
		{
			LogManager::GetInstance().Log("Texture failed to initialise!");
		}

		m_pLoadedTextures[pcFilename] = pTexture;
	}
	else
	{
		// Is already loaded...
		pTexture = m_pLoadedTextures[pcFilename];
	}

	return (pTexture);
}

