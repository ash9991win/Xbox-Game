#pragma once
#include "baseTypes.h"

#include"Constants.h"
//#include<Windows.h>
#include"physics.h"
class CollisionManager
{
public:
	static CollisionManager* getInstance();
	static CollisionManager* createInstance();
	bool checkForCollision(Circle firstObject, Circle secondObject);
	bool checkForCollision(Rect firstObject, Circle secondObject);
private:
	static CollisionManager* sInstance;
	CollisionManager() {};
};
