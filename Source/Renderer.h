#pragma once
#include"physics.h"
#include"baseTypes.h"

typedef enum {
	INVALID_TEXT_ID = -1,
	TEXT_MENU = 0,
	TEXT_BACKGROUND,
	TEXT_PLAYER,
	TEXT_DISC,
	TEXT_SCORE_FONT,
	TEXT_GAMEOVER,
	TEXT_TRANSITION,
	NUM_OF_TEXT_ID
}TEXT_ID;

#if IS_XBOX

#include <xtl.h>
#include <xgraphics.h>
#include <stdio.h>
#include <d3dx8.h>
#include "XboxFramework\Resource.h"

#else

#include<gl/glut.h>

#endif


class Renderer
{
private:

#if IS_XBOX
	static HRESULT InitD3D();
	static HRESULT LoadPackedResource();
#else
	static GLuint mTextureID[NUM_OF_TEXT_ID];
#endif

public:
	static void init2();
	static void Begin();
	static void End();
	void DrawSprite(Vector2 position, float width, float height, TexCoord textureCoordinate, float rotationAngle, Vector2 rotationPoint);
	void DrawSprite(Vector2 position, float width, float height, TexCoord textureCoordinates);

	TEXT_ID currentID;
	Renderer(TEXT_ID textId) {
		currentID = textId;
	}
};
