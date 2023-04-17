#pragma once

#include "ofMain.h"
#include "ofxCameraSaveLoad.h"

class circularMeshBuffer{
    // adapted from code by Gil_Fuser https://forum.openframeworks.cc/t/error-regarding-unknown-of-pixel-format/27191

public:
    circularMeshBuffer(){
        currentIndex = 0;
    }
    void setup(int numBoxes){
        boxes.resize(numBoxes);
        currentIndex = numBoxes -1;
    }
    void pushMesh(ofMesh& box){
        currentIndex--;
        if (currentIndex < 0) {
            currentIndex = boxes.size() -1;
        }
        boxes[currentIndex] = box;
    }
    ofMesh& getDelayedMesh(size_t delay){
        if(delay < boxes.size()){
            return boxes[ofWrap(delay + currentIndex, 0, boxes.size())];
        }
        return boxes[0];
    }
    
    int getCurrentIndex() {
        return currentIndex;
    }
    
protected:
    int currentIndex;
    deque<ofMesh> boxes;
};

class circularIntBuffer{
    // adapted from code by Gil_Fuser https://forum.openframeworks.cc/t/error-regarding-unknown-of-pixel-format/27191
public:
    circularIntBuffer(){
        currentIndex = 0;
    }
    void setup(int numBoxes){
        boxes.resize(numBoxes);
        currentIndex = numBoxes -1;
    }
    void pushMesh(float& box){
        currentIndex--;
        if (currentIndex < 0) {
            currentIndex = boxes.size() -1;
        }
        boxes[currentIndex] = box;
    }
    float& getDelayedMesh(size_t delay){
        if(delay < boxes.size()){
            return boxes[ofWrap(delay + currentIndex, 0, boxes.size())];
        }
        return boxes[0];
    }
    
    int getCurrentIndex() {
        return currentIndex;
    }
    
protected:
    int currentIndex;
    deque<float> boxes;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();    

		void keyPressed(int key);
    
    int scapeWidth, scapeDepth, boxSize, maxHeight;
   // circularMeshBuffer boxes;
    circularIntBuffer boxes;
    ofEasyCam cam;
    ofLight light;
    // ofBoxPrimitive box;
    bool b_rotate, b_march;
};
