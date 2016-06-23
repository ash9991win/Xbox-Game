#define STATE_MANAGER_CPP
#include "Constants.h"
#include "baseTypes.h"

//#include <windows.h>											// Header File For Windows

#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations

#if IS_COMP
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glut.h>
#include <assert.h>
#include "openglframework.h"	
#endif

#include "random.h"
#include "soil.h"
#include "physics.h"
#include "CameraManager.h"
#include "Renderer.h"
#include "BackgroundManager.h"

#include "PlayerManager.h"
//Draw the background
BackgroundManagerC *BackgroundManagerC::sInstance = NULL;

BackgroundManagerC* BackgroundManagerC::CreateInstance()
{
	if (sInstance != NULL)
	{
		return sInstance;
	}
	else
         sInstance = new BackgroundManagerC();
		return sInstance;

}
BackgroundManagerC* BackgroundManagerC::getInstance()
{
	return sInstance;
}
void BackgroundManagerC::init(int width, int height)
{
	mWidth = width;
	mHeight = height;
	renderer = new Renderer(TEXT_BACKGROUND);
}
void BackgroundManagerC::update(DWORD newMS)
{
	Vector2 convertedPosition;
	Vector2 screenSize;
	CameraManagerC::getInstance()->getCameraPosition(mPosition);

	convertedPosition = mPosition;
	mPosition.x = 0;
	mPosition.y = 0;
	CameraManagerC::getInstance()->getCameraSize(screenSize);
	Vector2::convertScreenToImageCoordinates(&convertedPosition);
	Vector2 texCoord = convertedPosition;
	Vector2::convertScreenToTextureCoordinates(&texCoord);

	mTextureCoordinates.x = texCoord.x;
	mTextureCoordinates.y = texCoord.y;
	mTextureCoordinates.width = CAMERA_WIDTH;
	mTextureCoordinates.height = CAMERA_HEIGHT;
}
void BackgroundManagerC::renderBackground()
{



	renderer->DrawSprite(mPosition, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, mTextureCoordinates);


};
