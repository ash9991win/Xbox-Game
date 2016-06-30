#include"DiscManagerC.h"
#include"PlayerManager.h"
#include"CameraManager.h"
using namespace Library;
DiscManagerC* DiscManagerC::sInstance = nullptr;

DiscManagerC* DiscManagerC::getInstance()
{
	if (sInstance == nullptr)
		sInstance = new DiscManagerC();
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
	renderer = nullptr;
}

DiscManagerC::~DiscManagerC() {
	if (renderer != nullptr) {
		delete renderer;
	}
}
void DiscManagerC::init()
{
	mAngle = 0;

	mRotationSpeed = 100;

	discList.Clear();
	minDistance = (JUMP_FORCE)*(JUMP_FORCE) ;
	if (renderer == nullptr) {
		renderer = new Renderer(TEXT_DISC);
	}
	//renderer = new Renderer(TEXT_DISC);
	currentTime = 0;
	currentTime = 0;
	randomIterator = 2;
	lastRadius = 0;
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
	for(auto currentData : discList)
	{
		currentData->currentAngle += currentData->speed * (newMS / (float)1000);
	}
}
void DiscManagerC::render()
{
	Vector2 cameraPosition;
    for(auto currentDisc : discList)
		{
			CameraManagerC::getInstance()->getCameraPosition(cameraPosition);
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

		} 
	
}

Vector<Discs*>* DiscManagerC::getDiscList()
{
	return &discList;
}
