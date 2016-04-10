#include"LevelLoader.h"
#include"PrincessMaanger.h"
#include"PlayerManager.h"
#include"ScoreManager.h"
LevelLoader* LevelLoader::sInstance = NULL;

LevelLoader* LevelLoader::createInstance()
{
	if (sInstance != NULL)
	{
		return sInstance;
	}
	else
	{
		sInstance = new LevelLoader();
		return sInstance;
	}
}


void LevelLoader::LoadFile(TiXmlDocument &doc, const char * fileName){
#if IS_COMP
	doc.LoadFile(fileName);
#else
	// Open File for Read
	HANDLE fileHandler = CreateFile((LPCSTR)fileName,	// file name
										GENERIC_READ,	// access mode
									 FILE_SHARE_READ,	// share mode
												NULL,	// SD (Ignore, mark NULL)
										OPEN_ALWAYS,//OPEN_EXISTING,	// how to create
								FILE_ATTRIBUTE_NORMAL,	// file attributes
												NULL);	// handle to template file (Un-implemented, Mark NULL)

	// If file does not exist, throw exception
	if( fileHandler == INVALID_HANDLE_VALUE){
		throw 0;
	}

	// Get File Size to allocate
	DWORD fileSize = GetFileSize(fileHandler,		// handle to file
										NULL);		// high-order doubleword of file size (can be NULL)
	
	// Allocate memory from local heap
	HANDLE fileData = LocalAlloc(LMEM_FIXED, fileSize);

	// Read files to memory
	DWORD bytesRead;
	BOOL result = ReadFile(  fileHandler,	// handle to file
								fileData,	// data buffer
								fileSize,	// number of bytes to read
								&bytesRead,	// number of bytes read
									NULL);	// for overlapped buffers only

	// If the function fails, the return value is zero
	if(result == 0 || bytesRead != fileSize){
		throw 0;
	}

	// Parse data using memory
	doc.Parse((const char*)fileData, 0, TIXML_ENCODING_UTF8);

	// Free memory
	if(LocalFree(fileData) != NULL){
		throw 0;
	}
#endif
}

