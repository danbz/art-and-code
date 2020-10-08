/*
 Project Title: SlitScan camera half push scan
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 https://youtube.com/danbuzzo
 */
#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    int numScreens = 4;
//        camWidth =  640;  // try to grab at this size from the camera. for Raspberry Pi
//        camHeight = 480;
    camWidth =  1280;  // try to grab at this size from an apple HDwebcam camera.
    camHeight = 720;
//        camWidth =  1280;  // try to grab at this size from a standard external 4x3 webcam camera.
//        camHeight = 1024;
    
    float aspectRatio = camHeight / camWidth;
    
    sWidth = ofGetWidth();
    sHeight = ofGetHeight();
    
    // calculate size of hour and minute thumbnails
    
    xSteps = ySteps = 0;
    speed = 1;
    b_smooth = false;
    b_drawCam = false;
    
    // ask the video grabber for a list of attached camera devices. & put it into a vector of devices
    vector<ofVideoDevice> devices = vidGrabber.listDevices();
    for(int i = 0; i < devices.size(); i++){ // loop through and print out the devices to the console log
        if(devices[i].bAvailable){
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
        }else{
            ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
        }
    }
    vidGrabber.setDeviceID(1); // set the ID of the camera we will use
    vidGrabber.setPixelFormat(OF_PIXELS_NATIVE);
    vidGrabber.setDesiredFrameRate(30); // set how fast we will grab frames from the camera
    vidGrabber.initGrabber(camWidth, camHeight); // set the width and height of the camera
    videoPixels.allocate(camWidth*numScreens,camHeight, OF_PIXELS_RGB); // set up our pixel object to be the same size as our camera object
    videoTexture.allocate(videoPixels);
     ofSetVerticalSync(true);
    
    ofSetBackgroundColor(0, 0, 0); // set the background colour to dark black
    ofSetFrameRate(30);
    ofDisableSmoothing();
   // ofEnableSmoothing();
    vidGrabber.update();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
   // pixels = vidGrabber.getPixels();
    
    
//    if (xSteps < videoPixels.getWidth()){
////        for (int y=0; y<camHeight; y++ ) { // loop through all the pixels on a line to draw new line at 0 in target image
////            color = pixels.getColor( camWidth/2, y); // get the pixels on line ySteps
////            camStrip.setColor(0, y, color);
////        }
////
////        for (int x = videoPixels.getWidth(); x>0; x-= 1){
////            for (int y=0; y<camHeight; y++ ) { // loop through all the pixels on a line
////                videoPixels.setColor(x+1, y, videoPixels.getColor( x, y )); // copy each pixel in the target to 1 pixel the right
////            }
////        }
////
////        for (int y=0; y<camHeight; y++ ) { // loop through all the pixels on a line to draw new line at 0 in target image
////            color = pixels.getColor( camWidth/2, y); // get the pixels on line ySteps
////            videoPixels.setColor(0, y, color);
////        }
//    }
    if (vidGrabber.isFrameNew()){
    videoTexture.loadScreenData(camWidth/2, 0, videoPixels.getWidth(), videoPixels.getHeight());
    }
//    // videoTexture.loadData(videoPixels);
//
//    if ( xSteps >= camWidth ) {
//        xSteps = 0; // if we are on the end of screen of the image then start at the top again
//    } else {
//        xSteps += speed; // step on to the next line. increase this number to make things faster
//    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vidGrabber.draw(0,0);
    videoTexture.draw(camWidth/2+1, 0); // draw the seconds slitscan video texture we have constructed
    
    if (b_drawCam){ // draw camera debug to screen
        vidGrabber.draw(sWidth-camWidth/4 -10, sHeight-camHeight/4 -10, camWidth/4, camHeight/4); // draw our plain image
        ofDrawBitmapString(" scanning half-push: press c: camview, a: antialiased, FPS:" + ofToString(ofGetFrameRate()) , 10, sHeight -10);
        
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 'c':
            b_drawCam =!b_drawCam;
            break;
            
        case 'a':
            if (b_smooth){
                ofEnableSmoothing();
            } else {
                ofDisableSmoothing();
            }
            b_smooth =!b_smooth;
            break;
            
        default:
            break;
    }
}
