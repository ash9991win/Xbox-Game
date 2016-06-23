#ifndef  CONSTANT_H
#define  CONSTANT_H
#include"PlayerManager.h"
#include"Constants.h"
#include "physics.h"
#include"CameraManager.h"
CameraManagerC* CameraManagerC::sInstance = NULL;

CameraManagerC* CameraManagerC::createInstance()
{
	if (sInstance != NULL)
	{
		return sInstance;
	}
	else
	{
		sInstance = new CameraManagerC();
		return sInstance;
	}
}

CameraManagerC* CameraManagerC::getInstance()
{
	return sInstance;
}

void CameraManagerC::getCameraPosition(Vector2 &position) {
	//position.x = -PlayerManager::getInstance()->getPosition().x -   (SCREEN_WIDTH / 2.0f) ;
	//position.y = -PlayerManager::getInstance()->getPosition().y - (SCREEN_HEIGHT / 2.0f) ;
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
	//glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();
	//glLoadIdentity();
	///*glScalef(2, 2, 0);*/

	//if (!PlayerManager::getInstance()->isRotating())
	//{
	//	glTranslatef(-(PlayerManager::getInstance()->getPosition().x - (SCREEN_WIDTH / 2.0f)), -(PlayerManager::getInstance()->getPosition().y - (SCREEN_HEIGHT / 2.0f)), 0);
	//}
	//glPushMatrix();

//	glGetDoublev(GL_MODELVIEW, Matrix);
	//glPopMatrix();
}
void CameraManagerC::update(DWORD newMS)
{
	//camera.x = (dot.getPosX() + Dot::DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
	//camera.y = (dot.getPosY() + Dot::DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;
	//if (camera.x < 0)
	//{
	//	camera.x = 0;
	//}
	//if (camera.y < 0)
	//{
	//	camera.y = 0;
	//}
	//if (camera.x > LEVEL_WIDTH - camera.w)
	//{
	//	camera.x = LEVEL_WIDTH - camera.w;
	//}
	//if (camera.y > LEVEL_HEIGHT - camera.h)
	//{
	//	camera.y = LEVEL_HEIGHT - camera.h;
	//}
	/*if (!PlayerManager::getInstance()->isRotating())
	{*/
		mPosition.x = (PlayerManager::getInstance()->getPosition().x + PlayerManager::getInstance()->mWidth / 2) - SCREEN_WIDTH / 2;
		mPosition.y = (PlayerManager::getInstance()->getPosition().y + PlayerManager::getInstance()->mHeight / 2) - SCREEN_HEIGHT / 2;
	/*}*/
	/*else
	{
		mPosition.x = (PlayerManager::getInstance()->getPosition().x + PlayerManager::getInstance()->mWidth / 2) - SCREEN_WIDTH / 2;

	}*/
	
	//
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
