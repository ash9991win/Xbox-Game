#pragma once
#include"Renderer.h"
#include"Vector.h"
#include"Constants.h"
class FirePoint
{
public:
	bool isVisible;
	TexCoord fireCoordinates[4];
	Vector2 mPosition;
	float_t mWidth;
	float_t mHeight;
	int currentFrame;
	Circle collider;


};
class Collectible
{
public:
	static Collectible* getInstance() {
		if (sInstance == nullptr)
			sInstance = new Collectible();
		return sInstance;
	};
	void update(float_t newMS);
	void init();
	void render();
	Library::Vector<FirePoint*>* getFireList();
private:
	Collectible() {};
	static Collectible* sInstance;
	float_t currentTime;
	float_t animationTime;
	Renderer *fireRenderer;
	Library::Vector<FirePoint*> collectibleList;

};