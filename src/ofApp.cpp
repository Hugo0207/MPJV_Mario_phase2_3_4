#include "ofApp.h"
#include "..\Particle.h"
#include "..\Vector.h"
#include "..\Collision.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {

	world = new World();
	// GUI
	panel.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
	float deltaTime = ofGetLastFrameTime() * 5;

	world->player->handleInput();

	world->applyWorldForces(deltaTime);
}

//--------------------------------------------------------------
void ofApp::draw() {

	world->drawParticle();
	// Affichage de l'UI
	panel.draw();
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}