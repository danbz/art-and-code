/*
 Project Title:
 Description: Mesh generation example with random and perlin noise distortion
 ©Daniel Buzzo 2021
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 http://youtube.com/danbuzzo
 */

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    mainMesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    ofEnableDepthTest();
    
    //set the width and height for our mesh and initial rendering values
    width = 500;
    height = 500;
    // set our rendering styles to false
    b_messyMesh = false;
    b_perlinMesh = false;
    b_marchMesh = false;
    b_drawWireFrame = true;
    //    // set the initial values to use for our perlinNoise
        perlinRange =1.0;
        perlinHeight = 5.0;
    
    ofBackground(0); // set the window background to black
    ofSetColor(255);
    mainCam.setPosition(0, 0, 80); // set initial position for our easyCam 3D viewer
    
    // here we make the points inside our mesh
    // add one vertex to the mesh across our width and height
    // we use these x and y values to set the x and y co-ordinates of the mesh, adding a z value of zero to complete the 3d location of each vertex
    
    for (int y = 0; y < height; y++){
        for (int x = 0; x<width; x++){
            mainMesh.addVertex( ofPoint(x - width /2 , y - height / 2 ,0)); // mesh index = x + y*width
            mainMesh.addColor(ofFloatColor(0,0,50));
            
        }
    }
    
    // here we loop through and join the vertices together as indices to make rows of triangles to make the wireframe grid
    
    for (int y = 0; y<height-1; y++){
        for (int x=0; x<width-1; x++){
            mainMesh.addIndex(x+y*width);                // 0
            mainMesh.addIndex((x+1)+y*width);            // 1
            mainMesh.addIndex(x+(y+1)*width);            // 10
            
            mainMesh.addIndex((x+1)+y*width);            // 1
            mainMesh.addIndex((x+1)+(y+1)*width);        // 11
            mainMesh.addIndex(x+(y+1)*width);            // 10
        }
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofColor newColor;
    ofVec3f newPosition, oldPosition;
    
    // change the z value for each vertex in our mesh
    if (b_messyMesh) {
        if (!b_marchMesh ){
        for (int i = 0; i < mainMesh.getNumVertices(); i++){ // find the total of all the vertices in the mesh and loop through them
            newPosition = mainMesh.getVertex(i); // get the current x,y,z position of this vertex
            newPosition.z = ofRandom(-perlinHeight, perlinHeight); // set the z value of it to a new random number
            mainMesh.setVertex(i, newPosition); // update the position of the vertex with the new co-ordinates
        }
                    } else {
                        for (int y = height; y>0; y--){
                            for (int  x= width; x>0; x--){
                                oldPosition = mainMesh.getVertex( x + ( y  * width));
                                newPosition = mainMesh.getVertex(x + ( (y - 1) * width) );
                                oldPosition.z = newPosition.z;
                                mainMesh.setVertex( x + ( y * width ), oldPosition); // update the position of the vertex with the new
                                newColor.setHsb(150 ,  255 - ofMap( newPosition.z, 0,  perlinHeight, 0 ,  255), 255);
                                mainMesh.setColor(x + ( y * width ), newColor);
        
                            }
                        }
                        for (int x=0; x<width; x++){
                            newPosition = mainMesh.getVertex(x); // get the current x,y,z position of this vertex
                            newPosition.z = ofRandom(-perlinHeight, perlinHeight); // set the z value of it to a new random number
                            mainMesh.setVertex(x, newPosition); // update the position of the vertex with the new co-ordinates
                        }
                    }
        
    }
    
    if (b_perlinMesh){
        // distort the z value of each point in our mesh with perlinNoise
        // use time to flow the perlin distortion of the mesh
        // use mesh height value to color the vertices
        float time = ofGetSystemTimeMillis() /100.0;
        int i=0;
        for (int y = 0; y<height; y++){
            for (int x=0; x<width; x++){
                newPosition = mainMesh.getVertex(i);
                // use the ofMap function to map our x,y inputs to a variable outpur range so we can see different levels of complexity / density in the perlinNoise. then multiply the z distortion by our perlinHeight value to get amplitude of distortion.
                newPosition.z = ofNoise( ofMap( x + time, 0, width, 0, perlinRange),  ofMap(y, 0, height, 0, perlinRange) ) * perlinHeight;
                newColor.setHsb(150 ,  255 - ofMap( newPosition.z, 0,  perlinHeight, 0 ,  255), 255);
                mainMesh.setVertex(i, newPosition); // update the position of the vertex with the new
                mainMesh.setColor(i, newColor);
                i++;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    glPointSize(10);
    mainCam.begin();

    if (b_drawWireFrame){ // choose to draw our mesh as wireframe or point cloud
        mainMesh.drawWireframe();
    } else {
        mainMesh.drawVertices();
    }
    
    mainCam.end();
    
    //draw the controls as text on the screen
    string msg = "f: toggle full screen, spacebar: random z-value in meshvertices, w: draw wireframe or point cloud \np: use PerlinNoise for z-value in meshvertices\nUp-key Down-key: increase/decrease PerlinNoise input range \nRight-key Left-key: increase/decrease amplitude of Perlin Noise distortion \nclick and drag in window to move camera";
    ofDrawBitmapString(msg, 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch(key) { // use a switch statement to evaluate which key is pressed
        case 'f':
            ofToggleFullscreen();
            break;
            
        case ' ':
            b_messyMesh = !b_messyMesh;
            break;
            
        case 'w':
            b_drawWireFrame = !b_drawWireFrame;
            break;
            
        case 'p':
            b_perlinMesh = !b_perlinMesh;
            break;
            
        case OF_KEY_UP: // increase or decrease the range/detail of the perlinNoise value
            perlinRange +=0.1;
            break;
            
        case OF_KEY_DOWN: // increase or decrease the range/detail of the perlinNoise value
            if (perlinRange > 0.1){
                perlinRange -=0.1;
            }
            break;
            
        case OF_KEY_RIGHT: // increase or decrease the height of the perlinNoise distortion
            perlinHeight +=0.1;
            break;
            
        case OF_KEY_LEFT: // increase or decrease the height of the perlinNoise distortion
            if (perlinHeight > 0.1){
                perlinHeight -=0.1;
            }
            break;
            
        case 'm':
            b_marchMesh = !b_marchMesh;
            break;
            
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}