void LevelLoader::LoadLevel(int levelNo)
{
	TiXmlDocument levelDocument;
	//coordinateDocument.LoadFile("Coordinates.xml");
	//levelDocument.LoadFile("Levels.xml");
	LoadFile(coordinateDocument, XML_COORDINATE);
	LoadFile(levelDocument, XML_LEVELS);
	char levelName[10];
	sprintf(levelName, "LEVEL%d", levelNo);
	TiXmlElement *level1 = levelDocument.FirstChildElement(levelName);

	PlayerManager::getInstance()->mPosition.x = (float)(atof(level1->FirstChildElement("PLAYER_START")->Attribute("x"))) * IMAGE_TO_SCREEN_X;
	PlayerManager::getInstance()->mPosition.y = (float)(atof(level1->FirstChildElement("PLAYER_START")->Attribute("y"))) * IMAGE_TO_SCREEN_Y;

	TiXmlElement *discElement;
	TiXmlElement *noDiscs = level1->FirstChildElement("DISCS");
	int noOfDiscs = (int)atof(noDiscs->Attribute("NO"));

	for (int i = 1; i < noOfDiscs + 1; i++)
	{
		char DISC_NAME[20];
		sprintf(DISC_NAME, "DISC_%d", i);
		discElement = level1->FirstChildElement(DISC_NAME);
		Discs *newDisc = new Discs();
		newDisc->discType = /*(DISC_TYPE)(getRangedRandom(0, 2) % 2);	*/(int)atof(discElement->Attribute("type"));;
		if (newDisc->discType > 0 && newDisc->discType < 9)
		{
			newDisc->discType = JUMPABLE_DISC;
		}
		else if (newDisc->discType > 8 && newDisc->discType < 12 )
		{
			newDisc->discType = ENEMY_DISC;
		}
		else
		{
			newDisc->discType = MEGA_JUMP;
		}

#if IS_COMP
		newDisc->position.x = (float32_t)atof(discElement->Attribute("x"));
		newDisc->position.y = (float32_t)atof(discElement->Attribute("y"));
		newDisc->radius =			(float32_t)atof(discElement->Attribute("radius")) ;
#else
		newDisc->position.x = (float32_t)atof(discElement->Attribute("x")) * IMAGE_TO_SCREEN_X;
		newDisc->position.y = (float32_t)atof(discElement->Attribute("y")) * IMAGE_TO_SCREEN_Y;
		newDisc->radius =			(float32_t)atof(discElement->Attribute("radius")) * IMAGE_TO_SCREEN_X;
#endif
		newDisc->direction =		atof(discElement->Attribute("direction"));
		newDisc->spokeRadius =		newDisc->radius * SPOKE_RADIUS_FACTOR;
		newDisc->center.x =			newDisc->position.x + newDisc->radius;
		newDisc->center.y =			newDisc->position.y + newDisc->radius;
		newDisc->speed =			(float32_t)atof(discElement->Attribute("speed"));
		newDisc->currentAngle =		0;
		newDisc->eyeCoordinates =	getEye();
		newDisc->eyePosition.x =	newDisc->center.x;
		newDisc->eyePosition.y =	newDisc->center.y;
		newDisc->eyeWidth =			newDisc->radius / 4.0f;
		newDisc->eyeHeight =		newDisc->radius / 4.0f;
		newDisc->smilePosition.x =	newDisc->center.x - newDisc->radius / 3.2f;
		newDisc->smilePosition.y =	newDisc->center.y + newDisc->radius / 3.0f;
		newDisc->smileHeight =		newDisc->radius / 3.0f;
		newDisc->smileWidth =		newDisc->radius / 1.5f;
		newDisc->isVisible =		true;
		newDisc->isVisited =		false;
		newDisc->canSeePlayer =		false;
		newDisc->discCoordinates =	getRandomDisc((int)atof(discElement->Attribute("type")));
		newDisc->smileCoordinates =	getSmile(atof(discElement->Attribute("smile")),newDisc->discType);
		newDisc->spokeCoordinates =	getDiscSpoke(newDisc->discType);
		newDisc->spokePosition.x =	newDisc->position.x + newDisc->radius - newDisc->spokeRadius;
		newDisc->spokePosition.y =	newDisc->position.y + newDisc->radius - newDisc->spokeRadius;
		newDisc->collider.radius =	newDisc->spokeRadius ;
		newDisc->collider.mCenter.x=newDisc->center.x;
		newDisc->collider.mCenter.y=newDisc->center.y;
	
		discList->Append(newDisc);
	}

	TiXmlElement *princessElement;
	for (int i = 0; i < NUMBER_OF_PRINCESS_FRAMES; i++)
	{
		char princessName[20];
		sprintf(princessName, "PRINCESS_%d", (i + 1));
		Vector2 position;
		princessElement = coordinateDocument.FirstChildElement(princessName);
		PrincessManager::getInstance()->princessFrame[i] = getTextureData(princessName);
	
	}
	princessElement = level1->FirstChildElement("WIN_POINT");
	Vector2 winLocation;
	winLocation.x = (float32_t)atof(princessElement->Attribute("x")) * IMAGE_TO_SCREEN_X;
	winLocation.y = (float32_t)atof(princessElement->Attribute("y")) * IMAGE_TO_SCREEN_Y;
	PrincessManager::getInstance()->setPosition(winLocation);

	PrincessManager::getInstance()->mWidth =			(float)atof(princessElement->Attribute("width"));
	PrincessManager::getInstance()->mHeight =			(float)atof(princessElement->Attribute("height"));
	PrincessManager::getInstance()->balconyPosition.x =	winLocation.x;
	PrincessManager::getInstance()->balconyPosition.y =	winLocation.y + PrincessManager::getInstance()->mHeight /2;
	PrincessManager::getInstance()->winDisc =			getTextureData("WIN_DISC");
	PrincessManager::getInstance()->balcony =			getTextureData("BALCONY");

	PrincessManager::getInstance()->collider.mCenter = PrincessManager::getInstance()->getPosition();
	PrincessManager::getInstance()->collider.mCenter.x += PrincessManager::getInstance()->mWidth / 2;
	PrincessManager::getInstance()->collider.mCenter.y += PrincessManager::getInstance()->mWidth / 2;
	PrincessManager::getInstance()->collider.radius = PrincessManager::getInstance()->mWidth / 2;

	int noOfCollectible = atof(level1->FirstChildElement("COLLECTIBLE")->Attribute("NO"));
	ScoreManagerC::GetInstance()->totalCollectibles = noOfCollectible;
	TiXmlElement *fireElement;
	for (int i = 1; i < noOfCollectible + 1; i++)
	{
		FirePoint *fire = new FirePoint();
		char fireText[20];
		sprintf(fireText, "FIRE_%d", i);
		fireElement = level1->FirstChildElement(fireText);

		/*
		given an angle and a disc ID we have to find the corresponding disc number too. 

		then we will know it's center. Then we will calculate it's position as 





		*/
		float angleOfFlame = atof(fireElement->Attribute("angle"));
		int discID = atof(fireElement->Attribute("disc"));

		discLoader->Start();
		for (int counter = 0; counter < discID - 1; counter++)
		{
			discLoader->forth();
		}
		Discs *currentDisc = discLoader->data();
		//Now to get the position, 
		//fire->mPosition.x = atof(fireElement->Attribute("x")) * IMAGE_TO_SCREEN_X;
		//fire->mPosition.y = atof(fireElement->Attribute("y")) * IMAGE_TO_SCREEN_Y;
		fire->mPosition.x = currentDisc->center.x + currentDisc->spokeRadius * cos(angleOfFlame * DEG_TO_RAD)  - 10;
		fire->mPosition.y = currentDisc->center.y + currentDisc->spokeRadius * sin(angleOfFlame * DEG_TO_RAD) - 10 ;

		fire->isVisible = true;
		fire->mWidth = atof(fireElement->Attribute("width"));
		fire->mHeight = atof(fireElement->Attribute("height"));
		fire->currentFrame = 0;
		fire->collider.mCenter.x = fire->mPosition.x;
		fire->collider.mCenter.y = fire->mPosition.y;
		fire->collider.radius = fire->mWidth / 2 ;
		for (int j = 1; j < 5; j++)
		{
			char fireCoord[6];
			sprintf(fireCoord, "FIRE_%d", j);
			fire->fireCoordinates[j - 1] = getTextureData(fireCoord);
		}
		collectibleList->Append(fire);
	}
	int noOfText = atof(level1->FirstChildElement("TEXT")->Attribute("NO"));
	TiXmlElement *textElement;

	for (int i = 1; i < (noOfText + 1); i++)
	{
		textToDisplay *text = new textToDisplay();
		char textValue[10];
		sprintf(textValue, "TEXT_%d", i);
		textElement = level1->FirstChildElement(textValue);
		text->currentText = new char[20];
		strcpy(text->currentText, (textElement->Attribute("value")));
		text->mPosition.x = atof(textElement->Attribute("x")) * IMAGE_TO_SCREEN_X / SCREEN_WIDTH;
		text->mPosition.y = atof(textElement->Attribute("y")) * IMAGE_TO_SCREEN_Y / SCREEN_HEIGHT;

		text->dimension.x = atof(textElement->Attribute("width")) * IMAGE_TO_SCREEN_X / SCREEN_WIDTH;
		text->dimension.y = atof(textElement->Attribute("height")) * IMAGE_TO_SCREEN_X / SCREEN_WIDTH;

		textList->Append(text);
	}
	
}

