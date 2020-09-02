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
#include "ofxLSystem.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    
    void saveMesh();
    void buildTree();
    
    ofMesh forest;

    ofLight light;
    ofEasyCam cam;
    ofPlanePrimitive plane;
    ofMaterial roadMaterial;
    ofMaterial treeMaterial;
    
    
};
