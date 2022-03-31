#include "ofMain.h"
#include "Emitter.h"
//Alexander Len
//March 31, 2019
//
//Manages player emitter and lasers

Emitter::Emitter(SpriteSystem *spriteSys) {
	sys = spriteSys;
	lifespan = 200;    // milliseconds
	started = false;

	lastSpawned = 0;
	rate = 1;    // sprites/sec
	haveChildImage = false;
	haveImage = false;
	velocity = ofVec3f(0, -2000, 0);
	drawable = true;
	width = 50;
	height = 50;
	childWidth = 10;
	childHeight = 10;
	laser.load("audio/laser.wav");
}

void Emitter::draw() {
	if (drawable) {

		if (haveImage) {
			image.draw(-image.getWidth() / 2.0 + trans.x, -image.getHeight() / 2.0 + trans.y);
		}
		else {
			ofSetColor(0, 0, 255);
			ofDrawRectangle(-width / 2 + trans.x, -height / 2 + trans.y, width, height);
		}
	}
	sys->draw();
}

void Emitter::update() {
	sys->update();
	if (!started) return;

	float time = ofGetElapsedTimeMillis();
	if ((time - lastSpawned) > (1000.0 / rate)) {
		laser.play();
		Sprite sprite;
		if (haveChildImage) sprite.setImage(childImage);
		sprite.velocity = velocity;
		sprite.lifespan = lifespan;
		sprite.setPosition(trans);
		sprite.birthtime = time;
		sprite.width = childWidth;
		sprite.height = childHeight;
		sys->add(sprite);
		lastSpawned = time;
	}
}

void Emitter::start() {
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
}

void Emitter::stop() {
	started = false;
}

void Emitter::restart() {
	started = true;
}

void Emitter::setLifespan(float life) {
	lifespan = life;
}

void Emitter::setVelocity(ofVec3f v) {
	velocity = v;
}

void Emitter::setChildImage(ofImage img) {
	childImage = img;
	haveChildImage = true;
	childWidth = img.getWidth();
	childHeight = img.getHeight();
}

void Emitter::setImage(ofImage img) {
	image = img;
	haveImage = true;
	width = img.getWidth();
	height = img.getHeight();
}

void Emitter::setRate(float r) {
	rate = r;
}

float Emitter::maxDistPerFrame() {
	return  velocity.length() / ofGetFrameRate();
}
