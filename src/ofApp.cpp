#include "ofApp.h"
#include "..\Particle.h"
#include "..\Vector.h"
#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {
	int centerX = 0;
	int centerY = ofGetHeight() / 2;	

	// GUI
	panel.setup();
}

//--------------------------------------------------------------
void ofApp::update() {
	float deltaTime = ofGetLastFrameTime() * 5;

    // Stop les projectiles qui sont sortis de l'écran
    for (int i = 0; i < projectiles.size(); i++) {
        if (projectiles[i].position.y > ofGetHeight()*1.3 || projectiles[i].position.x > ofGetWidth()*1.3 || projectiles[i].position.x < 0) {
            projectiles[i].velocity = Vector(0, 0, 0); 
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
	for (auto& projectile : projectiles) {
		projectile.draw(); 
	}

	// Affichage de l'UI
	panel.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::SpawnParticle() {
	Particle newParticle(
		Vector(ofGetWidth() / 2, ofGetHeight() / 2),
		Vector(ofRandom(-2, 2), ofRandom(-2, 2)),
		20
	);
	projectiles.push_back(newParticle);
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


