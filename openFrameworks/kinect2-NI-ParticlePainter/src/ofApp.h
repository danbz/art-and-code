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
// our particle class
public:
    particle(ofVec3f startPoint, ofColor col);
    ~particle();
    void update();
    void draw();
    ofVec3f location, direction, velocity;
    int size;
    ofColor col;
    float speed;
};


class ofApp : public ofBaseApp
{
public:
    void setup();
    void exit();
    
    void update();
    void draw();
    
    ofxNI2::Device device;
    ofxNiTE2::UserTracker tracker;
    ofPixels depthPixels;
    ofTexture depthTexture;
    
    
    ofEasyCam cam;
    ofLight light;
    
    
    // for our particle system
    vector<particle> particles;
    int maxAge, maxParticles;
    
    bool b_drawParticles;
};

