/*
 Project Title: Automatic writing based on sentence structures
 Description: a very simple linguistic parsing tree example
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#pragma once

#include "ofMain.h"
#include "ofxTextSuite.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
	
    
		
    void makeWriting();
    
    vector<string> nouns, verbs, adverbs, determiners, adjectives, pronouns, conjunctions, prepositions ;
    string generatedText;
    vector< vector <int>> textStructure;
    vector< vector <string>> textParts;
    int wordCount, numOfSentences;
    
    ofxTextBlock screenText;
};
