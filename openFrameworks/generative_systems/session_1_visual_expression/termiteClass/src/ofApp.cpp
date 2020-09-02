/*
Project Title: Termite Agents as class
Description:
©Daniel Buzzo 2020
dan@buzzo.com
http://buzzo.com
https://github.com/danbz
 derived from example in Reas and Fry 'Processing, handbook'
 this implementation builds termite agent as discrete class object
 see the termite agent for simple implementation
*/

#include "ofApp.h"

ofPixels screenImage; // make our screenimage global so termite class objects can access it

//--------------------------------------------------------------
void ofApp::setup(){
    numTermites = 10000; // how many termites to generate
    screenImage.allocate(ofGetWidth(), ofGetHeight(), OF_IMAGE_GRAYSCALE);
    
    // generate initial wood particle positions
    float woodDensity = ofGetWidth() * ofGetHeight() * 0.5;
    for (int i =0; i< woodDensity; i++){
        int rx = ofRandom(ofGetWidth());
        int ry = ofRandom(ofGetHeight());
        screenImage.setColor( rx, ry , black);
    }
    
    // generate termites and push into vector of termites
    for (int i = 0; i < numTermites; i++){
        termite newTermite;
        termites.push_back(newTermite);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0; i < numTermites; i++){
        termites[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    image.setFromPixels(screenImage);
    image.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
termite::termite(){
    // termite constructor
    angles = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1}, {-1,0},{-1,1}};
       numAngles = angles.size();
       dir =0;
       black.set(0);
       white.set(255);
       x = nx = ofGetWidth()/2;
       y = ny = ofGetHeight()/2;
}

//--------------------------------------------------------------
termite::~termite(){
    // destructor
}
//--------------------------------------------------------------
void termite::update(){
    int rand = abs(ofRandom(-1,2));
    int width = ofGetWidth();
    int height = ofGetHeight();
    
    dir = ( dir + rand + numAngles) % numAngles; // update direction termite is moving in
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
}
