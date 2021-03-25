/*
 Project Title: dirty-electro-sample-player
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
    sound.load("live for just these 20 years.aiff");
     sound.load("Dirty-electronic-samples/sample3.aif");
    
    // sound.load("VocalSamples_StayOnBeat/VocalSamples_15_StayOnBeat.com.wav");
    sound.setLoop(true);
    sound.play();
    ofSetBackgroundColor(0);
    ofSetColor(255);
    counter = 0.0;
    maxCounter = 100.0;
    oldTarget.set(0,0,0);
    newTarget.set( ofRandom( -1.0, 1.0) , ofRandom( 1.0 ), ofRandom( 0.5, 1.0) );
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (counter == maxCounter){
        oldTarget = newTarget;
        newTarget.set( ofRandom( -1.0, 1.0 ) , ofRandom( 1.0 ), ofRandom( 0.5, 1.0) );
        counter = 0;
      
   } else {

       float pan = ofLerp(oldTarget.x, newTarget.x,  counter / maxCounter );
        sound.setPan( pan );
       
       float vol = ofLerp(oldTarget.y, newTarget.y,  counter / maxCounter );
       sound.setVolume( vol );
       
       float speed = ofLerp(oldTarget.z, newTarget.z,  counter / maxCounter );
       sound.setSpeed( speed );
       
    }
    counter ++;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDrawCircle( (sound.getPan() + 1.0 ) * ofGetWidth() /2 , sound.getVolume() * ofGetHeight() , sound.getSpeed() * 50.0);

    ofDrawLine( (oldTarget.x + 1) * ofGetWidth()/2, oldTarget.y * ofGetHeight(), (newTarget.x + 1) * ofGetWidth()/2 , newTarget.y * ofGetHeight());
    
    ofDrawBitmapStringHighlight("pan " + ofToString( sound.getPan() ) + " vol " + ofToString( sound.getVolume() ) + " speed " + ofToString( sound.getSpeed() ),  20 , 20) ;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
       
        default:
            break;
    }
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

