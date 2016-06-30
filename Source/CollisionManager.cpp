#pragma once
#include"CollisionManager.h"
#include"physics.h"
#include<stdio.h>
CollisionManager* CollisionManager::sInstance = nullptr;

CollisionManager* CollisionManager::createInstance()
{
	if (sInstance != nullptr)
	{
		return sInstance;
	}
	else
	{
		sInstance = new CollisionManager();
		return sInstance;
	}
}

CollisionManager* CollisionManager::getInstance()
{
	return sInstance;
}
bool CollisionManager::checkForCollision(Circle object1, Circle object2)
{
	float_t sumOfRadii = (object1.radius + object2.radius) * (object1.radius + object2.radius);
	if (Vector2::distanceBetweenSquared(object1.mCenter, object2.mCenter) < (sumOfRadii ))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CollisionManager::checkForCollision(Rect object1, Circle object2)
{
	Vector2 circlePos;
	circlePos.x = object2.mCenter.x;
	circlePos.y = object2.mCenter.y;

	Vector2 rectPos;
	rectPos.x = object1.x;
	rectPos.y = object1.y;

	circlePos.rotateOnPivot(object1.angle * DEG_TO_RAD, &rectPos);
	// Test if within bounding-box
	float32_t rectCircleXDiff = circlePos.x - rectPos.x;
	float32_t rectCircleYDiff = circlePos.y - rectPos.y;
	float32_t rectCircleWidthDiff = (object1.width / 2) + object2.radius;
	float32_t rectCircleHeightDiff = (object1.height / 2) + object2.radius;
	bool answer = false;
	if (rectCircleXDiff <= rectCircleWidthDiff && rectCircleXDiff >= -rectCircleWidthDiff
		&& rectCircleYDiff <= rectCircleHeightDiff && rectCircleYDiff >= -rectCircleHeightDiff) {
		answer = true;
		printf("CODDIIDKKD\n" );
	}
	// Return results
	return answer;

}
