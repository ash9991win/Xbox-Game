#include<stdio.h>
#include"Constants.h"
#include"GameOverManager.h"
GameOverManagerC* GameOverManagerC::sInstance = NULL;

GameOverManagerC* GameOverManagerC::createInstance()
{
	if (sInstance != NULL)
	{
		return sInstance;
	}
	else
	{
		sInstance = new GameOverManagerC();
		return sInstance;
	}
}
void GameOverManagerC::init()
{
	renderer = new Renderer(TEXT_GAMEOVER);

}
void GameOverManagerC::render()
{
	Vector2 origin;
	origin.x = 0;
	origin.y = 0;
	TextureCoordinates texture;
	texture.x = 0;
	texture.y = 0;
	texture.width = 1.0f;
	texture.height = 1.0f;
	renderer->DrawSprite(origin, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, texture);
}
