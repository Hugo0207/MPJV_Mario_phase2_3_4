#include "ofApp.h"
#include "..\Particle.h"
#include "..\Vector.h"
#include "..\Collision.h"
#include "../Matrice.h"
#include "../TestMatrice.h"

#include <cmath>

//--------------------------------------------------------------
void ofApp::setup() {

	world = new World();

	// GUI
	/*panel.setup();
	spawnButton.addListener(this, &ofApp::SpawnBlobParticle);
	splitButton.addListener(this, &ofApp::SplitBlob);
	panel.add(blobGroup.setup("Blob"));
	blobGroup.add(blobParticlesNumberLabel.setup("Number of particles", world->separate ? "1" : std::to_string(world->nbParticle)));
	blobGroup.add(blobSplitLabel.setup("Split?", world->separate ? "Yes" : "No"));
	panel.add(spawnButton.setup("Add particle"));
	panel.add(splitButton.setup("Split/Merge"));
	panel.add(playerCommandsGroup.setup("Commands"));
	playerCommandsGroup.add(upCommand.setup("Up", "UP ARROW"));
	playerCommandsGroup.add(downCommand.setup("Down", "DOWN ARROW"));
	playerCommandsGroup.add(rightCommand.setup("Right", "RIGHT ARROW"));
	playerCommandsGroup.add(leftCommand.setup("Left", "LEFT ARROW"));*/

	Matrice<4>* m = new Matrice<4>{ 1.0f, 2.0f };
	cout << *m << endl;;

	TestMatrice().RunTest();
}

//--------------------------------------------------------------
void ofApp::update() {
	/*float deltaTime = ofGetLastFrameTime() * 5;


	world->applyWorldForces(deltaTime);

	blobParticlesNumberLabel.setup("Number of particles", world->separate ? "1" : std::to_string(world->nbParticle));
	blobSplitLabel.setup("Split?", world->separate ? "Yes" : "No");*/
}

//--------------------------------------------------------------
void ofApp::draw() {

	//world->drawParticle();

	//// Affichage de l'UI
	//panel.draw();
}

// Spawn particle and link it to the blob
void ofApp::SpawnBlobParticle()
{
	//world->SpawnParticle(Vector(0, 0), Vector(0, 0));
	//world->nbParticle += 1;
}

// Split the blob
void ofApp::SplitBlob()
{
	world->separate = !world->separate;
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