#pragma once
#include "baseTypes.h"
//#include<Windows.h>
#include"Renderer.h"
#include"LinkedList.h"
#include"baseTypes.h"
#include"physics.h"
#include"Constants.h"
class PrincessManager
{
public:
	static PrincessManager* getInstance() { return sInstance; }
	static PrincessManager* createInstance();
	void init();
	void Update(DWORD newMS);
	void render();
	void setPosition(Vector2 newPosition);
	Vector2 getPosition() {
		return mPosition;
	};
	TexCoord winDisc;
	TexCoord princessFrame[NUMBER_OF_PRINCESS_FRAMES];
	TexCoord balcony;
	TexCoord currentFrameTexture;
	float mWidth;
	float mHeight;
	bool amBurnt;
	Circle collider;
	bool isAnimationOver;
	Vector2 balconyPosition;
private:
	static PrincessManager* sInstance;
	PrincessManager() {};
	Vector2 mPosition;
	Renderer *princessRenderer;
	int currentFrame;
	float currentTime;
	float animatedTime;

};
