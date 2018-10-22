#pragma once

#ifndef __GUI_COMPONENT_H__
#define __GUI_COMPONENT_H__

// Forward Declarations
class Sprite;
class BackBuffer;

class GUIComponent
{
	// Member Methods:
public:
	GUIComponent();
	GUIComponent(int x, int y, int width, int height);
	~GUIComponent();

	bool Initialise(Sprite* sprite);

	void Draw(BackBuffer& backBuffer);

	void SetPosition(int x, int y);
	void SetDimension(int width, int height);

	void SetPositionX(int x);
	void SetPosiitionY(int y);
	void SetWidth(int width);
	void SetHeight(int height);

	void SetBackgroundColour(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	void SetTextColour(unsigned char r, unsigned char g, unsigned char b);

	void SetDrawBackground(bool draw);

	int GetPositionX();
	int GetPositionY();
	int GetWidth();
	int GetHeight();

protected:

private:

	// Member Fields:
public:

protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	Sprite* m_pSprite;

	unsigned char m_r;
	unsigned char m_g;
	unsigned char m_b;
	unsigned char m_a;

	unsigned char m_textRed;
	unsigned char m_textGreen;
	unsigned char m_textBlue;

	bool m_drawBackground;

private:

};

#endif // !__GUI_COMPONENT_H__
