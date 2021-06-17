/*
 Project Title:
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
    ofSetBackgroundColor(0, 0, 0);
    hue = 0;
}

//--------------------------------------------------------------
void ofApp::update(){
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'update' itself
    for (int i=0; i<particles.size();i++){
        particles[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'draw' itself
    for (int i=0; i<particles.size();i++){
        particles[i].draw();
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
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // when the mouse is clicked and dragged make a new particle object
    // and set it's initial x,y position to the mouse x,y position by
    // passing the mouseX and mouseY to the constructor routine as parameters
    particle newParticle( mouseX, mouseY , hue );
    // push the new particle we just made onto the back of the vector 'particles'
    particles.push_back(newParticle);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
     hue = ofRandom( 255); // pick random hue on each button press
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}


//--------------------------------------------------------------

particle::particle(int startX, int startY, int hue){
    // this is the constructor routine, called when we make a new object of our particle class defined in the header
    position = glm::vec2(startX, startY);
    force = glm::vec2(0, 0.02);
    direction = glm::vec2( ofRandom( -2.0, 2.0), ofRandom( -2.0, 2.0) );
    size = 30;
    color.setHsb(hue,  255,  255, 200);
}
//--------------------------------------------------------------

particle::~particle(){
    // destructor
}
//--------------------------------------------------------------

void particle::update(){
    // update the particle x,y position by incrementing each by the velocity vx and vy
    position += direction ;
    direction +=  force;
        if (size > 1){
            size -=0.07;
        }
        float brightness = color.getBrightness();
        float myHue = color.getHue();
    
        if (brightness >20){
           // color.setBrightness( brightness -=0.5 );
            color.setHue( myHue -=0.5 );
    
        }
}

//--------------------------------------------------------------

void particle::draw(){
    ofSetColor(color);
    ofDrawCircle(position, size);
}
