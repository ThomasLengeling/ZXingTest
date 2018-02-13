#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
  ofSetVerticalSync(true);
  cam.initGrabber(1280, 800);
  logo.loadImage("of.png");
}

//--------------------------------------------------------------
void ofApp::update() {
  cam.update();
  if (cam.isFrameNew()) {
    ofxZxing::Result curResult = ofxZxing::decode(cam.getPixelsRef(), true);
    float curTime = ofGetElapsedTimef();
    if (curResult.getFound()) { // only update if we found something, avoid
                                // flickering
      result = curResult;
      lastFound = curTime;
    } else if (curTime - lastFound >
               1) {       // if we haven't found anything after a second
      result = curResult; // then update anyway
    }
  }
}

//--------------------------------------------------------------
void ofApp::draw() {
  ofSetColor(255);
  if (result.getFound()) {
    cam.draw(0, 0);

    float rotation = result.getRotation();
    ofVec2f position = result.getScreenPosition();
    float size = result.getScreenSize() / logo.getWidth();

    ofPushMatrix();
    ofTranslate(position);
    ofRotate(rotation);
    ofScale(size, size, size);
    logo.draw(-logo.getWidth() / 2, -logo.getHeight() / 2);
    ofPopMatrix();

    result.draw();
  } else {
    cam.draw(0, 0);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {}
