/*
 Project Title: catmull rom drawing
 Description:
 ©Daniel Buzzo 2023
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 https://youtube.com/danbuzzo
 */
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    startPoint = glm::vec2(ofRandomWidth(), ofRandomHeight());
    endPoint = glm::vec2(ofRandomWidth(), ofRandomHeight());
    startCurve = glm::vec2(ofRandomWidth(), ofRandomHeight());
    endCurve = glm::vec2(ofRandomWidth(), ofRandomHeight());
    
    timeNow = ofGetSystemTimeMillis();
    timer = 5000;
    ofSetBackgroundAuto(false);
    ofSetBackgroundColor(0);
    ofSetFrameRate(120);
}


//--------------------------------------------------------------
void ofApp::update(){
    if (ofGetSystemTimeMillis() > timeNow + timer){
        timeNow = ofGetSystemTimeMillis();
        startPoint = endPoint;
        endPoint = glm::vec2(ofRandomWidth(), ofRandomHeight());
        startCurve = endCurve;
        endCurve = glm::vec2(ofRandomWidth(), ofRandomHeight());
    }
    
    //    drunkards walk version
    //    if (ofGetSystemTimeMillis() > timeNow + timer){
    //        timeNow = ofGetSystemTimeMillis();
    //        startPoint = endPoint;
    //        endPoint = glm::vec2(startPoint.x + ofRandom(-200, 200), startPoint.y + ofRandom(-200, 200));
    //        startCurve = endCurve;
    //        endCurve = glm::vec2(startCurve.x + ofRandom(-200, 200), startCurve.y + ofRandom(-200, 200));
    //    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef() ;
    ofColor drawColor;
    glm::vec2 drawPoint;
    // drawColor.set(255, 255, 255, 20);
    // drawColor.setHsb(127 + 127 * sin(0.1 * time), 255, 255);
    drawColor.setHsb(20 + 20 * sin(0.1 * time), 200, 170);
    // drawColor.setHsb(127 + 127 * sin(0.1 * time), 127 + 127 * sin(time *0.15), 127 + 127 * sin(time*0.2));
    ofSetColor(drawColor);
    
    float t = ofNormalize(ofGetSystemTimeMillis(), timeNow, timeNow + timer );
    drawPoint= glm::vec2 ( ofCurvePoint(startPoint, startCurve, endCurve, endPoint, t ) );
    // ofDrawCircle(drawPoint, 5);
    
    ofDrawCircle(drawPoint, 5 + 6 * sin(0.5 * time));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key){
        case 'f':
            ofToggleFullscreen();
            break;
            
        default:
            break;
            
    }
}
