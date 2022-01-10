#pragma once
#include "Eatable.h"

class Coin : public Eatable
{
	using Eatable::Eatable;
	virtual void handleCollision(DynamicObject& gameObject);
};