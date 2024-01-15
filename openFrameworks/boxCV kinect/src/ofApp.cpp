#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
   //ofDisableAntiAliasing();
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofSetVerticalSync(true);
    
    // Box2d initialisation
    box2d.init();
    box2d.enableEvents();   // <-- turn on the event listener
    box2d.setGravity(0, 5);
    box2d.createGround();
    box2d.setFPS(60.0);
    box2d.registerGrabbing();
    
    // register the box2D listener so that we get the events
    ofAddListener(box2d.contactStartEvents, this, &ofApp::contactStart);
    ofAddListener(box2d.contactEndEvents, this, &ofApp::contactEnd);

    // load the sfx soundfile
    for (int i=0; i<N_SOUNDS; i++) {
        sound[i].load("sfx/"+ofToString(i)+".mp3");
        sound[i].setMultiPlay(true);
        sound[i].setLoop(false);
    }
    
    // load the lines we saved as a text file...
    ifstream f;
    f.open(ofToDataPath("lines.txt").c_str());
    vector <string> strLines;
    while (!f.eof()) {
        string ptStr;
        getline(f, ptStr);
        strLines.push_back(ptStr);
    }
    f.close();
    
    for (int i=0; i<strLines.size(); i++) {
        vector <string> pts = ofSplitString(strLines[i], ",");
        if(pts.size() > 0) {
            auto edge = make_shared<ofxBox2dEdge>();
            for (int j=0; j<pts.size(); j+=2) {
                if(pts[j].size() > 0) {
                    float x = ofToFloat(pts[j]);
                    float y = ofToFloat(pts[j+1]);
                    edge->addVertex(x, y);
                }
            }
            edge->create(box2d.getWorld());
            edges.push_back(edge);
        }
    }
 
    ofSetLogLevel(OF_LOG_VERBOSE);
    // enable depth->video image calibration
    kinect.setRegistration(true);
    kinect.init();
    //kinect.init(true); // shows infrared instead of RGB video image
    //kinect.init(false, false); // disable video image (faster fps)
    
    kinect.open();        // opens first available kinect
    //kinect.open(1);    // open a kinect by id, starting with 0 (sorted by serial # lexicographically))
    //kinect.open("A00362A08602047A");    // open a kinect using it's unique serial #
    
    // print the intrinsic IR sensor values
    if(kinect.isConnected()) {
        ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
        ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
        ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
        ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
    }
    
#ifdef USE_TWO_KINECTS
    kinect2.init();
    kinect2.open();
#endif
    // set up CV image buffers we are going to use
    colorImg.allocate(kinect.width, kinect.height);
    grayImage.allocate(kinect.width, kinect.height);
    grayThreshNear.allocate(kinect.width, kinect.height);
    grayThreshFar.allocate(kinect.width, kinect.height);
     // set up initial values for kinect sensor
    nearThreshold = 230;
    farThreshold = 70;
    bThreshWithOpenCV = true;
    
    ofSetFrameRate(60);
    
    // zero the tilt on startup
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
    // start the display from the front showing debug vews from kinect sensor
    bDrawPointCloud = false;
}

