# pragma once
# ifndef _PIXEL
# define _PIXEL

#include "ofMain.h"

class Pixel
{
	public:
		void setup(int gridSize, int gridDimension);
		void update();
		void draw();
		void drawPrimitive(string primitive, float initRot, int alpha);
		void trigger(float amount);
		float triggerValue = 0;
		int size = 0;
		int dimension = 0;
		ofColor color;
		ofMaterial mat;
		int mode = 0;
		int boundary;
		void setColor(ofColor color);
		bool updating = true;
		string primitive = "box";
		int primResolution = 6;
		int rotateX;
		int rotateY;
		int rotateZ;
		string rotationCenter;
		int z;
		bool fill;

	Pixel();
};


# endif