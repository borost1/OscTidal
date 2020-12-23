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
		void trigger(float amount);
		float triggerValue = 0;
		int size = 0;
		int dimension = 0;
		ofColor color;
		ofMaterial mat;
		int mode = 0;
		int boundary;
		void setColor(ofColor color);

	Pixel();
};


# endif