//--------------------------------------------------------------
void ofApp::update() {
    // add some circles every so often
    if((int)ofRandom(0, 20) == 0) {
        auto c = make_shared<ofxBox2dCircle>();
        c->setPhysics(0.2, 0.2, 0.002);
       // c->setup(box2d.getWorld(), ofRandom(20, 50), -20, ofRandom(3, 10));
        c->setup(box2d.getWorld(), ofRandom(20, 400), -20, ofRandom(3, 20)); // create new particle with size, start position
        c->setVelocity(0, 15); // drop them down
        c->setData(new SoundData());
        auto * sd = (SoundData*)c->getData();
        sd->soundID = ofRandom(0, N_SOUNDS);
        sd->bHit    = false;
        circles.push_back(c);
    }
    box2d.update();
    kinect.update();
    
    // there is a new frame and we are connected to a kinect sensor
    if(kinect.isFrameNew()) {
        // load grayscale depth image from the kinect source
        grayImage.setFromPixels(kinect.getDepthPixels());
        // we do two thresholds - one for the far plane and one for the near plane
        // we then do a cvAnd to get the pixels which are a union of the two thresholds
        if(bThreshWithOpenCV) {
            grayThreshNear = grayImage;
            grayThreshFar = grayImage;
            grayThreshNear.threshold(nearThreshold, true);
            grayThreshFar.threshold(farThreshold);
            cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
        } else {
            // or we do it ourselves - show people how they can work with the pixels
            ofPixels & pix = grayImage.getPixels();
            int numPixels = pix.size();
            for(int i = 0; i < numPixels; i++) {
                if(pix[i] < nearThreshold && pix[i] > farThreshold) {
                    pix[i] = 255;
                } else {
                    pix[i] = 0;
                }
            }
        }
        // update the cv images
        grayImage.flagImageChanged();
        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
    }
    if(b_live) {
        faceToLine();
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    for (auto &circle : circles) { // draw all the box2D circles that are on the screen
        ofFill();
        ofSetHexColor(0xc0dd3b);
        SoundData * data = (SoundData*)circle->getData();
        circle->draw();
    }
    
    ofSetHexColor(0x444342); // draw the lines that we know of
    ofSetLineWidth(2);
    ofNoFill();
    for (auto &line : lines) {
        line.draw();
    }
    for (auto & edge : edges) {
        edge->draw();
    }
    
    if(bDrawPointCloud) { // if we are in debug point cloud mode then draw the point cloud
        easyCam.begin();
        drawPointCloud();
        easyCam.end();
    } else if (!b_live){ // else draw the debug views from the kinect sensor
        // draw from the live kinect
        kinect.drawDepth(420, 10, 400, 300);
       // kinect.draw(420, 10, 400, 300);
        grayImage.draw(10, 320, 400, 300); // and the threshholded view from openCV
        contourFinder.draw(10, 10, 400, 300); // and draw the contours over it
        
#ifdef USE_TWO_KINECTS
        kinect2.draw(420, 320, 400, 300);
#endif
    }
    
    // draw instructions on screen
    ofSetColor(0);
    stringstream reportStream;
        
    if(kinect.hasAccelControl()) {
        reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
        << ofToString(kinect.getMksAccel().y, 2) << " / "
        << ofToString(kinect.getMksAccel().z, 2) << endl;
    } else {
        reportStream << "Note: this is a newer Xbox Kinect or Kinect For Windows device," << endl
        << "motor / led / accel controls are not currently supported" << endl << endl;
    }
    
    reportStream << "press p to switch between images and point cloud, rotate the point cloud with the mouse" << endl
    << "using opencv threshold = " << bThreshWithOpenCV <<" (press spacebar)" << endl
    << "set near threshold " << nearThreshold << " (press: + -)" << endl
    << "set far threshold " << farThreshold << " (press: < >) num blobs found " << contourFinder.nBlobs
    << ", fps: " << ofGetFrameRate() << endl
    << "press c to close the connection and o to open it again, connection is: " << kinect.isConnected() << endl;

    if(kinect.hasCamTiltControl()) {
        reportStream << "press UP and DOWN to change the tilt angle: " << angle << " degrees" << endl
        << "press 1-5 & 0 to change the led mode" << endl;
    }
    
    ofDrawBitmapString(reportStream.str(), 20, 652);
    stringstream reportStr;
    
    string info = "Draw a shape with the mouse\n";
    info += "Press 1 to add some circles, ";
    info += "c to clear everything, ";
    info += "g to grab face contours \n" ;
    info += "l to run live contours, " ;
    info +="f to toggle fullscreen \n" ;
    info += "bg subtraction and blob detection \n";
    info += "press ' ' to capture bg \n";
    info += "num blobs found " + ofToString( contourFinder.nBlobs) + ", fps: " + ofToString( ofGetFrameRate());
    ofDrawBitmapString(info, 10, 15);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    
    /*
     // want to save out some line...
     if(key == ' ') {
     ofstream f;
     f.clear();
     f.open(ofToDataPath("lines.txt").c_str());
     for (int i=0; i<lines.size(); i++) {
     for (int j=0; j<lines[i].size(); j++) {
     float x = lines[i][j].x;
     float y = lines[i][j].y;
     f << x << "," << y << ",";
     }
     f << "\n";
     }
     f.close();lines.clear();
     }*/
    
    auto c = make_shared<ofxBox2dCircle>();
    
    switch (key){
        case 'c':
            lines.clear();
            edges.clear();
            break;
            
        case '1':
            // auto c = make_shared<ofxBox2dCircle>();
            c->setPhysics(1, 0.5, 0.5);
            c->setup(box2d.getWorld(), mouseX, mouseY, 10);
            circles.push_back(c);
            break;
            
        case 'f':
            ofToggleFullscreen();
            break;
            
        case 'l':
            b_live=!b_live;
            break;
            
        case 'g':
            faceToLine();
            break;
            
            case ' ':
            bThreshWithOpenCV = !bThreshWithOpenCV;
            break;
            
        case'p':
            bDrawPointCloud = !bDrawPointCloud;
            break;
            
        case '>':
        case '.':
            farThreshold ++;
            if (farThreshold > 255) farThreshold = 255;
            break;
            
        case '<':
        case ',':
            farThreshold --;
            if (farThreshold < 0) farThreshold = 0;
            break;
            
        case '+':
        case '=':
            nearThreshold ++;
            if (nearThreshold > 255) nearThreshold = 255;
            break;
            
        case '-':
            nearThreshold --;
            if (nearThreshold < 0) nearThreshold = 0;
            break;
            
        case 'w':
            kinect.enableDepthNearValueWhite(!kinect.isDepthNearValueWhite());
            break;
            
        case 'o':
            kinect.setCameraTiltAngle(angle); // go back to prev tilt
            kinect.open();
            break;
            
//        case 'c':
//            kinect.setCameraTiltAngle(0); // zero the tilt
//            kinect.close();
//            break;
//            
//        case '1':
//            kinect.setLed(ofxKinect::LED_GREEN);
//            break;
//            
        case '2':
            kinect.setLed(ofxKinect::LED_YELLOW);
            break;
            
        case '3':
            kinect.setLed(ofxKinect::LED_RED);
            break;
            
        case '4':
            kinect.setLed(ofxKinect::LED_BLINK_GREEN);
            break;
            
        case '5':
            kinect.setLed(ofxKinect::LED_BLINK_YELLOW_RED);
            break;
            
        case '0':
            kinect.setLed(ofxKinect::LED_OFF);
            break;
            
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;

        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    lines.back().addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
    lines.push_back(ofPolyline());
    lines.back().addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
    auto edge = make_shared<ofxBox2dEdge>();
    lines.back().simplify();
    for (int i=0; i<lines.back().size(); i++) {
        edge->addVertex(lines.back()[i]);
    }
    // edge->setPhysics(1, .2, 1);  // uncomment this to see it fall!
    edge->create(box2d.getWorld());
    edges.push_back(edge);
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
}
//--------------------------------------------------------------

void ofApp::faceToLine(){
    lines.clear();
    edges.clear();
    
    for (int i = 0; i < contourFinder.nBlobs; i++){
        lines.push_back(ofPolyline());
        //  contourFinder.blobs[i].draw(20,20);
        
        for (int p = 0; p < contourFinder.blobs[i].nPts; p++ ){
            lines.back().addVertex(    contourFinder.blobs[i].pts[p]);
        }
        auto edge = make_shared<ofxBox2dEdge>();
        lines.back().simplify();
        for (int i=0; i<lines.back().size(); i++) {
            edge->addVertex(lines.back()[i]);
        }
        edge->create(box2d.getWorld());
        edges.push_back(edge);
        // lines.push_back(ofPolyline());
    }
}
//--------------------------------------------------------------

void ofApp::drawPointCloud() {
    int w = 640;
    int h = 480;
    ofMesh mesh;
    mesh.setMode(OF_PRIMITIVE_POINTS);
    int step = 2;
    for(int y = 0; y < h; y += step) {
        for(int x = 0; x < w; x += step) {
            if(kinect.getDistanceAt(x, y) > 0) {
                mesh.addColor(kinect.getColorAt(x,y));
                mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
            }
        }
    }
    glPointSize(3);
    ofPushMatrix();
    // the projected points are 'upside down' and 'backwards'
    ofScale(1, -1, -1);
    ofTranslate(0, 0, -1000); // center the points a bit
    ofEnableDepthTest();
    mesh.drawVertices();
    ofDisableDepthTest();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
    
#ifdef USE_TWO_KINECTS
    kinect2.close();
#endif
}

//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        // if we collide with the ground we do not
        // want to play a sound. this is how you do that
        if(e.a->GetType() == b2Shape::e_circle && e.b->GetType() == b2Shape::e_circle) {
            SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
            SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
            if(aData) {
                aData->bHit = true;
                sound[aData->soundID].play();
            }
            cout << "hit" << endl;
            if(bData) {
                bData->bHit = true;
                sound[bData->soundID].play();
            }
     }
    }
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
    if(e.a != NULL && e.b != NULL) {
        SoundData * aData = (SoundData*)e.a->GetBody()->GetUserData();
        SoundData * bData = (SoundData*)e.b->GetBody()->GetUserData();
        if(aData) {
            aData->bHit = false;
        }
        
        if(bData) {
            bData->bHit = false;
        }
    }
}
