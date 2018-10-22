// This include:
#include "HUD.h"
#include "BackBuffer.h"
#include "Sprite.h"

const int X = 100;
const int Y = 550;
const int NUM_LABELS = 3;
const int LABEL_SIZE = 36;
const int X_OFFSET = 5;
const int Y_OFFSET = 4;
const int WIDTH = X_OFFSET * (NUM_LABELS + 1) + LABEL_SIZE * NUM_LABELS;
const int HEIGHT = Y_OFFSET * 2 + LABEL_SIZE;
const int PLAYER_LIVES = 3;

HUD::HUD()
: Panel(X, Y, WIDTH, HEIGHT)
, m_playerLives(PLAYER_LIVES)
{

}

void
HUD::Initialise(BackBuffer& backBuffer)
{
	Label* labels[NUM_LABELS];

	int y = Y_OFFSET + Y;
	for (int i = 0; i < NUM_LABELS; ++i)
	{
		int x = (i + 1) * X_OFFSET + LABEL_SIZE * i + X;
		labels[i] = new Label(x, y, LABEL_SIZE, LABEL_SIZE);

		Sprite* ballSprite = backBuffer.CreateSprite("..\\..\\Gold Build - 14883251\\Bin\\assets\\grey_circle.png");
		labels[i]->Initialise(ballSprite);
		ballSprite->SetX(x);
		ballSprite->SetY(y);

		AddLabel(labels[i]);
	}

	int offset = 25;
	Label* label = new Label(offset, y + (LABEL_SIZE / 4), X - (offset * 2), LABEL_SIZE, "Lives:");
	AddLabel(label);
}

void
HUD::Draw(BackBuffer& backBuffer)
{
	DrawLabels(backBuffer);
}

void
HUD::DrawLabels(BackBuffer& backBuffer)
{
	for (int i = 0; i < m_playerLives; ++i)
	{
		m_pLabels.at(i)->Draw(backBuffer);
	}

	m_pLabels.back()->Draw(backBuffer);
}

void
HUD::SetPlayerLives(int lives)
{
	m_playerLives = lives;
}