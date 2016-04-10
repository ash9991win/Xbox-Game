//#pragma once
//#include<Windows.h>
//#include"Constants.h"
//#include"physics.h"
//#include"LinkedList.h"
//#include"Renderer.h"
//
//class Slide
//{
//public:
//	Vector2 startPosition;
//	Vector2 endPosition;
//	float angleOfInclination;
//	float lengthOfSlide;
//	int   numberOfMiddleElements;
//	float startSlideWidth;
//	float middleSlideWidth;
//	float endSlideWidth;
//	TexCoord slideStart;
//	TexCoord slideMiddle;
//	TexCoord slideEnd;
//	Rect    collider;
//
//};
//class SlideManager
//{
//public:
//	static SlideManager* createInstance();
//	static SlideManager* getInstance();
//	void init();
//	void Update(DWORD newMS);
//	void render();
//	ListIterator<Slide*>* getSlideIterator();
//	LinkedList<Slide*>*    getSlideList();
//private:
//	static SlideManager* sInstance;
//	LinkedList<Slide*>* slideList;
//	ListIterator<Slide*>* slideIterator;
//	Renderer *slideRenderer;
//	SlideManager() {};
//
//};