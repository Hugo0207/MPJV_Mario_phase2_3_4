#include "ofApp.h"
#include "../TestMatrice.h"
#include "../QuaternionTest.h"
#include "../Boite.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofEnableAlphaBlending();
    ofSetGlobalAmbientColor(ofColor(200, 200, 200));

    // Initialisation du monde physique
    deltaTime = 1.0f / 60.0f; // Par d�faut, 60 FPS
    world = new World(deltaTime);

    BoundingBox worldBounds(Vector(0, 0, 0), Vector(ofGetWidth(), ofGetHeight(), 1000));
    world->octree = new OctreeNode(worldBounds);

    // Configuration initiale de la sc�ne
    setupScene();

    // Configuration de l'�clairage
    ofSetSmoothLighting(true);
    pointLight.setDiffuseColor(ofColor(246, 228, 188));
    pointLight.setSpecularColor(ofColor(246, 228, 188));
    pointLight.setPosition(0, 50, 0);

    directionalLight.setDiffuseColor(ofColor(246, 228, 188));
    directionalLight.setSpecularColor(ofColor(246, 228, 188));
    directionalLight.setOrientation(ofVec3f(45, -45, 0));

    // Configuration du mat�riau du cube
    cubeMaterial.setShininess(64);
    cubeMaterial.setDiffuseColor(ofColor(200, 0, 0, 150)); // Rouge pour bien voir la rotation

    // Configuration de la salle de jeu
    world->addPlane(new Plane(Vector(0,-1,0), Vector(0,10,0)));
    world->addPlane(new Plane(Vector(0,1,0), Vector(0,-5,0)));
    world->addPlane(new Plane(Vector(-1,0,0), Vector(15,-10,0)));
    world->addPlane(new Plane(Vector(1,0,0), Vector(-15,-10,0)));
    world->addPlane(new Plane(Vector(0,0,1), Vector(0,-10,15)));
    world->addPlane(new Plane(Vector(0,0,-1), Vector(0,-10,-15)));

    // Active la profondeur
    ofEnableDepthTest();

    // Configuration de la cam�ra
    camera.setNearClip(0.1f);
    camera.setFarClip(1000.0f);

    // Positionne la cam�ra pour une vue isom�trique
    float camDistance = 7.5f;
    camera.setPosition(camDistance, camDistance, camDistance);
    camera.lookAt(ofVec3f(0, 0, 0)); // La cam�ra regarde le centre de la sc�ne

    // D�sactive le contr�le de la cam�ra avec la souris pour un point de vue fixe
    camera.enableMouseInput();

    // Initialisation de la GUI
    gui.setup("Parametres de Lancement");

    // D�finition des valeurs par d�faut et des plages pour la force
    launchForce.set("Force de Lancement", 10.0f, 0.0f, 10000.0f);

    forceAzimuth.set("Azimut", 0.0f, -180.0f, 180.0f);
    forceElevation.set("Elevation", 0.0f, -90.0f, 90.0f);

    // D�finition des valeurs par d�faut et des plages pour le point d'application
    forcePointX.set("Point d'Application X", 0.0f, -0.5f, 0.5f);
    forcePointY.set("Point d'Application Y", 0.0f, -0.5f, 0.5f);
    forcePointZ.set("Point d'Application Z", 0.0f, -0.5f, 0.5f);

    // Ajoute les param�tres � la GUI
    gui.add(launchForce);
    gui.add(forcePointX);
    gui.add(forcePointY);
    gui.add(forcePointZ);
    gui.add(forceAzimuth);
    gui.add(forceElevation);

    // Affiche la GUI par d�faut
    showGui = true;

    QuaternionTest::runTests();
    TestMatrice().RunTest();
}


//--------------------------------------------------------------
void ofApp::setupScene()
{
    // Cr�e le g�n�rateur de gravit�
    gravityGenerator = new GravityGenerator(Vector(0, -9.81f, 0));

    // Initialise le mod�le du cube
    cubeMesh.set(1.0f); // Cube de c�t� 1 unit�


}

