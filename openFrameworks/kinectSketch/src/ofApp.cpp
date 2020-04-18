
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    kinect.setRegistration(true);
    kinect.init();
    kinect.open();
    
    b_drawPointCloud = false;
    b_drawGui = true;
    
    gui.setup("panel");
    gui.add(nearClip.set("nearClip", 500, 100, 2000));
    gui.add(farClip.set("farClip", 800, 500, 8000));
}

//--------------------------------------------------------------
void ofApp::update(){
    kinect.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if (b_drawPointCloud){
        cam.begin();
        drawPointCloud();
        cam.end();
        
    } else {
        
        // draw debug images to screen
        kinect.draw(0, 0, kinect.width/2, kinect.height/2);
        kinect.drawDepth(kinect.width/2, 0, kinect.width/2, kinect.height/2);
    }
    if (b_drawGui){
        gui.draw();
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
            pointCloud.save("cloud.ply");
            
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
    
    // triangulate the mesh points
    int height = kinect.height;
    int width = kinect.width;
    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            if ( pointIndex[x+y*width] && pointIndex[(x+1)+y*width] && pointIndex[x+(y+1)*width]){
                pointCloud.addIndex(x+y*width);                // 0
                pointCloud.addIndex((x+1)+y*width);            // 1
                pointCloud.addIndex(x+(y+1)*width);            // 10
             }
             if (pointIndex[(x+1)+y*width] && pointIndex[(x+1)+((y+1)*width)] && pointIndex[x+(y+1)*width]  ){
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
