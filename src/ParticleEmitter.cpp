#include "ofMain.h"
#include "ParticleEmitter.h"
//Alexander Len
//March 31, 2019
//
//Particle Emitter, gets position needed and creates an explosion at that position

ParticleEmitter::ParticleEmitter(ParticleSystem *ParticleSys) {
	sys = ParticleSys;
	lifespan = 1000;    // milliseconds
	amount = 10;
	rate = 1;    // Particles/sec
	velocity = ofVec3f(0, 50, 0);
	acceleration = ofVec3f(0, 20, 0);
	explosion.load("audio/laser.wav");
}

void ParticleEmitter::draw() {
	sys->draw();
}

void ParticleEmitter::update() {
	sys->update();
}

void ParticleEmitter::explode(ofVec3f pos) {
	float time = ofGetElapsedTimeMillis();
	explosion.play();

	for (int i = 0; i < amount; i++) {
		Particle particle;

		ofVec3f dir = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
		float speed = velocity.length();
		particle.velocity = dir.getNormalized() * speed;

		particle.acceleration.set(acceleration);
		particle.lifespan = lifespan;
		particle.setPosition(pos);
		particle.birthtime = time;
		sys->add(particle);
	}
}

void ParticleEmitter::setLifespan(float life) {
	lifespan = life;
}

void ParticleEmitter::setVelocity(ofVec3f v) {
	velocity = v;
}

