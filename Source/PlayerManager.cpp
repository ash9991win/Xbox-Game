#define STATE_MANAGER_CPP
#include "baseTypes.h"

//#include<Windows.h>

#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <stdlib.h>
#include <math.h>												// Header File For Math Operations

#if IS_COMP
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include <gl\glut.h>
#include <assert.h>
#include "openglframework.h"
#endif

#include "random.h"
#include "BackgroundManager.h"
#include "Constants.h"
#include "InputManager.h"
#include "PlayerManager.h"
#include "CameraManager.h"
#include "LevelLoader.h"
PlayerManager* PlayerManager::sInstance = nullptr;
PlayerManager* PlayerManager::getInstance()
{
	if (sInstance == nullptr)
		sInstance = new PlayerManager();
	return sInstance;
}
Vector2 PlayerManager::getPosition()
{

	return mPosition;
}
Vector2 PlayerManager::getHeading()
{
	return mHeading;
}

void PlayerManager::changeCurrentState(PlayerStates newState)
{
	if (newState != currentState)
	{
		if (newState != JUMPING_STATE)
		{
			currentState = newState;
			currentTime = 0;
			mVelocity.x = 0;
			mVelocity.y = 0;
		}
		else
		{
			currentTime = 0;
			Vector2 dir = mPosition;
			dir -= rotationPoint;
			//dir = dir.normalize();
		
			// *= JUMP_FORCE;
			float angleBetween = atan2f(dir.y, dir.x);
			//Initial velocity is a constant 
			mVelocity.x = JUMP_FORCE * cos(angleBetween);
			mVelocity.y = JUMP_FORCE * sin(angleBetween);
			currentState = JUMPING_STATE;
		}
	}
}

PlayerManager::PlayerManager() {
	playerRenderer = nullptr;
}

PlayerManager::~PlayerManager() {
	if (playerRenderer != nullptr) {
		delete playerRenderer;
	}
}

