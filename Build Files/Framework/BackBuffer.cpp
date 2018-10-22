// COMP710 GP 2D Framework 2018

// This include:
#include "BackBuffer.h"

// Local includes:
#include "LogManager.h"
#include "TextureManager.h"
#include "Sprite.h"
#include "AnimatedSprite.h"
#include "SpriteSheet.h"
#include "Texture.h"

// Library includes:
#include <SDL.h>
#include <SDL_image.h>
#include <cassert>

const int fontSize = 16;

BackBuffer::BackBuffer()
: m_pTextureManager(0)
, m_pWindow(0)
, m_pRenderer(0)
, m_width(0)
, m_height(0)
, m_clearRed(0)
, m_clearGreen(0)
, m_clearBlue(0)
, m_pDebugfont(0)
, m_textRed(0)
, m_textGreen(0)
, m_textBlue(0)
{

}

BackBuffer::~BackBuffer()
{
	delete m_pTextureManager;
	m_pTextureManager = 0;

	SDL_DestroyRenderer(m_pRenderer);
	m_pRenderer = 0;

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = 0;

	TTF_CloseFont(m_pDebugfont);
	m_pDebugfont = 0;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool
BackBuffer::Initialise(int width, int height)
{
	m_width = width;
	m_height = height;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		LogSDLError();
		return (false);
	}
	else
	{
		m_pWindow = SDL_CreateWindow("Alien Evasion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);

		if (m_pWindow == 0)
		{
			LogSDLError();
			return (false);
		}
		else
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);
			
			if (m_pRenderer == 0)
			{
				LogSDLError();
				return (false);
			}
			else
			{
				int imageResult = IMG_Init(IMG_INIT_PNG);

				if (imageResult == 0)
				{
					LogSDLError();
					return (false);
				}
				else
				{
					int blendResult = SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

					if (blendResult != 0)
					{
						LogSDLError();
						return (false);
					}
					else 
					{
						TTF_Init();
						m_pDebugfont = TTF_OpenFont("..\\..\\Gold Build - 14883251\\Bin\\assets\\font\\kenvector_future_thin.ttf", fontSize);

						if (!m_pDebugfont)
						{
							LogSDLError();
							return (false);
						}
					}					
				}
			}
		}
	}

	m_pTextureManager = new TextureManager();
	assert(m_pTextureManager);
	m_pTextureManager->Initialise(m_pRenderer);

	return (true);
}

void
BackBuffer::Clear()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearRed, m_clearGreen, m_clearBlue, 0xff);
	SDL_RenderClear(m_pRenderer);
}

void
BackBuffer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}

void
BackBuffer::SetTextColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_textRed = r;
	m_textGreen = g;
	m_textBlue = b;
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b)
{
	SetDrawColour(r, g, b, 0xFF);
}

void
BackBuffer::SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	SDL_SetRenderDrawColor(m_pRenderer, r, g, b, a);
}

void
BackBuffer::DrawSprite(Sprite& sprite)
{
	SDL_Rect dest;
	
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();
	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	
	SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest, sprite.GetAngle(), 0, SDL_FLIP_NONE);
}

void
BackBuffer::DrawSprite(Sprite& sprite, int width, int height)
{
	SDL_Rect dest;
	
	dest.w = width;
	dest.h = height;
	dest.x = sprite.GetX();
	dest.y = sprite.GetY();

	SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest, sprite.GetAngle(), 0, SDL_FLIP_NONE);
}

void
BackBuffer::DrawSprite(Sprite& sprite, unsigned char alpha)
{
	SDL_SetTextureAlphaMod(sprite.GetTexture()->GetTexture(), alpha);

	DrawSprite(sprite);
}

void
BackBuffer::DrawSprite(Sprite& sprite, int width, int height, unsigned char alpha)
{
	SDL_SetTextureAlphaMod(sprite.GetTexture()->GetTexture(), alpha);

	DrawSprite(sprite, width, height);
}

void
BackBuffer::DrawRotatedSprite(Sprite& sprite)
{
	SDL_Rect dest;

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = sprite.GetWidth();
	dest.h = sprite.GetHeight();

	SDL_RenderCopyEx(m_pRenderer, sprite.GetTexture()->GetTexture(), 0, &dest, sprite.GetAngle(), 0, SDL_FLIP_NONE);
}

void
BackBuffer::DrawAnimatedSprite(Sprite& sprite, int x, int width, int destWidth)
{
	SDL_Rect source;
	SDL_Rect dest;

	source.x = x;
	source.y = 0;
	source.w = width;
	source.h = sprite.GetHeight();

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = destWidth;
	dest.h = destWidth;

	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), &source, &dest);
}

