#include"SlideManager.h"
#include"CameraManager.h"

SlideManager* SlideManager::sInstance = NULL;

SlideManager* SlideManager::createInstance()
{
	if (sInstance != NULL)
	{
		return sInstance;

	}
	else
	{
		sInstance = new SlideManager();
		return sInstance;
	}
}
SlideManager* SlideManager::getInstance()
{
	return sInstance;
}
void SlideManager::init()
{
	slideRenderer = new Renderer(TEXT_DISC);

	slideList = new LinkedList<Slide*>();
	slideIterator = new ListIterator<Slide*>(slideList, slideList->m_head);

}
LinkedList<Slide*>* SlideManager::getSlideList()
{
	return slideList;
}
ListIterator<Slide*>* SlideManager::getSlideIterator()
{
	return slideIterator;
}
void SlideManager::render()
{
	Vector2 cameraPostion;
	slideIterator->Start();
	Vector2 centerPoint;
	while (!slideIterator->hasReachedEnd())
	{
		Slide *currentSlide = slideIterator->data();
		centerPoint.x = slideIterator->data()->startPosition.x + slideIterator->data()->lengthOfSlide / 2;
		centerPoint.y = slideIterator->data()->startPosition.y + slideIterator->data()->startSlideWidth / 2;
		CameraManagerC::getInstance()->getCameraPosition(cameraPostion);

		slideRenderer->DrawSprite(currentSlide->startPosition.findDiff(cameraPostion), currentSlide->lengthOfSlide, currentSlide->startSlideWidth, currentSlide->slideStart,currentSlide->angleOfInclination,centerPoint.findDiff(cameraPostion));

		slideIterator->forth();
	} 
}
