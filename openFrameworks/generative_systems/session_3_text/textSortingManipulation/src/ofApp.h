/*
 Project Title:
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

/* Refer to the README.md in the example's root folder for more information on usage */

#pragma once

#include "ofMain.h"

// ---------------------------------------------
class LyricWord {
public:
    string  word;
    int     occurrences;
    
};


// ---------------------------------------------
class ofApp : public ofBaseApp {
    
public:
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
    static bool sortOnABC(const LyricWord &a, const LyricWord &b);
    static bool sortOnOccurrences(const LyricWord &a, const LyricWord &b);
    static bool sortOnLength(const LyricWord &a, const LyricWord &b);    
    
    ofTrueTypeFont      font;
    string              sortTypeInfo;
    vector <LyricWord>  words;
    
    void setupWords(string content);
    void processOpenFileSelection(ofFileDialogResult openFileResult);
    string originalFileExtension;
    
    void urlResponse(ofHttpResponse & response);
    bool loading;
};