void
BackBuffer::DrawSpriteSheet(SpriteSheet& sprite, int x, int y, int destWidth, int destHeight)
{
	SDL_Rect source;
	SDL_Rect dest;

	source.x = x;
	source.y = y;
	source.w = sprite.GetFrameWidth();
	source.h = sprite.GetFrameHeight();

	dest.x = sprite.GetX();
	dest.y = sprite.GetY();
	dest.w = destWidth;
	dest.h = destHeight;

	SDL_RenderCopy(m_pRenderer, sprite.GetTexture()->GetTexture(), &source, &dest);
}

void
BackBuffer::DrawFilledRectangle(int x, int y, int width, int height)
{
	SDL_Rect fillRect;

	fillRect.x = x;
	fillRect.y = y;
	fillRect.w = width;
	fillRect.h = height;

	SDL_RenderFillRect(m_pRenderer, &fillRect);
}

void
BackBuffer::DrawRectangle(int x, int y, int width, int height)
{
	SDL_Rect rectToDraw;

	rectToDraw.x = x;
	rectToDraw.y = y;
	rectToDraw.w = width;
	rectToDraw.h = height;

	SDL_RenderDrawRect(m_pRenderer, &rectToDraw);
}

void
BackBuffer::DrawRectangle(int x, int y, int width, int height, int offset)
{
	SDL_Rect rect;

	rect.x = x - offset;
	rect.y = y - offset;
	rect.w = width + (offset * 2);
	rect.h = height + (offset * 2);

	SDL_RenderDrawRect(m_pRenderer, &rect);
}

void
BackBuffer::DrawLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(m_pRenderer, x1, y1, x2, y2);
}

void
BackBuffer::DrawText(int x, int y, const char* text)
{
	SDL_Color colour;
	colour.r = m_textRed;
	colour.g = m_textGreen;
	colour.b = m_textBlue;

	SDL_Surface* surface = TTF_RenderText_Solid(m_pDebugfont, text, colour);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);

	int w;
	int h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = w;
	destRect.h = h;

	SDL_RenderCopy(m_pRenderer, texture, 0, &destRect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void
BackBuffer::DrawText(int x, int y, int width, int height, const char* text)
{
	SDL_Color colour;
	colour.r = m_textRed;
	colour.g = m_textGreen;
	colour.b = m_textBlue;

	SDL_Surface* surface = TTF_RenderText_Solid(m_pDebugfont, text, colour);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);

	int w;
	int h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect destRect;
	destRect.x = x + ((width - w) / 2);
	destRect.y = y + ((height - h) / 2);
	destRect.w = w;
	destRect.h = h;

	SDL_RenderCopy(m_pRenderer, texture, 0, &destRect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void 
BackBuffer::DrawTextWrapped(int x, int y, int width, int height, const char* text, Uint32 wrapLength)
{
	SDL_Color colour;
	colour.r = m_textRed;
	colour.g = m_textGreen;
	colour.b = m_textBlue;

	SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(m_pDebugfont, text, colour, wrapLength);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_pRenderer, surface);

	int w;
	int h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	SDL_Rect destRect;
	destRect.x = x + ((width - w) / 2);
	destRect.y = y + ((height - h) / 2);
	destRect.w = w;
	destRect.h = h;

	SDL_RenderCopy(m_pRenderer, texture, 0, &destRect);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}

void
BackBuffer::LogSDLError()
{
	LogManager::GetInstance().Log(SDL_GetError());
}

Sprite*
BackBuffer::CreateSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	Sprite* pSprite = new Sprite();
	
	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Sprite failed to create!");
	}

	return (pSprite);
}

AnimatedSprite*
BackBuffer::CreateAnimatedSprite(const char* pcFilename)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	AnimatedSprite* pSprite = new AnimatedSprite();

	if (!pSprite->Initialise(*pTexture))
	{
		LogManager::GetInstance().Log("Animated sprite failed to create!");
	}

	return (pSprite);
}

SpriteSheet*
BackBuffer::CreateSpriteSheet(const char* pcFilename, int frameCounts, int frameWidth, int frameHeight, bool looping)
{
	assert(m_pTextureManager);

	Texture* pTexture = m_pTextureManager->GetTexture(pcFilename);

	SpriteSheet* pSpriteSheet = new SpriteSheet();

	if (!pSpriteSheet->Initialise(*pTexture, frameCounts, frameWidth, frameHeight, looping))
	{
		LogManager::GetInstance().Log("Sprite sheet failed to create!");
	}

	return (pSpriteSheet);
}

void
BackBuffer::SetClearColour(unsigned char r, unsigned char g, unsigned char b)
{
	m_clearRed = r;
	m_clearGreen = g;
	m_clearBlue = b;
}