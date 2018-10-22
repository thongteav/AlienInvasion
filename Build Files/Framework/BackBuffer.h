// COMP710 GP 2D Framework 2018
#pragma once

#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

// Library includes:
#include "SDL_ttf.h"

// Forward Declarations:
class TextureManager;
class Sprite;
class AnimatedSprite;
class SpriteSheet;
struct SDL_Window;
struct SDL_Renderer;

class BackBuffer
{
public:
	BackBuffer();
	~BackBuffer();

	bool Initialise(int width, int height);

	void Clear();
	void Present();

	void SetClearColour(unsigned char r, unsigned char g, unsigned char b);

	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b);
	void SetDrawColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void DrawSprite(Sprite& sprite);
	void DrawSprite(Sprite& sprite, unsigned char alpha);
	void DrawSprite(Sprite& sprite, int width, int height);
	void DrawSprite(Sprite& sprite, int width, int height, unsigned char alpha);
	
	void DrawRotatedSprite(Sprite& sprite);
	void DrawAnimatedSprite(Sprite& sprite, int x, int width, int destWidth);
	void DrawSpriteSheet(SpriteSheet& sprite, int x, int y, int destWidth, int destHeight);
	
	void DrawFilledRectangle(int x, int y, int width, int height);
	void DrawRectangle(int x, int y, int width, int height);
	void DrawRectangle(int x, int y, int width, int height, int offset);
	void DrawLine(int x1, int y1, int x2, int y2);

	void SetTextColour(unsigned char r, unsigned char g, unsigned char b);
	void DrawText(int x, int y, const char* pcText);
	void DrawText(int x, int y, int width, int height, const char* pcText);
	void DrawTextWrapped(int x, int y, int width, int height, const char* pcText, Uint32 wrapLength);

	Sprite* CreateSprite(const char* pcFilename);
	AnimatedSprite* CreateAnimatedSprite(const char* pcFilename);
	SpriteSheet* CreateSpriteSheet(const char* pcFilename, int frameCounts, int frameWidth, int frameHeight, bool looping);

protected:
	void LogSDLError();

private:
	BackBuffer(const BackBuffer& backBuffer);
	BackBuffer& operator=(const BackBuffer& backBuffer);

	// Member Fields:
public:

protected:
	TextureManager* m_pTextureManager;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	int m_width;
	int m_height;

	unsigned char m_clearRed;
	unsigned char m_clearGreen;
	unsigned char m_clearBlue;

	TTF_Font* m_pDebugfont;
	unsigned char m_textRed;
	unsigned char m_textGreen;
	unsigned char m_textBlue;

private:

};

#endif // !__BACKBUFFER_H__