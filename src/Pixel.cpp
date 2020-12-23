#include "Pixel.h"

Pixel::Pixel(){}

void Pixel::setup(int gridSize, int gridDimension){
	size = gridSize;
	dimension = gridDimension;
	color = ofColor::white;
	mode = 0;
	boundary = 255;
	mat.setDiffuseColor(color);
	mat.setAmbientColor(color);
	mat.setSpecularColor(color);
	mat.setShininess(128);
}

void Pixel::update() {
	if (triggerValue > 1) {
		triggerValue *= 0.95;
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
			ofFill();
			ofSetColor(color, alpha);
			ofTranslate((size / dimension) / 2, (size / dimension) / 2);
			ofDrawBox(ofPoint(0, 0, 0), size / dimension, size / dimension, 5);
		}
		break;
	case 1:
		ofTranslate((size / dimension) / 2, (size / dimension) / 2);
		ofFill();
		mat.begin();
		ofDrawBox(ofPoint(0, 0, 0), alpha);
		mat.end();
		break;
	case 2:
		if (alpha > 1) {
			ofFill();
			mat.begin();
			ofDrawBox(ofPoint(0, 0, 0), size / dimension + 1, size / dimension + 1, ofMap(alpha, 0, 255, 0, boundary));
			mat.end();
		}
		break;
	case 3:
		if (alpha > 1) {
			ofTranslate((size / dimension) / 2, (size / dimension) / 2, ofMap(alpha, 0, 255, 0, boundary) / 2);
			ofFill();
			mat.begin();
			ofDrawBox(ofPoint(0, 0, 0), size / dimension + 1, size / dimension + 1, ofMap(alpha, 0, 255, 0, boundary));
			mat.end();
		}
		break;
	case 4:
		if (alpha > 1) {
			ofTranslate((size / dimension) / 2, (size / dimension) / 2, ofMap(alpha, 0, 255, 0, -boundary) / 2);
			ofFill();
			mat.begin();
			ofDrawBox(ofPoint(0, 0, 0), size / dimension + 1, size / dimension + 1, ofMap(alpha, 0, 255, 0, -boundary));
			mat.end();
		}
		break;
	}


}

void Pixel::trigger(float amount) {
	triggerValue = amount;
}