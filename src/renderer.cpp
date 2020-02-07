#include "renderer.h"

void Renderer::setup()
{	
	cursor.setup();
	cursor.setCursorImage(CursorTypes::pencil);

	exportButton.addListener(this, &Renderer::exportButtonPressed);

	gui.setup("Test");
	gui.add(exportButton.setup("Export Image"));

}

void Renderer::draw()
{
	ofBackgroundGradient(ofColor::white, ofColor::gray);
	ofSetColor(255, 130, 0);
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 50);

	cursor.draw();

	gui.draw();
}

void Renderer::drawCursor()
{

	cout << "X: " << mousePosX << " Y: " << mousePosY << endl;
}

void Renderer::exportButtonPressed()
{
	fileManager.saveImage();
}