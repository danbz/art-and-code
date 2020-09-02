/*
 Project Title: generating nGrams for markov text
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#include "ofApp.h"

using namespace std;


//--------------------------------------------------------------
void ofApp::setup(){
    
    gramLength = 4; // how long ar ethe nGrams we will find
    numLetters = 600; // how much text to make when we make new markov text
    
    
    screenText.init("frabk.ttf", 20);
    screenText.wrapTextX(ofGetWidth());
    ofSetBackgroundColor(0);
    
    // sourceText = "I wandered lonely as a cloud That floats on high o'er vales and hills, When all at once I saw a crowd, A host, of golden daffodils; Beside the lake, beneath the trees, Fluttering and dancing in the breeze.";
    
    // A Declaration of the Independence of Cyberspace by John Perry Barlow Davos, Switzerland February 8, 1996
    sourceText = "Governments of the Industrial World, you weary giants of flesh and steel, I come from Cyberspace, the new home of Mind. On behalf of the future, I ask you of the past to leave us alone. You are not welcome among us. You have no sovereignty where we gather. We have no elected government, nor are we likely to have one, so I address you with no greater authority than that with which liberty itself always speaks. I declare the global social space we are building to be naturally independent of the tyrannies you seek to impose on us. You have no moral right to rule us nor do you possess any methods of enforcement we have true reason to fear. Governments derive their just powers from the consent of the governed. You have neither solicited nor received ours. We did not invite you. You do not know us, nor do you know our world. Cyberspace does not lie within your borders. Do not think that you can build it, as though it were a public construction project. You cannot. It is an act of nature and it grows itself through our collective actions. You have not engaged in our great and gathering conversation, nor did you create the wealth of our marketplaces. You do not know our culture, our ethics, or the unwritten codes that already provide our society more order than could be obtained by any of your impositions. You claim there are problems among us that you need to solve. You use this claim as an excuse to invade our precincts. Many of these problems don't exist. Where there are real conflicts, where there are wrongs, we will identify them and address them by our means. We are forming our own Social Contract. This governance will arise according to the conditions of our world, not yours. Our world is different. Cyberspace consists of transactions, relationships, and thought itself, arrayed like a standing wave in the web of our communications. Ours is a world that is both everywhere and nowhere, but it is not where bodies live. We are creating a world that all may enter without privilege or prejudice accorded by race, economic power, military force, or station of birth. We are creating a world where anyone, anywhere may express his or her beliefs, no matter how singular, without fear of being coerced into silence or conformity. Your legal concepts of property, expression, identity, movement, and context do not apply to us. They are all based on matter, and there is no matter here. Our identities have no bodies, so, unlike you, we cannot obtain order by physical coercion. We believe that from ethics, enlightened self-interest, and the commonweal, our governance will emerge. Our identities may be distributed across many of your jurisdictions. The only law that all our constituent cultures would generally recognize is the Golden Rule. We hope we will be able to build our particular solutions on that basis. But we cannot accept the solutions you are attempting to impose. In the United States, you have today created a law, the Telecommunications Reform Act, which repudiates your own Constitution and insults the dreams of Jefferson, Washington, Mill, Madison, DeToqueville, and Brandeis. These dreams must now be born anew in us. You are terrified of your own children, since they are natives in a world where you will always be immigrants. Because you fear them, you entrust your bureaucracies with the parental responsibilities you are too cowardly to confront yourselves. In our world, all the sentiments and expressions of humanity, from the debasing to the angelic, are parts of a seamless whole, the global conversation of bits. We cannot separate the air that chokes from the air upon which wings beat. In China, Germany, France, Russia, Singapore, Italy and the United States, you are trying to ward off the virus of liberty by erecting guard posts at the frontiers of Cyberspace. These may keep out the contagion for a small time, but they will not work in a world that will soon be blanketed in bit-bearing media. Your increasingly obsolete information industries would perpetuate themselves by proposing laws, in America and elsewhere, that claim to own speech itself throughout the world. These laws would declare ideas to be another industrial product, no more noble than pig iron. In our world, whatever the human mind may create can be reproduced and distributed infinitely at no cost. The global conveyance of thought no longer requires your factories to accomplish. These increasingly hostile and colonial measures place us in the same position as those previous lovers of freedom and self-determination who had to reject the authorities of distant, uninformed powers. We must declare our virtual selves immune to your sovereignty, even as we continue to consent to your rule over our bodies. We will spread ourselves across the Planet so that no one can arrest our thoughts. We will create a civilization of the Mind in Cyberspace. May it be more humane and fair than the world your governments have made before.";
    
    prepareText();
    createGrams();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);

    screenText.setText( markovText);
    screenText.wrapTextX(ofGetWidth()-10);
    screenText.draw(10, 20);
    
    ofSetColor(255, 100, 255);
    ofDrawBitmapString("press space ' ' to make new markovText, 'l' to load a .txt file \nsee console output for list of grams", 20,  ofGetHeight()-40);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            makeText();
            break;
            
        case 'l':
            loadTextFromFile();
            prepareText();
            createGrams();
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
bool ofApp::does_exist(const vector< vector<string> >&  v, string item){
    // find existence of a string in a 2D vector
    vector< vector<string> >::const_iterator row;
    for (row = v.begin(); row != v.end(); row++) {
        if(find(row->begin(), row->end(), item) != row->end() )
            return true;
    }
    return false;
}
//--------------------------------------------------------------

void ofApp::makeText(){
    string startText = uniqueGrams[ofRandom(uniqueGrams.size())][0];
    string nextLetter;
    // need to fix this as it crashes if it gets to a null gram at the end (eg breeze)
    for (int i=0; i<numLetters; i++){
        for (int j = 0; j < uniqueGrams.size(); j++){
           // if (startText.length()
            if (uniqueGrams[j][0] == startText.substr(i,gramLength)){
                nextLetter = uniqueGrams[j][ofRandom(uniqueGrams[j].size()-1 ) +1 ];
                // if (!nextLetter == "") {
                cout << "letter '" << nextLetter << "'" << endl;
//                } else {
//                    cout << "no ngram" << endl;
//                }
                startText+= nextLetter;
            }
        }
    }
    cout << startText << endl;
    markovText = startText;
}

//--------------------------------------------------------------
bool ofApp::loadTextFromFile(){
    ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a txt file"); //Open File Dialog
    if (openFileResult.bSuccess){ //Check if the user opened a file
        ofLogVerbose("User selected a file"); //We have a file, check it and process it
        ofLogVerbose("getName(): "  + openFileResult.getName());
        ofLogVerbose("getPath(): "  + openFileResult.getPath());
        ofFile file (openFileResult.getPath());
        if (file.exists()){
            ofLogVerbose("The file exists - now checking the type via file extension");
            string fileExtension = ofToUpper(file.getExtension());
            if (fileExtension == "TXT") {         //We only want text
                ofBuffer buffer = ofBufferFromFile(file); // load txt document into an ofBuffer
                sourceText = buffer.getText();
            }
        }
    }else {
        ofLogVerbose("User hit cancel");
    }
}

//--------------------------------------------------------------
void ofApp::prepareText(){
    markovText = "press space to markov this. " + sourceText;
    
    // force to lowercase
    std::transform(sourceText.begin(), sourceText.end(), sourceText.begin(), [](unsigned char c){ return std::tolower(c); });
    // remove punctuation
    for (int i = 0, len = sourceText.size(); i < len; i++)
    {
        // check whether parsing character is punctuation or not
        if (ispunct(sourceText[i]))
        {
            sourceText.erase(i--, 1);
            len = sourceText.size();
        }
    }
}
//--------------------------------------------------------------

void ofApp::createGrams(){
    // generate a vector of all grams
    allGrams.clear(); // clear the previous grams in case we are loading a new source textfile
    uniqueGrams.clear();
    
    for (int i = 0; i < sourceText.length()-gramLength +1; i++){
        string newGram = sourceText.substr(i, gramLength);
        allGrams.push_back(newGram);
    }
    
    // sort unique grams into new vector of grams
    vector<string> row;
    for (int i = 0; i < allGrams.size(); i++){
        row.clear();
        if ( !does_exist(uniqueGrams, allGrams[i])){
            // cout << "Item " << allGrams[i] << " is not a duplicate" << endl;
            row.push_back(allGrams[i]);
            uniqueGrams.push_back(row);
        }
    }
    
    // find all following letters to the grams
    for (int i = 0; i < uniqueGrams.size(); i ++){
        string gram = uniqueGrams[i][0];
        
        int pos = sourceText.find(gram);
        if (pos != sourceText.length() ){ // here?
            // uniqueGrams[i].push_back(sourceText.substr(pos + gramLength, 1));
            size_t pos = sourceText.find(gram);
            // Repeat till end is reached
            cout << gram << " gram: " ;
            while( pos != std::string::npos) {
                // Add position to the vector
                uniqueGrams[i].push_back(sourceText.substr(pos + gramLength, 1));
                cout << sourceText.substr(pos + gramLength, 1) ;
                
                // Get the next occurrence from the current position
                pos =sourceText.find(gram, pos + gram.size());
            }
            cout << endl;
        }
    }
}

