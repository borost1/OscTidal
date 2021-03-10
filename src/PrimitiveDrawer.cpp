#include "PrimitiveDrawer.h"

PrimitiveDrawer::PrimitiveDrawer() {}

void PrimitiveDrawer::setup() {
	primitive = "box";
	primitiveResolution = 6;
	color = ofColor::white;
	mat.setColors(color, color, color, color);
}

void PrimitiveDrawer::update() {

}

void PrimitiveDrawer::draw(basePixel& basePixel) {

	if (isNewSetup(basePixel)) {
		primitive = basePixel.primitive;
		primitiveResolution = basePixel.primitiveResolution;
		
		color = basePixel.color;
		mat.setColors(basePixel.color, basePixel.color, basePixel.color, basePixel.color);
		
		ofSetBoxResolution(primitiveResolution);
		ofSetConeResolution(primitiveResolution, primitiveResolution);
		ofSetCylinderResolution(primitiveResolution, primitiveResolution);
	}
	int alpha = static_cast<int>(basePixel.triggerValue);
	switch (basePixel.mode) {
	case 0:
		
		if (alpha > 1) {
			if (basePixel.fill) {
				ofFill();
			}
			else {
				ofNoFill();
			}
			ofSetColor(color, alpha);
			ofTranslate((basePixel.size / basePixel.dimension) / 2, (basePixel.size / basePixel.dimension) / 2, basePixel.z);

			ofRotateXDeg(basePixel.rotationX*ofGetElapsedTimef());
			ofRotateYDeg(basePixel.rotationY*ofGetElapsedTimef());
			ofRotateZDeg(basePixel.rotationZ*ofGetElapsedTimef());

			if (primitive == "box") {
				ofDrawBox(ofPoint(0, 0, 0), basePixel.size / basePixel.dimension, basePixel.size / basePixel.dimension, 5);
			}
			else if (primitive == "cone") {
				ofRotateXDeg(-90);
				ofRotateYDeg(45);
				ofDrawCone(ofPoint(0, 0, 0), basePixel.size / basePixel.dimension, basePixel.size / basePixel.dimension);
			}
			else if (primitive == "cylinder") {
				ofRotateXDeg(-90);
				ofDrawCylinder(ofPoint(0, 0, 0), basePixel.size / basePixel.dimension, basePixel.size / basePixel.dimension);
			}
		}
		break;
	case 1:
		cout << "case 1\n";
		break;
	default:
		cout << "default mode triggered\n";
		break;
	}

}

bool PrimitiveDrawer::isNewSetup(basePixel& basePixel) {
	if (
		primitive != basePixel.primitive ||
		primitiveResolution != basePixel.primitiveResolution ||
		color != basePixel.color
		) 
	{
		return true;
	}
	else {
		return false;
	}
}
