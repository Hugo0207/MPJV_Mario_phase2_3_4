#include "ofApp.h"
#include "..\Particle.h"
#include "..\Vector.h"
#include "..\Collision.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
	int centerX = ofGetWidth() / 2;
	int centerY = ofGetHeight() / 2;	

	world = new World();

	// GUI
	panel.setup();

	SpawnParticle(Vector(ofGetWidth(), centerY + 10), Vector(-50, -50), ofColor(255, 0, 0));
	SpawnParticle(Vector(0, centerY), Vector(30, -50), ofColor(0, 255, 0));
}

//--------------------------------------------------------------
void ofApp::update() {
	float deltaTime = ofGetLastFrameTime() * 5;

	world->applyWorldForces(deltaTime);
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (auto& particle : world->particles) {
		particle->draw();
	}

	// Affichage de l'UI
	panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::SpawnParticle(Vector initPosition, Vector initVelocity, ofColor color) {
	Particle* newParticle = new Particle(
		initPosition,
		initVelocity,
		20,
		ofColor(color),
		20
	);
	world->particles.push_back(newParticle);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}


