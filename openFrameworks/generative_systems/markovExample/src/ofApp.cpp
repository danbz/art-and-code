/*
 Project Title: Markov example
 Description: simple example of the of of ofxMarkovChain addon
 https://github.com/elaye/ofxMarkovChain
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"
 
//--------------------------------------------------------------
void ofApp::setup(){
    // load and set up our transition matrix into the markov chain addOn
    ofxMC::Matrix matrix("transitionMatrix.txt");
    markov.setup(matrix, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    markov.draw(40, 60); // use the built in draw function to show coloured dots indicating the current transition
    
    int currentState;
    currentState = markov.getState(); // get the current state of the matrix
    
    ofSetColor(255); // write the current state to the screen
    ofDrawBitmapString("Press space to step forward \nThe current item in Markov Chain is: " + ofToString( currentState) , 40, 20);
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == ' '){
        // if the space bar is pressed
        // update the markov chain to the next state
        markov.update();
    }
}
