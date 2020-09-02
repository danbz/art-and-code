/*
 Project Title:
 Description: 3D generative example
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    driftAmount = 0.1;
    primitive.setResolution(6, 6); // set the resolution of the underlying mesh in our primitive
    mesh = primitive.getMesh(); // use the vertices of our primitive to build our custom mesh object
    cam.setPosition(0, 0, 100); // set our 3D camera position
    light.setPosition(300, 300, 300); // set a light in our 3D world
    
    ofBackground(33,25,175); // darkblue
    ofSetColor(254,224,58); // yellow
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofVec3f newVec;
    
    // make each point in the mesh 'drift'
    // we could also use perlin noise here instead
    for (int i = 0; i < mesh.getNumVertices(); i++){
        newVec = mesh.getVertex(i);
        newVec.x += ofRandom(-driftAmount, driftAmount);
        newVec.y += ofRandom(-driftAmount, driftAmount);
        newVec.z += ofRandom(-driftAmount, driftAmount);
        mesh.setVertex(i, newVec);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    
    cam.begin();
    light.enable();
    
    ofSetColor(254,224,58); // yellow
    mesh.draw();

    ofSetColor(33,25,175); // darkblue
    mesh.drawWireframe();

    light.disable();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
