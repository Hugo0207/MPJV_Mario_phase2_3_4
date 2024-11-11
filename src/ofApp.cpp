#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    // Initialisation du monde physique
    deltaTime = 1.0f / 60.0f; // Par défaut, 60 FPS
    world = new World(deltaTime);

    // Configuration initiale de la scène
    setupScene();

    // Configuration de l'éclairage
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor(ofColor(246, 228, 188));
    pointLight.setSpecularColor(ofColor(246, 228, 188));
    pointLight.setPosition(0, 50, 0);

    directionalLight.setDiffuseColor(ofColor(246, 228, 188));
    directionalLight.setSpecularColor(ofColor(246, 228, 188));
    directionalLight.setOrientation(ofVec3f(45, -45, 0));

    // Configuration du matériau du cube
    cubeMaterial.setShininess(64);
    cubeMaterial.setDiffuseColor(ofColor(200, 0, 0, 150)); // Rouge pour bien voir la rotation

    groundMaterial.setShininess(64);
    groundMaterial.setDiffuseColor(ofColor(100, 100, 100)); // Gris pour le sol

    groundPlane.set(50, 50); // Taille du plan, subdivisé en 100x100 pour une meilleure qualité de texture
    groundPlane.rotateDeg(-90, 1, 0, 0); // Rotation du plan pour etre sur le plan XZ

    // Active la profondeur
    ofEnableDepthTest();

    // Configuration de la caméra
    camera.setNearClip(0.1f);
    camera.setFarClip(1000.0f);

    // Positionne la caméra pour une vue isométrique
    float camDistance = 10.0f; 
    camera.setPosition(camDistance, camDistance, camDistance);
    camera.lookAt(ofVec3f(0, 0, 0)); // La caméra regarde le centre de la scène

    // Désactive le contrôle de la caméra avec la souris pour un point de vue fixe
    camera.enableMouseInput();

    // Initialisation de la GUI
    gui.setup("Paramètres de Lancement");

    // Définition des valeurs par défaut et des plages pour la force
    launchForce.set("Force de Lancement", 10.0f, 0.0f, 10000.0f);

    forceAzimuth.set("Azimut", 0.0f, -180.0f, 180.0f);
    forceElevation.set("Élévation", 0.0f, -90.0f, 90.0f);

    // Définition des valeurs par défaut et des plages pour le point d'application
    forcePointX.set("Point d'Application X", 0.0f, -0.5f, 0.5f);
    forcePointY.set("Point d'Application Y", 0.0f, -0.5f, 0.5f);
    forcePointZ.set("Point d'Application Z", 0.0f, -0.5f, 0.5f);

    // Ajoute les paramètres à la GUI
    gui.add(launchForce);
    gui.add(forcePointX);
    gui.add(forcePointY);
    gui.add(forcePointZ);
    gui.add(forceAzimuth);
    gui.add(forceElevation);

    // Affiche la GUI par défaut
    showGui = true;
}


//--------------------------------------------------------------
void ofApp::setupScene()
{
    // Crée le générateur de gravité
    gravityGenerator = new GravityGenerator(Vector(0.0f, -9.81f, 0.0f));

    // Initialise le modèle du cube
    cubeMesh.set(1.0f); // Cube de côté 1 unité

    
}

