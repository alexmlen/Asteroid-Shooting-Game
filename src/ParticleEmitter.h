#pragma once
#include "Particle.h"
//Alexander Len
//March 31, 2019
//
//Particle Emitter, gets position needed and creates an explosion at that position

class ParticleEmitter : public BaseObject {
public:
	ParticleEmitter(ParticleSystem *);
	void draw();
	void setLifespan(float);
	void setVelocity(ofVec3f);
	void explode(ofVec3f pos);
	void update();
	ParticleSystem *sys;
	float rate;
	ofVec3f velocity;
	ofVec3f acceleration;
	float lifespan;
	int amount;
	ofSoundPlayer explosion;
};
