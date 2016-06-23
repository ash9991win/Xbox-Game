#pragma once
#pragma once
#include"Renderer.h"
#include"LinkedList.h"
#include"Constants.h"
#include"FontManager.h"
class textToDisplay
{
public:
	 char *currentText;
	Vector2 mPosition;
	Vector2 dimension;


};
class LevelTextManager
{
public:
	static LevelTextManager* getInstance() {
		return sInstance;
	};
	static LevelTextManager* createInstance();
	void update(float_t newMS);
	void init();
	void render();
	LinkedList<textToDisplay*>* getTextList() {
		return textList;
	};
	ListIterator<textToDisplay*>* getIterator() { return textListIterator; };
private:
	LevelTextManager() {};
	static LevelTextManager* sInstance;
	LinkedList<textToDisplay*> *textList;
	ListIterator<textToDisplay*> *textListIterator;

};