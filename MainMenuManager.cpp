#include"MainMenuManager.h"
#include<stdio.h>
#include"Constants.h"
MainMenuManagerC* MainMenuManagerC::sInstance = NULL;

MainMenuManagerC* MainMenuManagerC::createInstance()
{
	if (sInstance != NULL)
	{
		return sInstance;
	}
	else
	{
		sInstance = new MainMenuManagerC();
		return sInstance;
	}
}
void MainMenuManagerC::init()
{
	menurenderer = new Renderer(TEXT_MENU);
}
void MainMenuManagerC::render()
{
	Vector2 origin;
	origin.x = 0;
	origin.y = 0;
	TextureCoordinates texture;
	texture.x = 0;
	texture.y = 0;
	texture.width = 1.0f;
	texture.height = 1.0f;
	menurenderer->DrawSprite(origin, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, texture);
}