//--------------------------------------------------------------
void ofApp::update()
{
    // Met à jour le deltaTime pour une simulation indépendante du framerate
    deltaTime = ofGetLastFrameTime();
    if (deltaTime > 0.1f) deltaTime = 0.1f; // Limite le deltaTime en cas de lag

    world->setDeltaTime(deltaTime);
    world->update();

    const std::vector<CorpsRigide*>& rigidBodies = world->getRigidBodies();
    for (auto rigidBody : rigidBodies)
    {
        rigidBody->addPositionHistory(rigidBody->getPosition());
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    // Efface l'écran
    ofBackground(30, 30, 30);

    // Active le test de profondeur pour le dessin 3D
    ofEnableDepthTest();

    // Commence la caméra
    camera.begin();

    // Active les lumières
    pointLight.enable();
    directionalLight.enable();

    // **Dessine le sol dans le plan XZ**
    ofPushMatrix();

    ofTranslate(0, -10, 0);
    groundMaterial.begin();

    // Dessine le sol
    groundPlane.draw();

    // Termine le matériau
    groundMaterial.end();


    ofPopMatrix();

    // Dessine les corps rigides
    const std::vector<CorpsRigide*>& rigidBodies = world->getRigidBodies();

    for (auto rigidBody : rigidBodies)
    {
		// On get la matrice de transformation du corps rigide
        Matrice<4> transform = rigidBody->getTransformMatrix();

		// On la convertit en un tableau de 16 floats pour OpenGL
		float glMatrix[16]{}; // Initialisée à 0
        for (int i = 0; i < 4; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                glMatrix[j * 4 + i] = transform.values[i][j]; // Colonne-major
            }
        }

        // Applique la transformation OpenGL
        ofPushMatrix();
        ofMultMatrix(glMatrix);

        // Applique le matériau
        cubeMaterial.begin();

        // Dessine le cube
        cubeMesh.draw();

        // Termine le matériau
        cubeMaterial.end();

        // Dessine le centre de masse (dans le repère local du cube)
        ofSetColor(0, 255, 0); // Vert pour le centre de masse
        ofDrawSphere(0.0f, 0.0f, 0.0f, 0.05f); // Petit point au centre

        ofPopMatrix(); // Sort du repère du cube

        // Dessine la traînée du cube en coordonnées mondiales
        const std::vector<Vector>& positions = rigidBody->getPositionsHistory();
        ofSetColor(255, 255, 255); // Blanc pour la traînée
        ofSetLineWidth(2.0f); // Épaisseur de ligne pour la traînée
        for (size_t i = 1; i < positions.size(); ++i)
        {
            ofDrawLine(
                ofVec3f(positions[i - 1].x, positions[i - 1].y, positions[i - 1].z),
                ofVec3f(positions[i].x, positions[i].y, positions[i].z)
            );
        }
        ofSetLineWidth(1.0f); // Réinitialise l'épaisseur de ligne

        // Dessine le point d'application de la force et la flèche en coordonnées mondiales
        Vector forcePointWorld = rigidBody->getForceApplicationPoint();
        Vector forceDirWorld = rigidBody->getForceDirection();

        // Dessine le point d'application de la force
        ofSetColor(0, 0, 255); // Bleu pour le point d'application
        ofDrawSphere(forcePointWorld.x, forcePointWorld.y, forcePointWorld.z, 0.05f);

		// Dessine le point de centre de masse (dans le repère local du cube)
		ofSetColor(0, 255, 0); // Vert pour le point d'application
		ofDrawSphere(forcePointWorld.x, forcePointWorld.y, forcePointWorld.z, 0.05f);

        // Dessine la flèche de la force
        if (forceDirWorld.norm() > 0.0f)
        {
            ofSetColor(255, 0, 0); // Rouge pour la flèche de force

            // Définit la longueur de la flèche pour la visualisation
            float arrowLength = 1.0f; 

            // Calcule le point d'arrivée de la flèche
            ofVec3f arrowStart(forcePointWorld.x, forcePointWorld.y, forcePointWorld.z);
            ofVec3f arrowEnd(
                forcePointWorld.x + forceDirWorld.x * arrowLength,
                forcePointWorld.y + forceDirWorld.y * arrowLength,
                forcePointWorld.z + forceDirWorld.z * arrowLength
            );

            ofDrawArrow(
                arrowStart, // Point de départ
                arrowEnd,   // Point d'arrivée
                0.05f       // Taille de la tête de flèche
            );
        }
    }

    // Désactive les lumières
    pointLight.disable();
    directionalLight.disable();

    
    camera.end();

    // Désactive le test de profondeur pour le dessin 2D et l'interface
    ofDisableDepthTest();

    // Affiche la GUI
    if (showGui)
    {
        gui.draw();
    }

    // Dessine le repère XYZ
    drawAxisIndicator();
}



