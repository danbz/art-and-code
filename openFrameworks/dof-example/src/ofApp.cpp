/*
 Project Title:
 ©Daniel Buzzo 2021
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 http://youtube.com/danbuzzo
 */
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    b_wireFrame = b_swimDof = false;
    b_gui = true;
    depthOfField.setup(ofGetWidth(), ofGetHeight());
    int numBoxes = 500;
    spaceRange = 300;
    ofSetFrameRate(60);
    ofEnableDepthTest();
    
    for(int i = 0; i < numBoxes; i++){
        //  make random box primitives
        ofBoxPrimitive newBox;
        newBox.set(ofRandom(30, 100), ofRandom(30, 100), ofRandom(30, 100));
        newBox.setPosition(ofVec3f(ofRandom(-spaceRange, spaceRange),
                                   ofRandom(-spaceRange, spaceRange),
                                   ofRandom(-spaceRange, spaceRange)));
        for (int side = 0; side<6; side++){ // colour each side
            //complementing random hues
            newBox.setSideColor(side, ofColor::fromHsb(ofRandomuf() > .8 ? ofRandom(120, 130) : 128 - ofRandom(110, 128),
                                                       ofRandom(255), ofRandom(255)));
        }
        boxPrims.push_back(newBox);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    //swim the depth of field
    if (b_swimDof) depthOfField.setFocalDistance(ofMap(sin(ofGetElapsedTimef()/2),-1,1, 20, 150));
    
    float time = ofGetElapsedTimef() /100.0;
    
    spaceRange = 300 * ( ofNoise( 0.001 + time ) * 2);
    
    // change one box in vector;
   // if(ofRandom(1) >0.8){
        ofBoxPrimitive newBox;
        newBox.set(ofRandom(30, 100), ofRandom(30, 100), ofRandom(30, 100));
        newBox.setPosition(ofVec3f(ofRandom(-spaceRange, spaceRange),
                                   ofRandom(-spaceRange, spaceRange),
                                   ofRandom(-spaceRange, spaceRange)));
        for (int side = 0; side<6; side++){ // colour each side with complementing random hues
            newBox.setSideColor(side, ofColor::fromHsb(ofRandomuf() > .8 ? ofRandom(120, 130) : 128 - ofRandom(110, 128),
                                                       spaceRange/2.0, ofRandom(255)));
        }
        
        boxPrims[ ofRandom( boxPrims.size() ) ] = newBox;
    //}
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableAntiAliasing();
    float time = ofGetSystemTimeMillis() /100.0;
    
    depthOfField.begin();
    
    camera.begin(depthOfField.getDimensions());
    
    ofPushStyle();
    ofPushMatrix();
    ofRotateDeg(time );
    for(int i = 0; i < boxPrims.size(); i ++){
        if (b_wireFrame){
            boxPrims[i].drawWireframe();
            
        }else {
            boxPrims[i].draw();
        }
    }
    ofPopMatrix();
    ofPopStyle();
    
    camera.end();
    
    depthOfField.end();
    
    if(ofGetKeyPressed(' ')){
        depthOfField.drawFocusAssist(0, 0);
    }
    else{
        depthOfField.getFbo().draw(0, 0);
    }
    if (b_gui){
        ofDrawBitmapString("f: toggle fullscreen, w: toggle wireframe, space: focusassist, s: swim DOF \nspacerange is: " + ofToString(spaceRange) + " dof: " + ofToString(depthOfField.getFocalDistance() ) + " fps: " + ofToString(ofGetFrameRate()) , 10, 10 );
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f' :
            ofToggleFullscreen();
            depthOfField.setup(ofGetWidth(), ofGetHeight());
            break;
            
        case 'w':
            b_wireFrame=!b_wireFrame;
        default:
            
        case 's':
            b_swimDof=!b_swimDof;
            break;
            
        case 'g':
            b_gui = !b_gui;
            break;
            
        case OF_KEY_LEFT:
            spaceRange -=10;
            break;
            
        case OF_KEY_RIGHT:
            spaceRange +=10;
            break;
            
        case OF_KEY_UP :
            depthOfField.setFocalDistance( depthOfField.getFocalDistance() +3 );
            break;
            
        case OF_KEY_DOWN :
            depthOfField.setFocalDistance( depthOfField.getFocalDistance() -3 );
            break;

    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
