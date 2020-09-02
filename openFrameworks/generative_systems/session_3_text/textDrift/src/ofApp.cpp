/*
 Project Title:
 Description: playing with truetype font outlines
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    drift = 10;
    ofNoFill();
    ofSetBackgroundColor(255);
    ofSetColor(0);
    ofSetFrameRate(10);
    /* Parameters for font load:
     filename The name of the font file to load.
     fontsize The size in pixels to load the font.
     _bAntiAliased true if the font should be anti-aliased.
     _bFullCharacterSet true if the full character set should be cached.
     makeControus true if the vector contours should be cached.
     simplifyAmt the amount to simplify the vector contours. Larger number means more simplified.
     dpi the dots per inch used to specify rendering size.*/
    
    font.load("serif", 200, true, true, true);
    myText = "hello!";
    
    // load the string into a vector of letters as points
    myPath = font.getStringAsPoints(myText);
    // set the colour and size of each letter in the vector of letters
    for (int i=0; i < myPath.size(); i++){
        myPath[i].setStrokeColor( ofColor(255, 0,  0) );
        myPath[i].setStrokeWidth(2);
        myPath[i].setFilled(false);
        myPath[i].setMode(ofPath::POLYLINES);
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw each letter in the vector
    for (int i=0; i<myPath.size(); i++){
        myPath[i].draw(10 + i * font.getSize(), 200);
    }
    
    //loop through all the points in all the lines in each letter
    for (int i=0; i<myPath.size(); i++){
        ofPushMatrix();
        ofTranslate(10 + i * font.getSize(), 400, 0);
        ofBeginShape(); // this allows us to add vertices and make shapes dynamically
        for (int j = 0; j < myPath[i].getOutline().size(); j++){
            for(int k = 0; k < (int)myPath[i].getOutline()[j].size(); k++){
                
                // get each point of each path of each letter and add a random amount to the x and 7 position and make it a vertext in a new line we are drawing
                ofVertex(myPath[i].getOutline()[j].getVertices()[k].x + ofRandom(-drift,drift), myPath[i].getOutline()[j].getVertices()[k].y + ofRandom(-drift,drift));
               
                // also display the points in each path in each letter as blue circles.
                ofPoint newPoint;
                newPoint.x = myPath[i].getOutline()[j].getVertices()[k].x;
                newPoint.y = myPath[i].getOutline()[j].getVertices()[k].y;
                
                ofPushStyle(); // use push and pop style to preserve  and reset whatever style is being used
                ofSetColor(0, 0, 255); // temporarily change to draw in blue
                ofDrawCircle(newPoint,  3); // draw a dot
                ofPopStyle(); // pop back whatever the style was previously
            }
        }
        ofEndShape( true );
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}
