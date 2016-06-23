#pragma once
#include "baseTypes.h"
//#include<Windows.h>		// In baseTypes now 
#include "DiscManagerC.h"
//#include "SlideManager.h"
#include "tinyxml.h"
#include "Collectible.h"
#include"LevelTextManager.h"

class LevelLoader
{
public:
	static LevelLoader* createInstance();
	static LevelLoader* getInstance() { return sInstance; };

	void LoadFile(TiXmlDocument &doc, const char * fileName);
	void LoadLevel(int LevelNo);
	void setDIscIterator(ListIterator<Discs> *discIterator);
//	void setSlideIterator(ListIterator<Slide> *slideIterator);
	void setDiscList(LinkedList<Discs*> *discList);
//	void setSlideList(LinkedList<Slide*> *slideList);
	void setFireList(LinkedList<FirePoint*> *fireList);
	void setTextList(LinkedList<textToDisplay*> *textListValue);
	TexCoord getEye();
	TexCoord getRandomDisc(int discNo);
	TexCoord getSmile(int smileNo,int discType);
	TexCoord getRandomEnemyDisc(int enemyNo);
	TexCoord getEnemySmile(int smileId);
	TexCoord getDiscSpike();
	TexCoord getDiscSpoke(int discType);
	TexCoord getTextureData(char* slidePart);

private:
	TiXmlDocument coordinateDocument;
	ListIterator<Discs*> *discLoader;
	//ListIterator<Slide*> *slideLoader;
	LinkedList<Discs*> *discList;
	//LinkedList<Slide*> *slideList;
	LinkedList<FirePoint*> *collectibleList;
	LinkedList<textToDisplay*> *textList;
	static LevelLoader* sInstance;
	LevelLoader() {};

};
