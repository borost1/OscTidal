#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	guiEnabled = false;

	ofShowCursor();

	osc.setup(PORT);

	gridConfigButton.addListener(this, &ofApp::gridConfigButtonPressed);

	gui.setup();
	
	gui.add(uiPosition.set("position", ofVec3f(600, 600, 600), ofVec3f(-3000, -3000, -3000), ofVec3f(3000, 3000, 3000)));
	gui.add(gridSize.set("gridSize", 64,10,256));
	gui.add(gridDimension.set("gridDimension", 1000, 100, 4000));
	gui.add(gridConfigButton.setup("apply"));


	for (int i = 0; i < 3; i++) {
		Grid grid;
		grid.setup(gridSize, gridDimension);
		grids.push_back(grid);
	}

	manager.grids = &grids;
	
	post.init(ofGetWidth(), ofGetHeight());
	
	post.createPass<FxaaPass>()->setEnabled(false);
	post.createPass<BloomPass>()->setEnabled(false);
	post.createPass<DofPass>()->setEnabled(false);
	post.createPass<RGBShiftPass>()->setEnabled(false);	
	post.createPass<ToonPass>()->setEnabled(false);
	post.createPass<PixelatePass>()->setEnabled(false);
	post.createPass<EdgePass>()->setEnabled(false);
	post.createPass<VerticalTiltShifPass>()->setEnabled(false);
	post.createPass<GodRaysPass>()->setEnabled(false);

	cam.setPosition(1300, 1300, 1300);
	cam.lookAt(ofVec3f(0, 0, 0));
}

//--------------------------------------------------------------

void ofApp::gridConfigButtonPressed() {
	for (auto &grid : grids) {
		grid.resize(gridSize, gridDimension);
	}
}

//--------------------------------------------------------------
void ofApp::update(){

	

	while (osc.hasWaitingMessages()) {
		ofxOscMessage m;
		osc.getNextMessage(m);
		if (m.getAddress() == "/play2") {
			map<string, string> paramMap;
			
			for (int i = 0; i < m.getNumArgs(); i += 2) {
				paramMap[m.getArgAsString(i)] = m.getArgAsString(i + 1);
			}
			manager.receiveParams(paramMap);
			paramMap.clear();
		}
	}

	light.setPosition(uiPosition->x, uiPosition->y, uiPosition->z);

	for (auto &grid : grids) {
		grid.update();
	};

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(0);
	ofEnableDepthTest();
	
	light.enable();
	post.begin(cam);
	
	
	if (guiEnabled) {
		ofDrawSphere(uiPosition->x, uiPosition->y, uiPosition->z, 32);
	}
	//ofRotateY(20 * ofGetElapsedTimef());
	ofPushMatrix();
	grids[0].draw();
	ofPopMatrix();

	ofPushMatrix();
	ofRotateXDeg(90);
	grids[1].draw();
	ofPopMatrix();

	ofPushMatrix();
	
	ofRotateYDeg(-90);
	
	grids[2].draw();
	ofPopMatrix();
	
	post.end();
	light.disable();
	ofDisableDepthTest();

	if (guiEnabled) {
		gui.draw();
		ofSetColor(ofColor::red);
		ofDrawBitmapString("FPS: " + to_string(ofGetFrameRate()), 10, 700);
	}

	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == OF_KEY_TAB) {
		if (!guiEnabled) {
			guiEnabled = true;
		}
		else {
			guiEnabled = false;
		}
	}

	if (key == 't') {
		grids[0].midPointSquareTrigger(10, 10, 1, 10, 0, "");
	}


	if (key == 'a') {
		std::cout << "cam target:" << cam.getX() << ", " << cam.getY() << ", " << cam.getZ();
	}
	if (key == 's') {
		if (grids[0].mode < 4) {
			grids[0].mode++;
			grids[0].setMode();
		}
		else {
			grids[0].mode = 0;
			grids[0].setMode();
		}
	}

	if (key == 'd') {
		if (grids[1].mode < 4) {
			grids[1].mode++;
			grids[1].setMode();
		}
		else {
			grids[1].mode = 0;
			grids[1].setMode();
		}
	}

	if (key == 'f') {
		if (grids[2].mode < 4) {
			grids[2].mode++;
			grids[2].setMode();
		}
		else {
			grids[2].mode = 0;
			grids[2].setMode();
		}
	}

	if (key == 'g') {
		if (grids[0].gridVisibility) {
			for (auto &grid : grids) {
				grid.gridVisibility = false;
			}
		}
		else {
			for (auto &grid : grids) {
				grid.gridVisibility = true;
			};
		}
	}

	if (key == 'y') {
		cam.setPosition(-600, -600, -600);
		cam.lookAt(ofVec3f(0,0,0));
	}

	if (key == 'x') {
		cam.setPosition(1200, 1200, 1200);
		cam.lookAt(ofVec3f(0, 0, 0));
	}

	unsigned idx = key - '0';
	if (idx < post.size()) post[idx]->setEnabled(!post[idx]->getEnabled());
	
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
