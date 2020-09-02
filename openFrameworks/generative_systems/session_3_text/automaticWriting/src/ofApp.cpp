/*
 Project Title: Automatic writing based on sentence structures
 Description: a very simple linguistic parsing tree example
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    numOfSentences = 20;
    screenText.init("frabk.ttf", 20);
    screenText.wrapTextX(ofGetWidth());
    
    // example lexicons of words
    determiners = {"a", "the", "every", "each"};
    nouns = {"bird", "cat", "moonlight", "love", "table", "chair", "hat", "plate", "pen", "ink", "apple", "sky", "cloud", "rainstorm", "sea fog", "urchin", "berry", "twig", "forest", "raft", "sun", "moon", "stars" , "bottle", "egg", "seahorse", "drunkenness", "gladness", "happiness"};
    adverbs ={"gently", "here", "now", "very", "fast", "slow", "high", "low", "easy", "hard"};
    verbs = {"hear", "become", "happen", "run", "hit", "eat", "sit", "smile", "laugh" };
    adjectives = {"fast", "slow", "high", "low", "easy", "hard", "sweet", "red", "blue", "technical" };
    conjunctions = {"and", "but", "if", "then", "because"};
    pronouns = {"i", "you", "he", "she", "it", "we", "they", "us", "them", "this" };
    prepositions = {"on", "at", "in", "to", "after", "for"};
    
    textParts.push_back(determiners); // 0
    textParts.push_back(nouns); // 1
    textParts.push_back(verbs); // 2
    textParts.push_back(prepositions); //3
    textParts.push_back(adjectives); // 4
    textParts.push_back(conjunctions); // 5
    textParts.push_back(pronouns); // 6
    textParts.push_back(adverbs);  // 7
    
    // example sentence structures
    vector<int> sentence1 = {0,1,2,3,0,1};
    textStructure.push_back( sentence1);
    vector<int> sentence2 = {0,1,2,3,0,1,5,0,1,2,3,0,1};
    textStructure.push_back( sentence2);
    vector<int> sentence3 = {6, 2, 0, 1};
    textStructure.push_back( sentence3);
    vector<int> sentence4 = {6, 2, 0, 1, 5, 6, 2, 6, 7, 0, 1};
    textStructure.push_back( sentence4);
    vector<int> sentence5 = {6, 2, 0, 1, 5, 6, 2, 0, 1};
    textStructure.push_back( sentence5);
    
    generatedText = "press space to generate text";
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    screenText.setText( generatedText);
    screenText.wrapTextX(ofGetWidth()-10);
    screenText.draw(10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            makeWriting();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::makeWriting(){
    string writing;
    vector<int> sentence;
    for (int j = 0; j < numOfSentences; j++){
        sentence.clear();
        sentence = textStructure[ ofRandom(textStructure.size())];
        for (int i = 0 ; i< sentence.size(); i ++){
            
            writing += " ";
            int numWords =textParts[ sentence[i] ].size();
            writing += textParts[ sentence[i] ][ ofRandom( numWords)];
        }
        writing += ". ";
    }
    generatedText = writing;
    cout << writing << endl;
}


