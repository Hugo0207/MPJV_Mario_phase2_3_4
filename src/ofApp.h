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

    // G�n�rateur de gravit�
    GravityGenerator* gravityGenerator;

    // Delta time pour la simulation
    float deltaTime;

    // M�thodes auxiliaires
    void setupScene();
    void launchCube();

    // Mod�le 3D pour le cube
    ofBoxPrimitive cubeMesh;

    // Mat�riau pour le cube
    ofMaterial cubeMaterial;

    // Lumi�res pour l'�clairage
    ofLight pointLight;
    ofLight directionalLight;

    // Cam�ra pour la vue 3D
    ofEasyCam camera;

    // �l�ments GUI
    ofxPanel gui;
    ofParameter<float> launchForce;      // Magnitude de la force
    ofParameter<float> forceDirX;        // Direction X de la force
    ofParameter<float> forceDirY;        // Direction Y de la force
    ofParameter<float> forceDirZ;        // Direction Z de la force
    ofParameter<float> forcePointX;      // Point d'application X
    ofParameter<float> forcePointY;      // Point d'application Y
    ofParameter<float> forcePointZ;      // Point d'application Z

    ofParameter<float> forceAzimuth;    // Angle  (azimut)
    ofParameter<float> forceElevation;  // Angle  (�l�vation)
    bool showGui;

    ofPlanePrimitive groundPlane;
    ofMaterial groundMaterial;
};
