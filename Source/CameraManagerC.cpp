#ifndef  CONSTANT_H
#define  CONSTANT_H
#include"PlayerManager.h"
#include"Constants.h"
#include "physics.h"
#include"CameraManager.h"
CameraManagerC* CameraManagerC::sInstance = nullptr;
CameraManagerC* CameraManagerC::getInstance()
{
	if (sInstance == nullptr)
		sInstance = new CameraManagerC();
	return sInstance;
}

void CameraManagerC::getCameraPosition(Vector2 &position) {
	position.x = mPosition.x;
	position.y = mPosition.y;
}
void CameraManagerC::getCameraSize(Vector2 &size) {
	size.x = SCREEN_WIDTH;
	size.y = SCREEN_HEIGHT;
}
void CameraManagerC::Init()
{
	mPosition.x = 0;
	mPosition.y = 0;
	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
}
void CameraManagerC::render()
{
}
void CameraManagerC::update(DWORD newMS)
{
	mPosition.x = (PlayerManager::getInstance()->getPosition().x + PlayerManager::getInstance()->mWidth / 2) - SCREEN_WIDTH / 2;
	mPosition.y = (PlayerManager::getInstance()->getPosition().y + PlayerManager::getInstance()->mHeight / 2) - SCREEN_HEIGHT / 2;
	if (mPosition.x < 0)
	{
		mPosition.x = 0;
	}
	if (mPosition.y < 0)
	{
		mPosition.y = 0;
	}
	if (mPosition.x > IMAGE_WIDTH - CAMERA_WIDTH)
	{
		mPosition.x = IMAGE_WIDTH - CAMERA_WIDTH;
	}
	if (mPosition.y > IMAGE_HEIGHT - CAMERA_HEIGHT)
	{
		mPosition.y = IMAGE_HEIGHT - CAMERA_HEIGHT;
	}
}
#endif
