/*
 Project Title: Active Drawing
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 adapted from reas and fry 'processing' acive drawing
 */

#pragma once

#include "ofMain.h"

class movingLine { // moving line class definition to make movingLine objects
public:
    float x1,y1,x2,y2, wobble;
    
    movingLine();
    ~movingLine();
    void setPosition(int x, int y, int px, int py);
    void display();
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
    
    int numLines, currentLine;
    
    vector<movingLine> lines; // make a vector of movingLine objects to hold them all
};
