#pragma once
#ifndef CONSTANTS_H
#define CONSTANS_H
#include <math.h>
#include "baseTypes.h"
const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = 1024;
#if IS_COMP
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
#else
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
#endif

const float SCREEN_TO_IMAGE_X = IMAGE_WIDTH / (float)SCREEN_WIDTH;
const float SCREEN_TO_IMAGE_Y = IMAGE_HEIGHT / (float)SCREEN_HEIGHT;

const float IMAGE_TO_SCREEN_X = 1 / SCREEN_TO_IMAGE_X;
const float IMAGE_TO_SCREEN_Y = 1 / SCREEN_TO_IMAGE_Y;

const float_t GRAVITY = 10.0f;
const float_t PLAYER_JUMP_DISTANCE = 10;
const float_t  DEG_TO_RAD = (3.14159f / 180.0f);
const float JUMP_FORCE = 48.5f;
const int PLAYER_STARTING_POSITION_X = 50;
const int PLAYER_STARTING_POSITION_Y = 0;
const float CAMERA_WIDTH = 0.25f;
const float CAMERA_HEIGHT = 0.25f;
const int MIN_RADIUS = 80;
const int MAX_RADIUS = 100;
const float SPOKE_RADIUS_FACTOR = 1.125f;
const int NUMBER_OF_PRINCESS_FRAMES = 9;
const float FPS = 6;
const int MAX_LEVELS = 2;
const float ANIMATION_DURATION = 2.0f;

#if IS_COMP
const char XML_COORDINATE[]	= "Coordinates.xml";
const char XML_LEVELS[]		= "Levels.xml";
#else
const char XML_COORDINATE[] = "D:\\media\\Coordinates.xml";
const char XML_LEVELS[] = "D:\\media\\Levels.xml";
#endif
#endif
