#include"PrincessMaanger.h"
#include"CameraManager.h"
PrincessManager* PrincessManager::sInstance = nullptr;
void PrincessManager::init()
{
	mPosition.x = mPosition.y = 0;
	currentFrame = 7;
	princessRenderer = new Renderer(TEXT_PLAYER);
	currentTime = 0;
	animatedTime = 0;
	amBurnt = false;
	isAnimationOver = false;
}
void PrincessManager::render()
{
	Vector2 cameraPosition;
	CameraManagerC::getInstance()->getCameraPosition(cameraPosition);
	princessRenderer->DrawSprite(mPosition.findDiff(cameraPosition), mWidth, mHeight, winDisc);
	
    princessRenderer->DrawSprite(mPosition.findDiff(cameraPosition), mWidth, mHeight, currentFrameTexture);
	princessRenderer->DrawSprite(balconyPosition.findDiff(cameraPosition), mWidth, mHeight/2, balcony);
	
}
void PrincessManager::setPosition(Vector2 newPosition)
{
	mPosition = newPosition;
}
void PrincessManager::Update(DWORD newMS)
{

	if (animatedTime > ANIMATION_DURATION)
	{
		isAnimationOver = true;
	}
	
	currentTime += newMS / 1000.0f;
	if (currentTime > (1/FPS))
	{
		if (amBurnt)
		{
			animatedTime += (1/FPS);
			currentFrame++;
			if (currentFrame > 8)
			{
				currentFrame = 7;
			}
			else if (currentFrame < 8)
			{
				currentFrame = 7;
			}
			currentTime = 0;
		}
		else
		{
			//currentFrame++;
			if (currentFrame > 7)
			{
				currentFrame = 1;
			}
			currentFrame = 1;
		}
	}
	currentFrameTexture = princessFrame[currentFrame];

}
