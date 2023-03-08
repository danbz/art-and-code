/*
 Project Title: catmull rom drawing
 Description:
 ©Daniel Buzzo 2023
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 https://youtube.com/danbuzzo
 */
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		
		
    float timer, timeNow, curvePos;
    glm::vec2 startPoint, endPoint, startCurve, endCurve;
};
