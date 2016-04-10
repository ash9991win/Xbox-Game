#include"LevelTextManager.h"
#include"CameraManager.h"
LevelTextManager* LevelTextManager::sInstance = NULL;

LevelTextManager* LevelTextManager::createInstance()
{
	if (sInstance != NULL)
	{
		return sInstance;
	}
	else
	{
		sInstance = new LevelTextManager();
	}
}
void LevelTextManager::init()
{
	textList = new LinkedList<textToDisplay*>();
	textListIterator = new ListIterator<textToDisplay*>(textList, textList->m_head);
}

void LevelTextManager::render()
{

	Vector2 cameraPosition;
	CameraManagerC::getInstance()->getCameraPosition(cameraPosition);
	cameraPosition.x /= SCREEN_WIDTH;
	cameraPosition.y /= SCREEN_HEIGHT;
	textListIterator->Start();
	while (!textListIterator->hasReachedEnd())
	{
		textToDisplay *currentText = textListIterator->data();
		FontManagerC::GetInstance()->DrawStaticText(currentText->currentText, currentText->mPosition, currentText->dimension);
		textListIterator->forth();
	}

}
void LevelTextManager::update(float_t newMS)
{

}