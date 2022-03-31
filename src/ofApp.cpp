#include "ofApp.h"
#include "Emitter.h"
#include "Enemy.h"
#include "ParticleEmitter.h"
//Alexander Len
//March 31, 2019
//
//--------------------------------------------------------------
void ofApp::setup(){
	explosion.load("audio/explosion.wav");
	hit.load("audio/hit.wav");
	song.load("audio/song.wav");
	death.load("audio/death.wav");
	points = 0;
	lives = 3;
	emitter = new Emitter(new SpriteSystem());
	emitter->setChildSize(10, 10);
	imageLoaded = false;

	enemy = new Enemy(new SpriteSystem());
	enemy->setChildSize(10, 10);

	backStars = new Enemy(new SpriteSystem());
	backStars->setChildSize(10, 10);

	pEmitter = new ParticleEmitter(new ParticleSystem());

	if (defaultImage.load("images/player.png")) {
		emitter->setImage(defaultImage);
		width = defaultImage.getWidth();
		height = defaultImage.getHeight();
		imageLoaded = true;
	}
	if (laserImage.load("images/laser.png")) {
		emitter->setChildImage(laserImage);
	}

	if (enemyImage.load("images/enemy.png")) {
		enemy->setChildImage(enemyImage);
	}

	position = glm::vec3(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 0);
	emitter->setPosition(ofVec3f(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 0));
	emitter->start();
	emitter->stop();

	backStars->rate = 5;
	backStars->start();

	ofSetBackgroundColor(ofColor::black);
	song.setLoop(true);
	song.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	if (!gameOver) {
		emitter->update();
		enemy->update();

		checkCollisions();
	}
	pEmitter->update();
	backStars->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	if (!gameOver) {
		glm::vec3 temp = (position + glm::vec3(right - left, down - up, 0));
		if (started == true && temp.x >= 0 && temp.x <= ofGetWidth() && temp.y >= 0 && temp.y <= ofGetHeight()) {
			position += glm::vec3(right - left, down - up, 0);
			emitter->trans += glm::vec3(right - left, down - up, 0);
		}
		ofSetColor(255,255,255);
		emitter->draw();
		enemy->draw();
		if (!started) {
			ofDrawBitmapString("Asteroid Belt", 300, 100);
			ofDrawBitmapString("Press Space to Start", 300, 112);
		}
		else {
			ofDrawBitmapString("Asteroid Belt", 300, 100);
			string pString = "Points: " + std::to_string(points);
			ofDrawBitmapString(pString, 300, 112);
			string lString = "Lives: " + std::to_string(lives);
			ofDrawBitmapString(lString, 300, 124);
			ofDrawBitmapString("New life every 5,000 points!", 300, 136);
		}
	}
	else {
		ofDrawBitmapString("GAME OVER", 300, 100);
	}
	pEmitter->draw();
	backStars->draw();
}

//--------------------------------------------------------------
void ofApp::checkCollisions() {
	float dist = ofVec2f(laserImage.getWidth(), laserImage.getHeight()).length();
	for (int i = 0; i < enemy->sys->sprites.size(); i++ ) {
		ofVec3f pos = enemy->sys->sprites.at(i).trans;
		bool destroyed = emitter->sys->removeNear(pos, dist);
		if (destroyed) {
			enemy->sys->remove(i);
			addPoints(100);
			explosion.play();
			pEmitter->explode(pos);
		}
	}
	dist = ofVec2f(width, height).length();
	for (int i = 0; i < enemy->sys->sprites.size(); i++) {
		ofVec3f pos = enemy->sys->sprites.at(i).trans;
		ofVec3f v = pos - position;
		if (v.length() < dist) {
			enemy->sys->remove(i);
			damagePlayer();
		}
	}
}

void ofApp::addPoints(int amt) {
	points += amt;
	if (points % 5000 == 0) {
		lives++;
	}
}

void ofApp::damagePlayer() {
	lives--;
	if (lives <= 0) {
		gameOver = true;
		song.stop();
		explosion.play();
		pEmitter->explode(position);
		death.play();
	}
	else {
		explosion.play();
		hit.play();
		pEmitter->explode(position);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch (key) {
	case 'F':
	case 'f':
		ofToggleFullscreen();
		break;
	case OF_KEY_CONTROL:
		break;
	case ' ':
		if (started && shooting == false) {
			shooting = true;
			emitter->restart();
		}
		else {
			started = true;
			enemy->start();
		}
		break;
	case OF_KEY_LEFT:
		left = 1;
		break;
	case OF_KEY_RIGHT:
		right = 1;
		break;
	case OF_KEY_UP:
		up = 1;
		break;
	case OF_KEY_DOWN:
		down = 1;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key) {
	case ' ':
		if (started) {
			shooting = false;
			emitter->stop();
		}
	case OF_KEY_CONTROL:
		break;
	case OF_KEY_LEFT:
		left = 0;
		break;
	case OF_KEY_RIGHT:
		right = 0;
		break;
	case OF_KEY_UP:
		up = 0;
		break;
	case OF_KEY_DOWN:
		down = 0;
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	if (!bDrag || started == false) return;
	ofPoint mouse_cur = ofPoint(x, y);
	ofVec3f delta = mouse_cur - mouse_last;
	ofVec3f temp = (emitter->trans + delta);
	if (temp.x >= 0 && temp.x <= ofGetWidth() && temp.y >= 0 && temp.y <= ofGetHeight()) {
		emitter->trans += delta;
		mouse_last = mouse_cur;
		position += delta;
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	if (started == false) return;
	mouse_last = ofPoint(x, y);
	if (insideShape(glm::vec3(x, y, 0), position, width, height)) {
		bDrag = true;
		mouse_last = ofPoint(x, y);
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	bDrag = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
