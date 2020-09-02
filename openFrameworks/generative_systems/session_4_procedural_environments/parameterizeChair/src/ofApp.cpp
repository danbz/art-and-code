/*
 Project Title:
 Description:
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 
 * Parameterize: Chair from Form+Code in Design, Art, and Architecture
 * implemented in OpenFrameworks by Anthony Stellato <http://rabbitattack.com/>
updated March 2020 dan buzzo
 * Requires OpenFrameworks available at http://openframeworks.cc/
 * For more information about Form+Code visit http://formandcode.com
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    chairSeatHeight      = 100;
    chairWidth           = 50;
    chairDepth           = 50;
    chairBackHeight      = 100;
    chairFrameThickness  = 10;
    ofSetFrameRate(60);
    ofEnableSmoothing();
    
    ofBackground(255, 255, 255);
    ofSetColor(100, 100, 200);
    light.setPosition(-100, 500, 500); // make a light to light our 3D scene
    light.setPointLight();
    
    cam.setPosition(-100, 50, 300); // set the position of our easyCam
    ofVec3f centre(0,0,0);
    
    cam.lookAt(centre);
    
    ofDisableArbTex(); // important to call this before we load our texture
    // allocate an image as a surface texture
    string textureName = "woodgrain.jpeg"; // import an image to be a texture for our chair
    ofLoadImage(texture, textureName);

    ofEnableDepthTest();
    light.enable();
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin(); // start our 3d camera controls
    drawChair();
    cam.end();
    ofDrawBitmapString("press spacebar to make new chair, 'f' for fullscreen", 20, ofGetHeight() - 40);
}

//--------------------------------------------------------------
void ofApp::drawChair(){
    // draw all the boxes that make up our chair
    ofTranslate( chairWidth/2, chairSeatHeight); // move to draw chair in middle at 0,0,0
    ofRotateDeg(180, 0, 0, 1); // chair is upsidedown rotate in z axis to set it right way up

    texture.bind(); // start the wood texture, this will be wrapped to any 3d shape we draw until we unbind the texture.
    
    // make the back
    ofPushMatrix();
    ofTranslate(chairWidth/2, chairBackHeight/2, 0);
    ofDrawBox(0, 0, 0, chairWidth, chairBackHeight, chairFrameThickness);
    ofPopMatrix();
    
    // make the seat
    ofPushMatrix();
    ofTranslate(chairWidth/2, chairBackHeight + chairFrameThickness/2,
                chairDepth/2 - chairFrameThickness/2);
    ofDrawBox(0, 0, 0, chairWidth, chairFrameThickness, chairDepth);
    ofPopMatrix();
    
    // make the legs
    ofPushMatrix();
    ofTranslate(chairFrameThickness/2, chairBackHeight + chairSeatHeight/2 + chairFrameThickness, 0);
    ofDrawBox(0, 0, 0, chairFrameThickness, chairSeatHeight, chairFrameThickness);
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofTranslate(chairWidth - chairFrameThickness/2,
                chairBackHeight + chairSeatHeight/2 + chairFrameThickness, 0);
    ofDrawBox(0, 0, 0, chairFrameThickness, chairSeatHeight, chairFrameThickness);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(chairWidth - chairFrameThickness/2,
                chairBackHeight + chairSeatHeight/2 + chairFrameThickness, chairDepth - chairFrameThickness);
    ofDrawBox(0, 0, 0, chairFrameThickness, chairSeatHeight, chairFrameThickness);
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(chairFrameThickness/2, chairBackHeight + chairSeatHeight/2 + chairFrameThickness,
                chairDepth - chairFrameThickness);
    ofDrawBox(0, 0, 0, chairFrameThickness, chairSeatHeight, chairFrameThickness);
    ofPopMatrix();
    
    texture.unbind(); // stop the wood texture
}

void ofApp::scrambleChair(){
    chairSeatHeight = floor(ofRandom(10, 200));
    chairWidth = floor(ofRandom(10, 200));
    chairDepth = floor(ofRandom(10, 200));
    chairBackHeight = floor(ofRandom(10, 200));
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            scrambleChair();
            break;
            
        case 'f':
            ofToggleFullscreen();
            
        default:
            break;
    }
}
