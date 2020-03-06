#pragma once

#include "ofxGui.h"
#include "graphNode.h"

class SceneGraph2dGui {
public:
	SceneGraph2dGui(GraphNode& root);

	void setup();
	void draw();

private:
	ofxPanel gui;
	GraphNode& root;
};