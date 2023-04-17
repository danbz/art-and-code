/*
Project Title:
Description:
©Daniel Buzzo 2021
dan@buzzo.com
http://buzzo.com
https://github.com/danbz
http://youtube.com/danbuzzo
*/

#pragma once

#include "ofMain.h"

class particle {
public:
    // our new particle class
    // with each object containing an x and y position, and a vector direction as vx and vy and a size
    ofColor color;
    float size;
    glm::vec3 force, position, direction;
    
    // we also define two methods that the particle object understands
    void update();
    void draw();
    
    // and define a particle contructor and a destructor (the destructor is denoted by the tilde (~) character prefix
    // the contructor is expecting to be passed an initial x and y co-ordinate for the new particle
    particle(int x, int y, int z, int hue);
    ~particle();
};

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
	

    // define a vector containing our new particle class objects
    vector<particle> particles;
    int hue;
    ofEasyCam cam;
    ofLight light;
    int maxParticles;
};
