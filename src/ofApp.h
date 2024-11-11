#pragma once

#include "ofMain.h"
#include "../World.h"
#include "../CorpsRigide.h"
#include "../RigidBodyForceGenerator.h"
#include "../GravityGenerator.h"
#include "ofxGui.h"


// Classe principale de l'application
class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void drawAxisIndicator();
    void drawAxes(float size);

    void keyPressed(int key);
    //void mousePressed(int x, int y, int button);

private:
    // Pointeur vers le monde physique
    World* world;

    // Générateur de gravité
    GravityGenerator* gravityGenerator;

    // Delta time pour la simulation
    float deltaTime;

    // Méthodes auxiliaires
    void setupScene();
    void launchCube();

    // Modèle 3D pour le cube
    ofBoxPrimitive cubeMesh;

    // Matériau pour le cube
    ofMaterial cubeMaterial;

    // Lumières pour l'éclairage
    ofLight pointLight;
    ofLight directionalLight;

    // Caméra pour la vue 3D
    ofEasyCam camera;

    // Éléments GUI
    ofxPanel gui;
    ofParameter<float> launchForce;      // Magnitude de la force
    ofParameter<float> forceDirX;        // Direction X de la force
    ofParameter<float> forceDirY;        // Direction Y de la force
    ofParameter<float> forceDirZ;        // Direction Z de la force
    ofParameter<float> forcePointX;      // Point d'application X
    ofParameter<float> forcePointY;      // Point d'application Y
    ofParameter<float> forcePointZ;      // Point d'application Z

    ofParameter<float> forceAzimuth;    // Angle  (azimut)
    ofParameter<float> forceElevation;  // Angle  (élévation)
    bool showGui;

    ofPlanePrimitive groundPlane;
    ofMaterial groundMaterial;
};
