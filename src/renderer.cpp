#include "renderer.h"

void Renderer::setup()
{
	importButton.addListener(this, &Renderer::importButton_pressed);
	exportButton.addListener(this, &Renderer::exportButtonPressed);
	mosaiqueButton.addListener(this, &Renderer::mosaiqueButtonPressed);

	gui.setup("Test");
	gui.add(importButton.setup("Import Image"));
	gui.add(exportButton.setup("Export Image"));
	gui.add(mosaiqueButton.setup("Mosaique 3x3"));
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
	ofSetWindowShape(image.getWidth(), image.getHeight());
}

void Renderer::exportButtonPressed()
{
	fileManager.saveImage();
}

void Renderer::mosaiqueButtonPressed()
{
	const int pieces = 10;
	offsetVertical = 32;
	offsetHorizontal = 32;

	int image_width = image.getWidth() / pieces;
	int image_height = image.getHeight() / pieces;

	ofSetWindowShape(
		image.getWidth() + offsetHorizontal * (pieces + 1),
		image.getHeight() + offsetVertical * (pieces + 1));

	for (int j = 0; j < pieces; j++) {
		for (int i = 0; i < pieces; i++) {
			image.drawSubsection(offsetHorizontal * (i + 1) + image_width * i, offsetVertical * (j + 1) + image_height * j, image_width, image_height, image_width * i, image_height * j);
		}
	}

	image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());

}