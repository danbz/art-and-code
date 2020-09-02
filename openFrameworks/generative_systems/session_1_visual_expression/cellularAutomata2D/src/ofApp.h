/*
 Project Title: CellularAutomata 2D
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 with acknowledgement to Reas and Fry 'Processing, A programming handbook for visual designers and artists'
 
 */

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void mouseDragged(int x, int y, int button);
    
    int neighbors(int x, int y);
    
    vector <vector <int> >  grid;
    vector <vector <int> >  futureGrid;
    ofColor on, off;
};
