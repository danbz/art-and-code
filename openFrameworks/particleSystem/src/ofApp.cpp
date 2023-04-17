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
    maxParticles = 2000;
    ofEnableLighting();
    ofEnableDepthTest();
    light.setPosition(0,-600,300);
    
    ofSetSphereResolution(4);
}

//--------------------------------------------------------------
void ofApp::update(){
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'update' itself
    if (particles.size() > maxParticles){
        particles.erase(particles.begin());
    }
    for (int i=0; i<particles.size();i++){
        particles[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam.begin();
    ofRotateDeg(180, 0, 0, 1); // TRANSLATE THE CAMERA
    light.enable();
    ofDrawAxis(400);
    // look through all the 'particle' objects in the 'particles' vector and instruct each one to 'draw' itself
    for (int i=0; i<particles.size();i++){
        particles[i].draw();
    }
    light.disable();
    cam.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
        case 'F':
            ofToggleFullscreen();
            break;
            
        case ' ':
            int numParticles = 200;
            for (int i=0; i < numParticles; i++){
             particle newParticle( 0, 0, 0, hue );
             // push the new particle we just made onto the back of the vector 'particles'
             particles.push_back(newParticle);
            }
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    hue = ofRandom( 255); // pick random hue on each button press
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // when the mouse is clicked and dragged make a new particle object
    // and set it's initial x,y position to the mouse x,y position by
    // passing the mouseX and mouseY to the constructor routine as parameters
    //    particle newParticle( mouseX, mouseY, 0, hue );
    //    // push the new particle we just made onto the back of the vector 'particles'
    //    particles.push_back(newParticle);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //    hue = ofRandom( 255); // pick random hue on each button press
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}


//--------------------------------------------------------------

particle::particle(int startX, int startY, int startZ, int hue){
    // this is the constructor routine, called when we make a new object of our particle class defined in the header
    float speed = 20.0;
    position = glm::vec3(startX, startY, startZ);
    force = glm::vec3(0, 0.2, 0);
    direction = glm::vec3( ofRandom( -speed, speed), ofRandom( -speed, speed) , ofRandom( -speed, speed) );
    size = 20;
    color.setHsb(hue, 255, 255);
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
    //ofDrawCircle(position, size);
     ofDrawSphere(position, size);
    // ofDrawBox(position,  size);
}
