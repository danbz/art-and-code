/*
 Project Title: Random HSB colour palettes
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
    
    void generatePalette();
    vector<ofColor> palette;
    float tileWidth, tileHeight;
};
