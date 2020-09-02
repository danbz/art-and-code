/*
 Project Title:
 Description:
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 
 * Parameterize: Chair from Form+Code in Design, Art, and Architecture
 * implemented in OpenFrameworks by Anthony Stellato <http://rabbitattack.com/>
 updated March 2020 dan buzzo
 * Requires OpenFrameworks available at http://openframeworks.cc/
 * For more information about Form+Code visit http://formandcode.com
 */

#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    void scrambleChair();
    void drawChair();
    int chairSeatHeight, chairWidth, chairDepth, chairBackHeight, chairFrameThickness;
    
    ofEasyCam cam;
    ofLight light;
    ofTexture texture;
};
