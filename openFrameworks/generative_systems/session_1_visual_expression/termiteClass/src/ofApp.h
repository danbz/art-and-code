/*
 Project Title: Termite Agents as class
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 derived from example in Reas and Fry 'Processing, handbook'
 */


#pragma once

#include "ofMain.h"


class termite {

    vector< vector<int>> angles;
    int numAngles, dir, x, y, nx, ny;
    ofColor black, white;
    
    public :
    
    termite();
    ~termite();
    void update();

};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
        
    // int numAngles, dir, x, y, nx, ny;
    // ofColor black, white;
    
     ofColor black, white;
    int numTermites;
    ofImage image;
    vector<termite> termites;

};
