#include "PrimitiveDrawer.h"
#include "Grid.h"

PrimitiveDrawer::PrimitiveDrawer() {}

void PrimitiveDrawer::setup() {
	primitiveResolution = 6;
	color = ofColor::white;

}

void PrimitiveDrawer::update() {

}

void PrimitiveDrawer::draw(Grid::basePixel basePixel) {

	if (primitiveResolution != basePixel.primitiveResolution) {
		primitiveResolution = basePixel.primitiveResolution;
		// TODO switch primitive resolution based on shape
	}

	switch (basePixel.mode) {
	case 0:
		break;
	case 1:
		break;
	default:
		cout << "default mode triggered";
	}

}