TexCoord LevelLoader::getRandomDisc(int discIDno)
{
	TexCoord smile_coord;
	char discID[100];
	sprintf(discID, "DISC_%d", discIDno);
	/*sprintf(discID, "JUMP_DISC1"); */
	Vector2 newXy;
	newXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(discID)->Attribute("x")) ;
	newXy.y = (float32_t)atof(coordinateDocument.FirstChildElement(discID)->Attribute("y")) ;
	Vector2::convertScreenToTextureCoordinates(&newXy);

	Vector2 rightXy;
	rightXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(discID)->Attribute("rightX"));
	rightXy.y = (float32_t)atof((coordinateDocument.FirstChildElement(discID)->Attribute("rightY")));
	smile_coord.x = newXy.x;
	smile_coord.y = newXy.y;
	Vector2::convertScreenToTextureCoordinates(&rightXy);
	smile_coord.width = abs(rightXy.x - smile_coord.x);
	smile_coord.height = abs(rightXy.y - smile_coord.y);
	return smile_coord;
}
TexCoord LevelLoader::getEye()
{
	TexCoord smile_coord;
	Vector2 newXy;
	newXy.x = (float32_t)atof(coordinateDocument.FirstChildElement("EYE")->Attribute("x"));
	newXy.y = (float32_t)atof(coordinateDocument.FirstChildElement("EYE")->Attribute("y"));
	Vector2::convertScreenToTextureCoordinates(&newXy);

	Vector2 rightXy;
	rightXy.x = (float32_t)atof(coordinateDocument.FirstChildElement("EYE")->Attribute("rightX"));
	rightXy.y = (float32_t)atof((coordinateDocument.FirstChildElement("EYE")->Attribute("rightY")));
	smile_coord.x = newXy.x;
	smile_coord.y = newXy.y;
	Vector2::convertScreenToTextureCoordinates(&rightXy);
	smile_coord.width = abs(rightXy.x - smile_coord.x);
	smile_coord.height = abs(rightXy.y - smile_coord.y);
	return smile_coord;
	return smile_coord;
}
TexCoord LevelLoader::getSmile(int smileNo,int discType)
{
	TexCoord smile_coord;
	if (discType == JUMPABLE_DISC)
	{
		int randomDiscNumber = getRangedRandom(1, 4);
		char smileID[100];
		sprintf(smileID, "SMILE_%d", smileNo);
		Vector2 newXy;
		newXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("x"));
		newXy.y = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("y"));
		Vector2::convertScreenToTextureCoordinates(&newXy);

		Vector2 rightXy;
		rightXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("rightX"));
		rightXy.y = (float32_t)atof((coordinateDocument.FirstChildElement(smileID)->Attribute("rightY")));
		smile_coord.x = newXy.x;
		smile_coord.y = newXy.y;
		Vector2::convertScreenToTextureCoordinates(&rightXy);
		smile_coord.width = abs(rightXy.x - smile_coord.x);
		smile_coord.height = abs(rightXy.y - smile_coord.y);
		return smile_coord;
	}
	else if (discType == ENEMY_DISC)
	{
		char smileID[100];
		sprintf(smileID, "SMILE_%d", smileNo);
		Vector2 newXy;
		newXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("x"));
		newXy.y = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("y"));
		Vector2::convertScreenToTextureCoordinates(&newXy);

		Vector2 rightXy;
		rightXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("rightX"));
		rightXy.y = (float32_t)atof((coordinateDocument.FirstChildElement(smileID)->Attribute("rightY")));
		smile_coord.x = newXy.x;
		smile_coord.y = newXy.y;
		Vector2::convertScreenToTextureCoordinates(&rightXy);
		smile_coord.width = abs(rightXy.x - smile_coord.x);
		smile_coord.height = abs(rightXy.y - smile_coord.y);
		return smile_coord;
	} else {
		
	}
}
TexCoord LevelLoader::getRandomEnemyDisc(int enemyID)
{
	TexCoord smile_coord;
	int randomDiscNumber = getRangedRandom(1, 4);
	char smileID[100];
	sprintf(smileID, "ENEMY_DISC%d", enemyID);
	Vector2 newXy;
	newXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("x"));
	newXy.y = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("y"));
	Vector2::convertScreenToTextureCoordinates(&newXy);

	Vector2 rightXy;
	rightXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("rightX"));
	rightXy.y = (float32_t)atof((coordinateDocument.FirstChildElement(smileID)->Attribute("rightY")));
	smile_coord.x = newXy.x;
	smile_coord.y = newXy.y;
	Vector2::convertScreenToTextureCoordinates(&rightXy);
	smile_coord.width = abs(rightXy.x - smile_coord.x);
	smile_coord.height = abs(rightXy.y - smile_coord.y);
	return smile_coord;
	return smile_coord;
}
TexCoord LevelLoader::getDiscSpoke(int discType)
{
	
	TexCoord smile_coord;
	if (discType == JUMPABLE_DISC)
	{
		Vector2 newXy;
		newXy.x = (float32_t)atof(coordinateDocument.FirstChildElement("DISC_FRIENDLY")->Attribute("x"));
		newXy.y = (float32_t)atof(coordinateDocument.FirstChildElement("DISC_FRIENDLY")->Attribute("y"));
		Vector2::convertScreenToTextureCoordinates(&newXy);

		Vector2 rightXy;
		rightXy.x = (float32_t)atof(coordinateDocument.FirstChildElement("DISC_FRIENDLY")->Attribute("rightX"));
		rightXy.y = (float32_t)atof((coordinateDocument.FirstChildElement("DISC_FRIENDLY")->Attribute("rightY")));
		smile_coord.x = newXy.x;
		smile_coord.y = newXy.y;
		Vector2::convertScreenToTextureCoordinates(&rightXy);
		smile_coord.width = abs(rightXy.x - smile_coord.x);
		smile_coord.height = abs(rightXy.y - smile_coord.y);
		return smile_coord;
	}
	else if (discType == ENEMY_DISC)
	{
		Vector2 newXy;
		newXy.x = (float32_t)atof(coordinateDocument.FirstChildElement("DISC_SPIKE")->Attribute("x"));
		newXy.y = (float32_t)atof(coordinateDocument.FirstChildElement("DISC_SPIKE")->Attribute("y"));
		Vector2::convertScreenToTextureCoordinates(&newXy);

		Vector2 rightXy;
		rightXy.x = (float32_t)atof(coordinateDocument.FirstChildElement("DISC_SPIKE")->Attribute("rightX"));
		rightXy.y = (float32_t)atof((coordinateDocument.FirstChildElement("DISC_SPIKE")->Attribute("rightY")));
		smile_coord.x = newXy.x;
		smile_coord.y = newXy.y;
		Vector2::convertScreenToTextureCoordinates(&rightXy);
		smile_coord.width = abs(rightXy.x - smile_coord.x);
		smile_coord.height = abs(rightXy.y - smile_coord.y);
		return smile_coord;
	} else {
	}
}
TexCoord LevelLoader::getDiscSpike()
{
	TexCoord smile_coord;
	Vector2 newXy;
	newXy.x = (float32_t)atof(coordinateDocument.FirstChildElement("DISC_SPIKE")->Attribute("x"));
	newXy.y = (float32_t)atof(coordinateDocument.FirstChildElement("DISC_SPIKE")->Attribute("y"));
	Vector2::convertScreenToTextureCoordinates(&newXy);

	Vector2 rightXy;
	rightXy.x = (float32_t)atof(coordinateDocument.FirstChildElement("DISC_SPIKE")->Attribute("rightX"));
	rightXy.y = (float32_t)atof((coordinateDocument.FirstChildElement("DISC_SPIKE")->Attribute("rightY")));
	smile_coord.x = newXy.x;
	smile_coord.y = newXy.y;
	Vector2::convertScreenToTextureCoordinates(&rightXy);
	smile_coord.width = abs(rightXy.x - smile_coord.x);
	smile_coord.height = abs(rightXy.y - smile_coord.y);
	return smile_coord;
}
TexCoord LevelLoader::getEnemySmile(int smileIDno)
{
	TexCoord smile_coord;
	char smileID[100];
	sprintf(smileID, "ENEMY_SMILE%d", smileIDno);
	Vector2 newXy;
	newXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("x"));
	newXy.y = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("y"));
	Vector2::convertScreenToTextureCoordinates(&newXy);

	Vector2 rightXy;
	rightXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("rightX"));
	rightXy.y = (float32_t)atof((coordinateDocument.FirstChildElement(smileID)->Attribute("rightY")));
	smile_coord.x = newXy.x;
	smile_coord.y = newXy.y;
	Vector2::convertScreenToTextureCoordinates(&rightXy);
	smile_coord.width = abs(rightXy.x - smile_coord.x);
	smile_coord.height = abs(rightXy.y - smile_coord.y);
	return smile_coord;
}
TexCoord LevelLoader::getTextureData(char* smileID)
{
	TexCoord smile_coord;
	Vector2 newXy;
	newXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("x"));
	newXy.y = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("y"));
	Vector2::convertScreenToTextureCoordinates(&newXy);

	Vector2 rightXy;
	rightXy.x = (float32_t)atof(coordinateDocument.FirstChildElement(smileID)->Attribute("rightX"));
	rightXy.y = (float32_t)atof((coordinateDocument.FirstChildElement(smileID)->Attribute("rightY")));
	smile_coord.x = newXy.x;
	smile_coord.y = newXy.y;
	Vector2::convertScreenToTextureCoordinates(&rightXy);
	smile_coord.width = abs(rightXy.x - smile_coord.x);
	smile_coord.height = abs(rightXy.y - smile_coord.y);
	return smile_coord;
}
void LevelLoader::setDiscList(LinkedList<Discs*> *newList)
{
	discList = newList;
	discLoader = new ListIterator<Discs*>(discList, discList->m_head);
}


void LevelLoader::setFireList(LinkedList<FirePoint*> *newList)
{
	collectibleList = newList;
}
void LevelLoader::setTextList(LinkedList<textToDisplay*> *newList)
{
	textList = newList;
}