void PlayerManager::Init()
{
	amDead = false;
	mass = 1;
	gameOver = false;
	currentState = FALLING_STATE;
	TiXmlDocument coordinateDocument;
	LevelLoader::getInstance()->LoadFile(coordinateDocument, XML_COORDINATE);
	float x = (float)atof(coordinateDocument.FirstChildElement("PLAYER_FRAME1")->Attribute("x")) ;
	float y = (float)atof(coordinateDocument.FirstChildElement("PLAYER_FRAME1")->Attribute("y")) ;
	float_t rightX = (float_t)atof(coordinateDocument.FirstChildElement("PLAYER_FRAME1")->Attribute("rightX")) ;
	float_t rightY = (float_t)atof((coordinateDocument.FirstChildElement("PLAYER_FRAME1")->Attribute("rightY"))) ;
	
	Vector2 playerTexture;
	playerTexture.x = x;
	playerTexture.y = y;
	Vector2::convertScreenToTextureCoordinates(&playerTexture);
	
	Vector2 widthHeight;
	widthHeight.x = rightX;
	widthHeight.y = rightY;

	Vector2::convertScreenToTextureCoordinates(&widthHeight);
	playerFrames.x = playerTexture.x;
	playerFrames.y = playerTexture.y;

	playerFrames.width = abs(widthHeight.x - playerFrames.x);
	playerFrames.height = abs(widthHeight.y - playerFrames.y);

	currentTexture = playerFrames;
	for (int i = 1; i < 6; i++)
	{
		char newFrame[100] ;
		sprintf(newFrame, "FALL_FRAME%d", i);
		float x_fall = (float)atof(coordinateDocument.FirstChildElement(newFrame)->Attribute("x")) ;
		float y_fall = (float)atof(coordinateDocument.FirstChildElement(newFrame)->Attribute("y"));
		float_t rightX_fall = (float_t)atof(coordinateDocument.FirstChildElement(newFrame)->Attribute("rightX")) ;
		float_t rightY_fall = (float_t)atof((coordinateDocument.FirstChildElement(newFrame)->Attribute("rightY"))) ;
		
		Vector2 fallPlayerTexture;
		fallPlayerTexture.x = x_fall;
		fallPlayerTexture.y = y_fall;
		Vector2::convertScreenToTextureCoordinates(&fallPlayerTexture);

		Vector2 fallWidthHeight;
		fallWidthHeight.x = rightX_fall;
		fallWidthHeight.y = rightY_fall;
		Vector2::convertScreenToTextureCoordinates(&fallWidthHeight);
		FallMotion[i - 1].x = fallPlayerTexture.x;
		FallMotion[i - 1].y = fallPlayerTexture.y;
		FallMotion[i-1].width = abs(fallWidthHeight.x - fallPlayerTexture.x);
		FallMotion[i-1].height = abs(fallWidthHeight.y - fallPlayerTexture.y);
	}

	for (int i = 1; i < 9; i++)
	{
		char newFrame[100];
		sprintf(newFrame, "DEAD_FRAME%d", i);
		float x_fall = atof(coordinateDocument.FirstChildElement(newFrame)->Attribute("x"));
		float y_fall = atof(coordinateDocument.FirstChildElement(newFrame)->Attribute("y"));
		float_t rightX_fall = atof(coordinateDocument.FirstChildElement(newFrame)->Attribute("rightX"));
		float_t rightY_fall = atof((coordinateDocument.FirstChildElement(newFrame)->Attribute("rightY")));
		Vector2 fallPlayerTexture;
		fallPlayerTexture.x = x_fall;
		fallPlayerTexture.y = y_fall;
		Vector2::convertScreenToTextureCoordinates(&fallPlayerTexture);
		Vector2 fallWidthHeight;
		fallWidthHeight.x = rightX_fall;
		fallWidthHeight.y = rightY_fall;
		Vector2::convertScreenToTextureCoordinates(&fallWidthHeight);
		deadAnimation[i - 1].x = fallPlayerTexture.x;
		deadAnimation[i - 1].y = fallPlayerTexture.y;
		deadAnimation[i - 1].width = abs(fallWidthHeight.x - fallPlayerTexture.x);
		deadAnimation[i - 1].height = abs(fallWidthHeight.y - fallPlayerTexture.y);
	}

	if (playerRenderer == nullptr) {
		playerRenderer = new Renderer(TEXT_PLAYER);
	}

	rotationAngle = 0;
	rotationSpeed = 0;
	rotationPoint.x = 0;
	rotationPoint.y = 0;
	mWidth = 30;
	mHeight = 30;
	mVelocity.x = mVelocity.y = 0;
	mPosition.x = PLAYER_STARTING_POSITION_X;
	mPosition.y = PLAYER_STARTING_POSITION_Y;
	direction = true;
	collider.mCenter.x = 0;
	collider.mCenter.y = 0; 
	collider.radius = (mWidth / 2);
	currentFrame = 0;
	currentTime = 0;
	animationTime = 0;
	rectCollider.x = 0;
	rectCollider.y = 0;
	rectCollider.height = mHeight;
	rectCollider.width = mWidth;

}
void PlayerManager::Update(DWORD newMS)
{

	switch (currentState) {
	case FALLING_STATE:
		mVelocity.y += GRAVITY * newMS / 1000.0f;
		mPosition.x += mVelocity.x;
		mPosition.y += mVelocity.y;
		break;
	case ROTATING_STATE:
	{
		currentTime = 0;
		if (!direction)
		{
			rotationAngle += rotationSpeed * newMS / 1000.0f;
		}
		else
		{
			rotationAngle -= rotationSpeed * newMS / 1000.0f;

		}

		mPosition.x = discRadius * cos(rotationAngle ) + rotationPoint.x - 20;
		mPosition.y = discRadius * sin(rotationAngle ) + rotationPoint.y - 20;

		break;
	}
	case LAUNCH_STATE:
	{

		currentTime += newMS / 10000.0f;
		mPosition.x += mVelocity.x * currentTime;
		mPosition.y += mVelocity.y * currentTime + (0.5 *GRAVITY *currentTime * currentTime);
		currentTime = 0;
		currentState = JUMPING_STATE;
		break;
	}
	case JUMPING_STATE:
	{
		if (isMegajump)
		{
			currentTime += newMS / 10000.0f;
			mPosition.x += 20 *mVelocity.x * currentTime;
			mPosition.y += 20 *mVelocity.y * currentTime;
	
		}
		else
		{
			currentTime += newMS / 10000.0f;
			mPosition.x += mVelocity.x * currentTime;
			mPosition.y += mVelocity.y * currentTime;
	
		}
		break;
	}
	case JUMPDOWN_STATE:
		mVelocity.y += GRAVITY * newMS / 1000.0f;
		mPosition.x += mVelocity.x;
		mPosition.y += mVelocity.y;

		break;
	case SLIDING_STATE:
		printf("IN SLIDING \n");
		mVelocity.y += newMS / 1000.0f * sin(-slidingAngle );
		mVelocity.x += cos(-slidingAngle ) * newMS / 1000.0f;

		mPosition.x += mVelocity.x;
		mPosition.y += mVelocity.y;

		break;
	case MEGA_STATE:
	
		break;
	default:
		break;
	}
	

	if (((mPosition.x < 0) ||(( mPosition.x + mWidth)  > (IMAGE_WIDTH )) ))
	{
		if (!amDead)
		{
			//gameOver = true;
			amDead = true;
			deadanimationTime = 0;
			currentFrame = 0;
			currentState = MIN_STATE;
		}
	}
	if (((mPosition.y <0 )|| (mPosition.y + mHeight)  > (IMAGE_HEIGHT)))
	{

		//gameOver = true;
		if (!amDead)
		{
			amDead = true;
			deadanimationTime = 0;
			currentFrame = 0;
			currentState = MIN_STATE;
		}


	}

		collider.mCenter.x = mPosition.x + (mWidth /2 )  ;
		collider.mCenter.y = mPosition.y + (mWidth /2);




	if (amDead)
	{
		deadanimationTime += animationTime;
		if (deadanimationTime > 3)
		{
			gameOver = true;
		}
		animationTime += newMS / 1000.0f;
		if (animationTime > (1/ FPS ))
		{
			currentFrame++;
			currentTexture = deadAnimation[currentFrame];
			if (currentFrame > 7)
			{
				currentFrame = 0;
			}
			
			animationTime = 0;
		}
	}
}
void PlayerManager::Render()
{
	Vector2 cameraPosition;
	Vector2 newPosition;
     newPosition = mPosition;
   
	CameraManagerC::getInstance()->getCameraPosition(cameraPosition);
	newPosition.x -= cameraPosition.x;
	newPosition.y -= cameraPosition.y;	
	playerRenderer->DrawSprite(mPosition.findDiff(cameraPosition), mWidth, mHeight, currentTexture);
}
void PlayerManager::playFallAnimation()
{
	currentTexture = FallMotion[currentFrame];
	currentFrame++;
	if (currentFrame > 4)
	{
		currentFrame = 0;
	}

	Vector2::flipTexture(&currentTexture,RIGHT);

}
Circle PlayerManager::getCollider()
{
	return collider;
}
Rect PlayerManager::getRectCollider()
{
	return rectCollider;
}
void PlayerManager::setRotationAngle(float_t rotateAngle)
{
	rotationAngle = rotateAngle;
}
void PlayerManager::setRotationPoint(Vector2 point,float_t radius)
{
	rotationPoint = point;
	Vector2 relativeVector = mPosition;
	relativeVector.x -= rotationPoint.x;
	relativeVector.y -= rotationPoint.y;
	rotationAngle = atan2(relativeVector.y, relativeVector.x);
	discRadius = radius;
}
void PlayerManager::setRotationSpeed(float_t newSpeed)
{
	rotationSpeed = newSpeed;
}
void PlayerManager::setDirection(bool newDir)
{
	direction = newDir;
}
void PlayerManager::setDiscCollider(Circle other)
{
	discCollider = other;
}
bool PlayerManager::isFalling()
{
	return (currentState == FALLING_STATE);
}
bool PlayerManager::isJumping()
{
	return (currentState == JUMPING_STATE);
}
bool PlayerManager::isRotating()
{
	return (currentState == ROTATING_STATE);
}
bool PlayerManager::isSliding()
{
	return (currentState == SLIDING_STATE);
}
void PlayerManager::setSlidingPoints(float angle)
{
	slidingAngle = angle;
}
void PlayerManager::AddForce()
{
	Vector2 dirVector;
	 dirVector.x = mPosition.x - rotationPoint.x;
	 dirVector.y = mPosition.y - rotationPoint.y;
	 dirVector *= 3;
	 //F = m * a
	 Vector2 acceleration;
	 acceleration.x = (dirVector.x / 1);
	 acceleration.y = GRAVITY;

	 mVelocity.x += acceleration.x;
	 mVelocity.y += acceleration.y;


}
Vector2  PlayerManager::getRotatingPoint()
{
	return rotationPoint;
}
PlayerStates PlayerManager::getCurrentState()
{
	return currentState;
}
