#pragma once
#ifndef _PRIMITIVEDRAWER
#define _PRIMITIVEDRAWER
#include "ofxAssimpModelLoader.h"
#include "ofMain.h"

class PrimitiveDrawer
{
public:
	struct basePixel {
		int mode = 0;
		int size = 0;
		int dimension = 0;
		int rotationX = 0;
		int rotationY = 0;
		int rotationZ = 0;
		int boundayMin = 0;
		int boundaryMax = 255;
		int primitiveResolution = 6;
		float z = 0;
		float triggerValue = 0;
		float length = 0.95;
		bool fill = true;
		bool updating = true;
		string primitive = "box";
		ofColor color = ofColor::white;
		ofMaterial mat;
	};
	void setup();
	void update(const basePixel& basePixel);
	void draw(const basePixel& basePixel);
	void drawPrimitive(const basePixel& basePixel, float initRot);
	bool isNewSetup(const basePixel& basePixel);

string primitive;
int primitiveResolution;
ofColor color;
ofMaterial mat;
bool fill;
ofxAssimpModelLoader model;

PrimitiveDrawer();

};

#endif

