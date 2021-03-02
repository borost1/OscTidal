#include "Pixel.h"

Pixel::Pixel(){}

void Pixel::setup(int gridSize, int gridDimension){
	size = gridSize;
	dimension = gridDimension;
	color = ofColor::white;
	mode = 0;
	boundary = 255;
	updating = true;
	primitive = "box";
	primResolution = 6;
	z = 0;
	rotateX = 0;
	rotateY = 0;
	rotateZ = 0;
	rotationCenter = "pixel";
	fill = true;

	mat.setDiffuseColor(color);
	mat.setAmbientColor(color);
	mat.setSpecularColor(color);
	mat.setShininess(128);
}

void Pixel::update() {
	if(updating){
		if (triggerValue > 1) {
			triggerValue *= 0.95;
		}
	}
	
}

void Pixel::setColor(ofColor c) {
	color = c;
	mat.setDiffuseColor(c);
	mat.setAmbientColor(c);
	mat.setSpecularColor(c);
}

void Pixel::draw() {
	//std::cout << mode << " ";
	int alpha = static_cast<int>(triggerValue);
	switch (mode) {
	case 0:
		if (alpha > 1) {
			if (fill) {
				ofFill();
			}
			else {
				ofNoFill();
			}
			ofSetColor(color, alpha);
			ofTranslate((size / dimension) / 2, (size / dimension) / 2, z);

			ofRotateXDeg(rotateX*ofGetElapsedTimef());
			ofRotateYDeg(rotateY*ofGetElapsedTimef());
			ofRotateZDeg(rotateZ*ofGetElapsedTimef());

			if (primitive == "box") {
				ofSetBoxResolution(primResolution);
				ofDrawBox(ofPoint(0, 0, 0), size / dimension, size / dimension, 5);
			}
			else if(primitive == "cone") {
				ofRotateXDeg(-90);
				ofRotateYDeg(45);
				ofSetConeResolution(primResolution, primResolution);
				ofDrawCone(ofPoint(0, 0, 0), size / dimension, size / dimension);
			}
			else if (primitive == "cylinder") {
				ofRotateXDeg(-90);
				ofSetCylinderResolution(primResolution, primResolution);
				ofDrawCylinder(ofPoint(0, 0, 0), size / dimension, size / dimension);
			}
		}
		break;
	case 1:
		ofTranslate((size / dimension) / 2, (size / dimension) / 2, z);
		if (fill) {
			ofFill();
		}
		else {
			ofNoFill();
		}
		mat.begin();

		ofRotateXDeg(rotateX*ofGetElapsedTimef());
		ofRotateYDeg(rotateY*ofGetElapsedTimef());
		ofRotateZDeg(rotateZ*ofGetElapsedTimef());

		if (primitive == "box") {
			ofDrawBox(ofPoint(0, 0, 0), ofMap(alpha, 0, 255, 0, boundary));
		}
		else if (primitive == "cone") {
			ofRotateXDeg(-90);
			ofDrawCone(ofPoint(0, 0, 0), ofMap(alpha, 0, 255, 0, boundary), ofMap(alpha, 0, 255, 0, boundary));
		}
		else if (primitive == "cylinder") {
			ofRotateXDeg(-90);
			ofDrawCylinder(ofPoint(0, 0, 0), ofMap(alpha, 0, 255, 0, boundary), ofMap(alpha, 0, 255, 0, boundary));
		}
		mat.end();
		break;
	case 2:
		if (alpha > 1) {
			
			ofTranslate(0, 0, z);
			ofRotateXDeg(rotateX*ofGetElapsedTimef());
			ofRotateYDeg(rotateY*ofGetElapsedTimef());
			ofRotateZDeg(rotateZ*ofGetElapsedTimef());
			drawPrimitive(primitive, -90, alpha);
		}
		break;
	case 3:
		if (alpha > 1) {
			
			ofTranslate((size / dimension) / 2, (size / dimension) / 2, ofMap(alpha, 0, 255, 0, boundary) / 2 + z);
			ofRotateXDeg(rotateX*ofGetElapsedTimef());
			ofRotateYDeg(rotateY*ofGetElapsedTimef());
			ofRotateZDeg(rotateZ*ofGetElapsedTimef());
			drawPrimitive(primitive, -90, alpha);
		}
		break;
	case 4:
		if (alpha > 1) {
			
			ofTranslate((size / dimension) / 2, (size / dimension) / 2, ofMap(alpha, 0, 255, 0, -boundary) / 2 + z);
			ofRotateXDeg(rotateX*ofGetElapsedTimef());
			ofRotateYDeg(rotateY*ofGetElapsedTimef());
			ofRotateZDeg(rotateZ*ofGetElapsedTimef());
			drawPrimitive(primitive, 90, alpha);
			
		}
		break;
	}
}

void Pixel::drawPrimitive(string primitive, float initRot, int alpha) {
	if (fill) {
		ofFill();
	}
	else {
		ofNoFill();
	}
	mat.begin();
	if (primitive == "box") {
		ofDrawBox(ofPoint(0, 0, 0), size / dimension + 1, size / dimension + 1, ofMap(alpha, 0, 255, 0, boundary));
	}
	else if (primitive == "cone") {
		ofRotateXDeg(initRot);
		ofDrawCone(ofPoint(0, 0, 0), size / dimension + 1, ofMap(alpha, 0, 255, 0, boundary));
	}
	else if (primitive == "cylinder") {
		ofRotateXDeg(initRot);
		ofDrawCylinder(ofPoint(0, 0, 0), size / dimension + 1, ofMap(alpha, 0, 255, 0, boundary));
	}
	else if (primitive == "sphere") {
		ofDrawSphere(ofMap(alpha, 0, 255, 0, boundary));
	}
	mat.end();
}

void Pixel::trigger(float amount) {
	triggerValue = amount;
}