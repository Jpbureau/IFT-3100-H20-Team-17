#include "renderer.h"

void Renderer::setup()
{
	importButton.addListener(this, &Renderer::importButton_pressed);
	exportButton.addListener(this, &Renderer::exportButtonPressed);

	gui.setup("Test");
	gui.add(importButton.setup("Import Image"));
	gui.add(exportButton.setup("Export Image"));
}

void Renderer::draw()
{
	ofBackgroundGradient(ofColor::white, ofColor::gray);
	ofSetColor(255, 130, 0);
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 50);

	if (image.isAllocated()) {
		ofSetColor(255);
		image.draw(0, 0, ofGetWidth(), ofGetHeight());
	}

	gui.draw();
}

void Renderer::importButton_pressed()
{
	image = fileManager.image_import();
	ofLog() << "<Importation button pressed>";
}

void Renderer::exportButtonPressed()
{
	fileManager.saveImage();
}