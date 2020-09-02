/*
Project Title: recursion dots
Description:
©Daniel Buzzo 2020
dan@buzzo.com
http://buzzo.com
https://github.com/danbz
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    drawCircle (ofGetWidth()/2, ofGetWidth()/3, 7);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::drawCircle( int x, int radius, int num){
    float tt = 126 * num/4.0;
    ofSetColor( tt, tt);
    //ofNoFill();
    ofDrawEllipse(x, ofGetHeight()/2, radius*2, radius*2);
    if (num > 1) {
        num -=1;
        drawCircle(x - radius/2, radius/2, num);
        drawCircle(x + radius/2, radius/2, num);

    }
}
