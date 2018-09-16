#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofSetLineWidth(3.0);

	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->shader.load("shader/shader.vert", "shader/shader.frag");
}
//--------------------------------------------------------------
void ofApp::update() {
	
	ofSeedRandom(39);

	this->fbo.begin();
	ofClear(0);
	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	int deg_len = 130;
	for (int i = 0; i < 10; i++) {

		int radius = 30 * (i + 1);
		int circle_deg = ofGetFrameNum() + deg_len + i * 30;
		float x = radius * cos(circle_deg * DEG_TO_RAD);
		float y = radius * sin(circle_deg * DEG_TO_RAD);
		ofFill();
		ofDrawCircle(x, y, 10);

		ofPoint prev = ofPoint();
		for (int deg = ofGetFrameNum() + i * 30; deg < circle_deg; deg++) {

			x = radius * cos(deg * DEG_TO_RAD);
			y = radius * sin(deg * DEG_TO_RAD);

			if (prev != ofPoint()) { ofDrawLine(ofPoint(x, y), prev); }
			prev = ofPoint(x, y);
		}
	}
	
	this->fbo.end();
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex", this->fbo.getTexture(), 1);

	ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();	
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}