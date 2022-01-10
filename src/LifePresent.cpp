#include "LifePresent.h"
#include "DynamicObject.h"

//function that send to the player tell him he need to handle with taking a life present
void LifePresent::handleCollision(DynamicObject& gameObject)
{
	gameObject.handleCollision(*this);
}
