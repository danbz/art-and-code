/*
 Project Title:
 Description: 3d mesh example with perlin and random noise
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

    
    // make a new mesh object
    ofMesh mainMesh;
    ofEasyCam mainCam;
    int width, height;
    bool b_messyMesh, b_perlinMesh, b_drawWireFrame;
    float perlinRange, perlinHeight;
};
