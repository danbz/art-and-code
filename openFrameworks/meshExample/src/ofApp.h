/*
Project Title:
Description: Mesh generation example with random and perlin noise distortion
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
    void keyReleased(int key);
    
    // make a new mesh object
    ofMesh mainMesh;
    ofEasyCam mainCam;

    int width, height;
    bool b_messyMesh, b_perlinMesh, b_drawWireFrame, b_marchMesh;
    float perlinRange, perlinHeight;
};
