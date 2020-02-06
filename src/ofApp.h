#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Renderer.h"
#include "ofxDatGui.h"
#include "FileManager.h"

class ofApp : public ofBaseApp{

private:
	FileManager fileManager;
	Renderer renderer = Renderer(fileManager);

public:

	//ofxDatGui* gui = new ofxDatGui(100, 100);
	//ofxDatGuiButton* boutonImportation;

	ofxPanel gui;
	ofxButton exportButton;
	ofxButton importButton;

	void onButtonEvent(ofxDatGuiButtonEvent e);

	void buttonImportation_pressed();
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
};
