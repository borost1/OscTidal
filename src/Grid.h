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
		void midPointDiagonalTrigger(int x0, int y0, int radius, float amount, int mode, string color);
		void midPointCircleTrigger(int x0, int y0, int radius);
		void midPointSquareTrigger(int x0, int y0, int length, float amount, int mode, string color);
		void midPointEllipseTrigger(int rx, int ry, int xc, int yc, float amount, int mode, string color);
		void lineTrigger(int x0, int y0, int x1, int y1, float amount, int mode, string color);
		void receiveParams(vector<string> params);
		void update();
		void draw();
		void setMode();
		int dimension;
		int size;
		int mode = 0;
		bool gridVisibility = false;
	
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

