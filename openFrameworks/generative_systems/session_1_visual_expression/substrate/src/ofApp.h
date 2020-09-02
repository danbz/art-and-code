/*
 Project Title:
 Description:
 ©Daniel Buzzo 2020
 dan@buzzo.com
 http://buzzo.com
 https://github.com/danbz
 "A single line (known internally as a “crack”) begins drawing itself from some random point in some random direction. The line continues to draw itself until it either (a) hits the edge of the screen or (b) hits another line, at which point it stops and two more lines begin. The one simple rule used in the creation of new lines is that they begin at tangents to existing lines. This process is repeated until there are too many lines to keep track of or the program is stopped." Jared Tarbell
 
 http://www.complexification.net/gallery/machines/substrate/
 
 https://discourse.processing.org/t/trying-to-understand-the-substrate-algorithm/3031/6
 
 */
#pragma once

#include "ofMain.h"

// OBJECTS -------------------------------------------------------


 


class SandPainter {
public:
  ofColor c;
  float g;
    vector<ofColor>goodcolor;

  SandPainter() {
      ofColor c = somecolor();
      g = ofRandom(0.01,0.1);
  }
    ofColor somecolor();

  void render(float x, float y, float ox, float oy) {
      int sandRadius = 1;
    // modulate gain
    g+=ofRandom(-0.050,0.050);
    float maxg = 1.0;
    if (g<0) g=0;
    if (g>maxg) g=maxg;
    
    // calculate grains by distance
    //int grains = int(sqrt((ox-x)*(ox-x)+(oy-y)*(oy-y)));
    int grains = 64;

    // lay down grains of sand (transparent pixels)
    float w = g/(grains-1);
    for (int i=0;i<grains;i++) {
      float a = 0.1-i/(grains*10.0);
      //stroke(c.r ,c.g ,c.b, a*256);
        ofSetColor(c, a*256);
      ofDrawCircle(ox+(x-ox)*sin(sin(i*w)),oy+(y-oy)*sin(sin(i*w)), sandRadius);
    }
  }
};


class Crack {
    
    
    int dimx = 900;
     int dimy = 900;
     int num = 0;
     int maxnum = 200;
    

     // grid of cracks
     //int[] cgrid;
     vector<int> cgrid;

    // Crack[] cracks;
     vector<Crack> cracks;
public:
  float x, y;
  float t;    // direction of travel in degrees
  
  // sand painter
  SandPainter sp;
  
  Crack() {
    // find placement along existing crack
    findStart();
   // sp = new SandPainter();
      SandPainter sp;
  }
  void makeCrack();
    
  void findStart() {
    // pick random point
    int px=0;
    int py=0;
    
    // shift until crack is found
    bool found=false;
    int timeout = 0;
    while ((!found) || (timeout++>1000)) {
      px = int(ofRandom(dimx));
      py = int(ofRandom(dimy));
      if (cgrid[py*dimx+px]<10000) {
        found=true;
      }
    }
    
    if (found) {
      // start crack
      int a = cgrid[py*dimx+px];
      if (ofRandom(100)<50) {
        a-=90+int(ofRandom(-2,2.1));
      } else {
        a+=90+int(ofRandom(-2,2.1));
      }
      startCrack(px,py,a);
    } else {
      //println("timeout: "+timeout);
    }
  }
   
  void startCrack(int X, int Y, int T) {
    x=X;
    y=Y;
    t=T;//%360;
    x+=0.61*cos(t*PI/180);
    y+=0.61*sin(t*PI/180);
  }
             
  void move() {
    // continue cracking
    x+=0.42*cos(t*PI/180);
    y+=0.42*sin(t*PI/180);
    
    // bound check
    float z = 0.33;
    int cx = int(x+ofRandom(-z,z));  // add fuzz
    int cy = int(y+ofRandom(-z,z));
    
    // draw sand painter
    regionColor();
    
    // draw black crack
      int crackRadius = 1;
    stroke(0,85);
    ofDrawCircle(x+ofRandom(-z,z),y+ofRandom(-z,z), crackRadius);
    
    
    if ((cx>=0) && (cx<dimx) && (cy>=0) && (cy<dimy)) {
      // safe to check
      if ((cgrid[cy*dimx+cx]>10000) || (abs(cgrid[cy*dimx+cx]-t)<5)) {
        // continue cracking
        cgrid[cy*dimx+cx]=int(t);
      } else if (abs(cgrid[cy*dimx+cx]-t)>2) {
        // crack encountered (not self), stop cracking
        findStart();
        makeCrack();
      }
    } else {
      // out of bounds, stop cracking
      findStart();
      makeCrack();
    }
  }
  
  void regionColor() {
    // start checking one step away
    float rx=x;
    float ry=y;
    bool openspace=true;
    
    // find extents of open space
    while (openspace) {
      // move perpendicular to crack
      rx+=0.81*sin(t*PI/180);
      ry-=0.81*cos(t*PI/180);
      int cx = int(rx);
      int cy = int(ry);
      if ((cx>=0) && (cx<dimx) && (cy>=0) && (cy<dimy)) {
        // safe to check
        if (cgrid[cy*dimx+cx]>10000) {
          // space is open
        } else {
          openspace=false;
        }
      } else {
        openspace=false;
      }
    }
    // draw sand painter
    sp.render(rx,ry,x,y);
  }
};



class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
	
	
    // Substrate Watercolor
    // j.tarbell   June, 2004
    // Albuquerque, New Mexico
    // complexification.net

    // Processing 0085 Beta syntax update
    // j.tarbell   April, 2005

     
     // color parameters
     int maxpal = 512;
     int numpal = 0;
     
     //color[] goodcolor = new ofColor[maxpal];
     
     
     // sand painters
     //SandPainter[] sands;
     vector<SandPainter> sands;
     
     ///////
     
     void takecolor(string fn);
     void begin();
     
};
