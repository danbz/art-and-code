/*
 Project Title:
 Description:
 ©Daniel Buzzo 2023, 2024 portions adapted form openFrameworks demo examples
 see https://openframeworks.cc
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 https://youtube.com/danbuzzo
 */

#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"

#define N_SOUNDS 5

class SoundData {
public:
    int soundID;
    bool bHit;
};

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void drawPointCloud();
    
    void keyPressed(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    
    void faceToLine();
    
    vector <ofPolyline>                  lines;
    ofxBox2d                             box2d;
    vector <shared_ptr<ofxBox2dCircle>>  circles;
    vector <shared_ptr<ofxBox2dEdge>>    edges;
        
    ofxKinect kinect;
    
#ifdef USE_TWO_KINECTS
    ofxKinect kinect2;
#endif
    
    ofxCvColorImage colorImg;
    ofxCvGrayscaleImage grayImage; // grayscale depth image
    ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
    ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
    ofxCvContourFinder contourFinder;
    
    bool bThreshWithOpenCV;
    bool bDrawPointCloud, b_live;
    int nearThreshold;
    int farThreshold;
    int angle;
    
    // used for viewing the point cloud
    ofEasyCam easyCam;
    
    // this is the function for contacts
    void contactStart(ofxBox2dContactArgs &e);
    void contactEnd(ofxBox2dContactArgs &e);

    // when the ball hits we play this sound
    ofSoundPlayer  sound[N_SOUNDS];
};
