#include "Sprite.h"
//Alexander Len
//March 31, 2019
//
//Basic Sprite Object

BaseObject::BaseObject() {
	trans = ofVec3f(0,0,0);
	scale = ofVec3f(1, 1, 1);
	rot = 0;
}

void BaseObject::setPosition(ofVec3f pos) {
	trans = pos;
}

Sprite::Sprite() {
	speed = 0;
	velocity = ofVec3f(0, 0, 0);
	lifespan = -1;      // lifespan of -1 => immortal 
	birthtime = 0;
	bSelected = false;
	haveImage = false;
	name = "UnamedSprite";
	width = 20;
	height = 20;
	color1 = (int)ofRandom(0, 256);
	color2 = (int)ofRandom(0, 256);
	color3 = (int)ofRandom(0, 256);
}

float Sprite::age() {
	return (ofGetElapsedTimeMillis() - birthtime);
}

void Sprite::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = image.getWidth();
	height = image.getHeight();
}


void Sprite::draw() {

	ofSetColor(255, 255, 255, 255);

	if (haveImage) {
		image.draw(-width / 2.0 + trans.x, -height / 2.0 + trans.y);
	}
	else {
		ofFill();
		ofSetColor(color1, color2, color3);
		ofDrawRectangle(-width / 2.0 + trans.x, -height / 2.0 + trans.y, width, height);
	}
}

void SpriteSystem::add(Sprite s) {
	sprites.push_back(s);
}

void SpriteSystem::remove(int i) {
	sprites.erase(sprites.begin() + i);
}

bool SpriteSystem::removeNear(ofVec3f point, float dist) {
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;
	bool destroyed = false;

	while (s != sprites.end()) {
		ofVec3f v = s->trans - point;
		if (v.length() < dist) {
			tmp = sprites.erase(s);
			s = tmp;
			destroyed = true;
		}
		else s++;
	}
	return destroyed;
}

void SpriteSystem::update() {

	if (sprites.size() == 0) return;
	vector<Sprite>::iterator s = sprites.begin();
	vector<Sprite>::iterator tmp;

	while (s != sprites.end()) {
		if (s->lifespan != -1 && s->age() > s->lifespan) {
			tmp = sprites.erase(s);
			s = tmp;
		}
		else s++;
	}

	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].trans += sprites[i].velocity / ofGetFrameRate();
	}
}

void SpriteSystem::draw() {
	for (int i = 0; i < sprites.size(); i++) {
		sprites[i].draw();
	}
}
