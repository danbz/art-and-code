#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
//	ofSetupOpenGL(1280,960,OF_WINDOW);			// <-------- setup the GL context
//
//	// this kicks off the running of my app
//	// can be OF_WINDOW or OF_FULLSCREEN
//	// pass in width and height too:
//	ofRunApp(new ofApp());
//
      ofGLWindowSettings settings;
      settings.setGLVersion(3, 2); // try also 2, 1
//      settings.width = 1024;
//      settings.height = 768;
      settings.windowMode = OF_WINDOW;
      ofCreateWindow(settings);
      ofRunApp( new ofApp());

}
