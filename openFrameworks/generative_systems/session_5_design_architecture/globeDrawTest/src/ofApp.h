
/*
 Project Title: Globe Draw
 Description: generate points on the surface of a sphere using cartesian co-ordinates, then generate  curve path between each point and draw in 3D
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#pragma once

#include "ofMain.h"
#include "ofxVectorGraphics.h"

ofVec3f sphericalToCartesian( float lat, float lon, float radius );

class ant {
public:
    ofPoint startPoint, endPoint, currentPoint, nextPoint;
    ofPath path;
    float numDrinks, length, currentLength, acceleration, angularAcceleration, amplitude;
    ofVec2f velocity;
    
    ant();
    ~ant();
    void update();
    ofVec2f getPosition();
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		
    ofSpherePrimitive globe;
    ofEasyCam   cam;
    float driftAmount;
    vector<ofPoint> geoPositions, cartPositions;
    ofxVectorGraphics vectorGraphics;
    ofPath geoPath;
    ofLight light;
    // ant ant;
    vector<ant> ants;
};
