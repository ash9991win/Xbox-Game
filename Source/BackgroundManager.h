#pragma once
#include"Renderer.h"
class BackgroundManagerC
{
public:
	static BackgroundManagerC* getInstance();
	void init(int width, int height);
	void renderBackground();
	void update(DWORD newMS);
private:
	static BackgroundManagerC* sInstance;
	BackgroundManagerC() {};
	Renderer *renderer;
	int mWidth, mHeight;
	Vector2 mPosition;
	TexCoord mTextureCoordinates;
};
