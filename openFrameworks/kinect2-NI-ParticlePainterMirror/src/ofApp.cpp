// dan buzzo 2020 github/danbz
// buzzo.com
// adapted from the ofxNI2 tracker example
// depends upon ofxNI2 https://github.com/roymacdonald/ofxNI2
// possibly originally from https://github.com/satoruhiga

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);
    
    device.setLogLevel(OF_LOG_NOTICE);
    device.setup(0);
    device.setEnableRegistration();
    
    tracker.setup(device);
    tracker.setSkeletonSmoothingFactor(0.8f);
    
    maxParticles = 1000;
    b_drawParticles = true;
    b_drawDebug = true;
    
    cout << tracker.getUserMap().getWidth() << endl;
    userMask.allocate(640, 480, OF_IMAGE_GRAYSCALE);
    color.setup(device);
    color.setSize(640, 480);
    color.start();
}

//--------------------------------------------------------------
void ofApp::exit() {
    tracker.exit();
    device.exit();
    color.exit();
}

//--------------------------------------------------------------
void ofApp::update()
{
    device.update();
    
    // particles
    for (int i=0; i<particles.size(); i++){
        particles[i].update();
    }
    
    if (particles.size() >= maxParticles){
        particles.erase(particles.begin());
    }
    
    if(tracker.getNumUser() > 0){
        const short int *userPixels = tracker.getUserMap().getPixels();
        long total = tracker.getUserMap().getWidth() * tracker.getUserMap().getHeight();
        unsigned char maskPixels[total];
        
        for (int i=0; i<total; i++) {
            if (userPixels) {
                if (*userPixels != 0) {
                    maskPixels[i] = 255;
                } else {
                    maskPixels[i] = 0;
                }
            }
            userPixels++;
        }
        userMask.setFromPixels(maskPixels, tracker.getUserMap().getWidth(), tracker.getUserMap().getHeight(), OF_IMAGE_GRAYSCALE);
        userMask.update();
    }

    color.updateTextureIfNeeded();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    depthPixels = tracker.getPixelsRef(1000, 4000);
    depthTexture.loadData(depthPixels);
    
    // draw in 2D
    ofSetColor(255);
    
    ofTexture rgbTexture;
    ofPixels rgbPixels;
    rgbPixels = color.getPixelsRef();
    //rgbPixels.resize(640, 480);
    rgbTexture.loadData(rgbPixels);
    
    ofTexture mask = userMask.getTexture();
    ofTexture rgbMasked;
    rgbMasked = rgbTexture;
    rgbMasked.setAlphaMask(mask);
    
    
    if (b_drawDebug){
        depthTexture.draw(0, 0);
        tracker.draw();
        userMask.draw(640,0);
        rgbTexture.draw(userMask.getWidth(),480);
        rgbMasked.draw(0,480);
        
    } else {
        
        int offSetH = ofGetWidth()/2 - rgbMasked.getWidth()/2;
        int offSetW = ofGetHeight()/2 - rgbMasked.getHeight()/2;
        ofPushMatrix();
        ofTranslate(offSetH, offSetW);
        rgbMasked.draw( 0, 0);
        // tracker.draw();
        
        ofColor red(255, 0, 0);
        ofColor blue(0, 0, 255);
        ofColor green(0, 255,0);
        for (int i = 0; i < tracker.getNumUser(); i++)
        {
            ofxNiTE2::User::Ref user = tracker.getUser(i);
            ofVec2f head2D = user->head;
            ofVec2f lhd2D = user->leftHand;
            ofVec2f rhd2D = user->rightHand;
            
            // ofSetColor(255, 255, 255);
            // ofDrawCircle(head2D,20);
            
            // right hand
            ofSetColor(red);
            ofDrawCircle(rhd2D,5);
            
            // left hand
            ofSetColor(green);
            ofDrawCircle(lhd2D, 5);
            
            ofColor newCol;
            newCol.setHsb(ofMap(rhd2D.y, 0, 200, 0, 255), 255, 255);
            particle newParticle(lhd2D, newCol );
            particles.push_back(newParticle);
            
            // if (lhd2D.y > rhd2D.y){
            //   b_drawParticles = true;
            // } else {
            //   b_drawParticles = false;
            // }
        }
        
        if(b_drawParticles){
            for (int i=0; i<particles.size(); i++){
                particles[i].draw();
            }
        }
        ofPopMatrix();
    }
    
    ofSetColor(255);
    ofDrawBitmapString("Tracker FPS: "+ofToString(tracker.getFrameRate()),20,ofGetHeight()-40);
    ofDrawBitmapString("Application FPS: "+ofToString(ofGetFrameRate()),20,ofGetHeight()-20);
    ofDrawBitmapString("number people : "+ofToString(tracker.getNumUser()),20,ofGetHeight()-60);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'd':
            b_drawDebug = !b_drawDebug;
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
particle::particle(ofVec3f startPoint, ofColor newCol){
    // constructor
    speed = 6;
    col = newCol;
    size = 5;
    location = startPoint;
    direction.set( ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1) );
    velocity.set( ofRandom(-speed,speed), ofRandom(-speed,speed), ofRandom(-speed,speed) );
}

//--------------------------------------------------------------
particle::~particle(){
    
}

//--------------------------------------------------------------
void particle::update(){
    // location += direction * velocity;
    col.a -= 0.001;
}

//--------------------------------------------------------------
void particle::draw(){
    ofPushStyle();
    ofFill();
    ofSetColor(col);
    ofDrawCircle(location, size);
    ofPopStyle();
}
