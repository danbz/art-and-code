/*
 Project Title: Drunken Ant Music
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 adapted from example by Carl Lostrito in 'Computational Drawing'
 
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetBackgroundAuto(false);
    // ofBackground(80, 64, 251); // mid blue
    ofBackground(33,25,175); // darkblue
    ofSetColor(254,224,58); // yellow
    
    resetAnt();
    
    // set up sound synthesis
    ofSetVerticalSync(true);
    wavePhase = 0;
    pulsePhase = 0;
    // start the sound stream with a sample rate of 44100 Hz, and a buffer
    // size of 512 samples per audioOut() call
    ofSoundStreamSettings settings;
    settings.numOutputChannels = 2;
    settings.sampleRate = 44100;
    settings.bufferSize = 512;
    settings.numBuffers = 4;
    settings.setOutListener(this);
    soundStream.setup(settings);
    // ofSetFrameRate(12); // speed up and slow down the ant
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    // ofEnableSmoothing();
    // ofEnableAntiAliasing();
    // update ant position and draw path
    nextPoint = velocity + currentPoint;
    currentLength += amplitude;
    ofDrawLine(currentPoint, nextPoint); // draw our ant path
    currentPoint = nextPoint;
    velocity = velocity.getRotated(angularAcceleration);
    velocity.scale(amplitude+acceleration);
    acceleration += ofRandom(-0.1, 0.1) * numDrinks;
    angularAcceleration += ofRandom(-1, 1);
    
    ofDrawBitmapString("drunken AntMusic \npress 'r' to reset ant \n'f' to toggle fullscreen", 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'r':
            resetAnt();
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::resetAnt(){
    // set the ant parameters up
    startPoint.set(ofGetWidth()/2, ofGetHeight()/2);
    currentPoint = startPoint;
    currentLength = 0;
    velocity.set(ofRandom(1), ofRandom(1));
    velocity.scale( 1 ); // scale velocity amplitude
    amplitude = 1;
    acceleration =0;
    angularAcceleration = ofRandom(-1, 1);
    numDrinks = 1; // set the drunkeness of our Ant path
}

//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer &outBuffer) {

    // base frequency of the lowest sine wave in cycles per second (hertz)
    int minFreq = 80; // set the main frequency range we want our sound to be within
    int maxFreq = 500;
    
    // map the base audio frequency to the y position of our ant
    float frequency =ofMap(currentPoint.y, 0, ofGetHeight(), maxFreq, minFreq);
    
    // mapping frequencies from Hz into full oscillations of sin() (two pi)
    float wavePhaseStep = (frequency / outBuffer.getSampleRate()) * TWO_PI;
    float pulsePhaseStep = (0.5 / outBuffer.getSampleRate()) * TWO_PI;
    
    // this loop builds a buffer of audio containing 3 sine waves at different
    // frequencies, and pulses the volume of each sine wave individually. In
    // other words, 3 oscillators and 3 LFOs.
    
    for(size_t i = 0; i < outBuffer.getNumFrames(); i++) {
        
        // build up a chord out of sine waves at 3 different frequencies
        float sampleLow = sin(wavePhase);
        float sampleMid = sin(wavePhase * 1.5);
        float sampleHi = sin(wavePhase * 2.0);
        
        // pulse each sample's volume
         sampleLow *= sin(pulsePhase);
         sampleMid *= sin(pulsePhase * 1.04);
         sampleHi *= sin(pulsePhase * 1.09);
        
        float fullSample = (sampleLow + sampleMid + sampleHi);
        // float fullSample =  sampleMid ;
        
        // reduce the full sample's volume so it doesn't exceed 1
        // and map the base audio volume to the x position of our ant
        fullSample  *= ofMap(currentPoint.x, 0, ofGetWidth(), 0, 1);
        
        // write the computed sample to the left and right channels
        outBuffer.getSample(i, 0) = fullSample;
        outBuffer.getSample(i, 1) = fullSample;
        
        // get the two phase variables ready for the next sample
        wavePhase += wavePhaseStep;
        pulsePhase += pulsePhaseStep;
    }
    
    unique_lock<mutex> lock(audioMutex);
    lastBuffer = outBuffer;
}
