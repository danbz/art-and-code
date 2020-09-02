/*
 Project Title:
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
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
	

    ofTrueTypeFont font; // load a font into this
    string myText; // we load our text into this 
    vector< ofPath > myPath; // load the shape of each letter in our word string into this vector
    float drift;
};
