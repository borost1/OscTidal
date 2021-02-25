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

//obsolete stuff
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

void Grid::trigger(int x, int y, float amount, map<string, int> intParams, map<string, string> stringParams) {
	if ((-1 < x) and (x < dimension) and (-1 < y) and (y < dimension)) {
		gridData[x][y].trigger(amount);

		gridData[x][y].mode = intParams["mode"];
		gridData[x][y].primitive = stringParams["primitive"];
		gridData[x][y].primResolution = intParams["primres"];
		gridData[x][y].boundary = intParams["boundary"];
		gridData[x][y].z = intParams["z"];
		gridData[x][y].rotateX = intParams["rotateX"];
		gridData[x][y].rotateY = intParams["rotateY"];
		gridData[x][y].rotateZ = intParams["rotateZ"];
		
		// test for updating
		if (stringParams["updating"] == "true") {
			gridData[x][y].updating = true;
		}
		else {
			gridData[x][y].updating = false;
		}

		// set color based on tidal syntax
		if (intParams["red"] > -1 and intParams["green"] > -1 and intParams["blue"] > -1) {
			gridData[x][y].setColor(ofColor(intParams["red"], intParams["green"], intParams["blue"]));
		}
		else {
			gridData[x][y].setColor(colorMap[stringParams["color"]]);
		}

	}
}

void Grid::midPointDiagonalTrigger(int x0, int y0, int radius, float amount, map<string, int> intParams, map<string, string> stringParams) {
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		trigger(x0 + x, y0 + y, amount, intParams, stringParams);
		trigger(x0 + y, y0 + x, amount, intParams, stringParams);
		trigger(x0 - y, y0 + x, amount, intParams, stringParams);
		trigger(x0 - x, y0 + y, amount, intParams, stringParams);
		trigger(x0 - x, y0 - y, amount, intParams, stringParams);
		trigger(x0 - y, y0 - x, amount, intParams, stringParams);
		trigger(x0 + y, y0 - x, amount, intParams, stringParams);
		trigger(x0 + x, y0 - y, amount, intParams, stringParams);

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

void Grid::midPointSquareTrigger(int x0, int y0, int len, float amount, map<string, int> intParams, map<string, string> stringParams) {
	int shift = static_cast<int>(len / 2);
	for (int x = 0; x < len; x++) {
		for (int y = 0; y < len; y++) {
			if ((x == 0 || x == len - 1) || (y == 0 || y == len - 1)) {
				trigger(x0 + x - shift, y0 + y - shift, amount, intParams, stringParams);
			}	
		}
	}

}


void Grid::midPointCircleTrigger(int x0, int y0, int radius) {
	/*TODO*/
}

void Grid::midPointEllipseTrigger(int rx, int ry, int xc, int yc, float amount, map<string, int> intParams, map<string, string> stringParams) {
	float dx, dy, d1, d2, x, y;
	x = 0;
	y = ry;

	d1 = (ry * ry)
		- (rx * rx * ry)
		+ (0.25 * rx * rx);
	dx = 2 * ry * ry * x;
	dy = 2 * rx * rx * y;

	while (dx < dy) {


		trigger(x + xc, y + yc, amount, intParams, stringParams);
		trigger(-x + xc, y + yc, amount, intParams, stringParams);
		trigger(x + xc, -y + yc, amount, intParams, stringParams);
		trigger(-x + xc, -y + yc, amount, intParams, stringParams);


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


		trigger(x + xc, y + yc, amount, intParams, stringParams);
		trigger(-x + xc, y + yc, amount, intParams, stringParams);
		trigger(x + xc, -y + yc, amount, intParams, stringParams);
		trigger(-x + xc, -y + yc, amount, intParams, stringParams);


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
	int m_new = 2 * (y2 - y1);
	int slope_error_new = m_new - (x2 - x1);
	for (int x = x1, y = y1; x <= x2; x++)
	{
		cout << "(" << x << "," << y << ")\n";
		trigger(x, y, amount, mode, color);


		slope_error_new += m_new;

		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new -= 2 * (x2 - x1);
		}
	}
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

