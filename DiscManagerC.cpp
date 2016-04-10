#include"DiscManagerC.h"
#include"PlayerManager.h"
#include"CameraManager.h"

DiscManagerC* DiscManagerC::sInstance = NULL;

DiscManagerC* DiscManagerC::createInstance()
{
	if (sInstance == NULL){
		sInstance = new DiscManagerC();
	}
	return sInstance;
}
DiscManagerC* DiscManagerC::getInstance()
{
	return sInstance;
}
Vector2 DiscManagerC::getPosition()
{
	return mPosition;

}
Vector2 DiscManagerC::getCenter()
{
	return mCenter;
}

float DiscManagerC::getRadius()
{
	return mRadius;
}
bool DiscManagerC::getDirection()
{
	return mDirection;
}
DiscManagerC::DiscManagerC()
{
	discList = NULL;
	discIterator = NULL;
	renderer = NULL;
}

DiscManagerC::~DiscManagerC() {
	if (discIterator != NULL) {
		delete discIterator;
	}
	if (discList != NULL) {
		delete discList;
	}
	if (renderer != NULL) {
		delete renderer;
	}
}
void DiscManagerC::init()
{
	mAngle = 0;

	mRotationSpeed = 100;

	if (discList != NULL) {
		delete discList;
	}
	discList = new LinkedList<Discs*>();

	if (discIterator != NULL) {
		delete discIterator;
	}
	discIterator = new ListIterator<Discs*>(discList, discList->m_head);

	minDistance = (JUMP_FORCE)*(JUMP_FORCE) ;

	
	if (renderer == NULL) {
		renderer = new Renderer(TEXT_DISC);
	}
	//renderer = new Renderer(TEXT_DISC);

	currentTime = 0;
	
	currentTime = 0;
	randomIterator = 2;
	

	//if (newDisc->discType == JUMPABLE_DISC)
	//{
	//	newDisc->discCoordinates = getRandomDisc();
	//	newDisc->smileCoordinates = getRandomSmile();
	//	newDisc->spokeCoordinates = getDiscSpoke();
	//}
	//else if (newDisc->discType == ENEMY_DISC)
	//{
	//	newDisc->discCoordinates = getRandomEnemyDisc();
	//	newDisc->smileCoordinates = getEnemySmile();
	//	newDisc->spokeCoordinates = getDiscSpike();
	//}
	//newDisc->spokePosition.x = newDisc->position.x + newDisc->radius - newDisc->spokeRadius;
	//newDisc->spokePosition.y = newDisc->position.y + newDisc->radius - newDisc->spokeRadius;
	//newDisc->collider.radius = newDisc->spokeRadius;
	//newDisc->collider.mCenter.x = newDisc->center.x;
	//newDisc->collider.mCenter.y = newDisc->center.y;
	//discList->Append(newDisc); 

	//renderer->init();
	lastRadius = 0;
//	loadLevelData();
}
void DiscManagerC::loadLevelData()
{

}
void DiscManagerC::update(DWORD newMS)
{
	currentTime += newMS / 1000.0f;

		rotateDiscs(newMS);
	

}

void DiscManagerC::rotateDiscs(DWORD newMS)
{
	discIterator->Start();
	while (!discIterator->hasReachedEnd())
	{

		discIterator->data()->currentAngle += discIterator->data()->speed * (newMS / (float)1000);

		discIterator->forth();
	}
}
void DiscManagerC::render()
{
	Vector2 cameraPosition;

	discIterator->Start();
	
	while (!discIterator->hasReachedEnd())
		{
			CameraManagerC::getInstance()->getCameraPosition(cameraPosition);
			Discs *currentDisc = discIterator->data();
			if (currentDisc->isVisible )
			{
				if (currentDisc->direction)
				{
					renderer->DrawSprite(currentDisc->spokePosition.findDiff(cameraPosition), currentDisc->spokeRadius * 2, currentDisc->spokeRadius * 2, currentDisc->spokeCoordinates, currentDisc->currentAngle, currentDisc->center.findDiff(cameraPosition));
				}
				else
				{
					renderer->DrawSprite(currentDisc->spokePosition.findDiff(cameraPosition), currentDisc->spokeRadius * 2, currentDisc->spokeRadius * 2, currentDisc->spokeCoordinates, -currentDisc->currentAngle, currentDisc->center.findDiff(cameraPosition));

				}
				if (currentDisc->discType == MEGA_JUMP)
				{
					if (currentDisc->direction)
					{
						renderer->DrawSprite(currentDisc->position.findDiff(cameraPosition), currentDisc->radius * 2, currentDisc->radius * 2, currentDisc->discCoordinates, currentDisc->currentAngle, currentDisc->center.findDiff(cameraPosition));
					}
					else
					{
						renderer->DrawSprite(currentDisc->position.findDiff(cameraPosition), currentDisc->radius * 2, currentDisc->radius * 2, currentDisc->discCoordinates, -currentDisc->currentAngle, currentDisc->center.findDiff(cameraPosition));

					}
				}
				else
				{
					renderer->DrawSprite(currentDisc->position.findDiff(cameraPosition), currentDisc->radius * 2, currentDisc->radius * 2, currentDisc->discCoordinates, 0, currentDisc->center.findDiff(cameraPosition));

				}
				if (currentDisc->discType != MEGA_JUMP)
				{
					if (!currentDisc->canSeePlayer)
					{
						renderer->DrawSprite(currentDisc->eyePosition.findDiff(cameraPosition), currentDisc->eyeWidth, currentDisc->eyeHeight, currentDisc->eyeCoordinates, 0, currentDisc->center.findDiff(cameraPosition));
					}
					else
					{
						if (currentDisc->direction)
						{
							renderer->DrawSprite(currentDisc->eyePosition.findDiff(cameraPosition), currentDisc->eyeWidth, currentDisc->eyeHeight, currentDisc->eyeCoordinates, currentDisc->currentAngle, currentDisc->center.findDiff(cameraPosition));
						}
						else
						{
							renderer->DrawSprite(currentDisc->eyePosition.findDiff(cameraPosition), currentDisc->eyeWidth, currentDisc->eyeHeight, currentDisc->eyeCoordinates, -currentDisc->currentAngle, currentDisc->center.findDiff(cameraPosition));

						}
					}
				}
				renderer->DrawSprite(currentDisc->smilePosition.findDiff(cameraPosition), currentDisc->smileWidth, currentDisc->smileHeight, currentDisc->smileCoordinates, 0, currentDisc->center.findDiff(cameraPosition));
			}
			discIterator->forth();

		} 
	
}

ListIterator<Discs*>* DiscManagerC::getDiscs()
{
	return discIterator;
}
LinkedList<Discs*>* DiscManagerC::getDiscList()
{
	return discList;
}
