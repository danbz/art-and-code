
/*
 Project Title: Globe Draw
 Description: generate points on the surface of a sphere using cartesian co-ordinates, then generate  curve path between each point and draw in 3D
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

int globeRadius = 400;

//--------------------------------------------------------------
void ofApp::setup(){
    int numAnts = 10;
    driftAmount = 0.1;
    // globeRadius = 400;
    // initialise our points on the globe
    globe.set(globeRadius, 10);
    //    for (int i = 0; i<maxPoints; i++){
    //        ofPoint newCart;
    //        newCart.set(ofRandom(-180, 180.0), ofRandom(360.0),0);
    //        ofPoint newPoint = sphericalToCartesian(ofRandom(-180, 180.0), ofRandom(360.0), globeRadius);
    //        cartPositions.push_back(newCart);
    //        geoPositions.push_back(newPoint);
    //    }
   // ofBackground(33,25,175); // darkblue
    ofBackground(0);
    ofSetColor(254,224,58); // yellow
    // setup the path parameters we will draw with
    geoPath.setStrokeWidth(2);
    geoPath.setFilled(false);
    ofColor red(255,0,0, 200);
    geoPath.setColor(red);
    
    light.setPosition(1000, 2000, 2000);
    cam.setPosition(0, 0, 1000);
    
    for (int i = 0; i < numAnts; i++){
        ant newAnt;
        ants.push_back(newAnt);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    //    for (int i = 0; i < cartPositions.size(); i ++){
    //        ofPoint newCart= cartPositions[i];
    //        newCart.x += ofRandom(-driftAmount, driftAmount);
    //        newCart.y += ofRandom(-driftAmount, driftAmount) ;
    //        cartPositions[i] = newCart;
    //        ofPoint newPoint = sphericalToCartesian(newCart.x, newCart.y, globeRadius);
    //        geoPositions[i] = newPoint;
    //
    //    }
    for (int i = 0; i < ants.size(); i++){
        ants[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableDepthTest();
    cam.begin();
    light.enable();
    ofSetColor(100, 255, 100); // draw wire frame sphere in green
   // globe.drawWireframe();
    
    ofSetColor(200, 200, 200); //draw blobs at curve points in grey
    geoPath.clear();
    //    for (int i =0; i<geoPositions.size();i++){
    //        ofDrawSphere(geoPositions[i],  10.0);
    //        geoPath.curveTo(geoPositions[i]);
    //    }
    
    
    
    // draw ant curve
    for (int i = 0; i < ants.size(); i++){
        ofSetColor(200, 0, 200); //draw ant at curve points in grey
        ofPoint antLoc = ants[i].getPosition();
        ofPoint newPoint = sphericalToCartesian(antLoc.x, antLoc.y, globeRadius);
        ofDrawSphere(newPoint,  5.0);
        
        geoPath.curveTo(newPoint);
        ants[i].path.draw();
    }
    
    
    geoPath.draw();
    light.disable();
    cam.end();
    ofDisableDepthTest();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
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
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}


//--------------------------------------------------------------
ofVec3f sphericalToCartesian( float lat, float lon, float radius ){
    ofVec3f result;
    // new quaternion example
    // three rotations, two to represent the latitude and lontitude of the city
    // a third so that it spins along with the spinning sphere
    ofQuaternion latRot, longRot, spinQuat;
    lat *= -1;        // inverse latitude.
    lon += 180;        // longitude offset to match geometry of the sphere.
    latRot.makeRotate(lat, 1, 0, 0);
    longRot.makeRotate(lon, 0, 1, 0);
    spinQuat.makeRotate(0, 0, 1, 0);
    
    //our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
    ofVec3f center = ofVec3f(0,0,radius); // add distance above globe surface to draw to
    //multiplying a quat with another quat combines their rotations into one quat
    //multiplying a quat to a vector applies the quat's rotation to that vector
    //so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
    ofVec3f worldPoint = latRot * longRot * spinQuat * center;
    return worldPoint;
}

//--------------------------------------------------------------
ant::ant(){
    // constructor
    startPoint.set(ofGetWidth()/2, ofGetHeight()/2);
    currentPoint = startPoint;
    currentLength = 0;
    velocity.set(ofRandom(1), ofRandom(1));
    velocity.scale( 1 ); // scale velocity amplitude
    amplitude = 0.5;
    acceleration =0;
    angularAcceleration = ofRandom(-1, 1);
    numDrinks = 0.5; // set the drunkeness of our Ant path
    
    path.setStrokeWidth(4);
    path.setFilled(false);
    ofColor yellow(254,ofRandom(100, 255),ofRandom( 10, 255), 50);
    path.setColor(yellow);
}

//--------------------------------------------------------------
ant::~ant(){
    // destructor
}

//--------------------------------------------------------------
void ant::update(){
    nextPoint = velocity + currentPoint;
    currentLength += amplitude;
    // ofDrawLine(currentPoint, nextPoint);
    currentPoint = nextPoint;
    velocity = velocity.getRotated(angularAcceleration);
    velocity.scale(amplitude+acceleration);
    acceleration += ofRandom(-0.01, 0.01) * numDrinks;
    angularAcceleration += ofRandom(-1, 1);
    ofPoint newPoint = sphericalToCartesian(currentPoint.x, currentPoint.y, globeRadius);
    
    path.curveTo(newPoint);
}

//--------------------------------------------------------------
ofVec2f ant::getPosition(){
    return currentPoint;
}
