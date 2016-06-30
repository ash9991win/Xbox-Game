#pragma once
#pragma once
#include"Renderer.h"
#include"Vector.h"
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
		if (sInstance == nullptr)
			sInstance = new LevelTextManager();
		return sInstance;
	};
	void update(float_t newMS);
	void init();
	void render();
	Library::Vector<textToDisplay*>* getTextList() {
		return &textList;
	};
private:
	LevelTextManager() {};
	static LevelTextManager* sInstance;
	Library::Vector<textToDisplay*> textList;

};