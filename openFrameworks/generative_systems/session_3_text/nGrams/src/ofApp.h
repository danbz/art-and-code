/*
 Project Title: generating nGrams for markov text
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */
#pragma once

#include "ofMain.h"
#include "ofxTextSuite.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    
    bool does_exist(const vector< vector<string> >&  v, string item);
    void makeText();
    bool loadTextFromFile();
    
    void prepareText();
    void createGrams();
    
    string sourceText, markovText;
    vector<string> allGrams;
    vector<vector<string>> uniqueGrams;
    int gramLength, numLetters;
    ofxTextBlock screenText;
};
