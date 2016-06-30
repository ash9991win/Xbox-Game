#pragma once
#include "baseTypes.h" // Newly placed for XBox
#include "physics.h"
#include "tinyxml.h"
#include "Renderer.h"

//#include<Windows.h>

enum PlayerStates
{
	MIN_STATE, ROTATING_STATE,LAUNCH_STATE, JUMPING_STATE,JUMPDOWN_STATE,MEGA_STATE, FALLING_STATE,SLIDING_STATE, MAX_STATE
};
class PlayerManager
{
public:
	static PlayerManager* getInstance();
	~PlayerManager();
	void Init();
	void Update(DWORD milliseconds);
	void Render();
	Vector2 getPosition();
	void    AddForce();
	Vector2 getHeading();
	void    changeCurrentState(PlayerStates newState);
	void    setRotationPoint(Vector2 rotationPoint,float_t radius);
	void    setRotationSpeed(float_t rotSpeed);
	void    setRotationAngle(float_t rotAngle);
	void    setDirection(bool newDir);
	void    setDiscCollider(Circle newCollider);
	void    setSlidingPoints(float angleOfSlide);
	PlayerStates getCurrentState();
	bool    isFalling();
	bool    isRotating();
	bool    isJumping();
	bool    isSliding();
	Circle  getCollider();
	Rect    getRectCollider();
	void    playFallAnimation();
	bool    isgameOver() { return gameOver; };
	float_t deadanimationTime;
	bool    amDead;
	 float_t mWidth;
	 float_t mHeight;

	 Vector2  getRotatingPoint();
	 Vector2 mPosition;
	 float_t discRadius;
	 bool isMegajump;
	private:
	static PlayerManager* sInstance;
	Renderer *playerRenderer;
	PlayerManager();
	Vector2 mVelocity;
	Vector2 mHeading;
	Vector2 mSide;
	Vector2 rotationPoint;
	float_t rotationSpeed;
	float_t rotationAngle;
	float_t slidingAngle;
	PlayerStates currentState;
	TexCoord  playerFrames;
	TexCoord  FallMotion[4];
	TexCoord  deadAnimation[8];
	TexCoord  leftMovement;
	TexCoord  rightMovement;
	TexCoord  currentTexture;
	float_t spritePositionX; 
	float_t spritePostionY;
	int   currentFrame;
	float_t currentTime;
	float_t animationTime;
	float_t mass; 
	float_t maxSpeed;
	float_t maxRotationSpeed;
	bool  direction;
	Circle collider;
	Rect   rectCollider;
	Circle discCollider;
	float_t  distanceTravelled;
	float_t  distanceToCover;
	bool gameOver;
};
