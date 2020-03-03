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

	fileManagerGui.setup();
	canvas2dGui.setup(drawingCanvasY);
	
	//Il faudra ajuster la position de départ exacte plus tard
	const int HISTOGRAM_WIDTH = 600;
	const int HISTOGRAM_HEIGHT = 200;
	const int HISTOGRAM_X_POSITION = drawingCanvasX;
	const int HISTOGRAM_Y_POSITION = drawingCanvasY + drawingCanvasSize + HISTOGRAM_HEIGHT + 1;
	colorHistogram.setup(HISTOGRAM_WIDTH, HISTOGRAM_HEIGHT, HISTOGRAM_X_POSITION, HISTOGRAM_Y_POSITION);
	colorHistogramGui.setup(10, 560);

	const int PRIMITIVES_GEOMETRIQUES_GUI_POSITION_X = ofGetWidth() - 210;
	const int PRIMITIVES_GEOMETRIQUES_GUI_POSITION_Y = 100;
	primitivesGeometriquesGui.setup(PRIMITIVES_GEOMETRIQUES_GUI_POSITION_X, PRIMITIVES_GEOMETRIQUES_GUI_POSITION_Y);
}

void Renderer::update()
{
	canvas2dGui.update();
	textureDrawer.update();
	cursor.update();

	//À implémenter plus tard: Faire l'update automatique seulement lorsqu'il y a un changement, ou une fois à toutes les x frames
	if (colorHistogramGui.getUpdateHistogram())
	{
		//Vérifier les dimensions...
		image.grabScreen(drawingCanvasX, drawingCanvasY, drawingCanvasSize, drawingCanvasSize);
		ofPixels pixels = image.getPixels();
		colorHistogramGui.update(pixels);
		//colorHistogram.update();
	}
	primitivesGeometriquesGui.update();
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
	fileManagerGui.draw();
	canvas2dGui.draw();
	
	colorHistogramGui.draw();
	primitivesGeometriquesGui.draw();
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


