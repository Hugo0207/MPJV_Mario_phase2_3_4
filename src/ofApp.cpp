#include "ofApp.h"
#include "..\Particle.h"
#include "..\Vector.h"
#include "..\Collision.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
	int centerX = ofGetWidth() / 2;
	int centerY = ofGetHeight() / 2;	

	// GUI
	panel.setup();

	SpawnParticle(Vector(ofGetWidth(), centerY + 10), Vector(-50, 1), ofColor(255, 0, 0));
	SpawnParticle(Vector(0, centerY), Vector(30, 0), ofColor(0, 255, 0));
}

//--------------------------------------------------------------
void ofApp::update() {
	float deltaTime = ofGetLastFrameTime() * 5;

	for (auto& particle : particles)
	{
		particle->integrate(deltaTime);

		// Stop les projectiles qui sont sortis de l'écran
        if (particle->position.y > ofGetHeight()*1.3 || particle->position.x > ofGetWidth()*1.3 || particle->position.x < 0) {
			particle->velocity = Vector(0, 0, 0);
        }

		collisionSystem.update(particles);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (auto& particle : particles) {
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
	particles.push_back(newParticle);
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


