/*
 Project Title: markovChainDrum
 Description: markov chain drum machine
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

// dependencies: ofxMarkovChain addon //

#pragma once

#include "ofMain.h"
#include "ofxMarkovChain.h"


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
	
    vector<ofSoundPlayer> samples;
    ofxMC::MarkovChain markov;
    int currentSound, playedListSize;
    vector<int> playedList;
};
