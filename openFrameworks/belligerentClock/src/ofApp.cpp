/*
 Project Title: belligerentClock
 Description: from the openFrameworks superbasics youtube tutorial series
 ©Daniel Buzzo 2021
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 http://youtube.com/danbuzzo
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(1);
    // font.load("frabk.ttf", 90);
    font.load("terminal-grotesque_open.otf", 60);
    words = {"love", "hate", "clean", "make", "smash", "stop", "f*ck", "like", "bump", "fix", "burn", "smoke", "toast", "roast", "cook", "mash", "kick", "hack", "smack", "check", "forget" };
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    // this is the seconds loop
    
    ofSetColor(255,0,0);
    string word = words[ ofRandom( words.size() ) ];
    for (int i = 0; i <360; i+=10){
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
        ofRotateDeg( (ofGetSeconds() * 6) -90 );
        ofRotateDeg(i);
        font.drawString( "F*ck", 120, 0 );
        // font.drawString( word , 120, 0 ); // to use a word from our list
        ofSetColor(255, 255, 255, i - 100);
        ofPopMatrix();
    }
    // this is the minutes loop
    ofSetColor(0,255,0);
    for (int i = 0; i <360; i+=10){
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
        ofRotateDeg( (ofGetMinutes() * 6) - 90 );
        ofRotateDeg(i);
        if (ofGetMinutes()%2  == 0){
            font.drawString("this", 260,0 );
        } else {
            font.drawString("that", 260,0 );
        }
        
        ofSetColor(255, 255, 255, i -100);
        ofPopMatrix();
    }
    // this is the minutes loop
    
    ofSetColor(0,0,255);
    for (int i = 0; i <360; i+=10){
        ofPushMatrix();
        ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
        ofRotateDeg( (ofGetHours() * 30 ) - 90 );
        ofRotateDeg(i);
        font.drawString("sh*t", 400,0 );
        ofSetColor(255, 255, 255, i - 100);
        ofPopMatrix();
    }
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
