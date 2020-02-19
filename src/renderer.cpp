#include "renderer.h"

void Renderer::setup()
{
	cursor.setup(drawingCanvasX, drawingCanvasY, drawingCanvasSize);
	cursor.setCursorImage(none);

	textureDrawer.setup();
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

	drawingOptionsPanel.setup("Outils de dessin");
	drawingOptionsPanel.setPosition(10, drawingCanvasY);

	backGroundColor.set("Couleur du fond", ofColor::burlyWood, ofColor(0, 0), ofColor(255, 255));
	strokeColorPicker.set("Couleur du contour/trait", ofColor::darkCyan, ofColor(0, 0), ofColor(255, 255));
	fillColorPicker.set("Couleur du remplissage", ofColor::crimson, ofColor(0, 0), ofColor(255, 255));
	strokeWeightSlider.set("Largeur de la ligne", 1.0f, 0.0f, 5.0f);

	radiusSlider.set("LRayon", 1.0f, 0.0f, 40.0f);
	optionsPoint.setup("Point");
	optionsPoint.add(radiusSlider);
	optionsPoint.add(drawPointButton.setup("point"));

	drawingOptionsPanel.add(backGroundColor);
	drawingOptionsPanel.add(strokeColorPicker);
	drawingOptionsPanel.add(fillColorPicker);
	drawingOptionsPanel.add(strokeWeightSlider);
	drawingOptionsPanel.add(&optionsPoint);
	drawingOptionsPanel.add(drawLineButton.setup("ligne"));
	drawingOptionsPanel.add(drawRectangleButton.setup("rectangle"));
	drawingOptionsPanel.add(drawEllipseButton.setup("ellipse"));
	drawingOptionsPanel.add(selectButton.setup("Selectionner"));
	drawingOptionsPanel.add(deselectButton.setup("Deselectionner"));
	drawingOptionsPanel.add(deleteButton.setup("Supprimer"));

	drawPointButton.addListener(this, &Renderer::selectPointType);
	drawLineButton.addListener(this, &Renderer::selectLineType);
	drawRectangleButton.addListener(this, &Renderer::selectRectangleType);
	drawEllipseButton.addListener(this, &Renderer::selectEllipseType);
	selectButton.addListener(this, &Renderer::selectAction);
	deselectButton.addListener(this, &Renderer::deselectAction);
	deleteButton.addListener(this, &Renderer::deleteAction);
}

void Renderer::update()
{
	textureDrawer.updateColors(strokeColorPicker, fillColorPicker);
	textureDrawer.updateStrokeWeight(strokeWeightSlider);
	textureDrawer.updateRadius(radiusSlider);
	textureDrawer.update();
	cursor.update();
}

void Renderer::draw()
{
	ofSetBackgroundColor(backGroundColor);

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
	drawingOptionsPanel.draw();
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

void Renderer::selectAction()
{
	textureDrawer.selectSelectionType();
}

void Renderer::deleteAction()
{
	textureDrawer.deleteSelectedShapes();
}

void Renderer::deselectAction()
{
	textureDrawer.resetSelection();
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


