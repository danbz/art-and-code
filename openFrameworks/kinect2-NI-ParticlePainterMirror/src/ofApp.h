// dan buzzo 2020 github/danbz
// buzzo.com
// adapted from the ofxNI2 tracker example
// depends upon ofxNI2 https://github.com/roymacdonald/ofxNI2
// possibly originally from https://github.com/satoruhiga

#pragma once

#include "ofMain.h"
#include "ofxNI2.h"
#include "ofxNiTE2.h"


class particle{

public:
    particle(ofVec3f startPoint, ofColor col);
    ~particle();
    void update();
    void draw();
    ofVec3f location, direction, velocity;
    float size;
    ofColor col;
    float speed;
};


class ofApp : public ofBaseApp
{
public:
    void setup();
    void exit();
    void keyPressed(int key);
    void update();
    void draw();
    
    ofxNI2::Device device;
    ofxNiTE2::UserTracker tracker;
    ofPixels depthPixels;
    ofTexture depthTexture;
    
    // for particles
    vector<particle> particles;
    int maxParticles;
    
    bool b_drawParticles, b_drawDebug;
    
    ofImage userMask;
    
    // ofxNI2::DepthStream depth;
    ofxNI2::ColorStream color;
    
    ofFbo fbo;
};

