/*
 Project Title: Cave Designer
 Description: procedural cave design system
 adapted from python example from http://pixelenvy.ca/wa/ca_cave.html
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 */

#pragma once

#include "ofMain.h"

// A simple disjoint set ADT which uses path compression on finds
// to speed things up
//
class disJointSet {
public:
    
    int size = 0;
    vector< int > items;
    void disJoinSet();
    
    void unionMe( int root1, int root2){
        if (items[root2] < items[root1]){
            items[root1] = root2;
        } else {
            if (items[root1] == items[root2]){
                items[root1] -= 1;
            }
        }
        items[root2] = root1;
    };
    
    void find( int x){
        while (items[x] > 0){
            x = items[x];
            // except KeyError;
            items[x] = -1;
            return x;
        }
    };
    
    void split_sets(){
        vector<int> sets;
        int j = 0;
        for (j in items.keys()){
            root = find(j);
            
            if (root > 0){
                if (sets.has_key(root)){
                    list = sets[root];
                    list.append(j);
                    sets[root] = list;
                } else {
                    sets[root] = [j];
                }
            }
        }
        return sets;
    };
    
    void dump(){
        print __items;
    };
};
//


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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
};
