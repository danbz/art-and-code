/*
 Project Title:
 Description: from a demo by zach lieberman
 https://www.youtube.com/watch?v=bmztlO9_Wvo
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
    ofSetCircleResolution(100);
    ofSetDepthTest(false); // disable this for smooth colour // enable for shards of colour
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    float time = ofGetElapsedTimef();
    
    for (int x = 1; x < 40; x ++){
        
        for (int i=0; i < 900; i+=5){
           // ofSetCircleResolution(53 + 50 * sin(i *0.001 + time  )); // makes sure the smallest resolution is 3side (for triangles)
            
            ofSetColor(127 + 127 * sin(i * 0.01 + time + x ),
                       127 + 127 * sin(i * 0.011 + time ),
                       127 + 127 * sin(i * 0.012 + time ));
            
            // take your pick
            // ofDrawCircle( ofGetWidth()/2 , i, 100 );
            // ofDrawCircle( ofGetWidth()/2 + 100 * sin( i * 0.01 + time ), i , 50 +  40 * sin( i * 0.005 + time  ) ) ;
            
             ofDrawCircle( 50 * x + 100 * sin( i * 0.01 + time + x), 50 + i , 50 +  40 * sin( i * 0.005 + time + x) ) ;
            // ofDrawSphere(50 * x + 100 * sin( i * 0.01 + time + x), 50 * x + 100 * sin( i * 0.01 + time + x), 50 + i , 50 +  40 * sin( i * 0.005 + time + x) ) ; // draw spheres in 3D
        }
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

