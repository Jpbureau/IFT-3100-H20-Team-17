#include "renderer.h"

void Renderer::setup()
{
	cursor.setup();
	textureDrawer.setup();
	cursor.setCursorImage(CursorTypes::pencil);

	exportButton.addListener(this, &Renderer::exportButtonPressed);
	importButton.addListener(this, &Renderer::importButton_pressed);

	menuPanel.setup("Menu");
	menuPanel.add(importButton.setup("Import Image"));
	menuPanel.add(exportButton.setup("Export Image"));

	drawingOptionsPanel.setup("Outils de dessin");
	drawingOptionsPanel.setPosition(10, 200);

	backGroundColor.set("Couleur du fond", ofColor(255), ofColor(0, 0), ofColor(255, 255));

	drawingOptionsPanel.add(backGroundColor);
	drawingOptionsPanel.add(drawPointButton.setup("point"));
	drawingOptionsPanel.add(drawLineButton.setup("ligne"));
	drawingOptionsPanel.add(drawRectangleButton.setup("rectangle"));
	drawingOptionsPanel.add(drawEllipseButton.setup("ellipse"));

	drawPointButton.addListener(this, &Renderer::selectPointType);
	drawLineButton.addListener(this, &Renderer::selectLineType);
	drawRectangleButton.addListener(this, &Renderer::selectRectangleType);
	drawEllipseButton.addListener(this, &Renderer::selectEllipseType);
}

void Renderer::update()
{

}

void Renderer::draw()
{
	ofClear(backGroundColor);
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
	drawingOptionsPanel.draw();
}

void Renderer::drawCursor()
{

	cout << "X: " << mousePosX << " Y: " << mousePosY << endl;
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

//Malheureusement nécessaire pour l'instant si on veut déclencher une action avec le listener
void Renderer::selectPointType()
{
	textureDrawer.selectPointType();
}
void Renderer::selectLineType()
{
	textureDrawer.selectLineType();
}
void Renderer::selectRectangleType()
{
	textureDrawer.selectRectangleType();
}
void Renderer::selectEllipseType()
{
	textureDrawer.selectEllipseType();
}

void Renderer::mousePressed(int x, int y)
{
	textureDrawer.mouse_pressed_posX = x;
	textureDrawer.mouse_pressed_posY = y;
	
}

void Renderer::mouseReleased(int x, int y)
{
	textureDrawer.mouse_current_posX = x;
	textureDrawer.mouse_current_posY = y;
	textureDrawer.add_vector_shape();
}
