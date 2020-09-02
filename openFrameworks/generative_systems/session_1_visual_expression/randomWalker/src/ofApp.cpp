/*
 Project Title: randomWalker
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofEnableAlphaBlending();
    ofSetBackgroundColor(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    walker.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    walker.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
walker::walker(){
    xyPoint = ofVec2f(ofGetWidth()/2, ofGetHeight()/2);
    // make a first point in the centre of the screen
    walk.push_back(xyPoint);
    color = (255,255,255,10); // draw our dots white with transparency of 10
    radius = 2; // dotsize
}

//--------------------------------------------------------------
walker::~walker(){
    
}

//--------------------------------------------------------------
void walker::update(){
    // choose a random direction for the next step
    int stepSize = 4; // how far is each step from the last step
    int random = ofRandom(4);
    switch (random) {
        case 0: // up
            xyPoint += ofVec2f(0, stepSize);
            break;
        case 1: // down
            xyPoint += ofVec2f(0, -stepSize);
            break;
        case 2: // right
            xyPoint += ofVec2f(stepSize, 0);
            break;
        case 3: // left
            xyPoint += ofVec2f(-stepSize, 0);
            break;
            
        default:
            break;
    }
    walk.push_back(xyPoint); // add our step into the list of steps
}

//--------------------------------------------------------------
void walker::draw(){
    ofSetColor( color);
    for (int i=0; i<walk.size(); i++){ // loop though all the steps in the walk, drawing a point at each one
        ofDrawCircle(walk[i], radius);
    }
}
