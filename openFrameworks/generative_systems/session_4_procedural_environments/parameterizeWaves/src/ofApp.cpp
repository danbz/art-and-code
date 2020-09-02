/*
Project Title:
Description:
dan@buzzo.com
http://buzzo.com
https://github.com/danbz
 * Parameterize: Waves from Form+Code in Design, Art, and Architecture
* implemented in OpenFrameworks by Anthony Stellato <http://rabbitattack.com/>
* updated dan buzzo march 2020
* Requires OpenFrameworks available at http://openframeworks.cc/
* For more information about Form+Code visit http://formandcode.com
*/


 #include "ofApp.h"
int brickWidth = 40;
int brickHeight = 15;
int cols = 20;
int rows = 24;
int columnOffset = 60;
int rowOffset = 30;
float rotationIncrement = 0.15;
static float QUARTER_PI = PI/4.0f;
float r = ofRandom(-QUARTER_PI, QUARTER_PI);

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofEnableSmoothing();
    ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    ofSetColor(0, 0, 0);
    ofTranslate(30, 30, 0);
    for(int i = 0; i < cols; i++){
        ofPushMatrix();
        ofTranslate(i * columnOffset, 0, 0);
        int dir = 1;
        for(int j = 0; j < rows; j++){
            ofPushMatrix();
            ofTranslate(0, rowOffset * j, 0);
            ofRotateDeg(ofRadToDeg(r), 0, 0, 1);
            ofDrawRectangle(-brickWidth/2, -brickHeight/2, brickWidth, brickHeight);
            ofPopMatrix();
            r += dir * rotationIncrement;
            if(r > QUARTER_PI || r < -QUARTER_PI)
                dir *= -1;
        }
        ofPopMatrix();
    }
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
    r = ofRandom(-QUARTER_PI, QUARTER_PI);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}
