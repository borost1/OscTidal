#include "Grid.h"
#include "Pixel.h"

Grid::Grid() {}

void Grid::setup(int dim, int s) {
	dimension = dim;
	size = s;

	for (int x = 0; x < dimension; x++) {
		vector<Pixel> vals;
		for (int y = 0; y < dimension; y++) {
			Pixel p;
			p.setup(size, dimension);
			vals.push_back(p);	
		}
		gridData.push_back(vals);
	}

}


void Grid::resize(int dim, int s) {

	gridData.clear();

	dimension = dim;
	size = s;

	for (int x = 0; x < dimension; x++) {
		vector<Pixel> vals;
		for (int y = 0; y < dimension; y++) {
			Pixel p;
			p.setup(size, dimension);
			vals.push_back(p);
		}
		gridData.push_back(vals);
	}

}


void Grid::trigger(int x, int y, float amount, int m, string color) {
	if ((-1 < x) and (x < dimension) and (-1 < y) and (y < dimension)) {
		gridData[x][y].trigger(amount);
		if (m > -1) {
			gridData[x][y].mode = m;
		}
		if (color != "") {
			gridData[x][y].setColor(colorMap[color]);
		}
	}	
}

void Grid::midPointDiagonalTrigger(int x0, int y0, int radius, float amount, int m, string color) {
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		trigger(x0 + x, y0 + y, amount, m, color);
		trigger(x0 + y, y0 + x, amount, m, color);
		trigger(x0 - y, y0 + x, amount, m, color);
		trigger(x0 - x, y0 + y, amount, m, color);
		trigger(x0 - x, y0 - y, amount, m, color);
		trigger(x0 - y, y0 - x, amount, m, color);
		trigger(x0 + y, y0 - x, amount, m, color);
		trigger(x0 + x, y0 - y, amount, m, color);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void Grid::midPointSquareTrigger(int x0, int y0, int len, float amount, int mode, string color) {
	
	for (int x = 0; x < len; x++) {
		for (int y = 0; y < len; y++) {
			trigger(x0 + x, y0 + y, amount, mode, color);
		}
	}

}


void Grid::midPointCircleTrigger(int x0, int y0, int radius) {
	/*TODO*/
}

void Grid::update() {
	
	for (int x = 0; x < dimension; x++) {
		for (int y = 0; y < dimension; y++) {
			gridData[x][y].update();
		}	
	}
}

void Grid::draw() {
	ofEnableAlphaBlending();
	//ofRotateY(20 * ofGetElapsedTimef());
	for (int x = 0; x < dimension; x++) {
		for (int y = 0; y < dimension; y++) {		
			ofPushMatrix();
			ofTranslate(x * size / dimension, y * size / dimension);

			//display grid if visible
			if (gridVisibility) {
				ofNoFill();
				ofSetColor(ofColor::white, 127);
				ofDrawRectangle(0, 0, size / dimension, size / dimension);
			}

			if (gridData[x][y].triggerValue > 0) {
				gridData[x][y].draw();
				
			}
			ofPopMatrix();
		}
	}
	ofDisableAlphaBlending();
}

void Grid::setMode() {
	for (int x = 0; x < dimension; x++) {
		for (int y = 0; y < dimension; y++) {
			gridData[x][y].mode = mode;
		}
	}
}