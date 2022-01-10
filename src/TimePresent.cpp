#include "TimePresent.h"
#include "DynamicObject.h"

//function that send to the player tell him he need to handle with taking a time present
void TimePresent::handleCollision(DynamicObject& gameObject)
{
	gameObject.handleCollision(*this);
}
