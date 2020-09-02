/*
Project Title: Termite Agents
Description:
©Daniel Buzzo 2020
dan@buzzo.com
http://buzzo.com
https://github.com/danbz
 derived from example in Reas and Fry 'Processing, handbook'
 see also the termites Class example to see the termite code as a class object
*/


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    angles = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}, {-1,0},{-1,1}};
    numAngles = angles.size();
    dir =0;
    black.set(0);
    white.set(255);
    x = nx = ofGetWidth()/2;
    y = ny = ofGetHeight()/2;
    
    screenImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
    // generate initial wood particle positions
    screenImage.setColor(white);
    float woodDensity = ofGetWidth() * ofGetHeight() * 0.5;
    for (int i =0; i< woodDensity; i++){
        int rx = ofRandom(ofGetWidth());
        int ry = ofRandom(ofGetHeight());
        screenImage.setColor( rx, ry , black);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    int rand = abs(ofRandom(-1,2));
    int width = ofGetWidth();
    int height = ofGetHeight();
    
    dir = ( dir + rand + numAngles) % numAngles;
    nx = (nx + angles[dir][0] + width) % width;
    ny = (ny + angles[dir][1] + height) % height;
    
    if ((screenImage.getColor(x,y) == black) && (screenImage.getColor(nx,ny) == white)){
        // move chip one space
        screenImage.setColor(x, y,  white);
        screenImage.setColor( nx, ny,  black);
        x = nx;
        y = ny;

    } else if ((screenImage.getColor(x,y)== black) && (screenImage.getColor(nx,ny)==black)){
        // move in opposite direction
        dir = (dir + (numAngles/2)) % numAngles;
        x = (x + angles[dir][0] + width) % width;
        y = (y + angles[dir][1] + height) % height;
    } else {
        // not carrying anything
        x = nx;
    }
    image.setFromPixels(screenImage);
    image.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
