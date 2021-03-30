#include "PrimitiveDrawer.h"

PrimitiveDrawer::PrimitiveDrawer() {}

void PrimitiveDrawer::setup() {
	fill = true;
	primitive = "box";
	primitiveResolution = 6;
	color = ofColor::white;
	mat.setDiffuseColor(color);
	mat.setAmbientColor(color);
	mat.setSpecularColor(color);
	mat.setShininess(155);

	model.loadModel("models/david2.obj");
	model.calculateDimensions();
	model.setScaleNormalization(false);
}

void PrimitiveDrawer::update(const basePixel& basePixel) {
	primitive = basePixel.primitive;
	primitiveResolution = basePixel.primitiveResolution;
	fill = basePixel.fill;
	
	color = basePixel.color;
	mat.setDiffuseColor(color);
	mat.setAmbientColor(color);
	mat.setSpecularColor(color);

	ofSetBoxResolution(primitiveResolution);
	ofSetConeResolution(primitiveResolution, primitiveResolution);
	ofSetCylinderResolution(primitiveResolution, primitiveResolution);
}

void PrimitiveDrawer::draw(const basePixel& basePixel) {

	if (basePixel.primitive == "model") {
		drawModel(basePixel);
	}
	else {
		if (isNewSetup(basePixel)) {
			update(basePixel);
		}

		if (basePixel.fill) { ofFill(); }
		else { ofNoFill(); }
		float alpha = static_cast<int>(basePixel.triggerValue);

		switch (basePixel.mode) {
		case 0:
			if (alpha > 1) {
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
			if (alpha > 1) {
				ofTranslate((basePixel.size / basePixel.dimension) / 2, (basePixel.size / basePixel.dimension) / 2, basePixel.z);
				ofRotateXDeg(basePixel.rotationX*ofGetElapsedTimef());
				ofRotateYDeg(basePixel.rotationY*ofGetElapsedTimef());
				ofRotateZDeg(basePixel.rotationZ*ofGetElapsedTimef());
				mat.begin();

				if (primitive == "box") {
					ofDrawBox(ofPoint(0, 0, 0), ofMap(alpha, 0, 255, 0, basePixel.boundaryMax));
				}
				else if (primitive == "cone") {
					ofRotateXDeg(-90);
					ofDrawCone(ofPoint(0, 0, 0), ofMap(alpha, 0, 255, 0, basePixel.boundaryMax), ofMap(alpha, 0, 255, 0, basePixel.boundaryMax));
				}
				else if (primitive == "cylinder") {
					ofRotateXDeg(-90);
					ofDrawCylinder(ofPoint(0, 0, 0), ofMap(alpha, 0, 255, 0, basePixel.boundaryMax), ofMap(alpha, 0, 255, 0, basePixel.boundaryMax));
				}
				mat.end();
			}
			break;

		case 2:
			ofTranslate(0, 0, basePixel.z);
			ofRotateXDeg(basePixel.rotationX*ofGetElapsedTimef());
			ofRotateYDeg(basePixel.rotationY*ofGetElapsedTimef());
			ofRotateZDeg(basePixel.rotationZ*ofGetElapsedTimef());
			drawPrimitive(basePixel, -90);
			break;
		case 3:
			ofTranslate((basePixel.size / basePixel.dimension) / 2, (basePixel.size / basePixel.dimension) / 2, ofMap(alpha, 0, 255, 0, basePixel.boundaryMax) / 2 + basePixel.z);
			ofRotateXDeg(basePixel.rotationX*ofGetElapsedTimef());
			ofRotateYDeg(basePixel.rotationY*ofGetElapsedTimef());
			ofRotateZDeg(basePixel.rotationZ*ofGetElapsedTimef());
			drawPrimitive(basePixel, -90);
			break;
		case 4:
			ofTranslate((basePixel.size / basePixel.dimension) / 2, (basePixel.size / basePixel.dimension) / 2, ofMap(alpha, 0, 255, 0, -basePixel.boundaryMax) / 2 + basePixel.z);
			ofRotateXDeg(basePixel.rotationX*ofGetElapsedTimef());
			ofRotateYDeg(basePixel.rotationY*ofGetElapsedTimef());
			ofRotateZDeg(basePixel.rotationZ*ofGetElapsedTimef());
			drawPrimitive(basePixel, 90);
			break;
		default:
			cout << "default mode triggered\n";
			break;
		}
	}
}

bool PrimitiveDrawer::isNewSetup(const basePixel& basePixel) {
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

void PrimitiveDrawer::drawPrimitive(const basePixel& basePixel, float initRot) {
	if (basePixel.triggerValue > 1) {
		
		if (primitive == "box") {
			mat.begin();
			ofDrawBox(ofPoint(0, 0, 0), basePixel.size / basePixel.dimension + 1, basePixel.size / basePixel.dimension + 1, basePixel.triggerValue);
			mat.end();
		}
		else if (primitive == "cone") {
			mat.begin();
			ofRotateXDeg(initRot);
			ofDrawCone(ofPoint(0, 0, 0), basePixel.size / basePixel.dimension + 1, basePixel.triggerValue);
			mat.end();
		}
		else if (primitive == "cylinder") {
			mat.begin();
			ofRotateXDeg(initRot);
			ofDrawCylinder(ofPoint(0, 0, 0), basePixel.size / basePixel.dimension + 1, basePixel.triggerValue);
			mat.end();
		}
		else if (primitive == "sphere") {
			mat.begin();
			ofDrawSphere(basePixel.triggerValue);
			mat.end();
		}
	}
}

void PrimitiveDrawer::drawModel(const basePixel& basePixel) {
	ofRotateXDeg(basePixel.rotationX*ofGetElapsedTimef());
	ofRotateYDeg(basePixel.rotationY*ofGetElapsedTimef());
	ofRotateZDeg(basePixel.rotationZ*ofGetElapsedTimef());
	float scale = basePixel.triggerValue * basePixel.boundaryMax;
	model.setScale(scale, scale, scale);
	model.drawFaces();
}
