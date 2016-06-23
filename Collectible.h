#pragma once
#include"Renderer.h"
#include"LinkedList.h"
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
		return sInstance;
	};
	static Collectible* createInstance();
	void update(float_t newMS);
	void init();
	void render();
	LinkedList<FirePoint*>* getFireList();
	ListIterator<FirePoint*>* getIterator() { return collectibleIterator; };
private:
	Collectible() {};
	static Collectible* sInstance;
	float_t currentTime;
	float_t animationTime;
	Renderer *fireRenderer;
	LinkedList<FirePoint*> *collectibleList;
	ListIterator<FirePoint*> *collectibleIterator;

};