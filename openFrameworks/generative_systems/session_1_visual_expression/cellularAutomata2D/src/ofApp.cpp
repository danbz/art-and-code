/*
 Project Title: CellularAutomata 2D
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 with acknowledgement to Reas and Fry 'Processing, A programming handbook for visual designers and artists'
 */

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(8);
    float density = 0.3 * ofGetWidth() * ofGetHeight();
    int empty = 0;
    
    // resize the vectors to our width and height
    grid.resize(ofGetWidth(),vector<int>(ofGetHeight()));
    futureGrid.resize(ofGetWidth(),vector<int>(ofGetHeight()));
    
    // populate the vectors with empty cells
    for (int x =0; x<ofGetWidth(); x++){
        for (int y=0; y<ofGetHeight(); y++){
            grid[x][y]=empty;
            futureGrid[x][y]=empty;
        }
    }
    
    for (int i=0; i< density; i++){ // populate some random cells in our grid
        grid[ ofRandom(ofGetWidth()) ][ ofRandom(ofGetHeight()) ] = 1;
    }
    
    ofSetBackgroundColor(0, 0, 0);
    on = (255);
    off = (0);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (int x = 1; x < ofGetWidth() -1; x++){
        for (int y = 1; y < ofGetHeight() -1; y++){
            // check number of neightbours in adjacent cells
            int nb = neighbors(x,y);
            if ((grid[x][y] == 1) && (nb <2)){
                futureGrid[x][y] = 0; // isolation death
                ofSetColor(off);
                ofDrawCircle(x, y, 1);
                
            } else if ((grid[x][y] == 1) && (nb >3)){
                futureGrid[x][y] = 0; // overpopulation death
                ofSetColor(off);
                ofDrawCircle(x, y, 1);

            } else if ((grid[x][y] == 0) && (nb ==3)){
                futureGrid[x][y] = 1; // birth
                ofSetColor(on);
                ofDrawCircle(x, y, 1);
                
            } else {
                futureGrid[x][y] = grid[x][y]; // cell survives
                
            }
        }
    }
    // swap current and future grids
    vector<vector<int>> temp = grid;
    grid = futureGrid;
    futureGrid = temp;
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    // drag to add new cells into the grid
    grid[mouseX][mouseY]=1;
    grid[mouseX-1][mouseY]=1;
    grid[mouseX+1][mouseY]=1;
    grid[mouseX][mouseY-1]=1;
    grid[mouseX][mouseY+1]=1;
}

//--------------------------------------------------------------
int ofApp::neighbors(int x, int y){
    // check count for each neighbor cell in the grid
    return
    grid[x][y-1] + // north
    grid[x+1][y-1] + // northeast
    grid[x+1][y] + // east
    grid[x+1][y+1] + //southeast
    grid[x][y+1] + // south
    grid[x-1][y+1] + // southwest
    grid[x-1][y] + // west
    grid[x-1][y-1]; // northwest
}
