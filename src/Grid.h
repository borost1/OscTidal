#pragma once
#ifndef _GRID
#define _GRID

#include "Pixel.h"
#include "ofMain.h"


class Grid
{
	public:
		void setup(int dim, int s);
		void resize(int dim, int s);
		void trigger(int x, int y, float amount, int mode, string color);
		void trigger(int x, int y, float amount, map<string, int> intParams, map<string, string> stringParams);
		void midPointDiagonalTrigger(int x0, int y0, int radius, float amount, map<string, int> intParams, map<string, string> stringParams);
		void midPointCircleTrigger(int x0, int y0, int radius);
		void midPointSquareTrigger(int x0, int y0, int length, float amount, map<string, int> intParams, map<string, string> stringParams);
		void midPointEllipseTrigger(int rx, int ry, int xc, int yc, float amount, map<string, int> intParams, map<string, string> stringParams);
		void lineTrigger(int x0, int y0, int x1, int y1, float amount, int mode, string color);
		void update();
		void draw();
		void setMode();
		int dimension;
		int size;
		int mode = 0;
		bool gridVisibility = false;
		struct basePixel {
			int mode = 0;
			int rotationX = 0;
			int rotationY = 0;
			int rotationZ = 0;
			int boundary = 255;
			int primitiveResolution = 6;
			float z = 0;
			bool fill = true;
			bool updating = true;
			string primitive = "box";
			ofColor color = ofColor::white;
			ofMaterial mat;
		};
	
	vector<vector<Pixel>> gridData;

	

	map<string, ofColor> colorMap{
	{"red", ofColor::red},
	{"green", ofColor::green},
	{"blue", ofColor::blue},
	{"white", ofColor::white},
	{"yellow", ofColor::yellow},
	{"azure", ofColor::azure},
	{"beige", ofColor::beige},
	{"black", ofColor::black},
	{"cyan", ofColor::cyan},
	{"gray", ofColor::gray},
	{"silver", ofColor::silver}
	};

	Grid();

};
#endif

