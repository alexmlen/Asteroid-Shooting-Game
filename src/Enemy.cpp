#include "ofMain.h"
#include "Enemy.h"
//Alexander Len
//March 31, 2019
//
//Creates Enemies and a SpriteSystem to store these enemies in


Enemy::Enemy(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 7680;    // milliseconds
	started = false;

	lastSpawned = 0;
	rate = 3;			// sprites/sec
	haveChildImage = false;
	haveImage = false;
	velocity = ofVec3f(0, 100, 0);
	drawable = true;
	width = 50;
	height = 50;
	childWidth = 10;
	childHeight = 10;
}

void Enemy::draw() {
	sys->draw();
}

void Enemy::update() {
	sys->update();
	if (!started) return;

	float time = ofGetElapsedTimeMillis();
	if ((time - lastSpawned) > (1000.0 / rate)) {
		Sprite sprite;
		if (haveChildImage) sprite.setImage(childImage);
		int randomVel = (int)ofRandom(100, 1000);
		sprite.velocity = ofVec3f(0, randomVel, 0);
		sprite.lifespan = (ofGetWindowHeight()*1000)/randomVel;
		int randomPos = (int)ofRandom(0, ofGetWindowWidth()+1);
		sprite.setPosition(ofVec3f(randomPos, 0, 0));
		sprite.birthtime = time;
		sprite.width = childWidth;
		sprite.height = childHeight;
		sys->add(sprite);
		lastSpawned = time;
	}
}

void Enemy::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void Enemy::stop() {
	started = false;
}

void Enemy::restart() {
	started = true;
}

void Enemy::setLifespan(float life) {
	lifespan = life;
}

void Enemy::setVelocity(ofVec3f v) {
	velocity = v;
}

void Enemy::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
	childWidth = img.getWidth();
	childHeight = img.getHeight();
}

void Enemy::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = img.getWidth();
	height = img.getHeight();
}

void Enemy::setRate(float r) {
	rate = r;
}

float Enemy::maxDistPerFrame() {
	return  velocity.length() / ofGetFrameRate();
}
