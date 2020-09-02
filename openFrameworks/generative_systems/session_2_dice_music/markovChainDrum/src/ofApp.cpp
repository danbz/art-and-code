/*
 Project Title: markovChainDrum
 Description: markov chain drum machine
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    currentSound = 0;
    playedListSize = 16;
    // load our transition matrix into the markov chain addOn
    ofxMC::Matrix matrix("transitionMatrix.txt");
    markov.setup(matrix, 0);
    int numSamples = markov.getStatesNumber();
    // load sample files into a vector of sample player objects
    for (int i = 0; i< numSamples; i++){
        ofSoundPlayer newSample; // make a new sound player object
        newSample.load("sample" +  ofToString( i+1 ) + ".aif"); // generate the filename to load starting from 1
        newSample.setLoop(false);
        samples.push_back(newSample); // push the sample into the vector of soundplayer objects
    }
    samples[currentSound].play(); // start the first one
    
    playedList.push_back(currentSound);
}


//--------------------------------------------------------------
void ofApp::update(){
    if ( samples[currentSound].isPlaying() == false){ // if sample finished
        // play next sample from markov chain object
        markov.update();
        currentSound = markov.getState();
        samples[currentSound].play();
        // always play basic drum loop
        // samples[0].play();
        if (playedList.size() > playedListSize){ // only keep the last 12 samples in the list of samples being played
            playedList.erase(playedList.begin()); // if more than 12 then erase the first one
        }
        playedList.push_back(currentSound); // add our new one to the list of played samples
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    markov.draw(40, 60); // use the built in draw function to show pretty coloured dots indicating the current transition
    
    ofSetColor(200);
    ofDrawBitmapString("Markov ChainDrum: \nsample playing:", 30, 20);
    ofDrawBitmapString("Samples played:\n"+ ofToString(playedList), 30, 90);
    
    // print matrix out
    ofxMC::Matrix mat = markov.getTransitionMatrix();
    stringstream ss;
    ss << "Current transition matrix:\n\n";
    for(uint i = 0; i < mat.size(); ++i){ // loop through each value in each column of the matrix and push into a string
        for(uint j = 0; j < mat[i].size(); ++j){
            ss << mat[i][j] << "\t";
        }
        ss << "\n";
    }
    ofDrawBitmapString( ss.str(), 30, 120) ; // draw the string with the matrix in on the screen
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
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
