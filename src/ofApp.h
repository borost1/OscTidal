#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"
#include "ofxPostProcessing.h"
#include "Grid.h"
#include "Pixel.h"
#include <stack>

#define PORT 50500

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
		void gridConfigButtonPressed();

	ofxOscReceiver osc;

	vector<Grid> grids;

	//Grid grid;
	//Grid grid2;
	//Grid grid3;
	ofEasyCam cam;
	ofLight light;
	ofxPostProcessing post;

	ofxPanel gui;
	ofParameter <ofVec3f> uiPosition;
	ofParameter <int> gridSize;
	ofParameter <int> gridDimension;
	ofxButton gridConfigButton;

	vector<string> params;

	bool guiEnabled;
		
};
