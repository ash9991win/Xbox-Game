#include"Collectible.h"
#include"CameraManager.h"
using namespace Library;
Collectible* Collectible::sInstance = nullptr;
void Collectible::init()
{
	currentTime = 0;
	fireRenderer = new Renderer(TEXT_PLAYER);
	collectibleList.Clear();
}
Vector<FirePoint*>* Collectible::getFireList()
{
	return &collectibleList;
}
void Collectible::update(float_t newMS)
{
	currentTime += newMS / 1000.0f;

	if (currentTime > (1 / FPS))
	{
		for( auto currentData : collectibleList)
		{
			if (currentData->currentFrame < 3)
			{
				currentData->currentFrame++;
			}
			else
			{
				currentData->currentFrame = 0;
			}
		}
		currentTime = 0;
	}
}
void Collectible::render()
{
	Vector2 cameraPosition;
	CameraManagerC::getInstance()->getCameraPosition(cameraPosition);
	for(auto currentFire : collectibleList)
	{
		if (currentFire->isVisible)
		{
			fireRenderer->DrawSprite(currentFire->mPosition.findDiff(cameraPosition), currentFire->mWidth, currentFire->mHeight, currentFire->fireCoordinates[currentFire->currentFrame]);
		}
	}

}