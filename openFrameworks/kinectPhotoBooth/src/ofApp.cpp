
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // set up our kinect sensor
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    b_drawPointCloud = false;
    b_drawGui = true;
    b_saving = false;
    
    // set up our GUI
    gui.setup("panel");
    gui.add(nearClip.set("nearClip", 500, 100, 2000));
    gui.add(farClip.set("farClip", 800, 500, 8000));
    
    // load sounds and true type font
    beep.load("Beep_Short.mp3");
    click.load("Camera-shutter-sound-effect.mp3");
    font.load("frabk.ttf", 400);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    int delay = 1000; // set the delay between count down steps
    
    kinect.update(); // get fresh data from the kinect sensor
    
    // make a count-down when we want to save a 3D file
    if (b_saving){
        if ( ofGetSystemTimeMillis()  > counter + delay){
            if (countDown==1){
                click.play();
                // make a unique file name by including the system time in the name we save with
                pointCloud.save("cloud" + ofToString(ofGetSystemTimeMillis()) + ".ply");
                b_saving = false;
            } else {
                countDown--;
                counter = ofGetSystemTimeMillis();
                beep.play();
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (b_drawPointCloud){
        // draw our point cloud
        cam.begin();
        drawPointCloud();
        cam.end();
    } else {
        // draw debug images to screen
        kinect.draw(0, 0, kinect.width/2, kinect.height/2);
        kinect.drawDepth(kinect.width/2, 0, kinect.width/2, kinect.height/2);
    }
    if (b_drawGui){
        // draw the gui to screen
        gui.draw();
    }
    
    if (b_saving){
        // if we are saving a file draw the countdown number to screen
        font.drawString( ofToString( countDown ) , ofGetWidth() / 2 - font.stringWidth( ofToString( countDown ) ) / 2 , ofGetHeight() / 2 );
       // ofDrawBitmapString(countDown, ofGetWidth()/2, ofGetHeight()/2);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case 'p':
            b_drawPointCloud = ! b_drawPointCloud;
            break;
            
        case 'g':
            b_drawGui = ! b_drawGui;
            break;
            
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 's':
            b_saving = true;
            counter = ofGetSystemTimeMillis();
            countDown = 3; // start our count down from 3
            beep.play();

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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

//--------------------------------------------------------------
void ofApp::drawPointCloud(){
    
    //ofMesh pointCloud;
    pointCloud.clear();
   // pointCloud.setMode(OF_PRIMITIVE_POINTS);
    
    pointIndex.clear();
    
    // generate points in a mesh object for our point cloud
    for (int y = 0; y < kinect.height; y ++){
        for (int x = 0; x < kinect.width; x++) {
            ofVec3f point;
            point = kinect.getWorldCoordinateAt(x, y);
            // if (point.z > nearClip && point.z < farClip){
                pointCloud.addVertex(point);
                pointCloud.addColor(kinect.getColorAt(x, y));
                // ofColor col;
                // col.setHsb( ofMap(point.z, 100, 8000, 0, 255 ),  255,  255);
                // pointCloud.addColor(col);
            // }
            if(point.z){
                pointIndex.push_back(1);
            } else {
                pointIndex.push_back(0);
               // ofVec3f point;
                //pointCloud.addVertex(point);
            }
        }
    }
    
    /*
     triangulate the mesh points for our left and right handed triangles
     each triangle needs three indices described
     0-1-10 for left hand triangle and 1-11-10 for right hand triangle
     
     0  -- 1
     |  /  |
     | /   |
     10 -- 11
     
     */
    int height = kinect.height;
    int width = kinect.width;
    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            if ( pointIndex[x+y*width] && pointIndex[(x+1)+y*width] && pointIndex[x+(y+1)*width]){
                // indices for left hand triangle
                pointCloud.addIndex(x+y*width);                // 0
                pointCloud.addIndex((x+1)+y*width);            // 1
                pointCloud.addIndex(x+(y+1)*width);            // 10
             }
             if (pointIndex[(x+1)+y*width] && pointIndex[(x+1)+((y+1)*width)] && pointIndex[x+(y+1)*width]  ){
                 // indices for right hand triangle
                pointCloud.addIndex((x+1)+y*width);            // 1
                pointCloud.addIndex((x+1)+((y+1)*width));        // 11
                pointCloud.addIndex(x+(y+1)*width);            // 10
             }
        }
    }
    
    glPointSize(3);
    
    ofEnableDepthTest();
    ofPushMatrix();
    ofScale(1,-1,-1);
    ofTranslate(0,0, -1000);
    // pointCloud.drawVertices();
    // pointCloud.drawWireframe();
    pointCloud.draw();
    ofPopMatrix();
    
    ofDisableDepthTest();
}
