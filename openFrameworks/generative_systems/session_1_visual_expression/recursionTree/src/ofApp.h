/*
 Project Title: tree recursion demo
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
		
    void drawTree( int x, int y, int a, int n);
    
    int x,y,a,n;
    
    
};
