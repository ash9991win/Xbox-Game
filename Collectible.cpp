#include"Collectible.h"
#include"CameraManager.h"
Collectible* Collectible::sInstance = NULL;

Collectible* Collectible::createInstance()
{
	if (sInstance != NULL)
	{
		return sInstance;
	}
	else
	{
		sInstance = new Collectible();
	}
}
void Collectible::init()
{
	currentTime = 0;
	collectibleList = new LinkedList<FirePoint*>();

	collectibleIterator = new ListIterator<FirePoint*>(collectibleList, collectibleList->m_head);
	fireRenderer = new Renderer(TEXT_PLAYER);
	
}
LinkedList<FirePoint*>* Collectible::getFireList()
{
	return collectibleList;
}
void Collectible::update(float_t newMS)
{
	currentTime += newMS / 1000.0f;

	if (currentTime > (1 / FPS))
	{
		collectibleIterator->Start();
		while (!collectibleIterator->hasReachedEnd())
		{
			if (collectibleIterator->data()->currentFrame < 3)
			{
				collectibleIterator->data()->currentFrame++;
			}
			else
			{
				collectibleIterator->data()->currentFrame = 0;
			}
			collectibleIterator->forth();
		}
		currentTime = 0;
	}
}
void Collectible::render()
{
	collectibleIterator->Start();
	Vector2 cameraPosition;
	CameraManagerC::getInstance()->getCameraPosition(cameraPosition);
	while (!collectibleIterator->hasReachedEnd())
	{
		FirePoint *currentFire = collectibleIterator->data();

		if (currentFire->isVisible)
		{
			fireRenderer->DrawSprite(currentFire->mPosition.findDiff(cameraPosition), currentFire->mWidth, currentFire->mHeight, currentFire->fireCoordinates[currentFire->currentFrame]);
		}
		collectibleIterator->forth();
	}

}