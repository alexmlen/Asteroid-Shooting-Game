#pragma once
#include "ofMain.h"
#include "Sprite.h"
//Alexander Len
//March 31, 2019
//
//Particle class, handles particles from explosions

class Particle {
public:
	Particle();

	ofVec3f position;
	ofVec3f velocity;
	ofVec3f acceleration;
	ofVec3f forces;
	float	damping;
	float   mass;
	float   lifespan;
	float   radius;
	float   birthtime;
	void    integrate();
	void    draw();
	void	update();
	float	age();
	void	setPosition(ofVec3f pos);
	ofColor color;
	ofRectangle myPart;
};

class ParticleSystem {
public:
	void add(const Particle &);
	void remove(int);
	void update();
	void draw();
	vector<Particle> particles;
};

