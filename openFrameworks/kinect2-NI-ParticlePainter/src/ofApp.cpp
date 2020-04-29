#include "ofApp.h"
// dan buzzo 2020 github/danbz
// buzzo.com
// adapted from the ofxNI2 tracker example
// depends upon ofxNI2 https://github.com/roymacdonald/ofxNI2
// possibly originally from https://github.com/satoruhiga

ofEasyCam cam;

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    device.setLogLevel(OF_LOG_NOTICE);
    device.setup(0);
    tracker.setup(device);
    
    // tracker.enableTrackingOutOfFrame(true);
    
    tracker.setSkeletonSmoothingFactor(0.8f);
    
    maxParticles = 1000;
    b_drawParticles = false;
}

void ofApp::exit()
{
    tracker.exit();
    device.exit();
}

//--------------------------------------------------------------
void ofApp::update()
{
    device.update();
    
    // loop through our particles vector updating each individual particle
    for (int i=0; i<particles.size(); i++){
        particles[i].update();
        particles[i].col.a -= 0.001; // decrement the alpha value of each particle's colour
    }
    
    // if we have more than maxParticles in our vector of particles then erase the first one in the vector
    if (particles.size() >= maxParticles){
        particles.erase(particles.begin());
    }
    
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //    depthPixels = tracker.getPixelsRef(1000, 4000);
    //    depthTexture.loadData(depthPixels);
    //
    //    // draw in 2D
    //    ofSetColor(255);
    //    depthTexture.draw(0, 0);
    //    tracker.draw();
    //
    
    
    //    // draw 3D skeleton in 2D
    //    ofPushView();
    //    tracker.getOverlayCamera().begin(ofRectangle(0, 0, depthTexture.getWidth(), depthTexture.getHeight()));
    //    ofDrawAxis(100);
    //    tracker.draw3D();
    //    tracker.getOverlayCamera().end();
    //    ofPopView();
    
    // draw our skeleton in 3D
    ofEnableDepthTest();
    cam.begin();
    ofDrawAxis(100);
    tracker.draw3D();
    
    // draw box
    // ofNoFill();
    ofColor red(255, 0, 0);
    ofColor blue(0, 0, 255);
    ofColor green(0, 255,0);
    ofVec3f leftHandPos, rightHandPos;
    
    for (int i = 0; i < tracker.getNumUser(); i++)
    {
        ofxNiTE2::User::Ref user = tracker.getUser(i);
        
        // get the positions from the tracker of head, lefthand and right hand for each user
        const ofxNiTE2::Joint &head = user->getJoint(nite::JOINT_HEAD);
        const ofxNiTE2::Joint &RHD = user->getJoint(nite::JOINT_RIGHT_HAND);
        const ofxNiTE2::Joint &LHD = user->getJoint(nite::JOINT_LEFT_HAND);
        
        // use the transformGL to position and draw a sphere at the head position
        ofSetColor(255, 255, 255);
        head.transformGL();
        ofDrawSphere(100);
        head.restoreTransformGL();
        
        // draw right hand by getting position data
        ofSetColor(red);
        rightHandPos = RHD.getGlobalPosition();
        ofDrawSphere(rightHandPos,20);
        // ofDrawBitmapString( ofToString(rightHandPos), rightHandPos);
        
        
        // draw left hand by getting position data
        leftHandPos = LHD.getGlobalPosition();
        ofSetColor(green);
        ofDrawSphere(leftHandPos, 40);
        // ofDrawBitmapString( ofToString(leftHandPos), leftHandPos);
        
        // use postion data from right hand to add a new particle to the particles vector
        if (leftHandPos.y > rightHandPos.y){
            b_drawParticles = true;
            particle newParticle(leftHandPos, green );
            particles.push_back(newParticle);
        } else {
            b_drawParticles = false;
        }
    }
    
    // if(b_drawParticles){
        for (int i=0; i<particles.size(); i++){
            particles[i].draw();
        }
    // }
    
    cam.end();
    ofDisableDepthTest();
    
    ofSetColor(255);
    ofDrawBitmapString("Tracker FPS: "+ofToString(tracker.getFrameRate()),20,ofGetHeight()-40);
    ofDrawBitmapString("Application FPS: "+ofToString(ofGetFrameRate()),20,ofGetHeight()-20);
    ofDrawBitmapString("number people : "+ofToString(tracker.getNumUser()),20,ofGetHeight()-60);
    
}

//--------------------------------------------------------------
particle::particle(ofVec3f startPoint, ofColor newCol){
    // constructor
    speed = 20;
    col = newCol;
    size = 10;
    location = startPoint;
    direction.set( ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1) );
    velocity.set( ofRandom(-speed,speed), ofRandom(-speed,speed), ofRandom(-speed,speed) );
}

//--------------------------------------------------------------
particle::~particle(){
    
}

//--------------------------------------------------------------
void particle::update(){
    location += direction * velocity;
}

//--------------------------------------------------------------
void particle::draw(){
    ofPushStyle();
    ofFill();
    ofSetColor(col);
    ofDrawCircle(location, size);
    ofPopStyle();
}
