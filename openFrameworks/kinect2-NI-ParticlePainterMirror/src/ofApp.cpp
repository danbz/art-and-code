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
    ofBackground(155);
    
    device.setLogLevel(OF_LOG_NOTICE);
    device.setup(0);
    device.setEnableRegistration();
    
    tracker.setup(device);
    tracker.setSkeletonSmoothingFactor(0.8f);
    
    maxParticles = 100;
    b_drawParticles = true;
    b_drawDebug = true;
    
    userMask.allocate(640, 480, OF_IMAGE_GRAYSCALE);
    color.setup(device);
    color.setSize(640, 480);
    color.start();
    
    
    //Allocate drawing buffer
    int w = ofGetWidth();
    int h = ofGetHeight();
    fbo.allocate( w, h, GL_RGB32F_ARB );
    
    //Fill buffer with black color
    fbo.begin();
    ofBackground(155, 155, 155);
    fbo.end();
    
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
    
    // if there is a user found by the tracker then get the pixels in the user silhouette
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
void ofApp::draw(){
    int alphaHistory = 1.0;
    
    depthPixels = tracker.getPixelsRef(1000, 4000);
    depthTexture.loadData(depthPixels);
    
    // draw in 2D
    ofSetColor(255);
    
    ofTexture rgbTexture;
    ofPixels rgbPixels;
    rgbPixels = color.getPixelsRef();
    rgbTexture.loadData(rgbPixels);
    ofImage rgbMasked;
    
    ofImage mask = userMask;
    mask.setImageType(OF_IMAGE_COLOR_ALPHA);
    mask.getTexture().setSwizzle(GL_TEXTURE_SWIZZLE_A, GL_RED);
    
    rgbMasked = rgbPixels;
    rgbMasked.getTexture().setAlphaMask(mask.getTexture());
    
    
    if (b_drawDebug){
        ofEnableAlphaBlending();
        
        depthTexture.draw(0, 0);
        tracker.draw();
        userMask.draw(640,0);
        rgbTexture.draw(userMask.getWidth(),480);
        rgbMasked.draw(0,480);
        ofDisableAlphaBlending();
        
    } else {
        ofEnableAlphaBlending();
        
        int offSetH = ofGetWidth()/2 - rgbMasked.getWidth()/2;
        int offSetW = ofGetHeight()/2 - rgbMasked.getHeight()/2;
        
        ofPushMatrix();
        ofTranslate(offSetH, offSetW);
        
        int alphaHistory = 5;
        // ofEnableDepthTest();
        
        fbo.begin();
        ofSetColor(0, 0, 0, alphaHistory);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        ofSetColor(255);
        // tracker.draw();
        rgbMasked.draw( 0, 0);
        
        ofColor red(255, 0, 0);
        ofColor green(0, 255,0);
        for (int i = 0; i < tracker.getNumUser(); i++)
        {
            ofxNiTE2::User::Ref user = tracker.getUser(i);
            ofVec2f head2D = user->head;
            ofVec2f lhd2D = user->leftHand;
            ofVec2f rhd2D = user->rightHand;
            
            // right hand
            ofSetColor(red);
            ofDrawCircle(rhd2D,5);
            
            // left hand
            ofSetColor(green);
            ofDrawCircle(lhd2D, 5);
            int movDist = 10;
            
            // if the users left hand has moved then add a new particle
            if (!particles.empty()){
                if (abs( lhd2D.x  - particles.back().location.x ) > movDist || abs( lhd2D.y  - particles.back().location.y ) > movDist ){
                    ofColor newCol;
                    newCol.setHsb(ofMap(rhd2D.y, 0, 200, 0, 255), 255, 255);
                    particle newParticle(lhd2D, newCol );
                    particles.push_back(newParticle);
                }
            } else { // add first particle
                ofColor newCol;
                                 newCol.setHsb(ofMap(rhd2D.y, 0, 200, 0, 255), 255, 255);
                                 particle newParticle(lhd2D, newCol );
                                 particles.push_back(newParticle);
            }
        }
        
        if(b_drawParticles){
            for (int i=0; i<particles.size(); i++){
                particles[i].draw();
            }
        }
        
        ofPopMatrix();
        fbo.end();
        fbo.draw(0,0, ofGetWidth(), ofGetHeight());
        ofSetColor( 0, 0, 0 );
        
    }
    
    ////
    
    
//    //do the same thing from the first example...
//    ofMesh mesh;
//        ofSetColor( 200, 50, 50, 100 );
//    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
//    for(unsigned int i = 1; i < particles.size(); i++){
//
//        //find this point and the next point
//        glm::vec3 thisPoint = particles[i-1].location;
//        glm::vec3 nextPoint = particles[i].location;
//
//        //get the direction from one to the next.
//        //the ribbon should fan out from this direction
//        glm::vec3 direction = (nextPoint - thisPoint);
//
//        //get the distance from one point to the next
//        float distance = glm::length(direction);
//
//        //get the normalized direction. normalized vectors always have a length of one
//        //and are really useful for representing directions as opposed to something with length
//        glm::vec3 unitDirection = glm::normalize(direction);
//
//        //find both directions to the left and to the right
//        glm::vec3 toTheLeft =  glm::rotate(unitDirection, -90.f, glm::vec3(0,0,1));
//        glm::vec3 toTheRight = glm::rotate(unitDirection, 90.f, glm::vec3(0,0,1));
//
//        //use the map function to determine the distance.
//        //the longer the distance, the narrower the line.
//        //this makes it look a bit like brush strokes
//        float thickness = ofMap(distance, 0, 60, 20, 2, true);
//
//        //calculate the points to the left and to the right
//        //by extending the current point in the direction of left/right by the length
//        glm::vec3 leftPoint = thisPoint+toTheLeft*thickness;
//        glm::vec3 rightPoint = thisPoint+toTheRight*thickness;
//
//        //add these points to the triangle strip
//        mesh.addVertex(glm::vec3(leftPoint.x, leftPoint.y, leftPoint.z));
//        mesh.addVertex(glm::vec3(rightPoint.x, rightPoint.y, rightPoint.z));
//        mesh.addColor(particles[i].col);
//    }
//
//    //end the shape
//    mesh.draw();
    ///
    
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
            
        case 'f':
            ofToggleFullscreen();
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
    size = 10;
    location = startPoint;
    //    direction.set( ofRandom(-1,1), ofRandom(-1,1), ofRandom(-1,1) );
    //    velocity.set( ofRandom(-speed,speed), ofRandom(-speed,speed), ofRandom(-speed,speed) );
}

//--------------------------------------------------------------
particle::~particle(){
    
}

//--------------------------------------------------------------
void particle::update(){
    // location += direction * velocity;
    col.a -= 0.005;
    size -= 0.02;
}

//--------------------------------------------------------------
void particle::draw(){
    ofPushStyle();
    ofFill();
    ofSetColor(col);
    ofDrawCircle(location, size);
    ofPopStyle();
    
    
    
    
}
