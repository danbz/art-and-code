/*
Project Title: belligerentClock
Description: from the openFrameworks superbasics youtube tutorial series
©Daniel Buzzo 2021
dan@buzzo.com
http://buzzo.com
https://github.com/danbz
http://youtube.com/danbuzzo
*/

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		
    ofTrueTypeFont font;
    vector <string> words;
};
