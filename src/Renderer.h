#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "fileManager.h"

class Renderer
{
public:

	Renderer(const FileManager & fileManager);

	ofImage image;

	void setup();
	void draw();
	void drawImage(ofImage p_image);

private:
	const FileManager& fileManager;

};

