#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( )
{
	//ofSetupOpenGL(1080, 720, OF_WINDOW);

	ofGLFWWindowSettings windowSettings;

	// r�solution de la fen�tre d'affichage
	windowSettings.setSize(1080, 720);

	// s�lection de la version de OpenGL
	windowSettings.setGLVersion(3, 3);

	// cr�ation de la fen�tre
	ofCreateWindow(windowSettings);

	// d�marrer l'ex�cution de l'application
	ofRunApp(new ofApp());
}
