#include "renderer.h"

void Renderer::setup()
{
	cursor.setup();

	textureDrawer.setup(drawingCanvasX, drawingCanvasY, drawingCanvasSize);
	fileManagerGui.setup();
	canvas2dGui.setup(drawingCanvasY);
	
	//Il faudra ajuster la position de départ exacte plus tard
	colorHistogram.setup();
	colorHistogramGui.setup(10, 560);
	
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
	
}

void Renderer::draw()
{
	ofSetBackgroundColor(canvas2dGui.backGroundColor);
	textureDrawer.draw();
	cursor.draw();
	fileManagerGui.draw();
	canvas2dGui.draw();
	
	if (colorHistogramGui.getHistogramShown())
	{
		colorHistogram.draw();
	}
	colorHistogramGui.draw();
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


