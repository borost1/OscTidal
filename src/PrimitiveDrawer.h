#pragma once

#include "ofMain.h"
#include "Grid.h"

class PrimitiveDrawer
{
public:
	void setup();
	void update();
	void draw(Grid::basePixel basePixel);

int primitiveResolution;
ofColor color;
ofMaterial mat;
PrimitiveDrawer();
struct basePixel {} pixel;
};

