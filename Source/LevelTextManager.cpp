#include"LevelTextManager.h"
#include"CameraManager.h"
using namespace Library;
LevelTextManager* LevelTextManager::sInstance = nullptr;
void LevelTextManager::init()
{
	textList.Clear();
}

void LevelTextManager::render()
{

	Vector2 cameraPosition;
	CameraManagerC::getInstance()->getCameraPosition(cameraPosition);
	cameraPosition.x /= SCREEN_WIDTH;
	cameraPosition.y /= SCREEN_HEIGHT;
	for(auto currentText : textList)
	{
		FontManagerC::GetInstance()->DrawStaticText(currentText->currentText, currentText->mPosition, currentText->dimension);
	}

}
void LevelTextManager::update(float_t newMS)
{

}