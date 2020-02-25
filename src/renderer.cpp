#include "renderer.h"

void Renderer::setup()
{
	cursor.setup(drawingCanvasX, drawingCanvasY, drawingCanvasSize);
	cursor.setCursorImage(none);

	textureDrawer.setup(drawingCanvasX, drawingCanvasY, drawingCanvasSize);
	fboTexture.allocate(drawingCanvasSize, drawingCanvasSize, GL_RGBA);
	fboTexture.begin();
	ofClear(255, 255);
	ofSetColor(255);
	fboTexture.end();

	exportButton.addListener(this, &Renderer::exportButtonPressed);
	importButton.addListener(this, &Renderer::importButton_pressed);

	menuPanel.setup("Menu");
	menuPanel.add(importButton.setup("Import Image"));
	menuPanel.add(exportButton.setup("Export Image"));

	canvas2dGui.setup(drawingCanvasY);
}

void Renderer::update()
{
	canvas2dGui.update();
	textureDrawer.update();
	cursor.update();
}

void Renderer::draw()
{
	ofSetBackgroundColor(canvas2dGui.backGroundColor);

	ofSetColor(255);
	fboTexture.draw(drawingCanvasX, drawingCanvasY);
	/*ofBackgroundGradient(ofColor::white, ofColor::gray);
	ofSetColor(255, 130, 0);
	ofDrawCircle(ofGetWidth() / 2, ofGetHeight() / 2, 50);*/

	/*if (image.isAllocated()) {
		ofSetColor(255);
		image.draw(0, 0, ofGetWidth(), ofGetHeight());
	}*/
	textureDrawer.draw();
	cursor.draw();
	menuPanel.draw();
	canvas2dGui.draw();
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

void Renderer::mousePressed(int x, int y)
{
	textureDrawer.mouse_pressed_posX = x;
	textureDrawer.mouse_pressed_posY = y;
	textureDrawer.selectShape(x, y);
}

void Renderer::mouseReleased(int x, int y)
{
	textureDrawer.mouse_current_posX = x;
	textureDrawer.mouse_current_posY = y;
	textureDrawer.add_vector_shape();
}


