#include "Coin.h"
#include "DynamicObject.h"

//function that send to the player tell him he need to handle with eating a coin
void Coin::handleCollision(DynamicObject& gameObject)
{
	gameObject.handleCollision(*this);
}
