#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( )
{
	//ofSetupOpenGL(1080, 720, OF_WINDOW);

	ofGLFWWindowSettings windowSettings;

	// résolution de la fenêtre d'affichage
	windowSettings.setSize(1080, 720);

	// sélection de la version de OpenGL
	windowSettings.setGLVersion(3, 3);

	// création de la fenêtre
	ofCreateWindow(windowSettings);

	// démarrer l'exécution de l'application
	ofRunApp(new ofApp());
}
