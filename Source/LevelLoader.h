#pragma once
#include "baseTypes.h"
#include "DiscManagerC.h"
#include "tinyxml.h"
#include "Collectible.h"
#include"LevelTextManager.h"
#include"Vector.h"
class LevelLoader
{
public:
	static LevelLoader* getInstance() {
		if (sInstance == nullptr)
			sInstance = new LevelLoader();
		return sInstance;
	};

	void LoadFile(TiXmlDocument &doc, const char * fileName);
	void LoadLevel(int LevelNo);
	void setDiscList(Library::Vector<Discs*>& discList);
	void setFireList(Library::Vector<FirePoint*>& fireList);
	void setTextList(Library::Vector<textToDisplay*>& textListValue);
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
	Library::Vector<Discs*>::Iterator discLoader;
	//ListIterator<Slide*> *slideLoader;
	Library::Vector<Discs*> *discList;
	//LinkedList<Slide*> *slideList;
	Library::Vector<FirePoint*> *collectibleList;
	Library::Vector<textToDisplay*> *textList;
	static LevelLoader* sInstance;
	LevelLoader() {};

};
