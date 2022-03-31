#pragma once
#include "ofMain.h"
//Alexander Len
//March 31, 2019
//
//Basic Sprite Object

class BaseObject {
public:
	BaseObject();
	ofVec2f trans, scale;
	float	rot;
	bool	bSelected;
	void setPosition(ofVec3f);
};

class Sprite : public BaseObject {
public:
	Sprite();
	void draw();
	float age();
	void setImage(ofImage);
	float speed;    //   in pixels/sec
	ofVec3f velocity; // in pixels/sec
	ofImage image;
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	string name;
	bool haveImage;
	float width, height;
	int color1, color2, color3;
};

class SpriteSystem {
public:
	void add(Sprite);
	void remove(int);
	void update();
	bool removeNear(ofVec3f point, float dist);
	void draw();
	vector<Sprite> sprites;
};