void ofApp::drawAxisIndicator()
{
    // Sauvegarde la matrice de transformation
    ofPushMatrix();

    // Positionne le repère en bas à droite
    float indicatorSize = 500.0f; // Taille du repère en pixels
    float margin = 100.0f;         // Marge par rapport au bord de l'écran

    // Positionne le repère en utilisant les coordonnées de l'écran
    ofTranslate(ofGetWidth() - indicatorSize - margin, ofGetHeight() - indicatorSize - margin, 0);

    // Configure une petite caméra orthographique pour le repère
    ofRectangle viewport(0, 0, indicatorSize, indicatorSize);
    ofCamera indicatorCam;
    indicatorCam.begin(viewport);

    // Dessine le repère
    drawAxes(50.0f); // Taille des axes

    // Termine la caméra du repère
    indicatorCam.end();

    // Restaure la matrice de transformation
    ofPopMatrix();
}

void ofApp::drawAxes(float size)
{
    ofSetLineWidth(2.0f);

    // Axe X en rouge
    ofSetColor(255, 0, 0);
    ofDrawLine(0, 0, 0, size, 0, 0);

    // Axe Y en vert
    ofSetColor(0, 255, 0);
    ofDrawLine(0, 0, 0, 0, size, 0);

    // Axe Z en bleu
    ofSetColor(0, 0, 255);
    ofDrawLine(0, 0, 0, 0, 0, size);

    // Réinitialise la couleur et l'épaisseur de ligne
    ofSetColor(255, 255, 255);
    ofSetLineWidth(1.0f);
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == ' ')
    {
        // Lance un nouveau cube lorsque l'espace est pressé
        launchCube();
    }
    else if (key == 'g')
    {
        // Bascule l'affichage de la GUI
        showGui = !showGui;
    }
}


//--------------------------------------------------------------
void ofApp::launchCube()
{
    // Création d'un nouveau cube
    CorpsRigide* newCube = new CorpsRigide();
    newCube->setMass(2.0f);

    // Calcul du tenseur d'inertie pour un cube
    float cubeSide = 1.0f;
    float inertiaValue = (1.0f / 6.0f) * newCube->getMass() * cubeSide * cubeSide;
    Matrice<3> inertiaTensor({
        inertiaValue, 0.0f,        0.0f,
        0.0f,        inertiaValue, 0.0f,
        0.0f,        0.0f,        inertiaValue
        });
    newCube->setInertiaTensor(inertiaTensor);

    // Position initiale fixe pour le cube
    Vector cubePos(0.0f, 5.0f, 0.0f); 
    newCube->setPosition(cubePos);

    // Orientation initiale
    newCube->setOrientation(Quaternion()); 

    // Ajoute le cube au monde
    world->addRigidBody(newCube);

    // Convertit les angles d'azimut et d'élévation de degrés en radians
    float theta = ofDegToRad(forceAzimuth.get());    // Azimut 
    float phi = ofDegToRad(forceElevation.get());    // Élévation 

    // Calcule le vecteur de direction en coordonnées sphériques
    Vector forceDirection;
    forceDirection.x = cos(phi) * sin(theta);
    forceDirection.y = sin(phi);
    forceDirection.z = cos(phi) * cos(theta);

    // Normalise la direction de la force
    forceDirection = forceDirection.normalize();

    // Calcule la force appliquée en utilisant la magnitude et la direction
    Vector force = forceDirection * launchForce.get();

    // Point d'application de la force (relatif au centre du cube)
    Vector localPoint(forcePointX.get(), forcePointY.get(), forcePointZ.get());

    // Convertir le point d'application en coordonnées mondiales
    Vector worldPoint = localPoint + cubePos; // Utilise la position fixe du cube

    // Applique la force au point en coordonnées mondiales
    newCube->applyForceAtPoint(force, worldPoint);

    // Ajoute la gravité
    world->addForceGenerator(newCube, gravityGenerator);

    // Stocke le point d'application et la direction en coordonnées mondiales
    newCube->setForceApplicationPoint(worldPoint);
    newCube->setForceDirection(forceDirection);
}


