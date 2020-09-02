/*
 Project Title:
 Description: 3D generative example
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
    
    // ofSpherePrimitive primitive; // experiment with different starting shapes
    // ofBoxPrimitive primitive;
    ofPlanePrimitive primitive;
    
    ofMesh mesh;
    float driftAmount;
    
    ofEasyCam cam;
    ofLight light;
    
};
