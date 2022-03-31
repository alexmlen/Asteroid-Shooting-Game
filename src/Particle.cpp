#include "Particle.h"

//Alexander Len
//March 31, 2019
//
//Particle class, handles particles from explosions

Particle::Particle() {
	velocity.set(0, 0, 0);
	acceleration.set(0, 0, 0);
	position.set(0, 0, 0);
	forces.set(0, 0, 0);
	lifespan = 5;
	birthtime = 0;
	radius = 10;
	damping = .99;
	mass = 10;
	color = ofColor::aquamarine;
	myPart = ofRectangle(0, 0, 10, -10);
}

void Particle::setPosition(ofVec3f pos) {
	position.set(pos);
	myPart = ofRectangle(pos.x, pos.y, 10, -10);
}

void Particle::draw() {
	ofFill();
	ofSetColor(250, 250, 250);
	ofDrawRectangle(myPart);
}

void Particle::update() {
	integrate();
}

void Particle::integrate() {
	position = position + velocity / 60;
	velocity = velocity + acceleration / 60;
	velocity = velocity * damping;
	myPart = ofRectangle(position.x, position.y, 10, -10);
}

float Particle::age() {
	return (ofGetElapsedTimeMillis() - birthtime);
}

void ParticleSystem::add(const Particle &p) {
	particles.push_back(p);
}

void ParticleSystem::remove(int i) {
	particles.erase(particles.begin() + i);
}

void ParticleSystem::update() {
	// check if empty and just return
	if (particles.size() == 0) {
		return;
	}
	for (size_t i = 0; i < particles.size(); i++) {
		particles[i].update();
	}

	vector<Particle>::iterator s = particles.begin();
	vector<Particle>::iterator tmp;

	// check which sprites have exceed their lifespan and delete
	// from list.  When deleting multiple objects from a vector while
	// traversing at the same time, use an iterator.
	//
	while (s != particles.end()) {
		if (s->lifespan != -1 && s->age() > s->lifespan) {
			//			cout << "deleting sprite: " << s->name << endl;
			tmp = particles.erase(s);
			s = tmp;
		}
		else s++;
	}
}


void ParticleSystem::draw() {
	for (size_t i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
}