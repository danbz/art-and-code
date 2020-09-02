#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    // size(900,900,P3D);
    //  size(dimx,dimy,P3D);
      ofBackground(255);
      takecolor("pollockShimmering.gif");
      
      cgrid = new int[dimx*dimy];
      cracks = new Crack[maxnum];
    
      begin();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // crack all cracks
    for (int n=0;n<num;n++) {
      cracks[n].move();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}



void Crack::makeCrack() {
  if (num<maxnum) {
    // make a new crack instance
    cracks[num] = new Crack();
    num++;
  }
}


void ofApp::begin() {
  // erase crack grid
  for (int y=0;y<dimy;y++) {
    for (int x=0;x<dimx;x++) {
      cgrid[y*dimx+x] = 10001;
    }
  }
  // make random crack seeds
  for (int k=0;k<16;k++) {
    int i = int(ofRandom(dimx*dimy-1));
    cgrid[i]=int(ofRandom(360));
  }

  // make just three cracks
  num=0;
  for (int k=0;k<3;k++) {
    makeCrack();
  }
  ofBackground(255);
}


// COLOR METHODS ----------------------------------------------------------------

ofColor SandPainter::somecolor() {
  // pick some random good color
  return goodcolor[int(ofRandom(numpal))];
}

void ofApp::takecolor(string fn) {
  ofImage b;
  b.load(fn);
  image(b,0,0);

  for (int x=0;x<b.getWidth();x++){
    for (int y=0;y<b.getHeight();y++) {
      ofColor c = get(x,y);
      bool exists = false;
      for (int n=0;n<numpal;n++) {
        if (c==goodcolor[n]) {
          exists = true;
          break;
        }
      }
      if (!exists) {
        // add color to pal
        if (numpal<maxpal) {
          goodcolor[numpal] = c;
          numpal++;
        }
      }
    }
  }
}
