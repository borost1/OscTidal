#include "Grid.h"

Grid::Grid() {}

void Grid::setup(int dim, int s) {
	dimension = dim;
	size = s;
	drawer.setup();

	for (int x = 0; x < dimension; x++) {
		vector<PrimitiveDrawer::basePixel> vals;
		for (int y = 0; y < dimension; y++) {
			PrimitiveDrawer::basePixel p;
			p.size = size;
			p.dimension = dimension;
			vals.push_back(p);
		}
		baseGridData.push_back(vals);
	}

}


void Grid::resize(int dim, int s) {

	baseGridData.clear();

	dimension = dim;
	size = s;

	for (int x = 0; x < dimension; x++) {
		vector<PrimitiveDrawer::basePixel> vals;
		for (int y = 0; y < dimension; y++) {
			PrimitiveDrawer::basePixel p;
			p.size = size;
			p.dimension = dimension;
			vals.push_back(p);
		}
		baseGridData.push_back(vals);
	}

}

void Grid::trigger(int x, int y, map<string, float> floatParams, map<string, int> intParams, map<string, string> stringParams) {

	if ((-1 < x) and (x < dimension) and (-1 < y) and (y < dimension)) {
		baseGridData[x][y].length = floatParams["length"];
		baseGridData[x][y].triggerValue = ofMap(floatParams["gain"], 0, 1, intParams["boundMin"], intParams["boundMax"] * floatParams["gain"]);
		baseGridData[x][y].mode = intParams["mode"];
		baseGridData[x][y].primitive = stringParams["primitive"];
		baseGridData[x][y].primitiveResolution = intParams["primres"];
		baseGridData[x][y].boundaryMax = intParams["boundMin"];
		baseGridData[x][y].boundaryMax = intParams["boundMax"];
		baseGridData[x][y].z = intParams["z"];
		baseGridData[x][y].rotationX = intParams["rotateX"];
		baseGridData[x][y].rotationY = intParams["rotateY"];
		baseGridData[x][y].rotationZ = intParams["rotateZ"];

		//grid fill
		if (stringParams["fill"] == "true") {
			baseGridData[x][y].fill = true;
		}
		else {
			baseGridData[x][y].fill = false;
		}

		// test for updating
		if (stringParams["updating"] == "true") {
			baseGridData[x][y].updating = true;
		}
		else {
			baseGridData[x][y].updating = false;
		}

		// set color based on tidal syntax
		if (intParams["red"] > -1 and intParams["green"] > -1 and intParams["blue"] > -1) {
			baseGridData[x][y].color = ofColor(intParams["red"], intParams["green"], intParams["blue"]);
		}
		else {
			baseGridData[x][y].color = colorMap[stringParams["color"]];
		}

	}
}

void Grid::midPointDiagonalTrigger(int x0, int y0, int radius, map<string, float> floatParams, map<string, int> intParams, map<string, string> stringParams) {
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		trigger(x0 + x, y0 + y, floatParams, intParams, stringParams);
		trigger(x0 + y, y0 + x, floatParams, intParams, stringParams);
		trigger(x0 - y, y0 + x, floatParams, intParams, stringParams);
		trigger(x0 - x, y0 + y, floatParams, intParams, stringParams);
		trigger(x0 - x, y0 - y, floatParams, intParams, stringParams);
		trigger(x0 - y, y0 - x, floatParams, intParams, stringParams);
		trigger(x0 + y, y0 - x, floatParams, intParams, stringParams);
		trigger(x0 + x, y0 - y, floatParams, intParams, stringParams);

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

void Grid::midPointSquareTrigger(int x0, int y0, int len, map<string, float> floatParams, map<string, int> intParams, map<string, string> stringParams) {
	int shift = static_cast<int>(len / 2);
	for (int x = 0; x < len; x++) {
		for (int y = 0; y < len; y++) {
			if ((x == 0 || x == len - 1) || (y == 0 || y == len - 1)) {
				trigger(x0 + x - shift, y0 + y - shift, floatParams, intParams, stringParams);
			}	
		}
	}

}


void Grid::midPointCircleTrigger(int x0, int y0, int radius) {
	/*TODO*/
}

void Grid::midPointEllipseTrigger(int rx, int ry, int xc, int yc, map<string, float> floatParams, map<string, int> intParams, map<string, string> stringParams) {
	float dx, dy, d1, d2, x, y;
	x = 0;
	y = ry;

	d1 = (ry * ry)
		- (rx * rx * ry)
		+ (0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;

	while (dx < dy) {


		trigger(x + xc, y + yc, floatParams, intParams, stringParams);
		trigger(-x + xc, y + yc, floatParams, intParams, stringParams);
		trigger(x + xc, -y + yc, floatParams, intParams, stringParams);
		trigger(-x + xc, -y + yc, floatParams, intParams, stringParams);


		if (d1 < 0) {
			x++;
			dx = dx + (2 * ry * ry);
			d1 = d1 + dx + (ry * ry);
		}
		else {
			x++;
			y--;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d1 = d1 + dx - dy + (ry * ry);
		}
	}


	d2 = ((ry * ry) * ((x + 0.5) * (x + 0.5)))
		+ ((rx * rx) * ((y - 1) * (y - 1)))
		- (rx * rx * ry * ry);


	while (y >= 0) {


		trigger(x + xc, y + yc, floatParams, intParams, stringParams);
		trigger(-x + xc, y + yc, floatParams, intParams, stringParams);
		trigger(x + xc, -y + yc, floatParams, intParams, stringParams);
		trigger(-x + xc, -y + yc, floatParams, intParams, stringParams);


		if (d2 > 0) {
			y--;
			dy = dy - (2 * rx * rx);
			d2 = d2 + (rx * rx) - dy;
		}
		else {
			y--;
			x++;
			dx = dx + (2 * ry * ry);
			dy = dy - (2 * rx * rx);
			d2 = d2 + dx - dy + (rx * rx);
		}
	}
}

void Grid::lineTrigger(int x1, int y1, int x2, int y2, float amount, int mode, string color) {
	//TODO
}

void Grid::update() {
	for (int x = 0; x < dimension; x++) {
		for (int y = 0; y < dimension; y++) {
			baseGridData[x][y].triggerValue *= baseGridData[x][y].length;
		}
	}
}

void Grid::draw() {
	ofEnableAlphaBlending();
	for (int x = 0; x < dimension; x++) {
		for (int y = 0; y < dimension; y++) {
			ofPushMatrix();
			ofTranslate(x * size / dimension, y * size / dimension);
			if (gridVisibility) {
				ofNoFill();
				ofSetColor(ofColor::white, 100);
				ofDrawRectangle(0, 0, size / dimension, size / dimension);
			}

			if (baseGridData[x][y].triggerValue > 0) {
				drawer.draw(baseGridData[x][y]);

			}
			ofPopMatrix();
		}
	}
	ofDisableAlphaBlending();
}

