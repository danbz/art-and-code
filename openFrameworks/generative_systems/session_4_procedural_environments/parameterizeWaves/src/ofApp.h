/*
 Project Title:
 Description:
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
  * Parameterize: Waves from Form+Code in Design, Art, and Architecture
 * implemented in OpenFrameworks by Anthony Stellato <http://rabbitattack.com/>
 * updated dan buzzo march 2020
 * Requires OpenFrameworks available at http://openframeworks.cc/
 * For more information about Form+Code visit http://formandcode.com
 */

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

};
