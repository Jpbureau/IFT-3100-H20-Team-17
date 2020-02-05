#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Renderer.h"
#include "ofxDatGui.h"
#include "FileManager.h"

class Application : public ofBaseApp
{
private:
	FileManager fileManager;
	Renderer renderer = Renderer(fileManager);

public:

	//ofxDatGui* gui = new ofxDatGui(100, 100);
	//ofxDatGuiButton* boutonImportation;

	ofxPanel gui;
	ofxButton exportButton;
	ofxButton importButton;

	void setup();
	void draw();

	//void windowResized(int w, int h);

	void dragEvent(ofDragInfo dragInfo);

	void exit();

	void onButtonEvent(ofxDatGuiButtonEvent e);

	void buttonImportation_pressed();
};