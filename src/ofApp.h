#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Sprite.h"

//Alexander Len
//March 31, 2019
//

class Emitter;
class Enemy;
class ParticleEmitter;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		void checkCollisions();

		void keyPressed(int key);
		void keyReleased(int key);
	  	void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		Emitter *emitter;
		Enemy *enemy;
		ParticleEmitter *pEmitter;

		Enemy *backStars;

		ofImage defaultImage;
		ofImage laserImage;
		ofImage enemyImage;
		ofVec3f mouse_last;
		bool imageLoaded;

		bool insideShape(glm::vec3 p, glm::vec3 boxp, float width, float height) {
			glm::vec3 o = glm::vec3(boxp.x - width / 2.0, boxp.y - height / 2.0, 0);
			return (p.x >= o.x && p.x < o.x + width && p.y >= o.y && p.y < o.y + height);
		}
		
		glm::vec3 position;
		float width, height;
		glm::vec3 lastMouse;

		bool bDrag = false;
		bool started = false;
		int left = 0;
		int right = 0;
		int up = 0;
		int down = 0;
		bool shooting;
		
		void addPoints(int amt);

		int points;
		int lives;

		void damagePlayer();
		bool gameOver = false;

		ofSoundPlayer explosion;
		ofSoundPlayer hit;
		ofSoundPlayer song;
		ofSoundPlayer death;
};
