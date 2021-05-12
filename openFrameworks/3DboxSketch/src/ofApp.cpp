/*
 Project Title: 3D boxes in space
 Description:
 ©Daniel Buzzo 2021
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 http://youtube.com/danbuzzo
 */


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int maxBoxes = 500;
    spaceRange = 300;
    ofEnableDepthTest();
    ofSetBackgroundColor(0);
    light.setPosition(-500, 500, 500);
    light.enable();
    
    for (int i = 0; i < maxBoxes; i ++){
        ofBoxPrimitive newBox;
        newBox.set(100, 100, 100);
        newBox.setPosition( ofRandom(-spaceRange, spaceRange),
                           ofRandom(-spaceRange, spaceRange),
                           ofRandom(-spaceRange, spaceRange));
        for (int side =0; side < 6; side ++){
            newBox.setSideColor( side,  ofColor::fromHsb(ofRandom(255),  255,  255));
        }
        boxes.push_back(newBox);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    boxes[ofRandom( boxes.size()) ].setPosition( ofRandom(-spaceRange, spaceRange),
                       ofRandom(-spaceRange, spaceRange),
                       ofRandom(-spaceRange, spaceRange));
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetSystemTimeMillis()/100.0;
    cam.begin();

    ofPushMatrix();
    ofRotateDeg(time);
    for (int i = 0; i <boxes.size(); i++){
        boxes[i].draw();
    }
    ofPopMatrix();
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
            
            
        case OF_KEY_UP:
            spaceRange +=10;
            break;
            
        case OF_KEY_DOWN:
            spaceRange -=10;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

