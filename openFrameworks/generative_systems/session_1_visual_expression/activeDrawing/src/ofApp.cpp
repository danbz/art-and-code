/*
Project Title: Active Drawing
Description:
©Daniel Buzzo 2020
dan@buzzo.com
http://buzzo.com
https://github.com/danbz
adapted from reas and fry 'processing' acive drawing
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    numLines = 500;
    currentLine = 0;
    
    for (int i=0;  i < numLines; i++){ // make all our new movingLine objects and put into our vector of lines
        movingLine newLine;
        lines.push_back(newLine);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int i=0;  i < numLines; i++){
        lines[i].display();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // loop through lines in our lines vector each frame and set each one to the current and previous mounse position
    lines[currentLine].setPosition(mouseX, mouseY, ofGetPreviousMouseX(), ofGetPreviousMouseY());
    if (currentLine <numLines -1){
        currentLine++;
        
    } else { // if we have set all our 500 lines then start again at line zero
        currentLine=0;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
movingLine::movingLine(){ // constructor for our moving line class
    wobble = 0.2; // how much each line will move per frame as they decay
    
    //     uncomment this start our lines at initial random positions
    //     int w = ofGetWidth();
    //     int h = ofGetHeight();
    //     x1 = ofRandom(w);
    //     y1 = ofRandom(h);
    //     x2 = ofRandom(w);
    //     y2 = ofRandom(h);
}

movingLine::~movingLine(){
    // destructor for our moving line class
}

//--------------------------------------------------------------
void movingLine::display(){
    x1 += ofRandom(wobble) - wobble/2;
    y1 += ofRandom(wobble) - wobble/2;
    x2 += ofRandom(wobble) - wobble/2;
    y2 += ofRandom(wobble) - wobble/2;
    ofDrawLine(x1, y1, x2, y2);
}

//--------------------------------------------------------------
void movingLine::setPosition(int x, int y, int px, int py){
    x1 = x;
    y1 = y;
    x2 = px;
    y2 = py;
}
