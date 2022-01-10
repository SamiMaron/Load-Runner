#include "Eatable.h"
#include "DynamicObject.h"

//function that send to the player tell him he need to handle with eating something
void Eatable::handleCollision(DynamicObject& gameObject)
{
	gameObject.handleCollision(*this);
}
