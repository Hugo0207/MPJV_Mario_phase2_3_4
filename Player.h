#ifndef PLAYER_H
#define PLAYER_H

#include "Particle.h"
#include "ofMain.h"  

class Player : public Particle {
public:
    Player(Vector initPosition, Vector initVelocity, float inverseMass, ofColor color, float radius);
    void handleInput();
};

bool separate;

#endif // PLAYER_H