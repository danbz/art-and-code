/*
 Project Title: Cellular Automata in 1 dimension
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
    void mousePressed(int x, int y, int button);
    
    vector<int> rules;
    int generation;
    ofColor onCol, offCol;
    ofPixels screenImage;
    
    int applyRules(ofColor a, ofColor b, ofColor c);
};
