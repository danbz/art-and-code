/*
 Project Title: randomWalker
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */


#pragma once

#include "ofMain.h"

class walker {
    // walker class that contains vector of points and color and radius of each step
    ofPoint xyPoint;
    vector<ofPoint> walk;
    ofColor color;
    int radius;
    
public:
    walker();
    ~walker();
    void update();
    void draw();
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    walker walker; // create a wallker object
};