//--------------------------------------------------------------
void ofApp::update()
{
    // Met � jour le deltaTime pour une simulation ind�pendante du framerate
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
    // Efface l'�cran
    ofBackground(30, 30, 30);

    // Active le test de profondeur pour le dessin 3D
    ofEnableDepthTest();

    // Commence la cam�ra
    camera.begin();

    // Active les lumi�res
    pointLight.enable();
    directionalLight.enable();

    // Dessine les plans
    for (auto& plane : world->getPlanes())
    {
        plane->draw();
    }

    // Dessine les corps rigides
    const std::vector<CorpsRigide*>& rigidBodies = world->getRigidBodies();

    for (auto rigidBody : rigidBodies)
    {
        // On get la matrice de transformation du corps rigide
        Matrice<4> transform = rigidBody->getTransformMatrix();

        // On la convertit en un tableau de 16 floats pour OpenGL
        float glMatrix[16]{}; // Initialis�e � 0
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

        // Applique le mat�riau
        cubeMaterial.begin();

        // Dessine le cube
        cubeMesh.draw();

        // Termine le mat�riau
        cubeMaterial.end();

        // Dessine le centre de masse (dans le rep�re local du cube)
        ofSetColor(0, 255, 0); // Vert pour le centre de masse
        ofDrawSphere(0.0f, 0.0f, 0.0f, 0.05f); // Petit point au centre

        ofPopMatrix(); // Sort du rep�re du cube

        // Dessine la tra�n�e du cube en coordonn�es mondiales
        const std::vector<Vector>& positions = rigidBody->getPositionsHistory();
        ofSetColor(255, 255, 255); // Blanc pour la tra�n�e
        ofSetLineWidth(2.0f); // �paisseur de ligne pour la tra�n�e
        for (size_t i = 1; i < positions.size(); ++i)
        {
            ofDrawLine(
                ofVec3f(positions[i - 1].x, positions[i - 1].y, positions[i - 1].z),
                ofVec3f(positions[i].x, positions[i].y, positions[i].z)
            );
        }
        ofSetLineWidth(1.0f); // R�initialise l'�paisseur de ligne

        // Dessine le point d'application de la force et la fl�che en coordonn�es mondiales
        Vector forcePointWorld = rigidBody->getForceApplicationPoint();
        Vector forceDirWorld = rigidBody->getForceDirection();

        // Dessine le point d'application de la force
        ofSetColor(0, 0, 255); // Bleu pour le point d'application
        ofDrawSphere(forcePointWorld.x, forcePointWorld.y, forcePointWorld.z, 0.05f);

        // Dessine le point de centre de masse (dans le rep�re local du cube)
        ofSetColor(0, 255, 0); // Vert pour le point d'application
        ofDrawSphere(forcePointWorld.x, forcePointWorld.y, forcePointWorld.z, 0.05f);

        // Dessine la fl�che de la force
        if (forceDirWorld.norm() > 0.0f)
        {
            ofSetColor(255, 0, 0); // Rouge pour la fl�che de force

            // D�finit la longueur de la fl�che pour la visualisation
            float arrowLength = 1.0f;

            // Calcule le point d'arriv�e de la fl�che
            ofVec3f arrowStart(forcePointWorld.x, forcePointWorld.y, forcePointWorld.z);
            ofVec3f arrowEnd(
                forcePointWorld.x + forceDirWorld.x * arrowLength,
                forcePointWorld.y + forceDirWorld.y * arrowLength,
                forcePointWorld.z + forceDirWorld.z * arrowLength
            );

            ofDrawArrow(
                arrowStart, // Point de d�part
                arrowEnd,   // Point d'arriv�e
                0.05f       // Taille de la t�te de fl�che
            );
        }
    }

    // D�sactive les lumi�res
    pointLight.disable();
    directionalLight.disable();


    camera.end();

    // D�sactive le test de profondeur pour le dessin 2D et l'interface
    ofDisableDepthTest();

    // Affiche la GUI
    if (showGui)
    {
        gui.draw();
    }

    ofSetColor(0, 0, 0); 
    ofDrawBitmapString("Appuyer sur ESPACE pour lancer la boite", 20, ofGetHeight() - 20);

    // Dessine le rep�re XYZ
    drawAxisIndicator();
}



void ofApp::drawAxisIndicator()
{
    // Sauvegarde la matrice de transformation
    ofPushMatrix();

    // Positionne le rep�re en bas � droite
    float indicatorSize = 500.0f; // Taille du rep�re en pixels
    float margin = 100.0f;         // Marge par rapport au bord de l'�cran

    // Positionne le rep�re en utilisant les coordonn�es de l'�cran
    ofTranslate(ofGetWidth() - indicatorSize - margin, ofGetHeight() - indicatorSize - margin, 0);

    // Configure une petite cam�ra orthographique pour le rep�re
    ofRectangle viewport(0, 0, indicatorSize, indicatorSize);
    ofCamera indicatorCam;
    indicatorCam.begin(viewport);

    // Dessine le rep�re
    drawAxes(50.0f); // Taille des axes

    // Termine la cam�ra du rep�re
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

    // R�initialise la couleur et l'�paisseur de ligne
    ofSetColor(255, 255, 255);
    ofSetLineWidth(1.0f);
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    if (key == ' ')
    {
        // Lance un nouveau cube lorsque l'espace est press�
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
    // Cr�ation d'un nouveau cube
    Boite* newCube = new Boite(1.0f, 1.0f, 1.0f);
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

    // Convertit les angles d'azimut et d'�l�vation de degr�s en radians
    float theta = ofDegToRad(forceAzimuth.get());    // Azimut 
    float phi = ofDegToRad(forceElevation.get());    // �l�vation 

    // Calcule le vecteur de direction en coordonn�es sph�riques
    Vector forceDirection;
    forceDirection.x = cos(phi) * sin(theta);
    forceDirection.y = sin(phi);
    forceDirection.z = cos(phi) * cos(theta);

    // Normalise la direction de la force
    forceDirection = forceDirection.normalize();

    // Calcule la force appliqu�e en utilisant la magnitude et la direction
    Vector force = forceDirection * launchForce.get();

    // Point d'application de la force (relatif au centre du cube)
    Vector localPoint(forcePointX.get(), forcePointY.get(), forcePointZ.get());

    // Convertir le point d'application en coordonn�es mondiales
    Vector worldPoint = localPoint + cubePos; // Utilise la position fixe du cube

    // Applique la force au point en coordonn�es mondiales
    newCube->applyForceAtPoint(force, worldPoint);

    // Ajoute la gravit�
    world->addForceGenerator(newCube, gravityGenerator);

    // Stocke le point d'application et la direction en coordonn�es mondiales
    newCube->setForceApplicationPoint(worldPoint);
    newCube->setForceDirection(forceDirection);
}


