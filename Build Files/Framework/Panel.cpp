// This include:
#include "Panel.h"

// Local includes:
#include "GUIComponent.h"
#include "BackBuffer.h"
#include "Label.h"

// Library includes:
#include <vector>

Panel::Panel()
: GUIComponent()
, m_pLabels(0)
, m_pButtons(0)
, m_currentBtn(0)
{

}

Panel::Panel(int x, int y, int width, int height)
: GUIComponent(x, y, width, height)
, m_pLabels(0)
, m_pButtons(0)
, m_currentBtn(0)
{

}

Panel::~Panel()
{
	DeleteLabels();
	DeleteButtons();
	GUIComponent::~GUIComponent();
}

void
Panel::DeleteLabels()
{
	std::vector<Label*>::iterator iterLabel;
	iterLabel = m_pLabels.begin();

	while (iterLabel != m_pLabels.end())
	{
		delete (*iterLabel);
		*iterLabel = 0;
		iterLabel = m_pLabels.erase(iterLabel);
	}
}

void
Panel::DeleteButtons()
{
	std::vector<Button*>::iterator iterBtn;
	iterBtn = m_pButtons.begin();

	while (iterBtn != m_pButtons.end())
	{
		delete (*iterBtn);
		*iterBtn = 0;
		iterBtn = m_pButtons.erase(iterBtn);
	}
}

void
Panel::Draw(BackBuffer& backBuffer)
{
	GUIComponent::Draw(backBuffer);

	DrawLabels(backBuffer);
	DrawButtons(backBuffer);
}

void
Panel::DrawLabels(BackBuffer& backBuffer)
{
	std::vector<Label*>::iterator iterLabel;
	iterLabel = m_pLabels.begin();

	while (iterLabel != m_pLabels.end())
	{
		(*iterLabel)->Draw(backBuffer);
		++iterLabel;
	}
}

void
Panel::DrawButtons(BackBuffer& backBuffer)
{
	std::vector<Button*>::iterator iterBtn;
	iterBtn = m_pButtons.begin();

	while (iterBtn != m_pButtons.end())
	{
		(*iterBtn)->Draw(backBuffer);
		++iterBtn;
	}
}

void
Panel::AddLabel(Label* label)
{
	m_pLabels.push_back(label);
}

void
Panel::AddButton(Button* button)
{
	m_pButtons.push_back(button);
}

bool
Panel::CheckButtonsPressed(int x, int y)
{
	bool pressed = false;

	std::vector<Button*>::iterator iterBtn;
	iterBtn = m_pButtons.begin();

	while (iterBtn != m_pButtons.end())
	{
		if ((*iterBtn)->IsPressed(x, y))
		{
			pressed = true;
			(*iterBtn)->SetPressed(true);
		}

		++iterBtn;
	}

	return (pressed);
}

bool
Panel::CheckButtonsHovered(int x, int y)
{
	bool hovered = false;

	std::vector<Button*>::iterator iterBtn;
	iterBtn = m_pButtons.begin();

	while (iterBtn != m_pButtons.end())
	{
		if ((*iterBtn)->IsHovered(x, y))
		{
			hovered = true;
			(*iterBtn)->SetHighlighted(true);
		}
		else
		{
			(*iterBtn)->SetHighlighted(false);
		}

		++iterBtn;
	}

	return (hovered);
}

void
Panel::PreviousButton()
{
	int current = m_currentBtn;
	int prev = --m_currentBtn;

	if (prev < 0)
	{
		prev = m_pButtons.size() + prev;
	}

	m_pButtons.at(current)->SetHighlighted(false);
	m_pButtons.at(prev)->SetHighlighted(true);

	m_currentBtn = prev;
}

void
Panel::NextButton()
{
	int current = m_currentBtn;
	int next = ++m_currentBtn % m_pButtons.size();

	m_pButtons.at(current)->SetHighlighted(false);
	m_pButtons.at(next)->SetHighlighted(true);

	m_currentBtn = next;
}

void
Panel::PressButton()
{
	m_pButtons.at(m_currentBtn)->SetPressed(true);
}

void
Panel::ResetButtons()
{
	std::vector<Button*>::iterator iterBtn;
	iterBtn = m_pButtons.begin();

	while (iterBtn != m_pButtons.end())
	{
		(*iterBtn)->SetPressed(false);
		++iterBtn;
	}

	m_currentBtn = 0;
	m_pButtons.front()->SetHighlighted(true);
}