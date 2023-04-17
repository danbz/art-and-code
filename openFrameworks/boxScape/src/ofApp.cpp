#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    scapeWidth = 200;
    scapeDepth = 400;
    boxSize = 1;
    maxHeight = 8;
    b_rotate = b_march = false;
    
    boxes.setup(scapeDepth * scapeDepth );
    //  ofBoxPrimitive newBox;
    //  newBox.set(boxSize);
    //  newBox.setResolution(1);
    ofVboMesh vbo;
    for (int i = 0; i < scapeDepth * scapeWidth ; i ++){
        //        newBox.setHeight(ofRandom(1, maxHeight));
        //        boxes.pushMesh(newBox.getMesh());
        float height =ofRandom(1, maxHeight);
        boxes.pushMesh( height);
    }
    light.setPointLight();
    light.setPosition(0, 300 , 0);
    ofEnableDepthTest();
    light.enable();
    ofxLoadCamera(cam, "camera_position");
}

//--------------------------------------------------------------
void ofApp::update(){
    if (b_march){
        // ofBoxPrimitive newBox;
        // newBox.set(boxSize);
        float height;
        for (int i = 0; i < scapeWidth; i ++){
            // newBox.setHeight(ofRandom(1, maxHeight));
            // boxes.pushMesh(newBox.getMesh());
            
            if(ofRandom(10)<9.5){
                height =ofRandom(0, maxHeight);
            } else {
                height =ofRandom(1, maxHeight  * ofNoise( ofGetSystemTimeMillis()/10000.0f ) * maxHeight);
            }
            boxes.pushMesh( height);
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    int  i = 0;
    light.enable();
    cam.begin();
//    box.setResolution(1);
//    box.set(boxSize);
    for (int z = 0; z < scapeDepth; z ++){
        for (int x = 0; x < scapeWidth; x ++){
            ofPushMatrix();
            ofTranslate(x * boxSize - scapeWidth/2 * boxSize,0 , z * boxSize - scapeDepth/2 * boxSize);
             ofRotateYDeg(i / 100.0f);
            // ofRotateZDeg(i / 1000.0f);
            ofDrawBox(0, 0, 0, boxSize,  boxes.getDelayedMesh(i), boxSize);
            // ofDrawBox(0, 0, 0, boxes.getDelayedMesh(i)/5,  boxes.getDelayedMesh(i), boxes.getDelayedMesh(i)/5);
            
            ofPopMatrix();
            i ++;
        }
    }
    cam.end();
    light.disable();
    ofSetColor(255 );
    ofDrawBitmapString(ofToString(ofGetFrameRate()) + " : fps" , 20, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key){
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 'r':
            b_rotate = !b_rotate;
            break;
            
        case 'm':
            b_march= !b_march;
            break;
            
        case 's':
            ofxSaveCamera(cam, "camera_position");
            
        default:
            break;
    }
}
