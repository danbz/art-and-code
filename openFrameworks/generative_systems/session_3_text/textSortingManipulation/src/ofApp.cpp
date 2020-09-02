/*
Project Title:
Description:
©Daniel Buzzo 2020
dan@buzzo.com
http://buzzo.com
https://github.com/danbz
*/


#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    
    ofTrueTypeFont::setGlobalDpi(96);
    
    // load the font
    font.load("sans-serif", 18);
    // font.load("monospace", 18);
    // font.load("serif", 18); // use different typefaces
    
    sortTypeInfo = "no sort";
    
    // load the txt document into a ofBuffer
    ofBuffer buffer = ofBufferFromFile("cyberspace.txt");
    string   content = buffer.getText();
    setupWords(content);
    
    // set remote loading from web URL parameters
    loading=false;
    ofRegisterURLNotification(this);
    
    ofSetBackgroundColor(255);
    ofSetColor(0); // set  the words to black
    ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {
    
}

//--------------------------------------------------------------
void ofApp::draw() {
    int offset = 10;
    int startHeight = 50;
    int wordMargin = 10;
    int lineHeight = 20;
    int wordX, wordY = 10;
    int lineNum = 0;
    for(unsigned int i=0; i<words.size(); i++) {
        ofRectangle rect = font.getStringBoundingBox(words[i].word, 0,0);
        
        wordX = offset % ofGetWidth() - wordMargin ;
        wordY = offset / ofGetWidth() * font.getLineHeight() + 20;
        lineHeight = startHeight -  offset / ofGetWidth();
        font.setLineHeight(lineHeight);
//        ofPushMatrix(); // scale each word depending upon the order we see it
//        ofTranslate(wordX, wordY );
//        ofScale(lineHeight/20, lineHeight/20);
        
         font.drawString(words[i].word, wordX , wordY );
         ofDrawRectangle(rect.x + wordX - wordMargin/2 , rect.y + wordY, rect.width + wordMargin, lineHeight );

//        font.drawString(words[i].word, 0 , 0 );
//        ofDrawRectangle(rect.x  - wordMargin/2 , rect.y , rect.width + wordMargin, lineHeight );
        
        ofPopMatrix();
        offset += font.stringWidth( words[i].word ) + wordMargin ;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
    // sort raw
    if(key == '1')     {
        sortTypeInfo = "no sort";
         setup();
    }
    
    // sort alphabetically
    if(key == '2') {
        sortTypeInfo = "sorting alphabetically";
        ofSort(words, ofApp::sortOnABC);
    }
    
    // sort by length of word
    if(key == '3')     {
        sortTypeInfo = "sorting on word length";
        ofSort(words, ofApp::sortOnLength);
    }
    
    // sort by length of word
    if(key == '4')     {
        sortTypeInfo = "sorting on word occurrences";
        ofSort(words, ofApp::sortOnOccurrences);
    }
    
    if (key == 'l'){
        //Open the Open File Dialog to load text file
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a txt file");
        //Check if the user opened a file
        if (openFileResult.bSuccess){
            ofLogVerbose("User selected a file");
            //We have a file, check it and process it
            processOpenFileSelection(openFileResult);
        }else {
            ofLogVerbose("User hit cancel");
        }
    }
    
    if (key == 'w'){
        ofHttpResponse loadResult = ofLoadURL("http://www.google.com/robots.txt");
        urlResponse(loadResult);
    }
    
    if (key == 'f'){
        ofToggleFullscreen();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased  (int key){
    
}

//--------------------------------------------------------------

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){
    
    ofLogVerbose("getName(): "  + openFileResult.getName());
    ofLogVerbose("getPath(): "  + openFileResult.getPath());
    ofFile file (openFileResult.getPath());
    
    if (file.exists()){
        ofLogVerbose("The file exists - now checking the type via file extension");
        string fileExtension = ofToUpper(file.getExtension());
        //We only want text
        if (fileExtension == "TXT") {
            // load the txt document into an ofBuffer
            ofBuffer buffer = ofBufferFromFile(file);
            string   content = buffer.getText();
            setupWords(content);
        }
    }
}
//--------------------------------------------------------------

void ofApp::setupWords(string content){
    // take our text and process into a vector of words
    words.clear();
    
    // take the content and split it up by spaces
    // we need to also turn new lines into spaces so we can seperate words on new lines as well
    ofStringReplace(content, "\r", " ");
    ofStringReplace(content, "\n", " ");
    vector <string> splitString = ofSplitString(content, " ", true, true);

    // copy over the words to our object
    for (unsigned int i=0; i<splitString.size(); i++) {
        LyricWord wrd;
        wrd.occurrences = 1;
        wrd.word = ofToLower( splitString[i] );
        words.push_back(wrd);
    }
    
    // clean up the words removing any characters that we do not want
    for (unsigned int i=0; i<words.size(); i++) {
        // run throught this ignore list and replace
        // that char with nothing
        char ignoreList[12] = {',', '.', '(', ')', '?', '!', '-', ':', '"', '\'', '\n', '\t'};
        for(int j=0; j<12; j++) {
            
            // make string from char
            string removeStr;
            removeStr += ignoreList[j];
            
            // remove and of the chars found
            ofStringReplace(words[i].word, removeStr, "");
        }
    }
    
    // count the amount of times that we see a word
    for (unsigned int i=0; i<words.size(); i++) {
        int c = 1;
        for (unsigned int j=0; j<words.size(); j++) {
            if(words[i].word == words[j].word) c ++;
        }
        words[i].occurrences = c;
    }
    
    // remove duplicates of the words
    vector<LyricWord>tempWord;
    for (unsigned int i=0; i<words.size(); i++) {
        bool bAdd = true;
        for(unsigned int j=0; j<tempWord.size(); j++) {
            if(words[i].word == tempWord[j].word) bAdd = false;
        }
        
        if(bAdd) {
            tempWord.push_back(words[i]);
        }
    }
    words = tempWord;
}

//--------------------------------------------------------------
void ofApp::urlResponse(ofHttpResponse & response){
    if(response.status==200 ){
        // if our web request works the set up the text returned
        string   content = response.data;
        setupWords(content);
        loading=false;
    }else{
        cout << response.status << " " << response.error << " for request " << response.request.name << endl;
        if(response.status!=-1) loading=false;
    }
}

// sort on abc's
//--------------------------------------------------------------
bool ofApp::sortOnABC(const LyricWord &a, const LyricWord &b) {
    return a.word < b.word;
}

// sort on word length
//--------------------------------------------------------------
bool ofApp::sortOnLength(const LyricWord &a, const LyricWord &b) {
    return (int)a.word.size() > (int)b.word.size();
}

// sort on occurrences
//--------------------------------------------------------------
bool ofApp::sortOnOccurrences(const LyricWord &a, const LyricWord &b) {
    return a.occurrences > b.occurrences;
}
