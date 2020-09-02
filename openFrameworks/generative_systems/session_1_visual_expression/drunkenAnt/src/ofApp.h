/*
 Project Title: Drunken Ant path
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 adapted from example by Carl Lostrito in 'Computational Drawing'
 */

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    void resetAnt();
    ofPoint startPoint, endPoint, currentPoint, nextPoint;
    float numDrinks, length, currentLength, acceleration, angularAcceleration, amplitude;
    ofVec2f velocity;
};
