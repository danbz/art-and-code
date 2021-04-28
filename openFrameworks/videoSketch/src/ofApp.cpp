/*
 Project Title: Video Manipulation demo
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
    threshHold = 120;
    video.load("tiu keng leng platform walk1080.mov");
    video.setVolume(0);
    video.setSpeed(1.0);
    video.setLoopState(OF_LOOP_NORMAL);
    video.play();
    image = video.getPixels();
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    image = video.getPixels();
    image.update();
    
    ofColor col;
    for (int y = 0; y < image.getHeight(); y++ ){
        for (int x = 0; x < image.getWidth(); x++ ){
            col =  image.getColor( x, y );
            if (col.r > threshHold ){
               // col.set(255);
            col.setHsb( ofMap( x,  0,  image.getWidth(),  0,  255),  255,  255 );
            } else {
                col.set( 0 );
            }
            image.setColor(x, y, col);
        }
    }
    image.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
   // video.draw(0,0, ofGetWidth(), ofGetHeight());
    image.draw(0,0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
            
                    case OF_KEY_UP:
                        if( threshHold < 250){
                            threshHold += 5;
                        }
                        break;
            
                    case OF_KEY_DOWN:
                        if (threshHold > 10){
                            threshHold -= 5;
                        }
                        break;
            
        case OF_KEY_LEFT:
            video.setSpeed( video.getSpeed() - 0.1 );
            break;
            
        case OF_KEY_RIGHT:
            video.setSpeed( video.getSpeed() + 0.1 );
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}
