/*
 Project Title: Forest L System Example
 Description: example l system forest
 dependencies ofxLSystem and ofxLSystemGrammar by Davide Prati
 based upon forest example by Davide Prati @edapx
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
        // set up our light
    light.setPosition(500, 1000, 1600);
    light.enable();
    
    // set up our camera
    cam.setPosition(0, 100, 600);
    cam.lookAt(ofVec3f(0, 0, 0));
    //cam.setNearClip(0.01f);
    //cam.setMovementMaxSpeed( 25.f );
    
    // set up the ground plane
    plane.setPosition(100, 0, 0);
    plane.set(20000, 20000);
    plane.setResolution(20, 20);
    plane.rotateDeg(270, 1, 0 , 0);
    
    // set the surface material for the ground plane
    roadMaterial.setDiffuseColor(ofFloatColor::forestGreen);
    roadMaterial.setShininess(0.01);
    
    // set the surface material style for the trees
    treeMaterial.setAmbientColor(ofFloatColor::saddleBrown);
    treeMaterial.setSpecularColor(ofFloatColor::rosyBrown);
    treeMaterial.setDiffuseColor(ofFloatColor::burlyWood);
    treeMaterial.setShininess(0.02);
    
    ofEnableDepthTest();
    
    buildTree(); // add our first tree to the forest
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofDisableLighting();
    ofDisableDepthTest();
    ofBackgroundGradient( ofFloatColor::darkBlue, ofFloatColor::lemonChiffon, OF_GRADIENT_CIRCULAR);
    
    ofEnableDepthTest();
    ofEnableLighting();
    cam.begin();
    roadMaterial.begin();
    plane.draw();
    roadMaterial.end();
    treeMaterial.begin();
    forest.draw();
    treeMaterial.end();
    cam.end();
    
    ofDrawBitmapString("press 'f' to toggle fullscreen. 't' to add a new tree to the forest. \n'r' to reset the forest. 's' to save forest as .ply file", 20, ofGetHeight()-40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case 's':
            saveMesh();
            break;
            
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 't':
            buildTree();
            break;
            
        case 'r':
            forest.clear();
            buildTree();
            break;
    }
}
//--------------------------------------------------------------

void ofApp::keyReleased(int key){
    
}
//--------------------------------------------------------------


void ofApp::saveMesh(){
    // save the forest as a 3d .ply file into the data folder
    string randomFilename = ofGetTimestampString() + ".ply";
    forest.save(randomFilename);
}

//--------------------------------------------------------------

void ofApp::buildTree(){
    // add a fresh tree to our forest trees
    float halfScreen = ofGetWidth()/2;
    map<string, float> constants;
    constants.insert(make_pair("R", 1.356));
    
    //  generate a trees
    ofxLSystem tree;
    tree.setAxiom("A(100)");
    tree.setRules({"A(s) -> F(s)[+A(s/R)][-A(s/R)]"});
    tree.setRandomYRotation(true);
    tree.setConstants(constants);
    tree.setScaleWidth(true);
    tree.setResolution(20); // smoothness of the trunk cylinders
    tree.setStep(abs(ofRandom(5, 8))); // number of steps in the tree
    tree.setStepWidth(abs(ofRandom(30.5, 40.5))); // width of branches
    tree.setStepLength(abs(ofRandom(150, 600))); // length of branches
    tree.build();
    
    // position it randomly in the middle of the the screen
    auto pos = ofVec2f(ofRandom(-halfScreen, halfScreen),
                       ofRandom(-halfScreen, halfScreen));
    for (int i=0; i<tree.getMesh().getNumVertices(); i++) {
        tree.getMesh().getVerticesPointer()[i] += ofVec3f(pos.x, 0, pos.y);
    }
    // add the new tree into our forest vector of trees
    forest.append(tree.getMesh());
}
