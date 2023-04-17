/*
 Project Title: 3D boxes in space
 Description:
 ©Daniel Buzzo 2021
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 http://youtube.com/danbuzzo
 
 3d eye texture from http://www.rockthe3d.com/35-free-high-res-realistic-human-eye-textures/human-eye-texture-002/
 */


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    int maxBoxes = 500;
    int maxSpheres = 200;
    
    spaceRange = 1000;
    ofEnableDepthTest();
    ofSetBackgroundColor(0);
    ofSetColor(255);
    light.setPosition(-500, 500, 500);
    light.enable();
    eye.load("human-eye-texture-003.jpg");
    // eye.getTexture().setTextureWrap( GL_REPEAT, GL_REPEAT );
    
    for (int i = 0; i < maxBoxes; i ++){
//        ofBoxPrimitive newBox;
//        newBox.set(100, 100 , 100);
//        newBox.setPosition( ofRandom(-spaceRange, spaceRange),
//                           ofRandom(-spaceRange, spaceRange),
//                           ofRandom(-spaceRange, spaceRange));
//        for (int side =0; side < 6; side ++){
//            newBox.setSideColor( side,  ofColor::fromHsb(ofRandom(255),  255,  255));
//        }
//        boxes.push_back(newBox);
        makeABox();
    }
    
//        for (int i = 0; i < maxSpheres; i ++){
//            ofSpherePrimitive newSphere;
//            newSphere.set(ofRandom(20,150), 10); // randomise the size between 20-150
//            newSphere.mapTexCoordsFromTexture(eye.getTexture());
//            newSphere.setPosition( ofRandom(-spaceRange, spaceRange),
//                               ofRandom(-spaceRange, spaceRange),
//                               ofRandom(-spaceRange, spaceRange));
//
//            spheres.push_back(newSphere);
//        }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    boxes[ofRandom( boxes.size()) ].setPosition( ofRandom(-spaceRange, spaceRange),
                                                ofRandom(-spaceRange, spaceRange),
                                                ofRandom(-spaceRange, spaceRange));
    boxes[ofRandom( boxes.size()) ].set(ofRandom(500), ofRandom(500) , ofRandom(500));
    
    glm::vec3 boxOrientation(ofRandom(360),ofRandom(360),ofRandom(360));
    boxes[ofRandom( boxes.size()) ].setOrientation(boxOrientation );
    
//        spheres[ofRandom( spheres.size()) ].setPosition( ofRandom(-spaceRange, spaceRange),
//                           ofRandom(-spaceRange, spaceRange),
//                           ofRandom(-spaceRange, spaceRange));
//       glm::vec3 eyeOrientation(ofRandom(360),ofRandom(360),ofRandom(360));
//    spheres[ofRandom( spheres.size()) ].setOrientation(eyeOrientation );
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetSystemTimeMillis()/100.0;
    cam.begin();
    eye.getTexture().bind();
    ofPushMatrix();
    ofRotateDeg(time);
    
    for (int i = 0; i <boxes.size(); i++){
        boxes[i].draw();
    }
    
//        for (int i = 0; i <spheres.size(); i++){
//            eye.getTexture().bind();
//            spheres[i].draw();
//            eye.getTexture().unbind();
//        }
    ofPopMatrix();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
            
            
        case OF_KEY_UP:
            spaceRange +=10;
            break;
            
        case OF_KEY_DOWN:
            spaceRange -=10;
            break;
            
        case '+':
        case '=':
            makeABox();
            break;
            
        case '-':
        case '_':
            if (boxes.size()>2){
                boxes.erase(boxes.end() - 1);
            }
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

void ofApp::makeABox(){
    ofBoxPrimitive newBox;
    newBox.set(100, 100 , 100);
    newBox.setPosition( ofRandom(-spaceRange, spaceRange),
                       ofRandom(-spaceRange, spaceRange),
                       ofRandom(-spaceRange, spaceRange));
    for (int side =0; side < 6; side ++){
        newBox.setSideColor( side,  ofColor::fromHsb(ofRandom(255),  255,  255));
    }
    boxes.push_back(newBox);
}
