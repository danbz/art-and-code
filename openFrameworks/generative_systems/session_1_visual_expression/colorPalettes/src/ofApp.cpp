/*
 Project Title: Random HSB colour palettes
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    tileWidth = 20;
    tileHeight = 80;
    generatePalette();
    
    ofSetBackgroundColor(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    int i=0;
    for (int x = 0; x< ofGetWidth(); x+=tileWidth){
        for (int y = 0; y<ofGetHeight(); y+=tileHeight){
            ofSetColor(palette[i]);
            // draw different shapes in our grid
            ofDrawRectangle(x, y, tileWidth, tileHeight);
            // ofDrawEllipse(x, y, tileWidth, tileHeight);
            
            i++;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case ' ':
            generatePalette();
            break;
        case 'f':
            ofToggleFullscreen();
            generatePalette();
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::generatePalette(){
    // generate a new list of colours in our palette
    palette.clear();
    ofColor newColor;
    int hue = ofRandom(255); // choose random hue for the whole palette
    for (int x = 0; x< ofGetWidth(); x+=tileWidth){
        for (int y = 0; y<ofGetHeight(); y+=tileHeight){
            // generate a new HSB colour palette, keeping one element fixed
            // newColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
            // newColor.setHsb(ofRandom(255), 255, ofRandom(255));
            newColor.setHsb(hue, ofRandom(255), ofRandom(255)); // choose random saturation and brightness for each tile using fixed hue
            palette.push_back(newColor);
        }
    }
}
