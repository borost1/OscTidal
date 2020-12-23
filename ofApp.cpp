#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	osc.setup(PORT);
	grid.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	while (osc.hasWaitingMessages()) {
		ofxOscMessage m;
		osc.getNextMessage(m);
		if (m.getAddress() == "/play2") {
			for (int i = 0; i < m.getNumArgs(); i += 2) {
				if (m.getArgAsString(i) == "s") {
					std::cout << "arg: " << m.getArgAsString(i) << ": " << m.getArgAsString(i + 1) << "\n";
				}
				
			}
		}
	}
	grid.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(0);
	ofSetColor(255);
	ofFill();
	grid.draw();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
