#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	// param�tres du contexte de rendu OpenGL
  ofGLFWWindowSettings windowSettings;

  // option de redimentionnement de la fen�tre d'affichage
  windowSettings.resizable = false;

  // s�lection de la version de OpenGL
  windowSettings.setGLVersion(3, 3);

  // cr�ation de la fen�tre
  ofCreateWindow(windowSettings);

  // d�marrer l'ex�cution de l'application
  ofRunApp(new ofApp());
}
