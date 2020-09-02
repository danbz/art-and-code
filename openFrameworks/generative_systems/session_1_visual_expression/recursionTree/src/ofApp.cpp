/*
Project Title: tree recursion demo
Description:
©Daniel Buzzo 2020
dan@buzzo.com
http://buzzo.com
https://github.com/danbz
*/

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    x= ofGetWidth()/2;
    y= ofGetHeight()-10;
    a= (ofGetWidth()/4) -40;
    n=6;
    ofSetBackgroundAuto(false);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    drawTree(x, y, a, n);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}
//--------------------------------------------------------------
void ofApp::drawTree( int x, int y, int apex, int num){
    ofDrawLine(x, y, x, y-apex); // first vertical
    ofDrawLine(x-apex,y-apex,x+apex,y-apex); // first horizontal 
    
    if (num > 0 ){
        drawTree(x-apex, y-apex, apex/2, num-1); // draw left branch
        drawTree(x+apex, y-apex, apex/2, num-1); // draw right branch
        num --; // we deprecate the num variable so the recursion eventually stops
    }
}
