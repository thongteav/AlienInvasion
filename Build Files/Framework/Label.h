#pragma once

#ifndef __LABEL_H__
#define __LABEL_H__

// Local includes:
#include "GUIComponent.h"
#include "BackBuffer.h"

// Library includes:
#include <string>

class Label : public GUIComponent
{
	// Member Methods:
public:
	Label();
	Label(int x, int y, int width, int height);
	Label(int x, int y, int width, int height, std::string text);
	Label(std::string text);

	void Draw(BackBuffer& backBuffer);
	void DrawWrapped(BackBuffer& backBuffer);
	void SetText(std::string text);

protected:

private:

	// Member Fields;:
public:

protected:

private:
	std::string m_text;

};

#endif // !__LABEL_H__
