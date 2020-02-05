#include "ofMain.h"
#include "Application.h"

//========================================================================
int main( ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp());

	//ofSetupOpenGL(512, 512, OF_WINDOW);
	ofRunApp(new Application());

}
