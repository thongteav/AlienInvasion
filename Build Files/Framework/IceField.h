#pragma once

#ifndef __ICE_FIELD_H__
#define __ICE_FIELD_H__

// Local includes:
#include "Effect.h"

class IceField : public Effect
{
	// Member Functions
public:
	IceField();
	IceField(float x, float y, int width, int height);
	IceField(float x, float y, int width, int height, float maxAge);

	void Draw(BackBuffer& backBuffer);

protected:

private:

	// Member Fields
public:

protected:

private:

};

#endif // !__ICE_FIELD_H__
