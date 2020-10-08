/*
 Project Title: SlitScan  half push scan
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
    
    // initiate a videograbber object and objects to put image pixel data into
    ofVideoGrabber vidGrabber;
    ofPixels videoPixels, pixels;
    ofTexture videoTexture;
    ofColor color;
    int xSteps, ySteps, scanStyle, speed;
    int sWidth, sHeight;
    bool  b_drawCam, b_smooth;
    float camWidth, camHeight;

    ofTrueTypeFont font;
    vector<ofTexture> minuteThumbs, hourThumbs;
};
