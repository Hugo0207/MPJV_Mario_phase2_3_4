#include "Player.h"

Player::Player(Vector initPosition, Vector initVelocity, float inverseMass, ofColor color, float radius)
    : Particle(initPosition, initVelocity, inverseMass, color, radius) {}

void Player::handleInput() {
    if (ofGetKeyPressed(OF_KEY_LEFT)) {
        setVelocity(getVelocity() + Vector(-1, 0, 0));
    }
    if (ofGetKeyPressed(OF_KEY_RIGHT)) {
        setVelocity(getVelocity() + Vector(1, 0, 0));
    }
    if (ofGetKeyPressed(OF_KEY_UP)) {
        setVelocity(getVelocity() + Vector(0, -2, 0));
    }
    if (ofGetKeyPressed(OF_KEY_DOWN)) {
        setVelocity(getVelocity() + Vector(0, 1, 0));
    }
}

